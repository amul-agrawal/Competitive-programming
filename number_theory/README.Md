# Number Theory Notes
## Basic modular operations
```
(a + b + c)%m = ((a+b)%m + c)%m
(a*b*c)%m = ((a*b)%m * c)%m
```
## GCD / LCM
```cpp
int gcd(int a, int b) {
  if(b == 0) return a;
  else return gcd(b, a%b);
}
lcm(a, b) = (a*b)/gcd(a,b);
// c++ has inbuilt function for gcd
__gcd(a, b);
// for c++17 and higher versions.
gcd(a, b); lcm(a, b);
```
## Sieve and it's use cases
The main idea is the following. Suppose we want to find all primes between 2 and 50.
Iterate from 2 to 50. We start with 2. Since it is not checked, it is a prime number. Now check all numbers that are multiple of $2$ except 2. Now we move on, to number 3. It's not checked, so it is a prime number.
Now check all numbers that are multiple of $3$, except 3. Now move on to 4. We see that this is checked - this is a multiple of 2! So 4 is not a prime. We continue doing this.
```cpp
const int N = 1e6 + 13;
vector<bool> isprime(N, true);
isprime[0]=isprime[1]=false;
for(int i=2;i<N;i++) {
  if(isprime[i]) {
    for(int j=2*i;j<N;j+=i) {
      isprime[j] = false;
    }
  }
}
```
`Complexity: O(Nlog(log(N)))`
1. With Sieve preprocessing you can find all prime factors in just O(log(N)). 
## modular exponentiation
`a^b % m`
```cpp
int modpow(int a, int b, int m) {
  int ans=1;
  while(b>0) {
    if(b&1) {
      ans = (ans*a)%m;
    }
    b>>=1;
    a=(a*a)%m;
  }
  return ans;
}
```
1. `a^b % m = a^(b%m) % m` given `__gcd(a, m) == 1`, from Euler's generalization to fermat's little theorem.
  
## Diophantine equation solution
find `(x, y)` where `ax + by = c`
[cp algo blog](https://cp-algorithms.com/algebra/linear-diophantine-equation.html)
## Using Log
Suppose you want to maintain product of very large numbers, but the product doesn't fit in integer limits in c++. You can use log here.
1. Given `a_1, a_2, a_3, ... a_n`, `b_1, b_2, b_3, ... b_n` and you want to find `a_1 * a_2 * a_3 ... a_n`/`b_1 * b_2 * b_3, ... b_n`. 
What you can do is, store `log(a_1), log(a_2), log(a_3) ... log(a_n)` and same for `b_i's`. Now the product of `a_i's` is `sum(log(a_i)) from i=1 to i=n`, same for `b_i's`. Now if we observe the result of our qs is `pow(base, sum(log(a_i)) - sum(log(b_i)))`.
## Euler's totient function
In number theory, Euler's totient function counts the positive integers up to a given integer n that are relatively prime to n. It is written using the Greek letter phi.
For example, the totatives of n = 9 are the six numbers 1, 2, 4, 5, 7 and 8. They are all relatively prime to 9, but the other three numbers in this range, 3, 6, and 9 are not, since gcd(9, 3) = gcd(9, 6) = 3 and gcd(9, 9) = 9. Therefore, φ(9) = 6. As another example, φ(1) = 1 since for n = 1 the only integer in the range from 1 to n is 1 itself, and gcd(1, 1) = 1.
```cpp
// O(root(n))
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}
```
1. if p is prime
    - `phi(p) = p - 1`
    - `phi(p^k) = p^k - p^(k-1)`
2. if a and b are relatively prime
    - `phi(a*b) = phi(a) * phi(b)`
## Fermat's little theorem and Euler's Generalization of it.
fermat's theorem: `(a^(p-1)) % p = 1`
Euler's generalization: `(a^(phi(p))) % p = 1`

## Modular Inverse
A modular multiplicative inverse of an integer a is an integer x such that a⋅x is congruent to 1 modular some modulus m. To write it in a formal way: we want to find an integer x so that `ax % m = 1`
It can be proven that the modular inverse exists if and only if a and m are relatively prime (i.e. gcd(a,m)=1).
### Using Extended Euclidean algorithm
```cpp
int x, y;
// solution for ax + my = 1
int g = extended_euclidean(a, m, x, y);
if (g != 1) {
    cout << "No solution!";
}
else {
    x = (x % m + m) % m;
    cout << x << endl;
}
```
### Using Binary Exponentiation
`a^(phi(m)-1) % m = a^-1 % m`, given a and m are coprime, but a and m will have to coprime for modular inverse to exist.
