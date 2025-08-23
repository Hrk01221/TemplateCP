const int SZ = 26;
char INIT = 'a';
struct Trie { //init->Trie T
    struct Node {
        int wordCnt = 0, cnt = 0;
        Node* next[SZ] = {};
    };
    Node* root;
    Trie(){root = new Node();}
    void insert(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int id = c - INIT;
            if (!cur->next[id])
                cur->next[id] = new Node();
            cur = cur->next[id];
            cur->cnt++;
        }
        cur->wordCnt++;
    }
    void erase(const string &s) {
        if(!search(s))return;
        Node* cur = root;
        for (char c : s) {
            int id = c - INIT;
            cur = cur->next[id];
            cur->cnt--;
        }
        cur->wordCnt--;
    }
    bool search(const string &s) {
        Node* cur = root;
        for (char c : s) {
            int id = c - INIT;
            if (!cur->next[id]) return false;
            cur = cur->next[id];
        }
        return cur->wordCnt > 0;
    }
    int countPrefix(const string &p) {
        Node* cur = root;
        for (char c : p) {
            int id = c - INIT;
            if (!cur->next[id]) return 0;
            cur = cur->next[id];
        }
        return cur->cnt;
    }
    string longestPrefix(const string &s) {
        Node* cur = root;
        string res = "";
        for (char c : s) {
            int id = c - INIT;
            if (!cur->next[id]) break;
            cur = cur->next[id];
            res.push_back(c);
        }
        return res;
    }
};