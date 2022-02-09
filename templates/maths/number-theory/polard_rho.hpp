// factorize a number fast.
// returns a divisor of n, not necessarily prime
ll pollard_rho(ll n, ll seed) { // pollard-rho divisors factorization
    ll x, y;
    x = y = rand() % (n - 1) + 1;
    ll head = 1, tail = 2;
    while (true) {
        x = (x * x) % n;
        x = (x + seed) % n;
        if (x == y) return n;
        ll d = gcd(max(x - y, y - x), n);
        if (1 < d && d < n) return d;
        if (++head == tail) y = x, tail <<= 1;
    }
}

//returns a list of prime divisors
void factorize(ll n, vector<ll> &divisor) {
    if (n == 1) return;
    // ADD MILLER RABIN HERE
    if (prime_test(n)) divisor.push_back(n);
    else {
        ll d = n;
        while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
        factorize(n / d, divisor);
        factorize(d, divisor);
    }
}