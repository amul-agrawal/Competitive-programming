// problem link: https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/t1-1-6064aa64/description/
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
queue<pair<vi,int>> q;
set<vi> st;
int n;
bool check(vi v)
{
	for (int i = 1; i < v.size(); ++i)
	{
		if(v[i]<v[i-1]) return false;
	}
	return true;
}
int bfs(vi cur)
{
	q.push({cur,0});
	st.insert(cur);
	while(!q.empty())
	{
		if(check(q.front().ff))
		{
			return q.front().ss;
		}
		pair<vi,int> tmp=q.front();q.pop();
		for (int i = 2; i <=n; ++i)
		{
			vi go(tmp.ff);
			reverse(go.begin(),go.begin()+i);
			if(!present(st,go))
			{
				st.insert(go);
				q.push({go,tmp.ss+1});
			}
		}
	}
}
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    cin>>n;
    vi v;
    for (int i = 0; i < n; ++i)
    {
    	int x;
    	cin>>x;
    	v.pb(x);
    }
    int ans=bfs(v);
    cout<<ans<<endl;
    return 0;
}