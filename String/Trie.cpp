struct TrieNode
{
    TrieNode* childNode[26];
    bool wordEnd;
    TrieNode(){
        wordEnd = 0;
        for(int i=0;i<26;i++){
            childNode[i] = NULL;
        }
    }
};
void insert_key(TrieNode* root , string &key){
    TrieNode *currNode = root;
    for(auto c : key){
         if(currNode->childNode[c-'a']==NULL){
            TrieNode* newNode = new TrieNode();
            currNode->childNode[c-'a']= newNode;
            currNode = currNode->childNode[c-'a'];
         }
         currNode = currNode -> childNode[c-'a'];
    }
    currNode->wordEnd = 1;
}
bool search_key(TrieNode *root , string &key){
    TrieNode *currNode = root;
    for(auto c : key){
        if(currNode->childNode[c-'a']==NULL) return 0;
        currNode = currNode->childNode[c-'a'];
    }
    return (currNode->wordEnd);
}
