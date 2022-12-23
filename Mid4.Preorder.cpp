#include <cstdio>
using namespace std;

int in[100001];
int post[100001];
int inorder_ephe[100001];

void ans(int in_test, int in_test2, int post_test, int post_test2){
    if(in_test > in_test2 || post_test > post_test2)
        return;

    int root = post[post_test2];
    int in_Rpos = inorder_ephe[root];

    printf("%d ", root);
    ans(in_test, in_Rpos-1, post_test, post_test + (in_Rpos -1 - in_test));
    ans(in_Rpos+1, in_test2, post_test + (in_Rpos -1 - in_test)+1, post_test2-1);
}

int main (void) {
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        scanf("%d", &in[i]);
        inorder_ephe[in[i]] = i;
    }

    for(int i=0; i<n; i++){
        scanf("%d", &post[i]);
    }

    ans(0, n-1, 0, n-1);
}