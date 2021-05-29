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

//change to array implementation for faster results
struct matrix 
{
	lvvi mat;
	ll size,mmod;
	matrix(ll sz1=2,ll mods=mod)
	{
		size=sz1;
		mmod=mods;
		mat.resize(size,lvi(size,0));
		// identity assignment;
		for (int i = 0; i < size; ++i) 
		{
			mat[i][i]=1;
		}
	}
	void scan()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cin>>mat[i][j];
			}
		}
	}
	void print()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout<<mat[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	matrix operator*(const matrix& b)const {
		matrix temp(size,mmod);
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				temp.mat[i][j]=0;
				for (int k = 0; k < size; ++k)
				{
					temp.mat[i][j] = (temp.mat[i][j] + (mat[i][k]*b.mat[k][j])%mmod)%mmod;
				}
			}
		}
		return temp;
	}
	matrix operator+(const matrix& b) const {
		matrix temp(size,mmod);
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				temp.mat[i][j] = (mat[i][j] + b.mat[i][j])%mmod;
			}
		}
		return temp;
	}
	matrix operator-(const matrix& b) const {
		matrix temp(size,mmod);
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				temp.mat[i][j] = ((mat[i][j] - b.mat[i][j])%mmod + mmod)%mmod;
			}
		}
		return temp;
	}
};

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	matrix a,b;
	a.scan();
	b.scan();
	cout<<endl;
	
	a.print();
	cout<<endl;
	b.print();
	cout<<endl;


	matrix adds = a + b;
	adds.print();
	cout<<endl;


	matrix difs = a - b;
	difs.print();
	cout<<endl;

	matrix prods = a*b;
	prods.print();
	cout<<endl;
	return 0;
}	