#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Trie {
private :
struct TrieNode{
    unordered_map <char,TrieNode*> children;
    bool is_end_of_word;
    TrieNode(){
        is_end_of_word=false;
    }
};
TrieNode* root;
public:
    Trie() {
        root=new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* mode=root;
        for(char c:word){
            if(mode->children.find(c)==mode->children.end()){
                mode->children[c]=new TrieNode();
            }
            mode=mode->children[c];
        }
        mode->is_end_of_word=true;
    }
    
    bool search(string word) {
        TrieNode* Node=search_word(word);
        return Node!=nullptr && Node->is_end_of_word;
    }
    
    bool startsWith(string prefix) {
        return search_word(prefix)!=nullptr;
    }
private:
    TrieNode* search_word (string word){
        TrieNode* Node=root;
        for(char c:word){
            if(Node->children.find(c)==Node->children.end()) return nullptr;
            Node=Node->children[c];
        }
        return Node;
    }
};