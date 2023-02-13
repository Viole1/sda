#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
bool isOper(char str){ // проверяет является ли символ оператором
    return (str == '+' || str == '-' || str == '*' || str == '/' || str == '\0' || str == '(' || str == ')');
}
vector<string> tokenize(string expr){ // токенизирую, чтоб потом просто 
    vector<string> temp;             //пройтись по выражению как по массиву
    int start = 0;
    for (int i = 0; i <= expr.size();i++){
        if (isOper(expr[i])){ // если встретили оператор, значит число закончилось, добавляем его в вектор.
            string tmpStr(expr, start, i - start);
            temp.push_back(tmpStr);
            if (expr[i] != '\0') { // добавляем и сам оператор в вектор, после числа, если это не конец строки.
                tmpStr = expr[i];
                temp.push_back(tmpStr);
                
            }
            // проверка, идут ли операции друг за другом подряд и проверка, чтоб while не выходил за пределы.
            while (isOper(expr[i + 1]) && expr[i + 1] != '\0'){
                tmpStr = expr[++i];
                temp.push_back(tmpStr);
            }
            start = ++i;
            continue;
        }
    }
    return temp;
}
 
int getPriority(string str){ // получение приоритета операции
    if (str == "+" || str == "-") return 1;
    if (str == "*" || str == "/") return 2;
    return 100;
}
 
struct Node{
  string value_;
  Node *left_, *right_;
};
class BTree{
private:
    Node* tree = NULL;
    
    Node* init(vector<string> vStr, int start, int end){
        int MinPrt, prt, key, par = 0;
        Node* Tree = new Node;
        if (start == end){
            Tree->value_ = vStr[start];
            Tree->left_ = NULL;
            Tree->right_ = NULL;
            return Tree;
        }
        MinPrt = 100;
        for (int i = start; i <= end; i++){
            if (vStr[i] == "(") { par++; continue; }
            if (vStr[i] == ")") { par--; continue; }
            if (par > 0) continue;
            
            prt = getPriority(vStr[i]);
            if (prt <= MinPrt){
                MinPrt = prt;
                key = i;
            }
        }
        
        if (MinPrt == 100 && vStr[start] == "(" && vStr[end] == ")"){
            delete Tree;
            return init(vStr, start + 1, end - 1);
        }
        
        Tree->value_ = vStr[key];
        Tree->left_ = init(vStr, start, key - 1);
        Tree->right_ = init(vStr, key + 1, end);
        return Tree;
    }
    int eval(Node* root){
        int num1, num2;
        if (!root->left_) return stoi(root->value_); 
        
        num1 = eval(root->left_);
        num2 = eval(root->right_);
 
        if(root->value_ == "+") return num1 + num2;
        else if(root->value_ == "-") return num1 - num2;
        else if(root->value_ == "*") return num1 * num2;
        else if(root->value_ == "/") return num1 / num2;
    }
    void display(Node* node){
        if (!node) return;
        
        display(node->left_);
        cout << node->value_ << ' ';
        display(node->right_);
    }
    void clear(Node* node){
        if (!node) return;
        
        clear(node->left_);
        clear(node->right_);
        delete(node);
    }
public:
    ~BTree() { 
        cout << "\nTree has been removed." << endl;
        clear(tree); 
    }
    void initialize(vector<string> vStr, int start, int end)
        { tree = init(vStr, start, end); }
    int eval() { return eval(tree); }    
    void display() { display(tree); }
    void clear() { clear(tree); }
};
 
int main() {
    BTree t1;
    //string ex = "100+3*6/(2-1)";
    //string ex = "1+((2+3)*5+3)*7";
    string ex;
    cin >> ex;
    vector<string> exToken = tokenize(ex);
    //for (int i = 0; i < exToken.size(); i++) cout << exToken[i] << '.';
    int n = exToken.size() - 1;
    t1.initialize(exToken, 0, n);
    cout << endl;
    cout << "Data: "; t1.display();
    cout << "\nResult: " << t1.eval();
    
    return 0;
}
