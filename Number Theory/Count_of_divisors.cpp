int count_of_divisors(int n){
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