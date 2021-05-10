// advantage: O(1) RMQ DS
// disadvantage: cannot handle array mutability
template<class T = long long>
class SparseTable
{
	vector<vector<T>> st;
	vector<int> log;
	int n, logn;
public:
	SparseTable(int N = 1e6 + 13, int logN = 20)
	{
		st.resize(N, vector<T>(logN));
		log.resize(N + 1, 0);
		for(int i=2;i<=N;i++) log[i] = log[i/2] + 1;
		n = N;
		logn = logN;
	}
	// define your function here, eg: max, min, sum
	T f(T left,T right) 
	{
		return max(left, right);
	}
	void build(vector<T> arr) 
	{
		for (int i = 0; i < n; ++i)
			st[i][0] = arr[i];

		for(int j=1; j <= logn; j++)
			for (int i = 0; i + (1 << j) <= n; i++)
		        st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
	}
	T query(int L, int R)
	{
		int j = log[R - L + 1];
		return f(st[L][j], st[R - (1 << j) + 1][j]);
	}
};