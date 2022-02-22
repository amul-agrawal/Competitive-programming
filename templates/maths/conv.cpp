// https://codeforces.com/contest/914/problem/G
#include<bits/stdc++.h>
using namespace std;
#define ll long long
typedef vector<int> vi;
const int mod = 1e9 + 7;

template<class T = long long>
T modpow(T x,T y,T M=mod)
{
	T ans=1;
	while(y>0)
	{
		if(y&1) ans=(1LL*ans*x)%M;
		x=(1LL*x*x)%M;
		y>>=1;
	}
	return ans;
}
// usage: modpow<ll>(2, 3, mod)

// resize, transform and return.
template <typename T>
struct FWHT {
    static vector<T> fastXor(vector<T> tA, vector<T> tB) {
        transformXor(tA, false);
        transformXor(tB, false);
        for (int i = 0; i < tA.size(); i++) {
            tA[i] = (1LL * tA[i] * tB[i]) % mod;
        }
        transformXor(tA, true);
        return tA;
    }
    static vector<T> fastAnd(vector<T> tA, vector<T> tB) {
        transformAnd(tA, false);
        transformAnd(tB, false);
        for (int i = 0; i < tA.size(); i++) {
            tA[i] = (1LL * tA[i] * tB[i]) % mod;
        }
        transformAnd(tA, true);
        return tA;
    }

private:
    // the size of P must be a power of 2
    static void transformXor(vector<T>& P, bool inverse) {
        int N = int(P.size());
        for (int step = 1; step < N; step <<= 1) {
            for (int i = 0; i < N; i += (step << 1)) {
                for (int j = 0; j < step; j++) {
                    T u = P[i + j];
                    T v = P[i + step + j];
                    P[i + j] = (u + v) % mod;
                    P[i + step + j] = (u - v + mod) % mod;
                }
            }
        }
        if (inverse) {
        	T inv_N = modpow<int>(N, mod - 2);
            for (int i = 0; i < int(P.size()); i++)
                P[i] = (1LL * P[i] * inv_N) % mod;
        }
    }
    // the size of P must be a power of 2
    static void transformAnd(vector<T>& P, bool inverse) {
        int N = int(P.size());
        for (int step = 1; step < N; step <<= 1) {
            for (int i = 0; i < N; i += (step << 1)) {
                for (int j = 0; j < step; j++) {
                    T u = P[i + j];
                    T v = P[i + step + j];
                    if (!inverse) {
                        P[i + j] = v;
                        P[i + step + j] = (v + u) % mod;
                    } else {
                        P[i + j] = (v - u + mod) % mod;
                        P[i + step + j] = u;
                    }
                }
            }
        }
    }
};

const int N = 17;
vi cnt(1 << N);
vi A(1 << N), B(1 << N), C(1 << N), D(1 << N), fib(1 << N);
// A[s] => Sum(cnt[s']*cnt[s\s']) over all subsets s' of s.
// B[s] => cnt[s]
// C[s] => Xor convulation
// D[s] => And Convulation on A, B, C.

void convA() {
	vector<vi> tmp(N + 1, vi(1 << N, 0)), tmp1 = tmp;
	for(int i = 0; i < (1 << N); i++) tmp[__builtin_popcount(i)][i] = cnt[i];
	// zeta
	for(int b = 0; b <= N; b++) {
		for(int i = 0; i < N; i++) {
			for(int mask = (1 << N) - 1; mask >= 0; mask--) {
				if((mask >> i)&1) {
					tmp[b][mask] += tmp[b][mask ^ (1 << i)];
					tmp[b][mask] %= mod;
				}
			}
		}
	}
	// product
	for(int mask = 0; mask < (1 << N); mask++) {
		for(int i = 0; i <= N; i++) {
			for(int j = 0; j <= i; j++) {
				tmp1[i][mask] += (1LL * tmp[j][mask] * tmp[i - j][mask]) % mod;
				tmp1[i][mask] %= mod;
			}
		}
	}
	// inverse zeta
	for(int b = 0; b <= N; b++) {
		for(int i = 0; i < N; i++) {
			for(int mask = (1 << N) - 1; mask >= 0; mask--) {
				if((mask >> i)&1) {
					tmp1[b][mask] -= tmp1[b][mask ^ (1 << i)];
					tmp1[b][mask] += mod;
					tmp1[b][mask] %= mod;
				}
			}
		}
	}
	for(int mask = 0; mask < (1 << N); mask++) A[mask] = tmp1[__builtin_popcount(mask)][mask];
}

void convB() {
	B = cnt;
}

void convC() {
	FWHT<int> ds;
	C = ds.fastXor(cnt, cnt);
}

void convD() {
	FWHT<int> ds;
	D = ds.fastAnd(ds.fastAnd(A, B), C);
}

void mfib(vi &v) {
	for(int i = 0; i < (1 << N); i++) v[i] = (1LL * fib[i] * v[i]) % mod;
}

signed main() {
	fib[0] = 0; fib[1] = 1;
	for(int i = 2; i < (1 << N); i++) fib[i] = (fib[i-1] + fib[i-2]) % mod;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		int x; cin >> x;
		cnt[x]++;
	}
	convA(); mfib(A);
	convB(); mfib(B); 
	convC(); mfib(C);
	convD();
	ll ans = 0;
	for(int i = 0; i < N; i++) ans = (ans + D[1 << i]) % mod;
	cout << ans << endl;
	return 0;
}