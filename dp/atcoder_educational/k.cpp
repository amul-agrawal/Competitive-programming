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
int n,k,a[200];
int dp[200000][3];
int recurs(int k,int pos)
{
	if(k<0) return pos;
	if(dp[k][pos]!=-1) return dp[k][pos];
	int ch;
	for (int i = 0; i <n; ++i)
	{
		ch=recurs(k-a[i],(pos+1)%2);
		if(ch==pos) break;
	}
	dp[k][pos]=ch;
//	cout<<k<<" "<<pos<<" "<<dp[k][pos]<<"\n";
	return dp[k][pos];
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    cin>>n>>k;
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < n; ++i)
    {
    	cin>>a[i];
    }
    int ans=recurs(k,1);
    if(ans==1) cout<<"First";
    else cout<<"Second";
    return 0;
}