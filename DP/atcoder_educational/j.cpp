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
int n,n1=0,n2=0,n3=0;
long double dp[301][301][301];
long double recurs(int n1,int n2,int n3)
{
	if(n1<0||n2<0||n3<0) return 0;
	if(dp[n1][n2][n3]!=-1) return dp[n1][n2][n3];
	ld k=n1+n2+n3;
	dp[n1][n2][n3]=((ld)n/k)+((ld)1/k)*(recurs(n1-1,n2,n3)+recurs(n1+1,n2-1,n3)+recurs(n1,n2+1,n3-1));
	return dp[n1][n2][n3];
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    memset(dp,-1,sizeof(dp));
    cin>>n;
    dp[0][0][0]=0;
    for (int i = 0; i < n; ++i)
    {
    	int x;
    	cin>>x;
    	if(x==1) n1++;
    	else if(x==2) n2++;
    	else n3++;
    }
    long double ans=recurs(n1,n2,n3);
    cout<<setprecision(9)<<fixed<<ans<<endl;
    return 0;
}