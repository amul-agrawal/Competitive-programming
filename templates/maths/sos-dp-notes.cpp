#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9 + 7;
#define all(c) (c).begin(), (c).end()
typedef vector<int> vi;
typedef vector<vi> vvi;


const int M = 5;
int F[(1<<M)];

void base() {
	for(int mask = 0; mask < (1 << M); mask++) {
		F[mask] = mask;
	}
}

void print() {
	for(int mask = 0; mask < (1 << M); mask++) {
		cout << F[mask] << " ";
	}
	cout << endl;
} 

// SOS dp
// S(mask, i) => varying bits 0 .. i
// S(1011, 1) => 1000 + 1001 + 1010 + 1011
// S(mask, i) => S(mask, i-1)  ith bit OFF. (No change required)
// S(mask, i) => [ith bit 1]S(mask, i) + [ith bit 0]S(mask ^ (1 << i), i-1)  ith bit ON
void sos_from_base() {
	for(int i = 0; i < M; i++) {
		for(int mask = (1 << M) - 1; mask >= 0; mask--) {
			if((mask >> i)&1) {
				// RHS still in (i - 1)th state.
				F[mask] += F[mask ^ (1 << i)];
			}
		}
	}
}

// Given: S(mask, M - 1), find S(mask, -1)
// S(mask, i) => S(mask, i + 1)    									(i + 1)th bit is 0.
// S(mask, i) => S(mask, i + 1) - S(mask ^ (1 << (i + 1)), i + 1)   (i + 1)th bit is 1.
// So basically for 1s case we are removing cases when (i + 1)th bit was zero.
void base_from_sos() {
	// On iteration i: (i+1, M-1) have been fixed.
	// for(int i = M - 2; i >= -1; i--) {
	// 	for(int mask = (1 << M) - 1; mask >= 0; mask--) {
	// 		if((mask >> (i + 1))&1) {
	// 			// RHS still in (i + 1)th state.
	// 			F[mask] -= F[mask ^ (1 << (i + 1))];
	// 		}
	// 	}
	// }

	// On iteration i: (i, M-1) have been fixed.
	for(int i = M - 1; i >= 0; i--) {
		for(int mask = (1 << M) - 1; mask >= 0; mask--) {
			if((mask >> i)&1) {
				// RHS still in (i + 1)th state.
				F[mask] -= F[mask ^ (1 << i)];
			}
		}
	}
}

// Superset dp
// same as sos dp but vary 0 now.
void sum_over_superset() {
	for(int i = 0; i < M; i++) {
		for(int mask = (1 << M) - 1; mask >= 0; mask--) {
			if(!((mask >> i)&1)) {
				F[mask] += F[mask ^ (1 << i)];
			}
		}
	}
}

// Superset dp => base
// Same as sos => base, but we will now remove (i + 1)th bit is 1.
void base_from_sum_over_superset() {
	// On iteration i: (i, M-1) have been fixed.
	for(int i = M - 1; i >= 0; i--) {
		for(int mask = 0; mask < (1 << M); mask++) {
			if(!((mask >> i)&1)) {
				// RHS still in (i + 1)th state.
				F[mask] -= F[mask ^ (1 << i)];
			}
		}
	}
}

int main() 
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    base();
    cout << "Base" << endl;
    print();

    cout << "Sos" << endl;
    sos_from_base();
	print();

	cout << "Base from Sos" << endl;
    base_from_sos();
	print();

	cout << "Superset dp" << endl;
	sum_over_superset();
	print();

	cout << "Base from superset" << endl;
	base_from_sum_over_superset();
	print();

	return 0;
}


// step1: cnt[mask] => elements with mask
// step2: F[mask] => number of sets with and >= mask (superset dp)
// step3: inclusion exclusion
// F[000] - F[001] - F[010] - F[100] + F[110] + F[011] + F[101] - F[111]
