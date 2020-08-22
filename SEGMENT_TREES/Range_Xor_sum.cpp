/*
	created by :- amul_agrawal
	created on :- 21-08-2020
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
//added two more functions to set
//(1)*(set.find_by_order(k))[kth element in the sorted set] 
//(2)set.order_of_key(k)[count of elements strictly less than k]

typedef vector< int > vi;
typedef vector<long long> lvi;
typedef vector< vector<int> > vvi;
typedef vector< vector<long long> > lvvi;
typedef pair< int,int > ii;
typedef pair< long long,long long > lii;
typedef vector<pair<int,int>> vii;
typedef vector<pair<long long,long long>> lvii;
typedef vector<vector<pair<int,int>>> vvii;
typedef vector<vector<pair<long long,long long>>> lvvii;
typedef vector<bool> vb;

#ifdef ONLINE_JUDGE 
#define endl '\n'
#endif
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define ss second
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " is " << a << endl;
	err(++it, args...);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
const long long mod = 1e9 + 7;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

long long mos() { return 0LL; }
template<typename T, typename... Args>
T mos(T a, Args... args) { return ((a + mos(args...))%mod + mod)%mod; }

long long mop() { return 1LL; }
template<typename T, typename... Args>
T mop(T a, Args... args) { return (a*mop(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------


const int N = 1<<18;
int mask=0;
lvi a(N,0);
// 18 bit number [0,17]
// main task is to find sum [l,r,x] =>	 a[l^x] + a[(l+1)^x]....a[r^x];
// we can use segtree for this purpose.

class SegmentTrees
{
	lvi st;
public:
	SegmentTrees()
	{
		st.resize(4*N);
	}
	void build(int left=0,int right=N-1,int pos=1)
	{
		if(left == right)
		{
			st[pos]=a[left];
		}
		else
		{
			int mid = (left + right)/2;
			build(left,mid,pos<<1);
			build(mid+1,right,(pos<<1)+1);
			st[pos] = st[(pos<<1)] + st[(pos<<1)+1];
		}
	}
	void update(int idx,int val,int left=0,int right=N-1,int pos=1)
	{
		if(left > right) return;
		if(left == right) st[pos]=val;
		else
		{
			int mid = (left + right)/2;
			if(idx<=mid) update(idx,val,left,mid,(pos<<1));
			else update(idx,val,mid+1,right,(pos<<1)+1);
			st[pos]=st[(pos<<1)]+st[(pos<<1)+1];
		}
	}
	ll sum(int l,int r,int left=0,int right=N-1,int depth=17,int pos=1)
	{
		if(l>r) return 0;
		if(l==left && r==right)
		{
			// error(left,right);
			return st[pos];
		} 
		else
		{
			int mid = (left + right)/2;
			int flip = (mask>>depth)&1;

			// flip checks whether the bit at idx=depth is set in mask or not.
			// if it's set we change the direction of our path.

			return sum(l,min(r,mid),left,mid,depth-1,(pos<<1) + flip) +
			sum(max(l,mid+1),r,mid+1,right,depth-1,(pos<<1) + !flip);
		}
	}
};


signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n,q;
	cin>>n>>q;
	for (int i = 0; i < (1<<n); ++i)
	{
		cin>>a[i];
	}	
	SegmentTrees sgt;
	sgt.build();
	error(mask);
	while(q--)
	{
		int t;
		cin>>t;
		if(t==1) // replace
		{
			int idx,k;
			cin>>idx>>k;
			idx--;
			idx ^= mask;
			sgt.update(idx,k);
		}
		else if(t==2) // reverse
		{
			int k;
			cin>>k;
			mask ^= ((1<<k)-1);
		}	
		else if(t==3) // swap
		{
			int k;
			cin>>k;
			mask ^= ((1<<k));
		}
		else // sum
		{
			int l,r;
			cin>>l>>r;
			l--;r--;
			// error(mask);
			cout<<sgt.sum(l,r)<<endl;
		}
	}
	return 0;
}	


// WA
// 1. overflow
// 2. re-initialize global variables for every test case.
// 3. edge cases like n=1

// Run time error
// 1. division by zero.
// 2. array bounds.

// TLE
// 1. uncomment that #define endl '\n' line