int CSOD(int n){
	int i=1;
	int ans = 0;
	while(i<=n){
		int q = n/i;
		int j = (n/q) + 1;
		int s = sum(i,j-1);//i + (i+1) + ...(j-1)
		ans += s*q;
	}
	return ans;
}