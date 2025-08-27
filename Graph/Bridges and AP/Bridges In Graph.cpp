const int Mx_N = 1e4 + 10;
int Time,cnt;
vector<int>graph[Mx_N],disc(Mx_N),low(Mx_N);
vector<pii>bridges;
void dfsBr(int vertex,int parent){
	low[vertex] = disc[vertex] = ++Time;
	for(auto child : graph[vertex]){
		if(child == parent)continue;
		if(!disc[child]){
			dfsBr(child,vertex);
			if(disc[vertex] < low[child]){
				bridges.pb({min(vertex,child),max(vertex,child)});
			}
			low[vertex] = min(low[vertex],low[child]);
		}
		else low[vertex] = min(low[vertex],disc[child]);
	}
}
void Br(int n){
	Time = 0;
	for(int i=1;i<=n;i++)
		if(!disc[i])
			dfsBr(i,i);
	cnt = bridges.size();
}
void clear(int n){
	for(int i=1;i<=n;i++){
		graph[i].clear();
		disc[i]=low[i]=0;
		bridges.clear();
	}
}