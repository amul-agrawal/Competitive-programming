// https://arc077.contest.atcoder.jp/tasks/arc077_c?lang=en
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
//added two more functions to set
//(1)*(set.find_by_order(k))[kth element in the sorted set] 
//(2)set.order_of_key(k)[count of elements strictly less than k]
typedef vector< int > vi;
typedef vector< ll > lvi;
typedef vector< vi > vvi;
typedef vector< lvi > lvvi;
typedef pair< int,int > ii;
typedef pair< ll,ll > lii;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
#define present(c,x) ((c).find(x) != (c).end())//for sets,maps,multimaps
#define cpresent(c,x) (find(all(c),x) != (c).end())//for vectors
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define ss second
#define mp make_pair
#define ld long double
#define ull unsigned long long int
#define mod 1000000007
void update_prefix(lvi &v,ll l,ll r,ll x)
{
	v[l]+=x;
	v[r+1]-=x;
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n,m;
	cin>>n>>m;
	lvi a(n+2);
	lvi const_sum(m+2,0),linear_sum(m+2,0);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<n;i++)
	{
		ll x=a[i],y=a[i+1];
		if(x==y) continue;
		if(x<y)
		{
			update_prefix(const_sum,1,x,y-x);
			update_prefix(const_sum,x+1,y,y+1);
			update_prefix(const_sum,y+1,m,y-x);
			update_prefix(linear_sum,x+1,y,1);// basically we need to subtract index value 1 time;
		}
		else
		{
			update_prefix(const_sum,y+1,x,m-x+y);
			update_prefix(const_sum,1,y,1+y);
			update_prefix(const_sum,x+1,m,y+m+1);
			update_prefix(linear_sum,x+1,m,1);
			update_prefix(linear_sum,1,y,1);
		}
	}
	for (int i = 1; i <=m; ++i)
	{
		const_sum[i]+=const_sum[i-1];
		linear_sum[i]+=linear_sum[i-1];
	}
	for (int i = 1; i <=m; ++i)
	{
		const_sum[i]-=(i*linear_sum[i]);
	}
	ll ans=const_sum[1];
	for (int i = 1; i <=m; ++i)
	{
		ans=min(ans,const_sum[i]);
	}
	cout<<ans<<endl;
	return 0;
}