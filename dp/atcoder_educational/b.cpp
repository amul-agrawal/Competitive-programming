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
typedef vector< vi > vvi;
typedef pair< int,int > ii;
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
ll dp[200000],n,k,h[200000];
ll recurs(ll pos)
{
	if(dp[pos]!=-1) return dp[pos];
	if(pos>n) return (2e5);
	if(pos==n) return 0;
	ll min1=abs(h[pos+1]-h[pos])+recurs(pos+1);
	for (int i = 2; i <=k; ++i)
	{
		min1=min(abs(h[pos+i]-h[pos])+recurs(pos+i),min1);
	}
	dp[pos]=min1;
	return dp[pos];
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    cin>>n>>k;
 	for (int i = 1; i <=n; ++i)
	  {
	  		cin>>h[i];
	  }  
	 memset(dp,-1,sizeof(dp));
	 ll ans=recurs(1);
	 cout<<ans<<endl;
    return 0;
}