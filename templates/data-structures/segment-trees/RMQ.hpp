// Segment Trees for RMQ.

const ll INF = 1e18;

struct node {
	ll x;
};

class SegmentTrees
{
	vector<node> st;
public:
	SegmentTrees(ll n)
	{
		st.assign(4*n, {INF});
	}
	inline node combine(node a, node b)
	{
		node ret;
		ret.x = min(a.x, b.x);
		return ret;
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
	void update(ll idx,ll val,ll left,ll right,ll pos=1)
	{
		if(left > right) return;
		if(left == right)
		{
			st[pos].x = val;
		}
		else
		{
			ll mid = (left + right)/2;
			if(idx <= mid) update(idx, val, left, mid, (pos<<1LL));
			else update(idx, val, mid+1, right, (pos<<1LL) + 1);
			st[pos] = combine(st[pos*2], st[pos*2+1]);
		}
	}
	node query(ll l,ll r,ll left,ll right,ll pos=1)
	{
		if(l>r) return {INF};
		if(l==left && r==right) return st[pos];
		else
		{
			ll mid = (left + right)/2;
			return combine(query(l, min(r,mid), left, mid, (pos<<1LL)), query(max(l,mid+1), r, mid+1, right, (pos<<1LL)+1));
		}
	}
};