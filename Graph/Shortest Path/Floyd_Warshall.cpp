int dis[N][N];
void init(int n){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==j)dis[i][j] = 0;
            else dis[i][j] = 1e18;
        }
    }
}
void floyd_Warshall(int n){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j] = min(dis[i][j] , dis[i][k]+dis[k][j]);
}