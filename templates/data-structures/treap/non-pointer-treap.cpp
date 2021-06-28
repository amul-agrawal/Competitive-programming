
#include <bits/stdc++.h>
using namespace std;
typedef vector< int > vi;
typedef pair<int,int> ii;
typedef vector<pair<int,int>>  vii;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
// usage: x = rng() % k; shuffle(all(v), rng);
#define all(c) (c).begin(),(c).end()
#define price first
#define quality second

// Optimisations
// 1. removed operation => no need (NOT PASSED) TLE 9
// 2. removed pointers => (NOT PASSED) TLE 9
// 3. unite was slower very slower

struct node {
	int val, prior, lazy, id, shirts, lazyshirts;
	int l, r;
};

class Treap
{
public:
	int root, now;
	vector<node> st;
	inline node getnode(int val,int id) {
		node t;
		t.l = t.r = 0;
		t.prior = rng();
		t.lazy = 0;
		t.lazyshirts = 0;
		t.shirts = 0;
		t.id = id;
		t.val = val;
		return t;
	}
	inline void push(int t) {
		if(!t) return;
		if(st[t].lazy != 0) {
			st[t].shirts += st[t].lazyshirts;
			st[t].val += st[t].lazy;
			if(st[t].r) st[st[t].r].lazy += st[t].lazy;
			if(st[t].r) st[st[t].r].lazyshirts += st[t].lazyshirts;
			if(st[t].l) st[st[t].l].lazy += st[t].lazy;
			if(st[t].l) st[st[t].l].lazyshirts += st[t].lazyshirts;
			st[t].lazy = 0;
			st[t].lazyshirts = 0;
		}
	}
	void split(int t,int &l,int &r,int key) {
		push(t); 
		if(!t) return void(l=r=0);
		if(key >= st[t].val) {
			split(st[t].r, st[t].r, r, key);
			l = t;
		} else {
			split(st[t].l, l, st[t].l, key);
			r = t;
		}
	}
	void merge(int &t,int l,int r) {
		push(l); push(r);
		if(!l or !r) (t = (l ? l : r));
		else if(st[l].prior > st[r].prior) {
			merge(st[l].r, st[l].r, r);
			t = l;
		} else {
			merge(st[r].l, l, st[r].l);
			t = r;
		}
	}
	void insert(int &t,int it) {
		push(t); push(it);
		if(it==0) return;
		if(!t) return void(t=it);
		if(st[it].prior > st[t].prior) {
			split(t, st[it].l, st[it].r, st[it].val);
			t = it;
		} else {
			insert((st[it].val >= st[t].val ? st[t].r : st[t].l), it);
		}
	}
	Treap(vi &arr) {
		root = 0;
		now = 1;
		st.resize(arr.size() + 2);
		for(auto c : arr) {
			st[now] = getnode(c, now-1);
			insert(root, now);
			now++;
		}
	}	
	void move(int curr,int &to) {
		if(!curr) return;
		push(curr);
		move(st[curr].l, to);
		move(st[curr].r, to);
		st[curr].l = st[curr].r = 0;
		insert(to, curr);
	}
	void update(int price) {
		int L, R;
		split(root, L, R, price-1);
		if(R) {
			st[R].lazy -= price;
			st[R].lazyshirts += 1;
		}
		int temp;
		split(R, temp, R, price - 1);
		move(temp, L);
		merge(root, L, R);
	}
	void prepare_ans(int curr,vi &ans) {
		push(curr);
		if(!curr) return;
		prepare_ans(st[curr].l, ans);
		ans[st[curr].id] = st[curr].shirts;
		prepare_ans(st[curr].r, ans);
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(0);	
	int m;
	cin>>m;
	vii shirts(m);
	for (int i = 0; i < m; ++i)
	{
		cin>>shirts[i].price>>shirts[i].quality;
	}
	sort(all(shirts), [&](ii L,ii R) {
		if(L.quality != R.quality) return L.quality > R.quality;
		return L.price < R.price;
	});
	int n;
	cin>>n;
	vi budget(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>budget[i];
	}
	Treap tr(budget);
	for (int i = 0; i < m; ++i)
	{
		tr.update(shirts[i].price);
	}
	vi ans(n);
	tr.prepare_ans(tr.root, ans);
	for(auto c : ans)
		cout<<c<<" ";
	cout<<endl;
	return 0;
}	
