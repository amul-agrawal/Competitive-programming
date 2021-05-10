template<class T = long long>
class MinQueue
{
	deque<pair<T, T>> q;
	int cnt_added = 0;
	int cnt_removed = 0;
public:
	void add(T new_element)
	{
		// change '>' to '<' and you get max-queue
		while (!q.empty() && q.back().first > new_element)
		    q.pop_back();
		q.push_back({new_element, cnt_added});
		cnt_added++;
	}
	T remove()
	{
		T removed_element;
		if (!q.empty() && q.front().second == cnt_removed) {
			removed_element = q.front().first;
		    q.pop_front();
		}
		cnt_removed++;
		return removed_element;
	}
	T query()
	{
		return q.front().first;
	}
};
// usage: MinQueue<int> msq; msq.add(x);