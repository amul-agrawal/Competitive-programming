
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

class SegmentTrees
{
	vvi st;
public:
	SegmentTrees(int n)
	{
		st.resize(4*n);
	}
	void build(vi &arr,int left,int right,int pos=1)
	{
		if(left == right)
		{
			st[pos].pb(arr[left]);
		}
		else
		{
			int mid = (left + right)/2;
			build(arr,left,mid,pos*2);
			build(arr,mid+1,right,pos*2+1);
			merge(all(st[pos*2]),all(st[pos*2+1]),back_inserter(st[pos]));
		}
	}
	// return number of idx which are in the range [l,r] 
	int query(int l,int r,int k,int left,int right,int pos=1)
	{
		if(l>r) return 0;
		if(left == right)
		{
			return st[pos][0];
		}
		else
		{
			int mid = (left + right)/2;
			int count = upper_bound(all(st[pos*2]),r)-st[pos*2].begin(); // <=r
			count -= lower_bound(all(st[pos*2]),l) - st[pos*2].begin(); // < l;
			if(count >= k)
			{
				return query(l,r,k,left,mid,pos*2);
			}
			else
			{
				return query(l,r,k-count,mid+1,right,pos*2+1);
			}
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n,q;
	cin>>n>>q;
	vi val(n);
	vii a(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i].ff;
		val[i]=a[i].ff;
		a[i].ss = i;
	}
	sort(all(a));
	vi b(n);
	for (int i = 0; i < n; ++i)
	{
		b[i]=a[i].ss;
	}
	SegmentTrees sgt(n);
	sgt.build(b,0,n-1);
	while(q--)
	{
		int l,r,k;
		cin>>l>>r>>k;
		l--;r--;
		int idx = sgt.query(l,r,k,0,n-1);
		cout<<val[idx]<<endl;
	}
	return 0;
}	