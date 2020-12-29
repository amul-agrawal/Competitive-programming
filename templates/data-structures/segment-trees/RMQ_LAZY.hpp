// Segment Trees for RMQ + Lazy

const ll INF = 1e18;

struct node {
	ll x;
};

class SegmentTrees
{
	vector<node> st, lazy;
	node def;
public:
	SegmentTrees(ll n)
	{
		def = {INF}; 
		st.assign(4*n, {INF});
		lazy.assign(4*n, {INF});
	}
	inline node combine(node a, node b)
	{
		node ret;
		ret.x = min(a.x, b.x);
		return ret;
	}
	void push(int pos)
	{
		if(lazy[pos].x != INF)
		{
			st[(pos<<1LL)] = lazy[pos];
			st[(pos<<1LL)+1] = lazy[pos];
			lazy[(pos<<1LL)] = lazy[pos];
			lazy[(pos<<1LL)+1] = lazy[pos];
			lazy[pos] = def;
		}
	}
	void build(lvi &arr,ll left,ll right,ll pos=1)
	{
		if(left > right) return;
		if(left == right)
		{
			st[pos] = {arr[left]};
		}
		else
		{
			ll mid = (left + right)/2;
			build(arr, left, mid, (pos<<1LL));
			build(arr, mid+1, right, (pos<<1LL)+1);
			st[pos] = combine(st[pos*2], st[pos*2+1]);
		}
	}
	void update(ll l,ll r,ll val,ll left,ll right,ll pos=1)
	{
		if(l > r) return;
		if(l==left && r==right)
		{
			st[pos].x = val;
			lazy[pos] = {val};
		}
		else
		{
			push(pos);
			ll mid = (left + right)/2;
			update(l, min(r,mid), val, left, mid, (pos<<1LL));
			update(max(l,mid+1), r, val, mid+1, right, (pos<<1LL)+1);
			st[pos] = combine(st[pos*2], st[pos*2+1]);
		}
	}
	node query(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return def;
		if(l==left && r==right) return st[pos];
		else
		{
			push(pos);
			ll mid = (left + right)/2;
			return combine(query(l, min(r,mid), left, mid, (pos<<1LL)), query(max(l,mid+1), r, mid+1, right, (pos<<1LL)+1));
		}
	}
};