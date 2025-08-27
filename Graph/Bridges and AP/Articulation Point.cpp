const int Mx_N = 1e4 + 10;
int Time,cnt;
vector<int>graph[Mx_N],disc(Mx_N),low(Mx_N),ap(Mx_N);
int dfsAp(int vertex,int parent){
	int children = 0;
	low[vertex] = disc[vertex] = ++Time;
	for(auto child : graph[vertex]){
		if(child == parent)continue;
		if(!disc[child]){
			children++;
			dfsAp(child,vertex);
			if(disc[vertex] <= low[child])ap[vertex]=1;
			low[vertex] = min(low[vertex],low[child]);
		}
		else low[vertex] = min(low[vertex],disc[child]);
	}
	return children;
}
void AP(int n){
	Time = 0;
	for(int i=1;i<=n;i++)
		if(!disc[i])
			ap[i]=dfsAp(i,i)>1;
	cnt=0;
	for(int i=1;i<=n;i++)if(ap[i])cnt++;
}
void clear(int n){
	for(int i=1;i<=n;i++){
		graph[i].clear();
		disc[i]=low[i]=ap[i]=0;
	}
}
