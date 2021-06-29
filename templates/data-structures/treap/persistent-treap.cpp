// problem: https://www.codechef.com/problems/GENETICS
// gaurang's submission: https://www.codechef.com/viewsolution/48339850
#include <bits/stdc++.h>
using namespace std;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

const int MAX_DNAS = 3e4 + 20 + 13;
int assign[128];
char rev[4];

struct node {
	int count[4], size, val, prior;
	node *l, *r;
	node() {
		prior = rng();
		l = r = NULL;
		size = 0;
		val = -1;
		for (int i = 0; i < 4; ++i)
			count[i] = 0;
	}
	node(char _ch) {
		prior = rng();
		l = r = NULL;
		size = 1;
		val = assign[_ch]; 
		for (int i = 0; i < 4; ++i)
			count[i] = 0;
		count[assign[_ch]] = 1;
	}
	node(node* other) {
		prior = rng();
		l = other->l;
		r = other->r;
		size = other->size;
		val = other->val; 
		for (int i = 0; i < 4; ++i)
			count[i] = other->count[i];
	}
};
typedef node* pnode;

pnode dna[MAX_DNAS];
int dna_cnt = 0;

void inorder(pnode t) {
	if(!t) return;
	inorder(t->l);
	cout<<rev[t->val];
	inorder(t->r);
}

int sz(pnode t) {
	return t ? t->size : 0;
}

int getcount(pnode t,int id) {
	return t ? t->count[id] : 0;
}

void operation(pnode t) {
	if(!t) return;
	t->size = 1 + sz(t->l) + sz(t->r);
	for(int i=0;i<4;i++) {
		t->count[i] = getcount(t->l, i) + getcount(t->r, i);
	}
	t->count[t->val]++;
}

// One rule of thumb to check that your persistance is correct
// on the LHS of the assignment equations, always put newly created nodes ONLY
// if old nodes are never on the LHS, then you're sure they're not modified =>
// they remain persistent

pnode merge(pnode l,pnode r) {
	if(!l and !r) return NULL;
	if(!l or !r) return new node((l ? l : r));
	// if(!l or !r) return (l ? l : r);
	pnode root = NULL;

	if(l->prior > r->prior) {
		root = new node(l);
		root->r = merge(root->r, r);
	} else {
		root = new node(r);
		root->l = merge(l, root->l);
	}
	operation(root);
	return root;
}

void split_by_pos(pnode t,pnode &l,pnode &r,int pos,int add = 0) {
	if(!t) return void(l = r = NULL);
	int curr_pos = sz(t->l) + add;
	pnode new_t = new node(t);
	if(pos >= curr_pos) {
		split_by_pos(new_t->r, new_t->r, r, pos, curr_pos + 1);
		l = new_t;
	} else {
		split_by_pos(new_t->l, l, new_t->l, pos, add);
		r = new_t;
	}
	operation(new_t);
}

pnode build(const string &inp,int l,int r) {
	if(l == r) return new node(inp[l]);
	int mid = (l + r)/2;
	return merge(build(inp, l, mid), build(inp, mid + 1, r));
}

void update_node(pnode t,char ch) {
	int val = assign[ch];
	t->count[t->val]--;
	t->val = val;
	t->count[val]++;
}

void point_update(pnode &t,int p,char ch) {
	pnode l, mid, mid1, r;
	split_by_pos(t, l, mid, p - 1);
	split_by_pos(mid, mid, r, 0);
	update_node(mid, ch);
	mid1 = merge(mid, r);
	t = merge(l, mid1);
}

void cross_dnas(int l,int r,int k1,int k2) {
	pnode l1, r1, l2, r2;
	split_by_pos(dna[l], l1, r1, k1);
	split_by_pos(dna[r], l2, r2, k2);
	dna[dna_cnt++] = merge(l1, r2); 
	dna[dna_cnt++] = merge(l2, r1); 
}

void count(pnode t,int l,int r) {
	pnode l1, mid1, r1, mid2;
	split_by_pos(t, l1, mid1, l - 1);
	split_by_pos(mid1, mid2, r1, r - l);
	for(int i=0;i<4;i++)
		cout<<mid2->count[i]<<" ";
	cout<<endl;
}


signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	assign['A'] = 0; rev[0] = 'A';	
	assign['G'] = 1; rev[1] = 'G';	
	assign['T'] = 2; rev[2] = 'T';	
	assign['C'] = 3; rev[3] = 'C';
	int n;
	cin>>n;
	for(int i=0; i < n; i++) {
		string inp;
		cin>>inp;
		dna[dna_cnt++] = build(inp, 0, inp.size() - 1);
	}	
	int q;
	cin>>q;
	while(q--)
	{
		string op;
		cin>>op;
		if(op == "CROSS") {
			int id1, id2, k1, k2;
			cin>>id1>>id2>>k1>>k2;
			id1--; id2--; k1--; k2--;
			cross_dnas(id1, id2, k1, k2);
		} else if(op == "MUTATE") {
			int id, p;
			char ch;
			cin>>id>>p>>ch;
			id--; p--;
			point_update(dna[id], p, ch);
		} else {
			int id, k1, k2;
			cin>>id>>k1>>k2;
			id--; k1--; k2--;
			count(dna[id], k1, k2);
		}
	}
	return 0;
}	

