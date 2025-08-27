int count_of_divisors(int n){//O(sqrt(N))
	int ans = 1;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			int e =0;
			while(n%i==0){
				e++;
				n/=i;
			}
			ans *= (e+1);
		}
	}
	if(n > 1)ans *= 2;
	return ans;
}
int sum_of_divisors(int n){//O(sqrt(N))
	int total = 1;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			int exp = 0, sum = 1, p = 1;
			while(n%i==0){
				exp++;
				n/=i;
			}
            for (int j = 1; j <= exp; j++) {
                p *= i;
                sum += p;
            }
			total *= sum;
		}
	}
	if(n>1)total *= (n+1);
	return total;
}
//Number Of divisors in O(n^1/3)
...sieve Code Here...
bool isPrime(int n){
  for(int i=2;i*i<=n;i++)
    if(n%i==0)return 0;
  return 1;
}
int countDivisors(int N) {
    int ans = 1;
    int temp = N;
    for (int p : primes) {
        if (1LL * p * p * p > N) break;
        int cnt = 1;
        while (temp % p == 0) {
            temp /= p;
            cnt++;
        }
        ans *= cnt;
    }
    if (temp == 1) return ans;
    if (isPrime(temp))ans *= 2;
    else {
        int sq = sqrt(temp);
        if (sq * sq == temp && isPrime(sq))ans *= 3;
        else ans *= 4;
    }
    return ans;
}