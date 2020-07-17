
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define ordered_set tree < int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
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
	void build(int arr[],int left,int right,int pos=1)
	{
		if(left == right)
		{
			st[pos].insert(arr[left]);
		}
		else
		{
			int mid = (left + right)/2;
			for(int i=left;i<=right;i++)
			{
				st[pos].insert(arr[i]);
			}
			build(arr,left,mid,pos*2);
			build(arr,mid+1,right,pos*2+1);
		}
	}
	void rem(int idx,int val,int left,int right,int pos)
	{
		st[pos].erase(val);
		if(left == right)
		{
			return ;
		}
		else
		{
			int mid = (left + right)/2;
			if(idx <= mid)
			{
				rem(idx,val,left,mid,pos*2);
			}
			else
			{
				rem(idx,val,mid+1,right,pos*2+1);
			}
		}
	}
	void add(int idx,int val,int left,int right,int pos)
	{
		st[pos].insert(val);
		if(left == right)
		{
			return ;
		}
		else
		{
			int mid = (left + right)/2;
			if(idx <= mid)
			{
				add(idx,val,left,mid,pos*2);
			}
			else
			{
				add(idx,val,mid+1,right,pos*2+1);
			}
		}
	}
	int queryG(int l,int r,int k,int left,int right,int pos) // >k
	{
		if(l>r) return 0;
		if(l==left && r==right)
		{
			return st[pos].size() - st[pos].order_of_key(k+1);
		}
		else
		{
			int mid = (left + right)/2;
			return queryG(l,min(r,mid),k,left,mid,pos*2) +
				queryG(max(l,mid+1),r,k,mid+1,right,pos*2+1);
		}
	}
	int queryL(int l,int r,int k,int left,int right,int pos) // < k
	{
		if(l>r) return 0;
		if(l==left && r==right)
		{
			return st[pos].order_of_key(k);
		}
		else
		{
			int mid = (left + right)/2;
			return queryL(l,min(r,mid),k,left,mid,pos*2) +
				queryL(max(l,mid+1),r,k,mid+1,right,pos*2+1);
		}
	}
};


signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	int n,q;
	cin>>n>>q;
	int a[200005];
	for (int i = 0; i < n; ++i)
	{
		a[i]=i;
	}
	ll inv=0;
	SegmentTrees sgt(n);
	sgt.build(a,0,n-1);
	int l,r;
	while(q--)
	{
		cin>>l>>r;
		if(l==r)
		{
			cout<<inv<<'\n';
			continue;
		}
		if(l>r) swap(l,r);
		l--;r--;
		inv += ((sgt.queryL(l,r-1,a[r],0,n-1,1) + sgt.queryG(l,r-1,a[l],0,n-1,1)) - (sgt.queryL(l,r-1,a[l],0,n-1,1) + sgt.queryG(l,r-1,a[r],0,n-1,1)));
		sgt.rem(l,a[l],0,n-1,1);
		sgt.rem(r,a[r],0,n-1,1);
		swap(a[l],a[r]);
		sgt.add(l,a[l],0,n-1,1);
		sgt.add(r,a[r],0,n-1,1);
		cout<<inv<<'\n';
	}
	return 0;
}	