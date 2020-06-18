
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<stack>
using namespace std;
#define ll long long int
#define ull unsigned long long int
#define ld long double
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
typedef vector<ii> vii;
typedef vector<lii> lvii;

#define min_prq(t) priority_queue<t,vector<t>,greater<t>>
#define max_prq(t) priority_queue<t>
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
#define present(c,x) ((c).find(x) != (c).end())//for sets,maps,multimaps
#define cpresent(c,x) (find(all(c),x) != (c).end())//for vectors
#define tc(t) int (t); cin>>(t);while((t)--)
#define ff first
#define ss second
// #define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
// void err(istream_iterator<string> it) {}
// template<typename T, typename... Args>
// void err(istream_iterator<string> it, T a, Args... args) {
// 	cerr << *it << " is " << a << endl;
// 	err(++it, args...);
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
#define mod 1000000007
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

ll mod_sum() { return 0LL; }
template<typename T, typename... Args>
T mod_sum(T a, Args... args) { return ((a + mod_sum(args...))%mod + mod)%mod; }

ll mod_product() { return 1LL; }
template<typename T, typename... Args>
T mod_product(T a, Args... args) { return (a*mod_product(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
ll modpow(ll x,ll y,ll M=mod)
{
	ll ans=1;
	while(y>0){
		if(y&1) ans=(ans*x)%M;
		y=y>>1;
		x=(x*x)%M;
	}
	return ans;
}
ll q,p,x;
lvi map;
struct node{
	ll original,ct=0,ans=0,power=1;
};
class SegmentTrees{
	vector<node> st;
	ll n;
public:
	SegmentTrees(ll N)
	{
		n=N;
		st.resize(4*n);
	}
	ll lfc(ll x){ return (x<<1);}
	ll rgc(ll x){ return (x<<1)+1;}
	node merge(node n1,node n2)
	{
		node n;
		n.original=0;
		n.ct=n1.ct+n2.ct;
		n.power=mod_product(n1.power,n2.power);
		n.ans=mod_sum(n1.ans,mod_product(n2.ans,n1.power));
		return n;
	}
	void add(ll idx,ll val,ll left,ll right,ll pos=1){
		if(left==right){
			st[pos].original=val;
			st[pos].ct++;
			st[pos].power=mod_product(st[pos].power,p);
			st[pos].ans=mod_product(st[pos].ct,val,st[pos].power);
		}
		else {
			ll mid=(left+right)/2;
			if(idx<=mid){
				add(idx,val,left,mid,lfc(pos));
			}
			else add(idx,val,mid+1,right,rgc(pos));
			st[pos]=merge(st[lfc(pos)],st[rgc(pos)]);
		}
	}
	void del(ll idx,ll val,ll left,ll right,ll pos=1){
		if(left==right){
			if(st[pos].ct==0) return ;
			st[pos].ct--;
			st[pos].power=mod_product(st[pos].power,modpow(p,mod-2));
			st[pos].ans=mod_product(st[pos].ct,val,st[pos].power);
		}
		else{
			ll mid=(left+right)/2;
			if(idx<=mid){
				del(idx,val,left,mid,lfc(pos));
			}
			else del(idx,val,mid+1,right,rgc(pos));
			st[pos]=merge(st[lfc(pos)],st[rgc(pos)]);
		}
	}
	ll gethash()
	{
		return st[1].ans;
	}
};
signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>q>>p>>x;
	struct query{
		char ch;
		ll val;
	};
	vector<query> v;
	lvii v1;
	for (int i = 0; i < q; ++i)
	{
		char ch;
		ll val;
		cin>>ch;
		if(ch=='H'){
			val=-1;
		}
		else{
			cin>>val;
			v1.pb({val,i});
		}
		query q1;
		q1.ch=ch;
		q1.val=val;
		v.pb(q1);
	}
	sort(all(v1));
	ll curr=0;
	map.resize(q+2);
	map[v1[0].ss]=curr;
	for (int i = 1; i < v1.size(); ++i)
	{
		if(v1[i].ff==v1[i-1].ff)
		{
			map[v1[i].ss]=map[v1[i-1].ss];
		}
		else
		{
			map[v1[i].ss]=++curr;
		}
	}
	ll res=1;
	SegmentTrees sgt(curr+1);
	for (int i = 0; i < q; ++i)
	{
		char ch=v[i].ch;
		if(ch=='H')
		{
			res=mod_product(res,modpow(x,sgt.gethash()));
		}
		else if(ch=='D'){
			sgt.del(map[i],v[i].val,0,curr);
		}
		else{
			sgt.add(map[i],v[i].val,0,curr);
		}
	}
	cout<<res<<endl;
	return 0;
}