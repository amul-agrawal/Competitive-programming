
#include <bits/stdc++.h>
// #include <vector>
// #include <iostream>
// #include <stdlib.h>
// #include <string>
using namespace std;
#define ll long long
#define endl '\n'
typedef vector< int > vi;
typedef vector< ll > lvi;

struct node {
	int prior, val, min1, lazy, size;
	bool rev;
	node *l, *r;
};
typedef node* pnode;

template<class T = int>
class Treap 
{
public:
	pnode root;
	pnode getnode(T val) {
		pnode t = new node;
		t->l = t->r = NULL;
		t->prior = rand();
		t->size = 1;
		t->rev = false;
		t->lazy = 0;
		t->min1 = t->val = val;
		return t;
	}
	int sz(pnode t) {
		return t ? t->size : 0;
	}
	// t may denote same node as l or r, so take care of that.
	void combine(pnode &t,pnode l,pnode r) {
		if(!l or !r) return void(t = (l ? l : r));
		t->size = sz(l) + sz(r);
		t->min1 = min(l->min1, r->min1);
	}
	void operation(pnode t) {
		if(!t) return;
		// reset t;
		t->size = 1;
		t->min1 = t->val;
		push(t->l); push(t->r);
		// combine
		combine(t, t->l, t);
		combine(t, t, t->r);
	}
	void push(pnode &t) {
		if(!t) return;
		if(t->rev) {
			swap(t->r, t->l);
			if(t->r) t->r->rev = not t->r->rev;
			if(t->l) t->l->rev = not t->l->rev;
			t->rev = false;
		}
		if(t->lazy) {
			t->val += t->lazy;
			t->min1 += t->lazy;
			if(t->r) t->r->lazy += t->lazy;
			if(t->l) t->l->lazy += t->lazy;
			t->lazy = 0;
		}
	}
	void split(pnode t,pnode &l,pnode &r,int pos,int add=0) {
		push(t); 
		if(!t) return void(l=r=NULL);
		int curr_pos = add + sz(t->l);
		if(pos >= curr_pos) {
			split(t->r,t->r, r, pos, curr_pos + 1);
			l = t;
		} else {
			split(t->l, l, t->l, pos, add);
			r = t;
		}
		operation(t);
	}
	void merge(pnode &t,pnode l,pnode r) {
		push(l); push(r);
		if(!l or !r) return void(t = (l ? l : r));
		if(l->prior > r->prior) {
			merge(l->r, l->r, r);
			t = l;
		} else {
			merge(r->l, l, r->l);
			t = r;
		}
		operation(t);
	}
	Treap(vector<T> &arr) {
		root = NULL;
		// for(auto c : arr) {
		for(int i=0;i<arr.size();i++) {
			T c = arr[i];
			merge(root, root, getnode(c));
		}
	}
	void add(int l,int r,T d) {
		if(l>r) return;
		pnode L, mid, R;
		split(root, L, mid, l-1);
		split(mid, mid, R, r-l);
		if(mid) {
			mid->lazy += d;
		}
		merge(L, L, mid);
		merge(root, L, R);
	}
	void reverse(int l,int r) {
		if(l>r) return;
		pnode L, mid, R;
		split(root, L, mid, l-1);
		split(mid, mid, R, r-l);
		if(mid) {
			mid->rev = not mid->rev;
		}
		merge(R, mid, R);
		merge(root, L, R);
	}
	void revolve(int l,int r,int cnt) {
		if(cnt<=0 or l>r) return;
		int len = r - l + 1;
		// cnt = len => no rotation;
		cnt %= len;
		if(cnt == 0) return;
		// pick cnt elements from the end 
		// => (len - cnt) from front
		int mid = l + (len - cnt) - 1;
		pnode L, Range, R;
		split(root, L, Range, l-1);
		split(Range, Range, R, r - l);
		pnode first, second;
		split(Range, first, second, (len-cnt-1));
		merge(Range, second, first);
		merge(L, L, Range);
		merge(root, L, R);
	}
	void insert(int after,T val) {
		pnode L, R;
		split(root, L, R, after);
		merge(L, L, getnode(val));
		merge(root, L, R);
	}
	void del(int pos) {
		pnode L, mid, R;
		split(root, L, mid, pos-1);
		split(mid, mid, R, 0);
		if(mid) {	
			delete mid;
		}
		merge(root, L, R);
	}
	T range_min(int l,int r) {
		pnode L, mid, R;
		split(root, L, mid, l-1);
		split(mid, mid, R, r-l);
		push(mid);
		T ans = mid->min1;
		merge(L, L, mid);
		merge(root, L, R);
		return ans;
	}
	void inorder(pnode curr) {
		push(curr);
		if(!curr) return;
		inorder(curr->l);
		cerr<<curr->val<<" ";
		inorder(curr->r);
	}
	int query(int pos) {
		pnode l, mid, r;
		split(root, l, mid, pos-1);
		split(mid, mid, r, 0);
		int ans = mid->val;
		merge(l, l, mid);
		merge(root, l, r);
		return ans;
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n;
	cin>>n;
	vi a(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}
	Treap<int> tr(a);
	int m; cin>>m;
	while(m--) {
		// cerr<<"TREAP NOW: "; tr.inorder(tr.root); cerr<<endl;
		string op;
		cin>>op;
		if(op == "ADD") {
			int l, r, val;
			cin>>l>>r>>val;
			l--; r--;
			tr.add(l, r, val);
		} else if (op == "REVERSE") {
			int l, r;
			cin>>l>>r;
			l--; r--;
			tr.reverse(l, r);
		} else if(op == "REVOLVE") {
			int l, r, t;
			cin>>l>>r>>t;
			l--; r--;
			tr.revolve(l, r, t);
		} else if(op == "INSERT") {
			int pos, val;
			cin>>pos>>val;
			pos--;
			tr.insert(pos, val);
		} else if(op == "DELETE") {
			int pos;
			cin>>pos;
			pos--;
			tr.del(pos);
		} else if(op == "MIN") {
			int l, r;
			cin>>l>>r;
			l--; r--;
			cout<<tr.range_min(l, r)<<'\n';
		}
	}
	return 0;
}	
