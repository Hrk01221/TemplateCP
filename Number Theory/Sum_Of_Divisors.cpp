int sum_of_divisor(int n){
    int ans = 1;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            int e = 0 , gg=1,sum = 1;
            while(n%i==0){
                n/=i,e++;
                gg *= i;
                sum += gg;
            }
            ans *= sum;
        }
    }
    if(n > 1)
        ans *= (1+n);
    return ans;
}