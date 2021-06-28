struct node {
	int prior, val, size, min1;
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
		t->lazy = 0;
		t->min1 = t->val = val;
		return t;
	}
	inline int sz(pnode t) {
		return t ? t->size : 0;
	}
	// FRAGILE: HANDLE WITH CARE
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
	void push(pnode t) {
		if(!t) return;
		if(t->lazy) {
			t->val += t->lazy;
			t->min1 += t->lazy;
			if(t->r) t->r->lazy += t->lazy;
			if(t->l) t->l->lazy += t->lazy;
			t->lazy = 0;
		}
	}
	void split(pnode t,pnode &l,pnode &r,int key) {
		push(t); 
		if(!t) return void(l=r=NULL);
		else if(key >= t->val) {
			split(t->r,t->r, r, key);
			l = t;
		} else {
			split(t->l, l, t->l, key);
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
	void insert(pnode &t,pnode it){
	    if(!t) t=it;
	    else if(it->prior>t->prior)split(t,it->l,it->r,it->val),t=it;
	    else insert(t->val<=it->val?t->r:t->l,it);
	    operation(t);
	}
	void erase(pnode &t,int key){
	    if(!t)return;
	    else if(t->val==key){pnode temp=t;merge(t,t->l,t->r);free(temp);}
	    else erase(t->val<key?t->r:t->l,key);
	    operation(t);
	}
	void unite (pnode &t,pnode l, pnode r) {
	    if (!l || !r) return void(t = l ? l : r);
	    if (l->prior < r->prior) swap (l, r);
	    pnode lt, rt;
	    split (r,lt, rt,l->val);
	    unite (l->l,l->l, lt);
	    unite (l->r,l->r, rt);
	    t=l;operation(t);
	}
	void heapify(pnode t) {
		if(!t) return ;
	    pnode max = t;
	    if (t->l != NULL && t->l->prior > max->prior)
	        max = t->l;
	    if (t->r != NULL && t->r->prior > max->prior)
	        max = t->r;
	    if (max != t) {
	        swap (t->prior, max->prior);
	        heapify (max);
	    }
	}
	// O(n) treap build given array is increasing
	pnode build(T *arr,int n) {
		if(n==0) return NULL;
		int mid = n/2;
		pnode t = getnode(arr[mid]);
		t->l = build(arr, mid);
		t->r = build(arr + mid + 1, n - mid - 1);
		heapify(t);
		operation(t);
		return t;
	}
	Treap(vector<T> &arr) {
		root = NULL;
		for(auto c : arr) {
			insert(root, getnode(c));
		}
	}
	void inorder(pnode curr) {
		push(curr);
		if(!curr) return;
		inorder(curr->l);
		cerr<<curr->val<<" ";
		inorder(curr->r);
	}
};