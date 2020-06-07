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
struct node
{
	ll lft,rgt,ans;
};
class SegmentTree {
   private:
    vector<node> st;
    node zero;
    ll n;
   public:
    SegmentTree(ll N) {
        n = N;
        st.resize(4 * n);
        zero.lft=0,zero.rgt=0,zero.ans=0;
    }
    node merge_nodes(node a,node b)
    {
    	node c;
    	c.ans=a.ans+b.ans+2*min(a.rgt,b.lft);
    	c.lft=a.lft + max(0LL,b.lft-a.rgt);
    	c.rgt=b.rgt + max(0LL,a.rgt-b.lft);
    	return c;
    }
    void build(vi &arr, ll left, ll right, ll pos = 1) {
        if (left == right){
            st[pos].ans = 0;
        	st[pos].lft=(arr[left]==0);
        	st[pos].rgt=(arr[left]==1);
        }
        else {
            ll mid = (right + left) / 2; 
            ll lc=(pos<<1LL),rc=lc+1;;
            build(arr, left, mid, lc);
            build(arr, mid + 1, right, rc);
            st[pos]=merge_nodes(st[lc],st[rc]);
        }
    }
    node sum(ll l, ll r, ll left, ll right, ll pos = 1) {
        if (l > r)
            return  zero;
        if (l == left && r == right)
            return st[pos];

        ll mid = (left + right) / 2;
        return merge_nodes(sum(l, min(r, mid), left, mid, pos << 1LL),sum(max(l, mid + 1), r, mid + 1, right, (pos << 1LL) + 1));
    }
};
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
    string s;
    cin>>s;
    ll n=s.length(),new_n=1;
    vi arr(n,0);
    for (int i = 0; i < n; ++i) // right=1  left =0
    {
    	if(s[i]=='(')
    	{
    		arr[i]=1;
    	}
    	else arr[i]=0;
    }
    SegmentTree sgt(n);
    sgt.build(arr,0,n-1);
    tc(T)
    {
    	ll x,y;
    	cin>>x>>y;
    	x--;y--;
    	cout<<sgt.sum(x,y,0,n-1).ans<<endl;
    }
	return 0;
}