#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(char dat, Node* le, Node* ri) {
        data=(int)dat;
        left=le;
        right=ri;
    }
    Node(int dat) {
        data=dat;
        left=NULL;
        right=NULL;
    }
};

Node n1(1);
Node n2(4);
Node n3('*', &n1, &n2);
Node n4(16);
Node n5(25);
Node n6('+',&n4,&n5);
Node n7('+',&n3,&n6);
Node* exp = &n7;

int evaluate(Node *root) {
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    else {
        int op1 = evaluate(root->left);
        int op2 = evaluate(root->right);
        cout<<op1<<" "<<(char)(root->data)<<" "<<op2<<"을 계산합니다.\n";
        switch(root->data) {
            case '+':
                return op1+op2;
            case '-':
                return op1-op2;
            case '*':
                return op1*op2;
            case '/':
                return op1/op2;

        }
    }
    return 0;

}

int main(void) {
    cout << "수식의 값은 "<<evaluate(exp)<<"입니다. \n";
    return 0;
}