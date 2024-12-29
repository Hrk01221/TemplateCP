void build(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		pref[i][j] = pref[i-1][j] + pref[i][j-1]
				   - pref[i-1][j-1] + a[i][j];
}
int query(int x1,y1,x2,y2){
	return pref[x2][y2]-pref[x1-1][y2]
   		  -pref[x2][y1-1]+pref[x1-1][y1-1];
}
void update(int a1,b1,a2,b2){
	pref[a1][b1]++;pref[a2+1][b2+1]++;
	pref[a1][b2+1]--;pref[a2][b1+1]--;
}