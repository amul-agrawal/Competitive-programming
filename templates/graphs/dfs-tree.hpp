// DFS tree: https://codeforces.com/blog/entry/68138

// imp property: if you want to orient edges edges of undirected graph such that it still stays connected.
// orient span edges accordingly and back edges accordingly.

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
			// sum of all edge originations in the subtree of x
			dp[x] += dp[next];
		}
		else if(lvl[next] < lvl[x])
		{
			// found the first edge and hence adding a new edge origination.
			dp[x]++;
		}
		else
		{
			// found the second vertex here only and hence, 
			// have to remove some edge originations.
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
