
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
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
	int n_less(int l,int r,int x,int left,int right,int pos=1)
	{
		if(l>r) return 0;
		if(l==left && r==right)
		{
			return upper_bound(all(st[pos]),x) - st[pos].begin();
		}
		else
		{
			int mid = (left + right)/2;
			return n_less(l,min(r,mid),x,left,mid,pos*2) +
				n_less(max(l,mid+1),r,x,mid+1,right,pos*2+1);
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n;
	cin>>n;
	vii prs(n);
	for (int i = 0; i < n; ++i)
	{
		int a,b;
		cin>>a>>b;
		prs[i] = {a,b};
	}
	sort(all(prs));
	vi a(n);
	for (int i = 0; i < n; ++i)
	{
		a[i]=prs[i].ss;
	}
	SegmentTrees sgt(n);
	sgt.build(a,0,n-1);
	int q;
	cin>>q;
	while(q--)
	{
		int l1,r1,l2,r2;
		cin>>l1>>r1>>l2>>r2;
		ii p;
		p.ff=l1;p.ss=l1;
		int l = lower_bound(all(prs),p)-prs.begin();
		p.ff=r1;p.ss=1e6;
		int r = upper_bound(all(prs),p)-prs.begin()-1;
		if(l==n)
		{
			cout<<0<<endl;
			continue;
		}
		int ans = sgt.n_less(l,r,r2,0,n-1) - sgt.n_less(l,r,l2-1,0,n-1);
		cout<<ans<<endl;
	}
	return 0;
}	