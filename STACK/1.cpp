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
    int arr[5000],a[5000],b[5000],c[5000],d[5000];
    for (int i = 0; i < n; ++i)
    {
    	cin>>arr[i];
    }
    stack<int> s;
    for (int i = 0; i < n; ++i)
    {
    	while(!(s.empty())&&arr[s.top()]<arr[i])//next larger
    	{
    		a[s.top()]=arr[i];
    		s.pop();
    	}
    	s.push(i);
    }
    while(!s.empty())
    {
    	a[s.top()]=-1;
    	s.pop();
    }
    for (int i = 0; i < n; ++i)
    {
    	while(!(s.empty())&&arr[s.top()]>arr[i])//next smaller
    	{
    		b[s.top()]=arr[i];
    		s.pop();
    	}
    	s.push(i);
    }
    while(!s.empty())
    {
    	b[s.top()]=-1;
    	s.pop();
    }
    for (int i = n-1; i >=0; i--)
    {
    	while(!(s.empty())&&arr[s.top()]<arr[i])//previous larger
    	{
    		c[s.top()]=arr[i];
    		s.pop();
    	}
    	s.push(i);
    }
    while(!s.empty())
    {
    	c[s.top()]=-1;
    	s.pop();
    }
    for (int i = n-1; i >=0; i--)
    {
    	while(!(s.empty())&&arr[s.top()]>arr[i])//previous smaller
    	{
    		d[s.top()]=arr[i];
    		s.pop();
    	}
    	s.push(i);
    }
    while(!s.empty())
    {
    	d[s.top()]=-1;
    	s.pop();
    }    
    cout<<"next larger\n";
    for (int i = 0; i < n; ++i)
    {
    	cout<<a[i]<<" ";
    }
    cout<<endl;
    cout<<"next smaller\n";
    for (int i = 0; i < n; ++i)
    {
    	cout<<b[i]<<" ";
    }
    cout<<endl;
    cout<<"previous larger\n";
    for (int i = 0; i < n; ++i)
    {
    	cout<<c[i]<<" ";
    }
    cout<<endl;
    cout<<"previous smaller\n";
    for (int i = 0; i < n; ++i)
    {
    	cout<<d[i]<<" ";
    }
    cout<<endl;
    return 0;
}