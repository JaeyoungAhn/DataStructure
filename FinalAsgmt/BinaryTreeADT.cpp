#include <iostream>
using namespace std;

/* 트리의 전체 모양이 반드시 완전이진트리 일 필요가 없는 방식으로 구현하였습니다.
 * 루트만 가지고 있을때의 높이를 0이 아닌 1을 기준으로 삼았습니다. */

class BinaryTreeADT {
public:
    class Node { // 트리에 포함되는 노드 클래스
    public:
        char value; // 숫자 기호, 알파벳, 연산자 기호 등을 직관적으로 보기 위해 char를 사용
        Node* left; // 노드의 왼쪽
        Node* right; // 노드의 오른쪽

        Node(char _value) {
            value = _value; // 처음 들어온 char를 value로 사용
            left = nullptr; // 초기는 nullptr
            right = nullptr; // 초기는 nullptr
        }

        void addNode(Node *new_node, int isLeft) { // 새로 노드 추가
            if(isLeft == true) // 왼쪽 추가인 경우
                left = new_node; // 지정된 노드의 왼쪽에 새 node 주소 할당
            else if(isLeft == false) // 오른쪽 추가인 경우
                right = new_node; // 지정된 노드의 오른쪽에 새 node 주소 할당
        };

        void addTree(BinaryTreeADT *tree, int isLeft) { // 새로 트리 추가
            if(isLeft == true) // 왼쪽 추가인 경우
                left = tree->root; // 지정된 노드의 왼쪽에 트리의 root 주소 할당
            else if(isLeft == false) // 오른쪽 추가인 경우
                right = tree->root; // 지정된 노드의 왼쪽에 트리의 root 주소 할당
        };
    };

    Node* root; // BinaryTreeADT는 항상 root라는 노드를 포함
    BinaryTreeADT(char _value = '1'){ // constructor이고 value가 파라미터로 들어오지 않을 시 기본 '1'
        root = new Node(_value);
    }

    int getHeight(); // getHeightDrive()를 호출해서 구한 높이를 반환
    int getHeightDrive(Node*); // 재귀적으로 트리의 높이를 구하는 함수
    int getCountOfNodes(); // getCountOfNodesDrive()를 호출해서 구한 노드의 수를 반환
    int getCountOfNodesDrive(Node*); // 재귀적으로 노드의 개수를 구하는 함수
    char* traverse(string order); // traverseDrive()를 통해 받은 순회 결과 리스트를 반환
    void traverseDrive(string, Node *, char*, int*); // inorder, preorder, postorder에 따라 세가지 다른 방식으로 재귀적 순회
};

int BinaryTreeADT::getHeight() { // 높이를 구하기 위해 파라미터를 받지 않는 시작 함수
    return getHeightDrive(root); // 파라미터를 이용하여 실제 높이를 재귀적으로 계산하는 함수의 결과를 리턴
};

int BinaryTreeADT::getHeightDrive(Node* root) { // 파라미터를 이용하여 실제 높이를 재귀적으로 계산하는 함수
    int height = 0;
    if(root != nullptr) { // 재귀적으로 자기 자신의 높이와 왼쪽과 오른쪽 자식의 높이 중 큰 것을 더함
        return 1 + max(getHeightDrive(root->left), getHeightDrive(root->right));
    }
    return height;
};

int BinaryTreeADT::getCountOfNodes() { // 개수를 구하기 위해 파라미터를 받지 않는 시작 함수
    return getCountOfNodesDrive(root); // 파라미터를 이용하여 실제 개수를 재귀적으로 계산하는 함수의 결과를 리턴
};

int BinaryTreeADT::getCountOfNodesDrive(Node *root) { // 파라미터를 이용하여 실제 개수를 재귀적으로 계산하는 함수
    int return_val = 0;
    if(root != nullptr) { // 재귀적으로 자기 자신의 개수 1개와 왼쪽과 오른쪽 자식의 개수들을 재귀적으로 더함
        return_val = 1 + getCountOfNodesDrive(root->left) + getCountOfNodesDrive(root->right);
    }
    return return_val;
};

char* BinaryTreeADT::traverse(string order) { // inorder, preorder, postorder중 하나를 받은아 재귀적 순회를 하기 위한 함수
    int *index= new int(0); // traverseDrive에서 이용할 인덱스
    char *resultList = new char(getCountOfNodes()); // 순회 결과 리스트를 저장할 현재 노드 길이의 char 배열
    traverseDrive(order, root, resultList, index); // 재귀 방식, 탐색 대상이 되는 노드, 결과를 담을 리스트, 인덱스를 파라미터로 순회
    return resultList; // 순회 결과 리스트 리턴
};

void BinaryTreeADT::traverseDrive(string order, Node* root, char* resultList, int* index) { // 재귀 방식, 탐색 대상이 되는 노드, 결과를 담을 리스트, 인덱스를 파라미터로 순회
    if(order == "preorder") { // 전위 순회인 경우
        resultList[(*index)++] = root->value; // 결과 리스트에 현재 노드의 값을 담고 인덱스를 하나 증가
        if(root->left != nullptr)
            traverseDrive(order, root->left, resultList, index); // 현재 노드의 왼쪽 노드에 대하여 재귀적으로 순회
        if(root->right != nullptr)
            traverseDrive(order, root->right, resultList, index); // 현재 노드의 오른쪽 노드에 대하여 재귀적으로 순회
    }
    else if (order == "inorder") { // 중위 순회인 경우
        if(root->left != nullptr)
            traverseDrive(order, root->left, resultList, index); // 현재 노드의 왼쪽 노드에 대하여 재귀적으로 순회
        resultList[(*index)++] = root->value; // 결과 리스트에 현재 노드의 값을 담고 인덱스를 하나 증가
        if(root->right != nullptr)
            traverseDrive(order, root->right, resultList, index); // 현재 노드의 오른쪽 노드에 대하여 재귀적으로 순회
    }
    else if (order == "postorder") { // 후위 순회인 경우
        if(root->left != nullptr)
            traverseDrive(order, root->left, resultList, index); // 현재 노드의 왼쪽 노드에 대하여 재귀적으로 순회
        if(root->right != nullptr)
            traverseDrive(order, root->right, resultList, index); // 현재 노드의 오른쪽 노드에 대하여 재귀적으로 순회
        resultList[(*index)++] = root->value; // 결과 리스트에 현재 노드의 값을 담고 인덱스를 하나 증가
    }
};




int main() {
    BinaryTreeADT bt('*'); // 처음 루트의 값을 '*'로 초기화

    cout << "트리 높이?: " << bt.getHeight() << endl; // 루트 하나만을 가진 상태이므로 높이 1을 리턴
    cout << "노드 개수?: " << bt.getCountOfNodes() << endl; // 루트 하나만을 가진 상태이므로 개수 1을 리턴

    /*
    *         ('*')
    *         /     \
    *     ('+')      ('-')
    *     /   \       /  \
    *  ('2') ('3') ('7') ('9')
    *
    *   아래 코드들은 위 트리와 같은 모양을 만들기 위함
    */

    bt.root->addNode(new BinaryTreeADT::Node('+'), true); // 루트의 왼쪽에 '+' 값을 가진 노드 추가

    cout << "트리 높이?: " << bt.getHeight() << endl; // 높이 2를 리턴

    bt.root->addNode( new BinaryTreeADT::Node('-'), false); // 루트의 오른쪽에 '-' 값을 가진 노드 추가
    bt.root->left->addNode(new BinaryTreeADT::Node('2'), true); // 루트의 왼쪽의 왼쪽에 '2' 값을 가진 노드 추가

    cout << "노드 개수?: " << bt.getCountOfNodes() << endl; // 개수 4개를 리턴

    bt.root->left->addNode(new BinaryTreeADT::Node('3'), false); // 루트의 왼쪽의 오른쪽에 '3' 값을 가진 노드 추가
    bt.root->right->addNode(new BinaryTreeADT::Node('7'), true); // 루트의 오른쪽의 왼쪽에 '7' 값을 가진 노드 추가
    bt.root->right->addNode(new BinaryTreeADT::Node('9'), false); // 루트의 오른쪽의 오른쪽에 '9' 값을 가진 노드 추가

    cout << "트리 높이?: " << bt.getHeight() << endl; // 높이 3을 리턴
    cout << "노드 개수?: " << bt.getCountOfNodes() << endl; // 개수 7개를 리턴

    cout << "inorder 결과: ";
    char* expression = bt.traverse("inorder"); // BinaryTreeADT bt에 대하여 inorder 탐색을 한 결과 리스트를 expression에 저장
    for(int i=0; i<bt.getCountOfNodes(); i++) { // 노드 개수만큼 반복
        if(i==bt.getCountOfNodes()-1) cout << expression[i] << endl; // 마지막 인덱스인 경우 화살표 빼고 깔끔하게 출력
        else cout << expression[i] << " => "; // expression 순회 결과 배열의 i번째 인덱스의 값을 출력
    }

    cout << "preorder 결과: ";
    expression = bt.traverse("preorder"); // BinaryTreeADT bt에 대하여 preorder 탐색을 한 결과 리스트를 expression에 저장
    for(int i=0; i<bt.getCountOfNodes(); i++) { // 노드 개수만큼 반복
        if(i==bt.getCountOfNodes()-1) cout << expression[i] << endl; // 마지막 인덱스인 경우 화살표 빼고 깔끔하게 출력
        else cout << expression[i] << " => "; // expression 순회 결과 배열의 i번째 인덱스의 값을 출력
    }

    cout << "postorder 결과: ";
    expression = bt.traverse("postorder"); // BinaryTreeADT bt에 대하여 postorder 탐색을 한 결과 리스트를 expression에 저장
    for(int i=0; i<bt.getCountOfNodes(); i++) { // 노드 개수만큼 반복
        if(i==bt.getCountOfNodes()-1) cout << expression[i] << endl; // 마지막 인덱스인 경우 화살표 빼고 깔끔하게 출력
        else cout << expression[i] << " => "; // expression 순회 결과 배열의 i번째 인덱스의 값을 출력
    }


    /*
    *         ('/')
    *              \
    *              ('9')
    *
    *   아래 코드는 위와 같은 모양을 가진 새로운 트리를 만들기 위함
    */

    BinaryTreeADT new_bt('/'); // 새로 만든 트리의 초기 값을 '/'로 초기화
    new_bt.root->addNode(new BinaryTreeADT::Node('9'), false); // 새로 만든 트리의 루트의 오른쪽에 값을 '9'로 지정

    /*
     *            ('/')
     *           /     \
     *         ('*')   ('9')
     *         /     \
     *     ('+')      ('-')
     *     /   \       /  \
     *  ('2') ('3') ('7') ('9')
     *
     *   아래 addTree는 기존 트리와 새 트리를 결합한 위와 같은 모양을 만들기 위함
     */

    new_bt.root->addTree(&bt, true); // 새로 만든 트리의 루트의 왼쪽에 기존 트리를 추가

    cout << "트리 높이?: " << new_bt.getHeight() << endl; // 높이 4를 리턴
    cout << "노드 개수?: " << new_bt.getCountOfNodes() << endl; // 개수 9개를 리턴

    cout << "inorder 결과: ";
    expression = new_bt.traverse("inorder"); // BinaryTreeADT new_bt에 대하여 inorder 탐색을 한 결과 리스트를 expression에 저장
    for(int i=0; i<new_bt.getCountOfNodes(); i++) { // 노드 개수만큼 반복
        if(i==new_bt.getCountOfNodes()-1) cout << expression[i] << endl; // 마지막 인덱스인 경우 화살표 빼고 깔끔하게 출력
        else cout << expression[i] << " => "; // expression 순회 결과 배열의 i번째 인덱스의 값을 출력
    }

    cout << "preorder 결과: ";
    expression = new_bt.traverse("preorder"); // BinaryTreeADT new_bt에 대하여 preorder 탐색을 한 결과 리스트를 expression에 저장
    for(int i=0; i<new_bt.getCountOfNodes(); i++) { // 노드 개수만큼 반복
        if(i==new_bt.getCountOfNodes()-1) cout << expression[i] << endl; // 마지막 인덱스인 경우 화살표 빼고 깔끔하게 출력
        else cout << expression[i] << " => "; // expression 순회 결과 배열의 i번째 인덱스의 값을 출력
    }

    cout << "postorder 결과: ";
    expression = new_bt.traverse("postorder"); // BinaryTreeADT new_bt에 대하여 postorder 탐색을 한 결과 리스트를 expression에 저장
    for(int i=0; i<new_bt.getCountOfNodes(); i++) { // 노드 개수만큼 반복
        if(i==new_bt.getCountOfNodes()-1) cout << expression[i] << endl; // 마지막 인덱스인 경우 화살표 빼고 깔끔하게 출력
        else cout << expression[i] << " => "; // expression 순회 결과 배열의 i번째 인덱스의 값을 출력
    }

    return 0;
}

