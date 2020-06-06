
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

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
struct query{
	ll l,r,pos;
};
ll block;
bool mysort(query a,query b)
{
	if((a.l/block)!=(b.l/block))
	{
		return (a.l/block)<(b.l/block);
	}
	return (a.r<b.r)^((a.l/block)%2);
}
ll ans=0;
lvi a;
lvi freq;
ll n,m;
void add(ll pos)
{
	if(a[pos]>n) return ;
	freq[a[pos]]++;
	if(freq[a[pos]]==a[pos]) ans++;
	if(freq[a[pos]]==(a[pos]+1)) ans--;
}
void rem(ll pos){
	if(a[pos]>n) return ;
	freq[a[pos]]--;
	if(freq[a[pos]]==a[pos]) ans++;
	if(freq[a[pos]]==(a[pos]-1)) ans--;
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n>>m;
	vector<query> vqr(m);
	a.resize(n);
	freq.assign(n+1,0);
	block=ceil(sqrt(n));
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}
	for (int i = 0; i < m; ++i)
	{
		query q;
		cin>>q.l>>q.r;
		q.pos=i;
		vqr[i]=q;
	}
	sort(all(vqr),mysort);
	ll curr=0,curl=0;
	add(0);
	lvi result(m);
	for (int i = 0; i < m; ++i)
	{
		ll l=vqr[i].l,r=vqr[i].r,pos=vqr[i].pos;
		l--;r--;
		while(curr < r) {
			add(++curr);
		}
		while(curl > l){
			add(--curl);
		}
		while(curl < l){
			rem(curl++);
		}
		while(curr > r){
			rem(curr--);
		}
		result[pos]=ans;
	}
	for (int i = 0; i < m; ++i)
	{
		cout<<result[i]<<endl;
	}
	return 0;
}