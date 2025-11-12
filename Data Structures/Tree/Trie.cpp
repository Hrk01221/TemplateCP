const int SZ = 26;
char INIT = 'a';
struct Node {
    int wordCnt = 0, cnt = 0;
    Node* next[SZ] = {};
};
struct Trie { //init->Trie T
    Node* root;
    Trie(){root = new Node();}
    void insert(const string &s) {
        Node* curr = root;
        for (char c : s) {
            int id = c - INIT;
            if (!curr->next[id])
                curr->next[id] = new Node();
            curr = curr->next[id];
            curr->cnt++;
        }
        curr->wordCnt++;
    }
    void erase(const string &s) {
        if(!search(s))return;
        Node* curr = root;
        for (char c : s) {
            int id = c - INIT;
            curr = curr->next[id];
            curr->cnt--;
        }
        curr->wordCnt--;
    }
    bool search(const string &s) {
        Node* curr = root;
        for (char c : s) {
            int id = c - INIT;
            if (!curr->next[id]) return false;
            curr = curr->next[id];
        }
        return curr->wordCnt > 0;
    }
    int countPrefix(const string &p) {
        Node* curr = root;
        for (char c : p) {
            int id = c - INIT;
            if (!curr->next[id]) return 0;
            curr = curr->next[id];
        }
        return curr->cnt;
    }
    string longestPrefix(const string &s) {
        Node* curr = root;
        string res = "";
        for (char c : s) {
            int id = c - INIT;
            if (!curr->next[id]) break;
            curr = curr->next[id];
            res.push_back(c);
        }
        return res;
    }
};
