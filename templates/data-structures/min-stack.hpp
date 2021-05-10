template<class T = long long>
class MinStack
{
	stack<pair<T, T>> st;
public:
	void add(T new_elem)
	{
		// change operation to max and you get MaxStack
		T new_min = st.empty() ? new_elem : min(new_elem, st.top().second);
		st.push({new_elem, new_min});
	}
	T remove()
	{
		T removed_element = st.top().first;
		st.pop();
		return removed_element;
	}
	T query()
	{
		return st.top().second;
	}
};
// usage: MinStack<int> mst; mst.add(x);