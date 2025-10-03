struct BinaryTrie {
    struct Node {
        int cnt = 0, end = 0;
        Node* nxt[2] {};
        ~Node() {
            if (nxt[0]) delete nxt[0];
            if (nxt[1]) delete nxt[1];
        }
    };

    Node* root;
    int B;

    BinaryTrie(int b = 32) {
        B = b;
        root = new Node();
    }

    ~BinaryTrie() {
        delete root;
    }

    void insert(int x) {
        Node* cur = root;
        cur->cnt++;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!cur->nxt[b]) cur->nxt[b] = new Node();
            cur = cur->nxt[b];
            cur->cnt++;
        }
        cur->end++;
    }

    void erase(int x) {
        Node* cur = root;
        cur->cnt--;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            Node* next = cur->nxt[b];
            next->cnt--;
            if (next->cnt == 0) {
                delete next;
                cur->nxt[b] = nullptr;
                return;
            }
            cur = next;
        }
        cur->end--;
    }

    int xorMax(int x) {
        Node* cur = root;
        int ans = 0;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (cur->nxt[!b] && cur->nxt[!b]->cnt) {
                ans |= 1 << i;
                cur = cur->nxt[!b];
            } else cur = cur->nxt[b];
        }
        return ans;
    }

    int xorMin(int x) {
        Node* cur = root;
        int ans = 0;
        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (cur->nxt[b] && cur->nxt[b]->cnt) cur = cur->nxt[b];
            else {
                ans |= 1 << i;
                cur = cur->nxt[!b];
            }
        }
        return ans;
    }

    int lessThan(int x, int k) { // count {val : (val^x)<k}
        Node* cur = root;
        int ans = 0;
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
