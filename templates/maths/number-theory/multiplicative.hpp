//credits: https://github.com/AnimeshSinha1309/algorithms-notebook/blob/966b970ca1e866ce24b94efd626ace701a9e13e7/code/NumberTheory.hpp
class Multiplicative {
// This is the definition for mu
#define fn_prime_values(prime) (-1)
#define fn_non_coprime(num, prime) (0)
   public:
    int size;
    vector<int> fn;
    vector<int> primes;
    vector<int> lowest_prime_factor;
 
    Multiplicative(int size) {
        size = size;
        lowest_prime_factor = vector<int>(size, 0);
        fn = vector<int>(size, 0);
        // https://stackoverflow.com/questions/34260399
        // linear sieve
        for (int i = 2; i < size; i++)
            lowest_prime_factor[i] = i;
        // put any specific initialization code here like
        fn[1] = 1;
        for (int i = 2; i < size; i++) {
            if (lowest_prime_factor[i] == i) {
                fn[i] = fn_prime_values(i);
                primes.push_back(i);
            }
 
            for (auto p : primes) {
                int ith_multiple = i * p;
                if (ith_multiple >= size)
                    break;
 
                lowest_prime_factor[ith_multiple] =
                    min(lowest_prime_factor[i], p);
 
                if (i % p) {
                    fn[ith_multiple] = fn[i] * fn[p];
                } else {
                    fn[ith_multiple] = fn_non_coprime(i, p);
                    break;
                }
            }
        }
    }
};
