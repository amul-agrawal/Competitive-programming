//https://www.codechef.com/APRIL20A/problems/REBIT
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
#define mod 998244353
ll modpow(ll x,ll y)
{
	ll ans=1;
	while(y>0)
	{
		if(y&1)
		{
			ans=(ans*x)%mod;
		}
		x=(x*x)%mod;
		y=y>>1;
	}
	return ans;
}
vector<lii> child;
// lvi dp;
// ll dp[200000][8];
vector<lvi> dp;
string s;
ll dfs(ll lvl,char req)
{
	int ref=-1;
	if(req=='0') ref=1;
	else if(req=='1') ref=2;
	else if(req=='a')ref=3;
	else ref=4;
	if(dp[lvl][ref]!=-1) return dp[lvl][ref];
	if(s[lvl]=='#') return 1;
	ll rval=0;
	if(s[lvl]=='^')
	{
		if(req=='0')
		{
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'1'))%mod)%mod;
		}
		else if(req=='a')
		{
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'1'))%mod)%mod;
		}
		else if(req=='A')
		{
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'1'))%mod)%mod;
		}
		else if(req=='1') 
		{
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'a'))%mod)%mod;
		}
	}
	else if(s[lvl]=='&')
	{
		if(req=='0')
		{
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'0'))%mod)%mod;
		}
		else if(req=='a')
		{
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'a'))%mod)%mod;
		}
		else if(req=='A')
		{
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'A'))%mod)%mod;
		}
		else if(req=='1') 
		{
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'1'))%mod)%mod;
		}
	}
	else if(s[lvl]=='|')
	{
		if(req=='0')
		{
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'0'))%mod)%mod;
		}
		else if(req=='a')
		{
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'a'))%mod)%mod;
		}
		else if(req=='A')
		{
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'A'))%mod)%mod;
		}
		else if(req=='1') 
		{
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'0'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'a'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'1')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'0')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'1'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'a')*dfs(child[lvl].ss,'A'))%mod)%mod;
			rval=(rval+(dfs(child[lvl].ff,'A')*dfs(child[lvl].ss,'a'))%mod)%mod;
		}
	}
	dp[lvl][ref]=rval;
	return rval;
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	tc(T)
	{
		cin>>s;
		ll n=s.length();
	    child.assign(n+2,{-1,-1});
	    dp.resize(n+2);
	    for (int i = 0; i < n+1; ++i)
	    {
	    	dp[i].assign(8,-1);
	    }
		stack<ll> st;//push index
		ll q=1,hsh=0;
		for (int i = 0; i < n; ++i)
		 {
		 	char ch=s[i];
		 	if(s[i]=='#') 
		 	{
		 		q=(q*4)%mod;
		 	}
		 	if(ch==')')
		 	{
		 		ll val1=st.top();
		 		st.pop();
		 		ll op=st.top();
		 		st.pop();
		 		ll val2=st.top();
		 		st.pop();
		 		st.push(op);
		 		child[op]={val1,val2};
		 	}
		 	else if(ch!='(')
		 	{
		 		st.push(i);
		 	}
		 } 
		 ll root=st.top();
		 q=modpow(q,mod-2);
		 cout<<(dfs(root,'0')*q)%mod<<" ";
		 cout<<(dfs(root,'1')*q)%mod<<" ";
		 cout<<(dfs(root,'a')*q)%mod<<" ";
		 cout<<(dfs(root,'A')*q)%mod<<endl;
	}
	return 0;
}