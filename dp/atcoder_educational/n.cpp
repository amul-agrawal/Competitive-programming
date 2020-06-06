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
ll dp[500][500];
ll prefix[500];
int n,a[500];
ll recurs(int start,int end)
{
	if(start==end) return 0;
	if(start>end) return (1e12);
	if(dp[start][end]!=-1) return dp[start][end];
	ll ans=(1e16);
	for (int i = start; i <end; ++i)
	{
		ans=min(ans,recurs(start,i)+recurs(i+1,end)+prefix[i]+prefix[end]-prefix[start-1]-prefix[i]);
	}
	dp[start][end]=ans;
//	cout<<start<<" "<<end<<" "<<dp[start][end]<<"\n";
	return ans;
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    cin>>n;
    memset(dp,-1,sizeof(dp));
    prefix[0]=0;
    for (int i = 1; i <=n; ++i)
    {
    	cin>>a[i];
    	if(i==1) prefix[i]=a[i];
    	else prefix[i]=prefix[i-1]+a[i];
    }
    ll ans=recurs(1,n);
    cout<<ans;
    return 0;
}