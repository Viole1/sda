#include <iostream>
using namespace std;
 
struct Node {
    string name_;
    Node* next;
};
 
class LinkList {
private:
    Node* link;
public:
    LinkList() { link = NULL; }
    void clear();
    int length() {
        int count = 0;
        Node* current = link;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
    Node* tail() {
        Node* tmp = link;
        while (tmp->next) tmp = tmp->next;
        return tmp;
    }
    void push_front(string str){
        Node* newlink = new Node;
        newlink->name_ = str;
        newlink->next = link;
        link = newlink;
    }
    void push_back(string str) {
        Node* last = tail();
        Node* newlink = new Node;
 
        newlink->name_ = str;
        newlink->next = NULL;
        last->next = newlink;
    }
    Node* pop_front() {
        Node* tmp = link;
        link = link->next;
        return tmp;
    }
    Node* pop_back() {
        Node* last = tail();
        Node* tmp = link;
 
        while (tmp->next != last) tmp = tmp->next;
        tmp->next = NULL;
 
        return last;
    }
    void insert(string str, int n) {
        Node* pos = link;
        Node* tmp = new Node;
        tmp->name_ = str;
        while (n--) {
            pos = pos->next;
        }
        tmp->next = pos->next;
        pos->next = tmp;
    }
    void remove(string str) {
        Node* pos = link;
        int n = (searchPos(str) - 1) > 0 ? (searchPos(str) - 1) : 0;
        while (n--) {
            pos = pos->next;
        }
        pos->next = pos->next->next;
    }
 
    int searchPos(string str) {
        int count = 0;
        Node* pos = link;
        while (pos->name_ != str) {
            count++;
            pos = pos->next;
        }
        return count;
    }
    void display() {
        Node* current = link;
        while (current) {
            cout << current->name_ << endl;
            current = current->next;
        }
    }
};
