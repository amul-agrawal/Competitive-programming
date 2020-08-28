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
#define pr 101
 long long int prefix[6000],suffix[6000],prime[6000],modpows[6000];
int location[5002][5002]={0},sum[5002][5002]={0};
 ll modpow( ll x, ll y)
{
	 ll ans=1;
	while(y>0)
	{
		if(y&1) ans=(ans*x)%mod;
		y=y>>1;
		x=(x*x)%mod;
	}
	return ans;
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    string s;
    cin>>s;
    int n=s.length();
    prime[0]=1;
    for (int i = 1; i <=n; ++i)
    {
    	prime[i]=(prime[i-1]*pr)%mod;
    }
    prefix[0]=0;prefix[1]=s[0];
    suffix[0]=0;suffix[1]=s[n-1];
    for (int i = 1; i < n; ++i)
    {
    	prefix[i+1]=(prefix[i]+(s[i]*prime[i])%mod)%mod;
    }
    for (int i = n-2,j=2;i>=0;j++, --i)
    {
    	suffix[j]=(suffix[j-1]+(s[i]*prime[j-1])%mod)%mod;
    }
    for(int i=0;i<=n;i++)
    {
    	modpows[i]=modpow(prime[i],mod-2);
    }
    for (int i = 1; i <=n; ++i)
    {
    	location[i][i]=1;
    	for(int j=i+1;j<=n;j++)
    	{
    		if(s[i-1]!=s[j-1])continue;
    		if(s[j-1]==s[i-1]&&j==(i+1)) 
    		{
    			location[i][j]=1;
    			continue;
    		}
    		int l=i,r=j,temp=l;
    		 ll val1,val2;
    		val1=(((prefix[r]-prefix[l-1]+mod)%mod)*modpows[l-1])%mod;
    		l=n-r+1;r=n-temp+1;
    		val2=(((suffix[r]-suffix[l-1]+mod)%mod)*modpows[l-1])%mod;
    		if(val1==val2) location[i][j]=1;
    	}
    }
   sum[1][1]=location[1][1];
   for(int i=1;i<=n;i++)
   {
    	sum[i][1]=sum[i-1][1]+location[i][1];
    	sum[1][i]=sum[1][i-1]+location[1][i];
   }
    for (int i = 2; i <=n; ++i)
    {
    	for (int j = 2; j <=n; ++j)
    	{
    		sum[i][j]=location[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
    	}
    }
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int l,r;
    	scanf("%d%d",&l,&r);
    	ll ans=sum[r][r]-sum[l-1][r]-sum[r][l-1]+sum[l-1][l-1];
    	printf("%lld\n",ans);
    }
    return 0;
}