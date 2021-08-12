// O(nlogn merge overall), usage: Dsu<int> ds;
template<class T = int>
class Dsu
{
	vector<T> parent, size;
	vector<vector<T>> comp;
public:
	Dsu(T n)
	{
		parent.assign(n+2,-1);
		size.assign(n+2,1);
		comp.resize(n+2);
		for(T i=0;i<n+2;i++) comp[i].pb(i);
	}
	T getparent(T x)
	{
		if(parent[x] == -1) return x;
		else return parent[x] = getparent(parent[x]);
	}
	bool IsSameSet(T x,T y) {return getparent(x) == getparent(y);}
	void join(T x,T y)
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


// O(logN) per merge
template<class T = int>
class Dsu
{
	int sts;
	vector<T> parent, size;
public:
	Dsu(T n) {
		sts = n;
		parent.assign(n, -1);
		size.assign(n, 1);
	}
	T getparent(T x) {
		if(parent[x] == -1) return x;
		else return parent[x] = getparent(parent[x]);
	}
	bool IsSameSet(T x,T y) {return getparent(x) == getparent(y);}
	void join(T x,T y) {
		x = getparent(x);
		y = getparent(y);
		if(x == y) return;
		if(size[x] < size[y]) swap(x, y);
		parent[y] = x;
		sts--;
		size[x] += size[y];
	}
	int get_sets(){return sts;}
};
