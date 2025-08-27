deg.assign(n + 1, 0);

for (int i = 0; i < e; i++){
	//input graph
	deg[v] += 1;
}
for (int i = 1; i <= n; i++)
	if(!deg[i])q.push(i);
while (!q.empty()) {
	int v = q.front();q.pop();
	order.pb(v);
	for (auto it : graph[v]) {
		deg[it]--;
		if (!deg[it])q.push(it);
	}
}
if(order.size()==n)for(auto it : order)cout << it << " ";
