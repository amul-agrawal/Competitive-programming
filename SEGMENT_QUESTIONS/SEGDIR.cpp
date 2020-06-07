// problem link : https://www.codechef.com/ICPCIN19/problems/SEGDIR
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
    tc(T)
    {
    	multiset<pair<int,ii>> ms;
    	map<int,int> mp;
    	int n;
    	cin>>n;
    	for (int i = 0; i < n; ++i)
    	{
    		int x,y,v;
    		cin>>x>>y>>v;
    		ms.insert({x,{0,v}});
    		ms.insert({y,{1,v}});
    	}
    	int flag=0;
    	tr(ms,it)
    	{
    		if(it->ss.ff==1)
    		{
    			mp[it->ss.ss]--;;
    		}
    		else
    		{
    			mp[it->ss.ss]++;
    		}
    		if(mp[it->ss.ss]>2) 
    		{
    			cout<<"NO\n";
    			flag=1;
    			break;
    		}
    	}
    	if(flag==0) cout<<"YES\n";
    }
    return 0;
}