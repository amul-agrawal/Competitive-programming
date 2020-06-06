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
	ll dp[3005][3005];
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    string s,t;
    cin>>s>>t;
    int n=s.length(),m=t.length();
	memset(dp,-1,sizeof(dp));
	for(int i=0;i<=max(n,m);i++)
	{
		if(i<=m) dp[n][i]=0;
		if(i<=n) dp[i][m]=0;
	}   
	for (int i = n-1; i>=0; --i)
	{
		for (int j = m-1; j>=0; --j)
		{
			if(s[i]==t[j])
			{
				dp[i][j]=1+dp[i+1][j+1];
			}
			else
			{
				dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
			}
		}
	}
	int m1=dp[0][0];
/*	cout<<dp[0][0]<<endl;
*/	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(m1==0) break;
			if((dp[i][j]>dp[i+1][j])&&(dp[i][j]>dp[i][j+1]))
			{
				cout<<s[i];
				i++;m1--;
				continue;
			}
			if(dp[i][j]>dp[i+1][j])
			{
				continue;
			}
			if(dp[i][j]>dp[i][j+1])
			{
				i++;j--;
			}
		}
		//cout<<"\n";
	}
	cout<<endl;
    return 0;
}