// link: https://codeforces.com/blog/entry/68953

// Number of subset xors: 2^(basis.size())
int basis[d]; // basis[i] keeps the mask of the vector whose f value is i
int sz; // Current size of the basis
void insertVector(int mask) {
	for (int i = 0; i < d; i++) {
		if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)
		if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
			basis[i] = mask;
			++sz;
			
			return;
		}
		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}

// Maximum xor , In this problem, we need to slightly alter the definition of f(b⃗ ).
// Instead of f being the first position with a set bit, let it be the last position with a set bit.
const int N = 1e5 + 10, LOG_A = 20;
int basis[LOG_A];
void insertVector(int mask) {
	for (int i = LOG_A - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;
		if (!basis[i]) {
			basis[i] = mask;
			return;
		}
		mask ^= basis[i];
	}
}
int ans = 0;
for (int i = LOG_A - 1; i >= 0; i--) {
	if (!basis[i]) continue;

	if (ans & 1 << i) continue;

	ans ^= basis[i];
}
