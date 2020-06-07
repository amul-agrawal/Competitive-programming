#include <bits/stdc++.h>
using namespace std;
typedef vector< int > vi;
typedef vector< vi > vvi;
typedef pair< int,int > ii;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c)).begin() i = (c).begin(); i != (c).end(); i++)//remember i is an iterator
#define present(c,x) ((c).find(x) != (c).end())//for sets,maps,multimaps
#define cpresent(c,x) (find(all(c),x) != (c).end())//for vectors
#define tc(t) int (t); cin>>(t);while((t)--)
#define mod 1000000007
#define ll long long int
int main()
{
    ios_base::sync_with_stdio(false);//this works only
    cin.tie(NULL);// when first all inputs are from user
    cout.tie(NULL);//you will see all outputs afterwards
    int n;
    cin>>n;
    int a[2000];
    for (int i = 0; i < n; ++i)
    {
    	cin>>a[i];
    }
    int left[2500],right[25000];
    stack<ii> s;
    //left[0]=1;
    for (int i = 0; i < n; ++i)
    {
        int cnt=1;
        while(!s.empty()&&s.top().first>=a[i])
        {
            cnt+=s.top().second;
            s.pop();
        }
        s.push({a[i],cnt});
        left[i]=cnt;
    }
    //right[n-1]=1;
  //  s.clear();
    while(!s.empty())
    {
        s.pop();
    }
    for (int i = n-1; i >=0; --i)
    {
        int cnt=1;
    	while(!s.empty()&&s.top().first>=a[i])
        {
            cnt+=s.top().second;
            s.pop();
        }
        right[i]=cnt;
        s.push({a[i],cnt});
    }
    int sum=0;
    for(int i=0;i<n;i++)
    {
    	sum+=(a[i]*left[i]*right[i]);
    }
    cout<<sum<<endl;
    return 0;
}	