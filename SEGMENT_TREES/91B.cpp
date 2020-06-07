
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

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
typedef pair< long,long > lii;
typedef vector<pair<int,int>> vii;
typedef vector<pair<long,long>> lvii;
typedef vector<vector<pair<int,int>>> vvii;
typedef vector<vector<pair<long,long>>> lvvii;

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
#define mod 1000000007
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

long long mod_sum() { return 0LL; }
template<typename T, typename... Args>
T mod_sum(T a, Args... args) { return ((a + mod_sum(args...))%mod + mod)%mod; }

long long mod_product() { return 1LL; }
template<typename T, typename... Args>
T mod_product(T a, Args... args) { return (a*mod_product(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

struct node{
	ll pos,val;
};

class SegmentTrees 
{
	vector<node> st;
public:
	SegmentTrees(ll n)
	{
		st.resize(4*n);
	}
	node merge(node a,node b)
	{
		node c;
		if(a.val<b.val) c=a;
		else c=b;
		return c;
	}
	void build(lvi &arr,ll left,ll right,ll pos=1)
	{
		if(left>right) return ;
		if(left==right)
		{
			st[pos]={left,arr[left]};
		}
		else
		{
			ll mid=(left+right)/2;
			build(arr,left,mid,pos*2);
			build(arr,mid+1,right,pos*2 + 1);
			st[pos]=merge(st[pos*2],st[pos*2 + 1]);
		}
	}
	node query(ll val,ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return {-1,LLONG_MAX};
		if(l==left && r==right)
		{
			if(left==right) return st[pos];
			ll mid=(left+right)/2;
			if(st[pos*2 + 1].val<val) return query(val,max(mid+1,l),r,mid+1,right,pos*2+1);
			else return query(val,l,min(r,mid),left,mid,pos*2);
		}
		else
		{
			ll mid=(left+right)/2;
			node a=query(val,max(mid+1,l),r,mid+1,right,pos*2+1);
			if(a.val<val) return a;
			a=query(val,l,min(r,mid),left,mid,pos*2);
			return a;
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n;
	lvi a(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}
	SegmentTrees sgt(n);
	sgt.build(a,0,n-1);
	for(int i=0;i<n;i++)
	{
		node a1=sgt.query(a[i],i+1,n-1,0,n-1);
		if(a1.pos==-1) cout<<a1.pos<<endl;
		else cout<<a1.pos-i-1<<endl;
	}
	return 0;
}	