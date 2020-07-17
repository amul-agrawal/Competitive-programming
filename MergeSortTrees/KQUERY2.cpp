// https://www.spoj.com/problems/KQUERY2/en/


// this includes point updates
// note that for point update we need to have distinct elements
// so when the elements are not distinct make them distinct by having them as a
// pair {val,idx}.


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < pair<int,int> ,  null_type ,  less<pair<int,int>> ,  rb_tree_tag ,  tree_order_statistics_node_update >
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

class SegmentTrees
{
	vector<ordered_set> st;
public:
	SegmentTrees(int n)
	{
		st.resize(4*n);
	}
	inline void merge(int l,int r,int pos)
	{
		for(auto curr:st[l])
		{
			st[pos].insert(curr);
		}
		for(auto curr:st[r])
		{
			st[pos].insert(curr);
		}
	}
	void build(vii &arr,int left,int right,int pos=1)
	{
		if(left == right)
		{
			st[pos].insert(arr[left]);
		}
		else 
		{
			int mid = (left + right)/2;
			build(arr,left,mid,pos*2);
			build(arr,mid+1,right,pos*2+1);
			merge(pos*2,pos*2+1,pos);
		}
	}
	void update(int idx,int val,int oldval,int left,int right,int pos = 1)
	{
		auto it = st[pos].find({oldval,idx});
		st[pos].erase(it);
		st[pos].insert({val,idx});
		if(left == right)
		{
			return ;
		}
		else
		{
			int mid = (left + right)/2;
			if(idx<=mid)
			{
				update(idx,val,oldval,left,mid,pos*2);
			}
			else
			{
				update(idx,val,oldval,mid+1,right,pos*2+1);
			}
		}
	}
	int query(int l,int r,int x,int left,int right,int pos=1)
	{
		if(l>r) return 0;
		if(l==left && r==right)
		{
			return st[pos].size()-st[pos].order_of_key({x+1,-1});
		}
		else
		{
			int mid = (left + right)/2;
			return query(l,min(r,mid),x,left,mid,pos*2) +
				query(max(mid+1,l),r,x,mid+1,right,pos*2+1);
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n;
	cin>>n;
	vii a(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i].ff;
		a[i].ss=i;
	}
	SegmentTrees sgt(n);
	sgt.build(a,0,n-1);
	tc(T)
	{
		int t;
		cin>>t;
		if(t==0)
		{
			int idx,val;
			cin>>idx>>val;
			idx--;
			sgt.update(idx,val,a[idx].ff,0,n-1);
			a[idx].ff=val;
		}
		else
		{
			int l,r,k;
			cin>>l>>r>>k;
			l--;r--;
			cout<<sgt.query(l,r,k,0,n-1)<<endl;
		}
	}
	return 0;
}	