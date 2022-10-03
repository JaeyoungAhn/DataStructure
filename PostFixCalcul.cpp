#include <iostream>
#include <stack>
#include <string>
#include <cstring>
using namespace std;

int main(void) {

    stack<char> s1;
    stack<int> s2;

    string expression;
    cin >> expression;  // 1+2*8
    //  - 3 + 4, 4 - ( - 3 )
    // 4 - ( - 3 )
    // 4 3 - - |
    char* answer = new char[expression.length()];
    char* ans_iter = answer;
    int temp1, temp2;
    int flag = 0;
    int flag2 = 0;
    int idx=0;
    int flag3 =0;

    for(string::iterator iter = expression.begin(); iter != expression.end(); ++iter) {
        if(flag3>=0) flag3-=1;

        if(*iter=='-' && idx==0) {
            flag2=1;
        }
        else if ( (0 <= *iter - '0') && (*iter - '0' <= 9) ) {
            if(flag2==1) {
                flag2=0;
                *(ans_iter++)=*iter+*iter;
            }
            else if(!s1.empty() && s1.top() == '-') {
                if(flag3==1) {
                    s1.pop();
                    flag3=0;
                    *(ans_iter++)=*iter+*iter;
                }
                else *(ans_iter++)=*iter;
            }
            else *(ans_iter++)=*iter;
        }


        else if ( *iter == '(') {
            flag3=3;
            s1.push(*iter);
        }

        else if ( *iter == ')') {
            while( s1.top() != '(' ) {
                *(ans_iter++)=s1.top();
                s1.pop();
            }
            s1.pop(); // pop '('
        }

        else if ( *iter == '+' || *iter == '-' ) {
            while (!s1.empty() && s1.top() != '(') {
                *(ans_iter++) = s1.top();
                s1.pop();
            }
            s1.push(*iter);
        }

        else if ( *iter == '*' || *iter == '/') {
            while (!s1.empty() && s1.top() != '(' && (s1.top() == '*' || s1.top() == '/')) {
                *(ans_iter++) = s1.top();
                s1.pop();
            }
            s1.push(*iter);
        }
        idx++;

    }

    while(!s1.empty()) {
        *(ans_iter++) = s1.top();
        s1.pop();
    }


    for(int i=0; i<strlen(answer); i++) {
        if ( (0 <= answer[i] - '0') && (answer[i] - '0' <= 9) ) {
            s2.push(answer[i] - '0');
        }
        else if ((answer[i]>=96) && (0 <= answer[i]/2 - '0') && (answer[i]/2 - '0' <= 9) ){
            s2.push(-1*(answer[i]/2 - '0'));
        }
        else {
            temp1 = s2.top();
            s2.pop();
            temp2 = s2.top();
            s2.pop();
            if ( answer[i] == '+' ) s2.push(temp1+temp2);
            else if ( answer[i] == '-' ) s2.push(temp2-temp1);
            else if ( answer[i] == '*' ) s2.push(temp2*temp1);
            else if ( answer[i] == '/' ) {
                if (temp1 == 0) {
                    cout << "Divide by zero\n";
                    flag=1;
                    break;
                }
                s2.push(temp2/temp1);
            }
        }
    }

    if(flag==0) cout << s2.top();

    return 0;
}