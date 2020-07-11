// Problem link: https://www.spoj.com/problems/HORRIBLE/en/


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
//added two more functions to set
//(1)*(set.find_by_order(k))[kth element in the sorted set] 
//(2)set.order_of_key(k)[count of elements strictly less than k]

typedef vector< int > vi;
typedef vector<long long> lvi;
typedef vector< vector<int> > vvi;
typedef vector< vector<long long> > lvvi;
typedef pair< int,int > ii;
typedef pair< long,long > lii;
typedef vector<pair<int,int>> vii;
typedef vector<pair<long,long>> lvii;
typedef vector<vector<pair<int,int>>> vvii;
typedef vector<vector<pair<long,long>>> lvvii;

#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(auto i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
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

long long mod_sum() { return 0LL; }
template<typename T, typename... Args>
T mod_sum(T a, Args... args) { return ((a + mod_sum(args...))%mod + mod)%mod; }

long long mod_product() { return 1LL; }
template<typename T, typename... Args>
T mod_product(T a, Args... args) { return (a*mod_product(args...))%mod; }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

class SegmentTrees{
	lvi st,lazy,LeavesUnder;
public:

	SegmentTrees(ll n){
		st.resize(4*n);
		lazy.assign(4*n,0);
		LeavesUnder.resize(4*n,0);
	}

//	this is to initialize LeavesUnder array which stores the number of leaf nodes under that node.
	void begin(ll left,ll right,ll pos=1){
		if(left==right){
			LeavesUnder[pos]=1;
		}
		else{
			ll mid=(left+right)/2;
			begin(left,mid,pos*2);
			begin(mid+1,right,pos*2+1);
			LeavesUnder[pos] = LeavesUnder[pos*2] + LeavesUnder[pos*2+1];
		}
	}

//	push function for lazy operation
	void push(ll a){
		lazy[a*2] += lazy[a];
		st[a*2] += lazy[a]*LeavesUnder[a*2];
		lazy[a*2 + 1] += lazy[a];
		st[a*2+1] += lazy[a]*LeavesUnder[a*2+1];
		lazy[a]=0;
	}

//  range addition
	void add(ll val,ll l,ll r,ll left,ll right,ll pos=1){
		if(l>r){
			return ;
		}
		if(l==left && r==right){
			st[pos]+=val*LeavesUnder[pos];
			lazy[pos]+=val;
		}
		else{
			push(pos);
			ll mid = (left+right)/2;
			add(val,l,min(r,mid),left,mid,pos*2);
			add(val,max(l,mid+1),r,mid+1,right,pos*2+1);
			st[pos]=st[pos*2] + st[pos*2+1];
		}
	}

//	range sum query
	ll sum(ll l,ll r,ll left,ll right,ll pos=1){
		if(l>r) return 0;
		if(l==left && r==right){
			return st[pos];
		}
		else{
			push(pos);
			ll mid = (left+right)/2;
			return sum(l,min(r,mid),left,mid,pos*2) +
				sum(max(mid+1,l),r,mid+1,right,pos*2 + 1);
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	tc(T)
	{
		ll n,c;
		cin>>n>>c;
		SegmentTrees sgt(n);
		sgt.begin(0,n-1);
		while(c--){
			ll type;
			cin>>type;
			ll l,r;
			if(type==0){
				ll val;
				cin>>l>>r>>val;
				l--;r--;
				sgt.add(val,l,r,0,n-1);
			}
			else{
				cin>>l>>r;
				l--;r--;
				cout<<sgt.sum(l,r,0,n-1)<<endl;
			}
		}
	}	
	return 0;
}	