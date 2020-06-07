
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

class SegmentTrees
{
	lvi st;
	ll n;
public:
	SegmentTrees(ll N)
	{
		n=N;
		st.resize(4*n);
	}
	ll lfc(ll x){ return (x<<1LL);}
	ll rgc(ll x){ return (x<<1LL)+1;}
	void update(ll idx,ll val,ll left,ll right,ll pos=1)
	{
		if(left==right) st[pos]+=val;
		else 
		{
			ll mid=(left+right)/2;
			if(idx<=mid)
			{
				update(idx,val,left,mid,lfc(pos));
			}
			else
			{
				update(idx,val,mid+1,right,rgc(pos));
			}
			st[pos]=st[lfc(pos)]+st[rgc(pos)];
		}
	}
	ll getcount(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return 0;
		if(l==left && r==right) return st[pos];
		else
		{
			ll mid=(left+right)/2;
			return getcount(l,min(mid,r),left,mid,lfc(pos))+
			getcount(max(mid+1,l),r,mid+1,right,rgc(pos));
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n,k;
	cin>>n>>k;
	lvi a(n);
	lvi b(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	map<ll,ll> mp;
	sort(all(b));
	ll curr=0;
	mp[b[0]]=curr++;
	for (int i = 1; i < n; ++i)
	{
		if(b[i]==b[i-1]) continue;
		mp[b[i]]=curr++;
	}
	for (int i = 0; i < n; ++i)
	{
		a[i]=mp[a[i]];
		// cout<<a[i]<<" ";
	}
	cout<<endl;
	ll total_inversions=0;
	lvi left_inversions(n),right_inversions(n);
	SegmentTrees sgt1(n),sgt2(n),sgt3(n);
	for (int i = 0; i < n; ++i)
	{
		left_inversions[i]=sgt1.getcount(a[i]+1,n,0,n);
		total_inversions+=left_inversions[i];
		sgt1.update(a[i],1,0,n);
		// error(i,left_inversions[i]);
	}
	for(int i=n-1;i>=0;i--)
	{
		right_inversions[i]=sgt2.getcount(0,a[i]-1,0,n);
		sgt2.update(a[i],1,0,n);
		// error(i,right_inversions[i]);
	}
	ll ans=0,rem_val=0;
	ll l=0,r=1;
	while(r<n)
	{
		ll curr_ans=total_inversions-rem_val;
		while(r<n &&curr_ans>k)
		{
			sgt3.update(a[r],1,0,n);
			rem_val+=(left_inversions[r]+right_inversions[r]-sgt3.getcount(a[r]+1,n,0,n));
			r++;
			curr_ans=total_inversions- rem_val;
		}
		if(r==n) break;
		ans+=(n-r);
		l++;
		if(l!=r)
		{
			sgt3.update(a[l],-1,0,n);
			rem_val-=(left_inversions[l]+right_inversions[l]-sgt3.getcount(0,a[l]-1,0,n));
		}
		r=max(l+1,r);
	}
	cout<<ans<<endl;
	return 0;
}	