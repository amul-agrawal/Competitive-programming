
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
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
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " is " << a << endl;
	err(++it, args...);
}

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

struct data1{
	ll n4,n7,l,rl;
};
class SegmentTrees
{
	ll n;
	vector<data1> st;
	data1 zero;
	vector<bool> marked;
public:
	SegmentTrees(ll N)
	{
		n=N;
		st.resize(4*n);
		marked.assign(4*n,false);
		zero.n4=zero.n7=zero.l=zero.rl=0;
	}
	ll lfc(ll x) {return (x<<1LL);}
	ll rgc(ll x) {return (x<<1LL)+1;}
	void ulta(ll x)
	{
		if(marked[x]==false)
		marked[x]=true;
		else marked[x]=false;
		swap(st[x].n4,st[x].n7);
		swap(st[x].rl,st[x].l);
	}
	void push(ll x)
	{
		if(marked[x])
		{
			marked[x]=false;
			ulta(lfc(x));
			ulta(rgc(x));
		}
	}
	data1 merge(data1 d1,data1 d2)
	{
		data1 d;
		d.n4=d1.n4 + d2.n4;
		d.n7=d1.n7 + d2.n7;
		d.l=max(d1.n4+d2.l,d1.l+d2.n7);
		d.rl=max(d1.n7 + d2.rl,d1.rl + d2.n4);
		return d;
	}
	void build(string &s,ll left,ll right,ll pos=1)
	{
		if(left==right)
		{
			ll val=s[left]-'0';
			st[pos].rl=st[pos].l=st[pos].n7=st[pos].n4=1;
			if(val==4) st[pos].n7=0;
			else st[pos].n4=0;
		}
		else
		{
			ll mid=(left+right)/2;
			build(s,left,mid,lfc(pos));
			build(s,mid+1,right,rgc(pos));
			st[pos]=merge(st[lfc(pos)],st[rgc(pos)]);
		}
	}
	void update(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return ;
		if(l==left && r==right)
		{
			ulta(pos);
		}
		else
		{
			push(pos);
			ll mid=(left+right)/2;
			update(l,min(r,mid),left,mid,lfc(pos));
			update(max(mid+1,l),r,mid+1,right,rgc(pos));
			st[pos]=merge(st[lfc(pos)],st[rgc(pos)]);
		}
	}
	data1 get_max()
	{
		return st[1];
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n,m;
	cin>>n>>m;
	SegmentTrees sgt(n);
	string s;
	cin>>s;
	sgt.build(s,0,n-1);
	while(m--)
	{
		string temp;
		cin>>temp;
		if(temp=="count")
		{
			data1 d=sgt.get_max();
			cout<<d.l<<endl;
		}
		else
		{
			ll x,y;
			cin>>x>>y;
			x--;
			y--;
			sgt.update(x,y,0,n-1);
		}
	}
	return 0;
}