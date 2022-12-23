#include<iostream>
using namespace std;

int n, m;
bool table[26][26] = { 0 };
char subject, predicate;
string throwaway;

void Floyd() {
    for (int tmp = 0; tmp < 26; tmp++) {
        for (int from = 0; from < 26; from++) {
            if (!table[from][tmp]) continue;

            for (int to = 0; to < 26; to++) {
                if (!table[from][tmp]) continue;

                if (table[from][tmp] && table[tmp][to]) table[from][to] = 1;
                if (!table[from][tmp] && !table[tmp][to]) table[from][to] = 0;
            }
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> subject >> throwaway >> predicate;
        table[subject -'a'][predicate -'a'] = 1;
    }
    Floyd();
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> subject >> throwaway >> predicate;
        if (table[subject - 'a'][predicate - 'a'] == 1) printf("T\n");
        else printf("F\n");
    }
}