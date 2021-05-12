template<class T = long long>
class SqrtD
{
	int n, len;
	vector<T> a, b;
public:
	SqrtD(vector<T> arr)
	{
		a = arr;
		n = a.size();
		b.resize(n);
		len = (int)sqrt((long double)n) + 1;
	}
	void pre()
	{
		for (int i = 0; i < n; ++i)
			b[i/len] += a[i];
	}
	void update(int idx, T val)
	{
		b[idx/len] -= a[idx];
		a[idx] = val;
		b[idx/len] += a[idx];

	}
	T query(int l, int r)
	{
		T sum = 0;
		int c_l = l / len,   c_r = r / len;
		if (c_l == c_r)
		    for (int i=l; i<=r; ++i)
		        sum += a[i];
		else {
		    for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
		        sum += a[i];
		    for (int i=c_l+1; i<=c_r-1; ++i)
		        sum += b[i];
		    for (int i=c_r*len; i<=r; ++i)
		        sum += a[i];
		}
		return sum;
	}
};