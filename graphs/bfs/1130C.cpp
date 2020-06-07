
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

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
#define x first
#define y second
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
const int N = 55;
const int ax[]={-1,1,0,0};
const int ay[]={0,0,-1,1};
string s[N];
int n;
bool vis[2][N][N]={0};

void bfs(int x,int y,int m)
{
	queue<ii> q;
	q.push({x,y});
	vis[m][x][y]=1;
	while(!q.empty())
	{
		ii curr=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			x=curr.x+ax[i];y=curr.y+ay[i];
			if(x<0 || x>=n || y<0 || y>=n) continue;
			if(!vis[m][x][y]&&s[x][y]=='0')
			{
				vis[m][x][y]=1;
				q.push({x,y});
			}
		}
	}
}

int cost(int x1,int y1,int x2,int y2) { return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);}

signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	cin>>n;
	int x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	x1--;x2--;y1--;y2--;
	for (int i = 0; i < n; ++i)
	{
		cin>>s[i];
	}
	bfs(x1,y1,0);
	bfs(x2,y2,1);
	int ans=cost(x1,y1,x2,y2);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(vis[0][i][j])
			{
				for(int p=0;p<n;p++)
				{
					for(int q=0;q<n;q++)
					{

						if(vis[1][p][q]) ans=min(ans,cost(i,j,p,q));
					}
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}	