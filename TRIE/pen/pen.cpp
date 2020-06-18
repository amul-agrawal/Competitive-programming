
// **** WHEN THE GOING GETS TOUGH, THE TOUGH GETS GOING. ****

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<stack>
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
// void err(istream_iterator<string> it) {}
// template<typename T, typename... Args>
// void err(istream_iterator<string> it, T a, Args... args) {
// 	cerr << *it << " is " << a << endl;
// 	err(++it, args...);
// }

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

struct node
{
	node *child[27];
	bool isend;
};
node* getnode()
{
	node* temp=new node;
	temp->isend = false;
	for(int i=0;i<27;i++)
	{
		temp->child[i]=NULL;
	}
	return temp;
}
node* insert_node(node* curr,string &s,ll idx)
{
	if(idx==s.length())
	{
		curr->isend=true;
		return curr;
	}
	ll ch=s[idx]-'a';
	if(curr->child[ch]==NULL) curr->child[ch]=getnode();
	curr->child[ch]=insert_node(curr->child[ch],s,idx+1);
	curr->isend=true;
	return curr;
}
void change_dp(node* curr,lvi &dp,ll idx,string &s,ll val,ll len)
{
	if(curr->isend==false) return ;
	if(idx!=0)
	if(dp[idx-1]==-1) dp[idx-1]=val;
	if(idx==len) return ;
	ll ch=s[idx]-'a';
	if(curr->child[ch]==NULL) return ;
	change_dp(curr->child[ch],dp,idx+1,s,val,len);
}
signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
    string s;
    cin>>s;
    ll len=s.length();
    lvi dp(len+2,-1);
   	ll n;
   	cin>>n;
   	node* root=getnode();
   	for(int i=0;i<n;i++)
   	{
   		string temp;
   		cin>>temp;
   		root=insert_node(root,temp,0);
   	}
   	change_dp(root,dp,0,s,1,len);
   	ll ans=dp[0];
   	bool flag=false;
   	for(int i=1;i<len;i++)
   	{
   		change_dp(root,dp,i,s,dp[i-1]+1,len);
   		if(dp[i]==-1)
   		{
   			flag=true;
   			break;
   		}
   		ans=dp[i];
   	}
   	if(flag || ans==-1)
   	{
   		cout<<"-1\n";
   	}
   	else
   	{
   		cout<<ans<<endl;
   	}
	return 0;
}