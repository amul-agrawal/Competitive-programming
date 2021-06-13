// https://docs.google.com/presentation/d/1eqhE23HTkohxiAN9Fq0FSLae1BF1WQHegBofv6PMyJo/edit#slide=id.gb2408ab330_0_37


// GCD
// - gcd(x, 0) = x
// - gcd(ma, mb) = m*gcd(a,b)
// - gcd(a + mb, b) = gcd(a, b)


// Euler's Theorem
// - a ^ (phi(m)) = 1(mod m), where phi(m) is number of coprimes to m less than m.
// phi(prime) = prime - 1.

// stars and bars: (x_1 + x_2 .. x_n = r) s.t. x_i >= 0.
// solution: (n+r-1)C(r-1).

// Trick
// Count number of arrays s.t. a[i+1] >= a[i] and 1 <= a[i] <= k.
// difference array: 1 <= i < n, dif[i] > 0. dif[i] = a[i] - a[i-1].
// Sum of diff array <= k - 1
// x_1, x_2, .. x_n = dif_1, dif_2, .. dif_n.
// create x_0 = which denotes the 1st character. 
// create x_n+1 = which denotes the left sum to k - 1.
// therefore, answer = (n+1+k-1)C(n)


// Upper bound for number of divisors of x is x^1/3.


// factorization
factorization.push_back(1);
for (int d = 2; d * d <= n; d++) 
{
     while (n % d == 0) 
		 {
        factorization.push_back(d);
        n /= d;
     }
}
if (n > 1)
   factorization.push_back(n);

// divisors
for(int i=1;i<=n;i++)
{
	for(int j=i;j<=n;j+=i)
	{
		div[j] += 1;
	}
}

// sieve 
vb is_prime(n+1, false);
for(int i=2;i<=n;i++)
{
	if(is_prime[i])
	{
		for(int j=2*i;j<=n;j+=i)
		{
			is_prime[j] = false;
		}
	}
}