#include <iostream>
#include <stack>
using namespace std;

int main(void) {
    char sudden_finish = 0;
    char input[100];
    while(1) {
        stack<char> st;

        cin.getline(input, 100, '.');
        cin.ignore();
        for(int i=0; i<100; i++) {
            if(i==0 && input[i] == '\0')
            {
                sudden_finish=2;
                break;
            }

            if (input[i] == '\0') {
                break;

            }

            if (input[i] == '(')
                st.push('(');
            else if (input[i] == '[')
                st.push('[');
            else if (input[i] == ')') {
                if (!st.empty() && st.top() == '(')
                    st.pop();
                else {
                    cout << "no\n";
                    sudden_finish=1;
                    break;
                }
            }

            else if (input[i] == ']') {
                if (!st.empty() && st.top() == '[')
                    st.pop();
                else {
                    cout << "no\n";
                    sudden_finish=1;
                    break;
                }
            }
        }
        if(sudden_finish==0) {
            if(st.empty()) cout << "yes\n";
            else cout << "no\n";
        }
        else if (sudden_finish==1) {
            sudden_finish=0;
        }
        else if (sudden_finish==2) {
            break;
        }

    }
}