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
    int max1=-100000000;
    for(int i=0;i<n;i++)
    {
    	max1=max(max1+a[i],a[i]);
    }  
    cout<<max1;
    return 0;
}