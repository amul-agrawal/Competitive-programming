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
#define mod 1000000007
bool ispal[5005][5005];
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    memset(ispal,false,sizeof(ispal));
    string s;cin>>s;
    int n=s.length();
    for(int i=1;i<=n;i++)
    {
    	ispal[i][i]=1;
    }
    for(int len=2;len<=n;len++)
    {
    	for(int j=1;(j+len-1)<=n;j++)
    	{
    		int l=j,r=j+len-1;
    		if(s[l-1]==s[r-1]&&(r==(l+1))) {
    			ispal[l][r]=true;
    			continue;
    		}
    		if((s[l-1]==s[r-1])&&ispal[l+1][r-1]) ispal[l][r]=1;
    	}
    }
    tc(Q)
    {
    	int l,r;
    	cin>>l>>r;
    	if(ispal[l][r]) cout<<"YES\n";
    	else cout<<"NO\n";
    }
    return 0;
}