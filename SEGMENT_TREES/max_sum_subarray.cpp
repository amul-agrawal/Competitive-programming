
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

const ll inf = 1e18;

struct node{
	ll max_prefix,max_suffix,max_subarray,sum;
};
class SegmentTrees{
	vector<node> st;
public:
	SegmentTrees(ll n)
	{
		st.resize(4*n);
	}
	node merge(node a,node b)
	{
		node c;
		c.max_prefix=max(a.max_prefix,a.sum+b.max_prefix);
		c.max_suffix=max(b.max_suffix,b.sum+a.max_suffix);
		c.sum=a.sum+b.sum;
		c.max_subarray=max(max(a.max_subarray,b.max_subarray),max(c.max_prefix,c.max_suffix));
		return c;
	}	
	void build(lvi &arr,ll left,ll right,ll pos=1)
	{
		if(left>right) return ;
		if(left==right)
		{
			st[pos].sum=arr[left];
			ll v=max(0LL,arr[left]);
			st[pos].max_suffix=st[pos].max_prefix=st[pos].max_subarray=v;
		}
		else
		{
			ll mid=(left+right)/2;
			build(arr,left,mid,pos*2);
			build(arr,mid+1,right,pos*2+1);
			st[pos]=merge(st[pos*2],st[pos*2+1]);
		}
	}
	node query(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return {0,0,0,0};
		if(l==left && r==right)
		{
			// error(l,r,left,right,st[pos].max_subarray,st[pos].max_suffix,st[pos].max_prefix,st[pos].sum);
			return st[pos];
		}
		else
		{
			ll mid=(left+right)/2;
			node n1=query(l,min(r,mid),left,mid,pos*2);
			node n2=query(max(mid+1,l),r,mid+1,right,pos*2+1);
			// error(left,right,n1.max_prefix,n1.max_suffix,n1.sum,n1.max_subarray,n2.max_subarray,n2.max_prefix,n2.max_suffix,n2.sum);
			return merge(n1,n2);
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
	tc(T)
	{
		ll l,r;
		cin>>l>>r;
		node n1=sgt.query(l,r,0LL,n-1);
		cout<<n1.max_subarray<<endl;
	}
	return 0;
}	