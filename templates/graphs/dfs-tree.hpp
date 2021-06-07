// DFS tree: https://codeforces.com/blog/entry/68138

// lvl[x] => root has level 1, children of root have level 2 and so on.
// dp[x] => number of edges from subtree of x and passing over {x, p[x]}.

void dfs(int x,int l=1)
{
	lvl[x] = l;
	for(auto next : adj[x])
	{
		if(lvl[next] == 0)
		{
			// spanning edge
			dfs(next, l+1);
			dp[x] += dp[next];
		}
		else if(lvl[next] < lvl[x])
		{
			dp[x]++;
		}
		else
		{
			dp[x]--;
		}
	}
	// for {x, p[x]}
	dp[x]--;
	if(dp[x] == 0 and x != 0)
	{
		// {x, p[x]} is a bridge
		bridgec++;
	}
}