
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

ll n;
struct matrix{
	lvvi m;
	matrix(ll N)
	{
		m.resize(N+2,lvi(N+2));
	}
	matrix operator*(const matrix& b) const { // the last const means that we can alter the data of the struct
		matrix temp(n);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				for(int k=0;k<n;k++)
				{
					temp.m[i][j]=mod_sum(temp.m[i][j],mod_product(m[i][k],b.m[k][j]));
				}
			}
		}
		return temp;
	}
	void printmat()
	{
		cout<<endl;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout<<m[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll k;	
	cin>>n>>k;
	matrix a(n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin>>a.m[i][j];
		}
	}
	matrix res(n);
	for (int i = 0; i < n; ++i)
	{
		res.m[i][i]=1;
	}
	while(k>0)
	{
		if(k&1) res=res*a;
		k>>=1;
		a=a*a;
	}
	ll ans=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			ans=mod_sum(ans,res.m[i][j]);
		}
	}
	cout<<ans<<endl;
	return 0;
}