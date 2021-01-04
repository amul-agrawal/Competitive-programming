// 
class Dsu
{
	vector<int> parent, size, L;
public:
	Dsu(int n)
	{
		parent.assign(n+2, -1);
		size.assign(n+2, 1);
		L.assign(n+2, 0);
	}
	int getparent(int x)
	{
		if(parent[x] == -1) return x;
		int y = getparent(parent[x]);
		L[x] ^= L[parent[x]];
		parent[x] = y;
		return y;
	}
	void join(int x,int y)
	{
		int cx = x, cy = y;
		x = getparent(x);
		y = getparent(y);
		if(x == y) return;
		if(size[x] < size[y]) swap(x, y);
		parent[y] = x;
		L[y] = 1 ^ L[cy] ^ L[cx];
		size[x] += size[y];
	} 
	bool SameColor(int x,int y)
	{
		getparent(x);
		getparent(y);
		return L[x] == L[y];
	}
};