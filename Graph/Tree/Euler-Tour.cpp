int timer = 0;
    function<void(int, int)> dfs = [&](int v, int p) {
        in[v] = ++timer;
        for (auto it : tree[v]) {
            if (it == p) continue;
            dfs(it, v);
        }
        out[v] = timer;
    };
    dfs(1, 0);
