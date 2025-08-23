struct BinaryTrie {
    struct Node {
        int cnt = 0, end = 0;
        Node* nxt[2]{};
    };
    Node* root; int B;
    BinaryTrie(int b = 30) { B = b; root = new Node(); }
    //insert,erase,search same as Trie
    int xorMax(int x) {
        Node* cur = root; int ans = 0;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (cur->nxt[!b] && cur->nxt[!b]->cnt) {
                ans |= 1 << i; cur = cur->nxt[!b];
            } else cur = cur->nxt[b];
        }
        return ans;
    }
    int xorMin(int x) {
        Node* cur = root; int ans = 0;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (cur->nxt[b] && cur->nxt[b]->cnt) cur = cur->nxt[b];
            else { ans |= 1 << i; cur = cur->nxt[!b]; }
        }
        return ans;
    }
    int lessThan(int x, int k) { // count {val : (val^x)<k}
        Node* cur = root; int ans = 0;
        for (int i = B; i >= 0 && cur; i--) {
            int b1 = (x >> i) & 1, b2 = (k >> i) & 1;
            if (b2) {
                if (cur->nxt[b1]) ans += cur->nxt[b1]->cnt;
                cur = cur->nxt[!b1];
            } else cur = cur->nxt[b1];
        }
        return ans;
    }
};