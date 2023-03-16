#include <assert.h>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::max;

struct Node
{
    string data;
    Node* left{ nullptr };
    Node* right{ nullptr };
};

class BTree{
private:
    Node* root;
    void insert(string data, Node* node) {
        if (data.compare(node->data) < 0) {
            if (node->left != NULL) insert(data, node->left);
            else {
                node->left = new Node;
                node->left->data = data;
                node->left->left = NULL;
                node->left->right = NULL;
            }
        }
        else if (data.compare(node->data) >= 0) {
            if (node->right != NULL) insert(data, node->right);
            else {
                node->right = new Node;
                node->right->data = data;
                node->right->left = NULL;
                node->right->right = NULL;
            }
        }
    }
    size_t height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }
    Node* find(const string& word, Node* node) {
        if (node != NULL) {
            if (word.compare(node->data) == 0) return node;
            if (word.compare(node->data) < 0)
                return find(word, node->left);
            if (word.compare(node->data) > 0)
                return find(word, node->right);
        }
        return NULL;
    }
    void clear(Node* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete(node);
    }
    void sort(Node* node, string* arr, int& i) {
        if (!node) return;

        sort(node->left, arr, i);
        arr[i++] = node->data;
        sort(node->right, arr, i);
    };
public:
    BTree(const string* arr, size_t n) {
        for (int i = 0; i < n; i++) {
            insert(arr[i]);
        }
    }
    ~BTree() { clear(root); }
    void insert(string data) {
        if (root != NULL) insert(data, root);
        else {
            root = new Node;
            root->data = data;
            root->left = NULL;
            root->right = NULL;
        }
    }
    size_t height() { return height(root); }
    Node* find(const string& word) { return find(word, root); }
    void sort(string* arr, int& i) { sort(root, arr, i); };
};

int main(int argc, char const* argv[])
{
    size_t n = 0, k = 0;

    cin >> n >> k;

    string* a = new string[n];
    for (size_t i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    BTree tree(a, n);

    //cout << tree.height();
    assert(k == tree.height());

    for (size_t i = 0; i < n; ++i)
    {
        assert(a[i] == tree.find(a[i])->data);
    }

    int iter = 0;
    tree.sort(a, iter);

    for (size_t i = 0; i < n; ++i)
    {
        cout << a[i] << "\n";
    }
}
// тесты:
// 11 10 j i h g f e d c b a c
// 7 3 sunday monday tuesday wednesday thursday friday saturday
// 4 3 Upon-the-ground The-wet-leaves-lie Without-a-sound Until-they-die
