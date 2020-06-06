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
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    int h,w,dp[1005][1005];
    cin>>h>>w;
    for (int i = 1; i <=h; ++i)
    {
 		string s;
 		cin>>s;
 		for(int j=1;j<=w;j++)
 		{
 			if(s[j-1]=='.') dp[i][j]=-1;
 			else dp[i][j]=0;
 		}   
    }
    for(int i=0;i<=max(h,w);i++)
    {
    	if(i<=w) dp[0][i]=0;
    	if(i<=h) dp[i][0]=0;
    }
    /*for (int i = 0; i <=h; ++i)
    {
    	for (int j = 0; j <=w; ++j)
    	{
    		cout<<dp[i][j]<<" ";
    	}
    	cout<<"\n";
    }*/
    dp[1][1]=1;
    for(int i=1;i<=h;i++)
    {
    	for(int j=1;j<=w;j++)
    	{
    		if(dp[i][j]!=-1) continue;
    		dp[i][j]=(dp[i-1][j]+dp[i][j-1])%mod;
    		//cout<<dp[i][j]<<" ";
    	}
    	//cout<<endl;
    }
    cout<<dp[h][w]<<endl;
    return 0;
}