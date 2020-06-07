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
class SegmentTree
{
	lvi data;
	vector<bool> mark;
	ll n;
public:
	SegmentTree(ll N)
	{
		n=N;
		data.resize(4*n,LLONG_MAX);
		mark.assign(4*n,false);
	}
	ll lfc(ll x) { return (x<<1LL);}
	ll rgc(ll x) { return (x<<1LL)+1;}
	void push(ll v)
	{
		if(mark[v]){
			mark[lfc(v)]=mark[rgc(v)]=true;
			data[lfc(v)]=data[rgc(v)]=data[v];
			mark[v]=false;
		}
	}
	void modify(ll l,ll r,ll left,ll right,ll val,ll pos=1) // From [l,r) we are storing val;
	{
		if(l>r) return ;
		if(l==left && r==right) {
			mark[pos]=true;
			data[pos]=val;
		}else{
			push(pos);
			ll mid=(left+right)/2;
			modify(l,min(r,mid),left,mid,val,lfc(pos));
			modify(max(l,mid+1),r,mid+1,right,val,rgc(pos));
		}
	}
	ll query(ll idx,ll left,ll right,ll pos=1)
	{
		if(left==right) return data[pos];
		push(pos);
		ll mid=(left+right)/2;
		if(idx<=mid) return query(idx,left,mid,lfc(pos));
		else return query(idx,mid+1,right,rgc(pos));
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	struct query
	{
		ll l,r,winner;
	};
	ll n,m;
	cin>>n>>m;
	vector<query> v(m);
	for (int i = 0; i < m; ++i)
	{
		cin>>v[i].l>>v[i].r>>v[i].winner;
	}
	SegmentTree sgt(n);
	for (int i = m-1; i >=0; i--)
	{
		sgt.modify(v[i].l-1,v[i].winner-2,0,n-1,i);
		sgt.modify(v[i].winner,v[i].r-1,0,n-1,i);//not updating winner position
	}
	for(int i=0;i<n;i++)
	{
		ll round=sgt.query(i,0,n-1);
		if(round==LLONG_MAX) cout<<0<<" ";
		else cout<<v[round].winner<<" ";
	}
	cout<<endl;
	return 0;
}