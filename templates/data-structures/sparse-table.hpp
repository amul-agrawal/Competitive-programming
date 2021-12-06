// advantage: O(1) RMQ DS
// disadvantage: cannot handle array mutability
template<class T = long long>
class SparseTable
{
	vector<vector<T>> st;
	vector<int> log;
	int N, logN;
public:
	// define your function here, eg: max, min, sum
	T f(T left,T right) {
		return max(left, right);
	}
	SparseTable(vector<T> arr, int n1 = 1e6 + 13) {
		logN = log2(n1) + 1; N = n1;
		st.resize(N + 1, vector<T>(logN + 1));
		log.resize(N + 1, 0);
		for(int i=2;i<=N;i++) 
			log[i] = log[i/2] + 1;
		for(int i = 1; i <= N; i++) 
			st[i][0] = arr[i];
		for(int j=1; j <= logN; j++)
			for (int i = 1; i + (1 << j) <= N + 1; i++)
		        st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
	}
	T query(int L, int R) {
		int j = log[R - L + 1];
		return f(st[L][j], st[R - (1 << j) + 1][j]);
	}
};
