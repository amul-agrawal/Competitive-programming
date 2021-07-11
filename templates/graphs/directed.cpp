// good problem with good editorial.
// contains the principle of (processed nodes, processing nodes, unprocessed nodes)
// https://codeforces.com/contest/1547/problem/G
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  
    int T; cin>>T; while(T--)
    {
        int n, m;
        cin>>n>>m;
        vvi adj(n+2);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin>>u>>v;
            adj[u].push_back(v);
        }
        vi state(n+2, 0), twos, cycles;
        function<void(int)> dfs = [&](int x)
        {
            state[x] = 1;
            for(auto nx : adj[x])
            {
                // done processing
                if(state[nx] == 2) {
                    twos.push_back(nx);
                    continue;
                }
                // processing
                if(state[nx] == 1) {
                    cycles.push_back(nx);
                    continue;
                }
                // left to process
                if(state[nx] == 0) {
                    dfs(nx);
                }
            }
            state[x] = 2;
        };
        dfs(1);     
        vi ans(n+1, 0);
        // first span infinite and then span 2 and then 1
        function<void(int,int)> span = [&](int x,int ch)
        {
            if(ans[x] != 0) return;
            ans[x] = ch;
            for(auto nx : adj[x])
            {
                if(ans[nx] == 0) {
                    span(nx, ch);
                }
            }
        };
        for(auto c : cycles) span(c, -1);
        for(auto t : twos) span(t, 2);
        span(1, 1);
        for(int i=1;i<=n;i++)
            cout<<ans[i]<<" ";
        cout<<endl;
    }
    return 0;
}   
