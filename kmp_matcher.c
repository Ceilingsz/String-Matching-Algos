#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void compute_pi(int* pi, char* P, int m){
    pi[0] = -1;
    // let k denote the largest prefix that matches 
    int k = -1;
    for(int i = 1; i <= m; i++){
        while(k >= 0 && P[k+1] != P[i]){
            k = pi[k];
        }
        if(P[k+1] == P[i])
            k++;

        pi[i] = k;
    }
}

void kmp_matcher(int * pi, char *P, char *T, int m, int n){
    int q = -1;
    for(int i = 0; i < n; i++){
        while(q >= 0 && T[i] != P[q+1]){
            q = pi[q];
        }
        if(T[i] == P[q+1]){
            q++;
        }
        if(q+1 == m){
            printf("Found match at shift %d.\n", i-m+1);
            q = pi[q];
        }    
    }
}

int main(){
    char T[] = "babcaababcabcaa";
    char P[] = "abcaa";
    int m = strlen(P);
    int n = strlen(T);

    int *pi = malloc(sizeof(int) * m);
    compute_pi(pi, P, m);
    kmp_matcher(pi, P, T, m, n);
}