#include <iostream>
#include <string>
using namespace std;
 
struct Node{
    string key;
    Node *left, *right;
};
 
class BTree{
private:
    Node* root = NULL;
    void insert(string data, Node* node){
        if (data.compare(node->key) < 0){
            if (node->left != NULL) insert(data, node->left);
            else{
                node->left = new Node;
                node->left->key = data;
                node->left->left = NULL;
                node->left->right = NULL;
            }
        }
        else if (data.compare(node->key) >= 0){
            if (node->right != NULL) insert(data, node->right);
            else{
                node->right = new Node;
                node->right->key = data;
                node->right->left = NULL;
                node->right->right = NULL;
            }
        }
    }
    Node* search(string word, Node* node){
        if (node != NULL){
            if (word.compare(node->key) == 0) return node;
            if (word.compare(node->key) < 0)
                return search(word, node->left);
            if (word.compare(node->key) > 0)
                return search(word, node->right);
        }
        return NULL;
    }
    void sort(Node* node, vector<string>& data, int& i){
        if (!node) return;
        
        sort(node->left, data, i);
        data[i++] = node->key;
        sort(node->right, data, i);
    }
    int height(Node* node){// золотой метод гения.
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
    void display(Node* node){
        if (!node) return;
        
        display(node->left);
        cout << node->key << ' ';
        display(node->right);
    }
    void clear(Node* node){
        if (!node) return;
        
        clear(node->left);
        clear(node->right);
        delete(node);
    }
public:
    ~BTree(){
        cout << "Tree was cleared";
        clear();
    }
    void insert(string data){
        if (root != NULL) insert(data, root);
        else{
            root = new Node;
            root->key = data;
            root->left = NULL;
            root->right = NULL;
        }
    }
    Node* search(string word){
        return search(word, root);
    }
    void sort(vector<string>& data, int& i){
        return sort(root, data, i);
    }
    int height(){
       height(root); 
    }
    void display(){
        display(root);
    }
    void clear(){
        clear(root);
    }
};
