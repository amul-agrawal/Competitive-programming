<!-- https://codeforces.com/blog/entry/72488 -->
1. zeta/sos => subset sum. `N2^N`
```cpp
for(int i = 0; i < M; i++) {
		for(int mask = (1 << M) - 1; mask >= 0; mask--) {
			if((mask >> i)&1) {
				// RHS still in (i - 1)th state.
				F[mask] += F[mask ^ (1 << i)];
			}
		}
	}
```
2. mobius => f(s) = sum(-1^|s/s'| f(s')), s' is a subset of s. `N2^N`
f(1011) = f(1011) - f(0011) - f(1010) - f(1001) + f(1000) + f(0010) + f(0001) - f(0000)
```cpp
for(int i = 0; i < N; i++) {
    for(int mask = 0; mask < (1 << N); mask++) {
        if((mask & (1 << i)) != 0) {
            f[mask] -= f[mask ^ (1 << i)]
        }
    }
}
```
3. mu^-1 = zeta, zeta^-1 = mu. zeta(mu(f(x))) = f(x) = mu(zeta(f(x))).
4. subset sum conv => f o g(s) = sum(f(s') * g(s\s'), s' is a subset of s), `N^2*2^N`.
The general idea is to build fhat and ghat and then multiply them.

```cpp
// Make fhat[][] = {0} and ghat[][] = {0}
for(int mask = 0; mask < (1 << N); mask++) {
    fhat[__builtin_popcount(mask)][mask] = f[mask];
    ghat[__builtin_popcount(mask)][mask] = g[mask];
}

// Apply zeta transform on fhat[][] and ghat[][]
for(int i = 0; i <= N; i++) {
    for(int j = 0; j < N; j++) {
        for(int mask = 0; mask < (1 << N); mask++) {
            if((mask & (1 << j)) != 0) {
                fhat[i][mask] += fhat[i][mask ^ (1 << j)];
                ghat[i][mask] += ghat[i][mask ^ (1 << j)];
            }
        }
    }
}

// Do the convolution and store into h[][] = {0}
for(int mask = 0; mask < (1 << N); mask++) {
    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= i; j++) {
            h[i][mask] += fhat[j][mask] * ghat[i - j][mask];
        } 
    }
}

// Apply inverse SOS dp on h[][]
for(int i = 0; i <= N; i++) {
    for(int j = 0; j < N; j++) {
        for(int mask = 0; mask < (1 << N); mask++) {
            if((mask & (1 << j)) != 0) {
                h[i][mask] -= h[i][mask ^ (1 << j)];
            }
        }
    }
}
for(int mask = 0; mask < (1 << N); mask++)  fog[mask] = h[__builtin_popcount(mask)][mask];
```
