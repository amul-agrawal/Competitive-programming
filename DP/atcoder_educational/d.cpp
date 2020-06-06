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
ll dp[100005][101],n,w,val[105],wgh[105];
ll recurs(int pos,int w1)
{
	if(w1>w) return -1*(2e11);
	if(pos>n) return 0;
	if(w1==w) return 0;
	if(dp[w1][pos]!=-1) return dp[w1][pos];
	dp[w1][pos]=max((val[pos]+recurs(pos+1,w1+wgh[pos])),recurs(pos+1,w1));
//	cout<<pos<<" "<<w1<<" "<<dp[w1][pos]<<"\n";
	return dp[w1][pos];
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    memset(dp,-1,sizeof(dp));
    cin>>n>>w;
    for (int i = 1; i <=n; ++i)
    {
    	cin>>wgh[i]>>val[i];
    }
    ll ans=recurs(1,0);
    cout<<ans<<endl;
    return 0;
}