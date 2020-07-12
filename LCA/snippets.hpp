// ALWAYS DEFINE LOGN = 1 + REQUIREMENT


// dfs before lcs
// requirements:-
// 1) depth array declared
// 2) par array	declared
// 3) logN defined
template <typename T>
void dfs(T x,T pr=0,T d=0)
{
	depth[x]=d;
	par[x][0]=pr;
	for(int i=1;i<logN;i++)
	{
		par[x][i]=par[par[x][i-1]][i-1];
	}
	for(auto next:adj[x])
	{
		if(next!=pr)
		{
			dfs(next,x,d+1);
		}
	}
}

// lowest common ancestor of u and v.
// requirements:-
// 1) depth array
// 2) par array
// 3) logN defined
template <typename T>
T lca(T u,T v)
{
	if(depth[u]>depth[v]) swap(u,v);
	T diff=depth[v]-depth[u];
	for(int i=0;i<logN;i++)
	{
		if((1<<i)&diff) v=par[v][i];
	}
	if(u==v) return u;
	for(int i=logN-1;i>=0;i--)
	{
		if(par[u][i]!=par[v][i])
		{
			u=par[u][i];
			v=par[v][i];
		}
	}
	return par[u][0];
}

// kthpar of x
// requirements:-
// 1) logN defined
// 2) par array defined
template <typename T>
T kthpar(T x,T k)
{
	T ret=x;
	for(int i=0;i<logN;i++)
	{
		if(k&(1<<i))
		{
			ret=par[ret][i];
		}
	}
	return ret;
}
