
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
class SegmentTree{
	lvi data;
	ll n;
public:
	SegmentTree(ll N)
	{
		n=N;
		data.assign(4*n,0);
	}
	ll lfc(ll x){ return (x<<1LL);};
	ll rgc(ll x){ return (x<<1LL)+1;}
	void build(lvi &arr,ll left,ll right,ll pos=1)
	{
		if(left==right){
			data[pos]=arr[left];
		}
		else{
			ll mid=(left+right)/2;
			build(arr,left,mid,lfc(pos));
			build(arr,mid+1,right,rgc(pos));
			data[pos]=max(data[lfc(pos)],data[rgc(pos)]);
		}
	}
	void update(ll idx,ll val,ll left,ll right,ll pos=1)
	{
		if(left==right){
			data[pos]=val;
		}
		else{
			ll mid=(left+right)/2;
			if(idx<=mid){
				update(idx,val,left,mid,lfc(pos));
			}
			else{
				update(idx,val,mid+1,right,rgc(pos));
			}
			data[pos]=max(data[lfc(pos)],data[rgc(pos)]);
		}
	}
	ll get_first(ll val,ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return -1;
		if(data[pos]<=val) return -1;
		if(left==right){
			return left;
		}
		else{
			ll mid=(left+right)/2;
			ll rs=get_first(val,l,min(r,mid),left,mid,lfc(pos));
			if(rs!=-1) return rs;
			rs=get_first(val,max(l,mid+1),r,mid+1,right,rgc(pos));
			return rs;
		}
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	ll n;
	cin>>n;
	lvi a(n);
	for (int i = 0; i < n; ++i)
	{
		cin>>a[i];
	}
	SegmentTree sgt(n);
	sgt.build(a,0,n-1);
	tc(T)
	{
		ll t;
		cin>>t;
		if(t==1){
			ll l,r,x;
			cin>>l>>r>>x;
			ll idx=sgt.get_first(x,l,r,0,n-1);
			if(idx!=-1)
			cout<<idx<<" "<<a[idx]<<endl;
			else cout<<idx<<endl;
		}
		else{
			ll idx,val;
			cin>>idx>>val;
			a[idx]=val;
			sgt.update(idx,val,0,n-1);
		}
	}
	return 0;
}