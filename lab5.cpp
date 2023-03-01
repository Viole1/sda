#include <cassert>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

struct node
{
    string data;
    node* next{ nullptr };
};

class LinkList {
private:
    node* first{ nullptr };
    node* last{ nullptr };
    size_t length{ 0 };

    bool test(node* h1, node* h2) {
        if (h1 && h2) {
            if (h1->data != h2->data) return true;
            else test(h1->next, h2->next);
        }
        return false;
    }

    node* merge(node* h1, node* h2) {
        if (!h1->next) return h2;
        if (!h2->next) return h1;

        if (h1->data < h2->data) {
            h1->next = merge(h1->next, h2);
            return h1;
        }
        else if (h1->data > h2->data) {
            length++;
            h2->next = merge(h1, h2->next);
            return h2;
        }
        else if (h1->data == h2->data) {
            h1->next = merge(h1->next, h2->next);
            return h1; 
        }
    }
public:
    void merge_sorted(LinkList& lst) {
        length--;
        node* cur1 = first;
        node* cur2 = lst.getFirst();
        if (!test(cur1, cur2)) {
            first = cur1;
        }
        else {
            first = merge(cur1, cur2);
            lst.setFirst(nullptr);
            lst.setLength(0);
            //lst.dealloc();
        }
    }
    void dealloc() {
        node* current = first;
        while (current) {
            node* tmp = current;
            current = current->next;
            delete tmp;
        }
    }
    node* find(const string& str) {
        node* pos = first;
        while (pos->data != str && pos->next != NULL) pos = pos->next;
        if (pos->next == NULL && pos->data != str) return nullptr;
        return pos;
    }
    void output() {
        node* current = first;
        while (current->next->next) {
            cout << current->data << ' ';
            current = current->next;
        }
    }
    LinkList split(const string& str) {
        node* current = find(str);
        LinkList tmpList;
        while (current) {
            tmpList.push_back(current->data);
            current = current->next;
        }
        return tmpList;
    }

    void push_back(string str) {
        length++;
        if (!first) {
            last = new node;
            node* newNode = new node;
            first = last;

            last->data = str;
            last->next = newNode;
            last = newNode;

        }
        else {
            node* newNode = new node;
            newNode->next = NULL;

            last->data = str;
            last->next = newNode;
            last = newNode;
        }
    }
    string pop_back() {
        node* current = first;
        //while (current->next->next->next != NULL) current = current->next;
        while (current->next->next != NULL) current = current->next;
        string result = current->data;
        remove_after(result);
        node* tmp = current;
        delete tmp->next;
        current->next = NULL;

        return  result;
        
    }
    void insert_after(const string& str1, const string& str2) {
        length++;
        node* current = find(str1);
        if (current->next) {
            node* tmp = new node;
            tmp->data = str2;
            tmp->next = current->next;
            current->next = tmp;
        }
        else push_back(str1);
    }
    void remove_after(const string& str) {
        length--;
        node* current = find(str);
        if (current->next) {
            node* tmp = current->next->next;
            delete current->next;
            current->next = tmp;
        }
    }
    size_t getLength() {
        return length;
    }
    node* getFirst() {
        return first;
    }
    void setFirst(node* n) {
        first = n;
    }
    void setLength(size_t n) {
        length = n;
    }
    node* getLast() {
        node* current = first;
        while (current->next->next) current = current->next;
        return current;
    }
};

int main(int argc, char const* argv[]){
    LinkList l;

    l.push_back("a");
    l.push_back("b");
    l.push_back("c");
    assert(3 == l.getLength());

    l.merge_sorted(l);

    l.output();
    cout << l.getLast()->data << ' ';

    l.insert_after("c", "d");

    LinkList l2;
    l2 = l.split("c");
    l2.insert_after( "d", "e");

    l2.merge_sorted(l);
    assert(nullptr == l.getFirst());
    assert(0 == l.getLength());
    assert(5 == l2.getLength());

    l2.output();

    l2.remove_after("c");

    l2.pop_back();
    assert(3 == l2.getLength());

    l2.output();
    l.dealloc(); l2.dealloc();

    return 0;
}
