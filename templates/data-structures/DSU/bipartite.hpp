// Dsu for bipartitie graphs, more information: https://codeforces.com/edu/course/2/lesson/7/2
// 1. given nodes, we are adding edges.
// 2. we want to check if two nodes belong to same bipartite component or not.
template<class T = int>
class Dsu
{
	vector<T> parent, size, L;
public:
	Dsu(T n)
	{
		parent.assign(n+2, -1);
		size.assign(n+2, 1);
		L.assign(n+2, 0);
	}
	T getparent(T x)
	{
		if(parent[x] == -1) return x;
		T y = getparent(parent[x]);
		L[x] ^= L[parent[x]];
		parent[x] = y;
		return y;
	}
	void join(T x,T y)
	{
		T cx = x, cy = y;
		x = getparent(x);
		y = getparent(y);
		if(x == y) return;
		if(size[x] < size[y]) swap(x, y);
		parent[y] = x;
		L[y] = 1 ^ L[cy] ^ L[cx];
		size[x] += size[y];
	} 
	bool SameColor(T x,T y)
	{
		getparent(x);
		getparent(y);
		return L[x] == L[y];
	}
};