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
typedef vector< ll > lvi;
typedef vector< vi > vvi;
typedef vector< lvi > lvvi;
typedef pair< int,int > ii;
typedef pair< ll,ll > lii;
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
class Dsu
{
	lvi parent,xor_with_parent,size;
	public:
	Dsu(ll n)
	{
		parent.assign(n+1,-1);
		xor_with_parent.assign(n+1,0);
		size.assign(n+1,1);
	}
	ll getparent(ll x)
	{
		if(parent[x]==-1) return x;
		else
		{
			ll par=parent[x];
			parent[x]=getparent(par);
			xor_with_parent[x]^=(xor_with_parent[par]);
			return parent[x];
		}
	}
	void unionset(ll x,ll y,ll val)
	{
		ll x1=x;
		ll y1=y;
		x=getparent(x);
		y=getparent(y);
		ll v1=xor_with_parent[x1];
		ll v2=xor_with_parent[y1];
		if(x==y) return;
		if(size[x]<size[y]) swap(x,y);
		parent[y]=x;
		xor_with_parent[y]=v1^v2^val;
		size[x]+=size[y];
	}
	bool issameset(ll x,ll y)
	{
		x=getparent(x);
		y=getparent(y);
		if(x==y) return true;
		else return false;
	}
	ll getxor(ll x,ll y)
	{
		return xor_with_parent[x]^xor_with_parent[y];
	}
};
ll modpow(ll x,ll y,ll mod1=mod)
{
	ll ans=1;
	while(y>0)
	{
		if(y&1)
		{
			ans=(ans*x)%mod1;
		}
		x=(x*x)%mod1;
		y=y>>1;
	}
	return ans;
}
ll getresult(ll a,ll b,ll c)
{
	ll tmp1=modpow(2,mod-2,mod-1);
	tmp1=modpow(tmp1,c/(mod-2),mod-1);
	tmp1=(tmp1*modpow(2,c%(mod-2),mod-1));
	return modpow(a,tmp1,mod);
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n,m,k,X;
	cin>>n>>m>>k>>X;
	ll total=n+m-1;
	Dsu myd(2*k+2);
	map<ll,ll> rtr,ctc;
	ll res=1;
	ll map_rows=1,map_columns=1+k;
	bool flag1=false;
	for (int i = 0; i < k; ++i)
	{
		ll x,y,val;
		cin>>x>>y>>val;
		if(rtr[x]==0)
		{
			rtr[x]=map_rows++;
		}
		if(ctc[y]==0)
		{
			ctc[y]=map_columns++;
		}
		x=rtr[x];
		y=ctc[y];
		bool isredundant=false;
		if(myd.issameset(x,y))
		{
			isredundant=true;
			if(myd.getxor(x,y)!=val)
			{
				flag1=true;
			}
		}
		else
		{
			myd.unionset(x,y,val);
		}
		if(!isredundant) // if the current was not reduntant ..we have filled one more place holder
		{
			total--;
		}	
		ll ans; // ans is X^(y)
		if(flag1)
		{
			ans=1;
		}	
		else
	    ans=getresult(X,2LL,(ll)30*(total));
		res=(res*ans)%mod;
	}
	cout<<res<<endl;
	return 0;
}