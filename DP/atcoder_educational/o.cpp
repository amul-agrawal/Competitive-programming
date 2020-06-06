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
int a[30][30];
int dp[22][2050000];
int n;
int recurs(int pos,int k)
{
	if(dp[pos][k]!=-1) return dp[pos][k];
	ll ans=0;
	for (int i = 0; i < n; ++i)
	{
		if(a[pos][i]==0) continue;
		if((k&(1<<i))!=0) continue;
		if(pos==(n-1)) 
		{
			return 1;
		}
		ans=(ans+recurs(pos+1,k|(1<<i)))%mod;
	}
	dp[pos][k]=ans;
	return ans;
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    cin>>n;
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < n; ++i)
    {
    	for (int j = 0; j < n; ++j)
    	{
    		cin>>a[i][j];
    	}
    }
    int ans=recurs(0,0);
    cout<<ans;
    return 0;
}