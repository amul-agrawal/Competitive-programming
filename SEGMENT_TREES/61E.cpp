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
class SegmentTree {
   private:
    vi st;
    ll n;

   public:
    SegmentTree(ll N) {
        n = N;
        st.assign(4*n,0);
    }
    ll sum(ll l, ll r, ll left, ll right, ll pos = 1) {
        if (l > r)
            return 0;
        if (l == left && r == right)
            return st[pos];

        ll mid = (left + right) / 2;
        return sum(l, min(r, mid), left, mid, pos << 1LL) +
               sum(max(l, mid + 1), r, mid + 1, right, (pos << 1LL) + 1);
    }

    void update( ll left, ll right, ll index, ll pos = 1) {
        if (left == right)
            st[pos]++;
        else {
            ll mid = (left + right) / 2;
            if (index <= mid)
                update( left, mid, index, pos << 1LL);
            else
                update( mid + 1, right, index, (pos << 1LL) + 1);
            st[pos] = st[pos << 1LL] + st[(pos << 1LL) + 1];
        }
    }
};
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n;
	lvi a(n),b(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	sort(all(b));
	ll curr=0;
	map<ll,ll> mp1;
	for (int i = 0; i < n; ++i)
	{
		mp1[b[i]]=curr++;
	}
	for (int i = 0; i < n; ++i)
	{
		a[i]=mp1[a[i]];
	}
	SegmentTree sgt(n);
	lvi previous_greater(n),next_smaller(n);
	for (int i = n-1; i >0; --i)
	{
		sgt.update(0,n-1,a[i]);
		next_smaller[i-1]=sgt.sum(0,a[i-1]-1,0,n-1);
	}
	SegmentTree sgt1(n);
	for (int i = 0; i <n-1; ++i)
	{
		sgt1.update(0,n-1,a[i]);
		previous_greater[i+1]=sgt1.sum(a[i+1]+1,n-1,0,n-1);
	}
	ll ans=0;
	for(int i=1;i<n-1;i++)
	{
		ans+=(previous_greater[i]*next_smaller[i]);
	}
	cout<<ans<<endl;
	return 0;
}