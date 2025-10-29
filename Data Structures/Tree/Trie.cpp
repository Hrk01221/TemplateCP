struct Trie { //init->Trie T
    struct node {
        int wordCnt = 0, cnt = 0;
        node* next[26] = {};
        ~node() {
            for(int i=0;i<26;i++)
                if(next[i])
                    delete(next[i]);
        }
    };
    node* root;
    Trie(){root = new node();}
    ~Trie(){delete root;}
    void insert(const string &s) {
        node* cur = root;
        for (char c : s) {
            int id = c - 'a';
            if (!cur->next[id])
                cur->next[id] = new node();
            cur = cur->next[id];
            cur->cnt++;
        }
        cur->wordCnt++;
    }
    void erase(const string &s) {
        if(!search(s))return;
        node* cur = root;
        for (char c : s) {
            int id = c - 'a';
            cur = cur->next[id];
            cur->cnt--;
        }
        cur->wordCnt--;
    }
    bool search(const string &s) {
        node* cur = root;
        for (char c : s) {
            int id = c - 'a';
            if (!cur->next[id]) return false;
            cur = cur->next[id];
        }
        return cur->wordCnt > 0;
    }
    int countPrefix(const string &p) {
        node* cur = root;
        for (char c : p) {
            int id = c - 'a';
            if (!cur->next[id]) return 0;
            cur = cur->next[id];
        }
        return cur->cnt;
    }
    string longestPrefix(const string &s) {
        node* cur = root;
        string res = "";
        for (char c : s) {
            int id = c - 'a';
            if (!cur->next[id]) break;
            cur = cur->next[id];
            res.push_back(c);
        }
        return res;
    }
};
