// O(nlogn merge overall)
class Dsu
{
	vector<int> parent, size;
	vector<vector<int>> comp;
public:
	Dsu(int n)
	{
		parent.assign(n+2,-1);
		size.assign(n+2,1);
		comp.resize(n+2);
		for(int i=0;i<n+2;i++) comp[i].pb(i);
	}
	int getparent(int x)
	{
		if(parent[x] == -1) return x;
		else return parent[x] = getparent(parent[x]);
	}
	bool IsSameSet(int x,int y) {return getparent(x) == getparent(y)};
	void join(int x,int y)
	{
		x = getparent(x);
		y = getparent(y);
		if(x == y) return;
		if(size[x] < size[y]) swap(x, y);
		for(auto now:comp[y])
		{
			parent[now] = x;
			comp[x].pb(now);
		}
		comp[y].clear();
		size[x] += size[y];
	}
};


// O(logN)
class Dsu
{
	vector<int> parent, size;
public:
	Dsu(int n)
	{
		parent.assign(n+2,-1);
		size.assign(n+2,1);
	}
	int getparent(int x)
	{
		if(parent[x] == -1) return x;
		else return parent[x] = getparent(parent[x]);
	}
	bool IsSameSet(int x,int y) {return getparent(x) == getparent(y)};
	void join(int x,int y)
	{
		x = getparent(x);
		y = getparent(y);
		if(x == y) return;
		if(size[x] < size[y]) swap(x, y);
		parent[y] = x;
		size[x] += size[y];
	}
};
