
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);	
	while(1)
	{
		int n, m;
		cin>>n>>m;
		if(n==0 and m==0) break;
		vector<vector<int>> adj(n+1);
		for(int i=0;i<m;i++)
		{
			int u, v;
			cin>>u>>v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		int ap = 0;
		int root = 1;
		vector<int> lvl(n+1, 0), highest(n+1);
		function<void(int,int)> dfs = [&](int x,int p)
		{
			highest[x] = x;
			lvl[x] = lvl[p] + 1;
			int comps = 1;
			if(x==root)
				comps = 0;
			for(auto nx : adj[x])
			{
				// parent edge
				if(nx == p) {
					continue;
				} else if (lvl[nx] == 0) {
					// spanning edge
					dfs(nx, x);
					// if subtree of nx, was pointing above my original ptr
					if(lvl[highest[nx]] < lvl[highest[x]]) 
						highest[x] = highest[nx];	
					
					// if I can't go to parent of x from subtree of nx.
					if(lvl[highest[nx]] >= lvl[x]) 
						comps++;
				} else if (lvl[nx] < lvl[highest[x]]) {
					highest[x] = nx;
				}
			}
			if(comps > 1) {
				// error(x);
				ap++;
			}
		};
		dfs(root, 0);
		cout<<ap<<endl;
	}	
	return 0;
}	
