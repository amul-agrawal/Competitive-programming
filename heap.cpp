
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

// min heap
class heap{
	lvi data;
	ll size;
public:
	heap()
	{
		size=0;
		data.push_back(LLONG_MIN);
	}
	bool isempty() { return (size==0?true:false);}
	ll front() { return data[1];}
	void insert(ll x)
	{
		size++;
		data.push_back(x);
		ll pos=size;
		ll parent=pos/2;
		while(parent>=1)
		{
			if(data[parent]<=data[pos]) break;
			swap(data[parent],data[pos]);
			pos=parent;
			parent/=2;
		}
	}
	void del()
	{
		if(size<=0) return ;
		swap(data[1],data[size]);
		data.pop_back();
		size--;
		ll pos=1;
		while(pos<=size)
		{
			ll lfc=pos*2;
			ll rgc=pos*2 +1;
			if(lfc > size && rgc > size) break;
			else if(lfc > size)
			{
				if(data[rgc]>=data[pos]) break;
				swap(data[rgc],data[pos]);
				pos=rgc; 
			}
			else if(rgc > size)
			{
				if(data[lfc]>=data[pos]) break;
				swap(data[lfc],data[pos]);
				pos=lfc;
			}
			else
			{
				if(data[rgc]>=data[lfc])
				{
					swap(data[lfc],data[pos]);
					pos=lfc;
				}
				else
				{
					swap(data[rgc],data[pos]);
					pos=rgc;
				}
			}
		}
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	heap pq;
	ll n;
	cin>>n;
	while(n--)
	{
		ll x;
		cin>>x;
		pq.insert(x);
	}
	tc(T)
	{
		ll q;
		cin>>q;
		if(q==1)
		{
			cout<<pq.front()<<endl;
		}
		else if(q==2)
		{
			pq.del();
		}
		else
		{
			ll x;
			cin>>x;
			pq.insert(x);
		}
	}
	return 0;
}