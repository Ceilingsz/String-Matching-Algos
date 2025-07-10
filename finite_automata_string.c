#include <stdio.h>
#include <stdlib.h>

void compute_transition_function(int** delta, int m, int sig, char* charset, char *P){

    for(int i = 0; i < m + 1; i++){
        for(int j = 0; j < sig; j++){
            // check largest suffix of P[:i-1]charset[j] which is a prefix of P
            // i+1 characters to be checked?
            for(int h = (0 > i-m+1 ? 0 : i-m+1); h < i + 1; h++){
                int flag = 1;
                // suffix starts at h
                for(int k = h; k < i + 1; k++){
                    if(k < i && P[k] != P[k-h]){
                        flag = 0;
                        break;
                    } else if(k == i && P[k-h] != charset[j]){
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    delta[i][j] = i-h+1; 
                    break;
                }
            }
        }
    }
}

void string_matcher(char* T, char* P, int n, int m, int** delta){
    int q = 0;

    for(int i = 0; i < n; i++){
        q = delta[q][T[i]-'a'];
        if(q == m){
            printf("Found a match at i = %d\n", i+1-m);
        }
    }
}



int main(){
    int n=15, m = 5, sig = 3;
    char P[5] = "abcaa";
    char charset[3] = "abc";
    char T[] = "babcaababcabcaa";
    int** delta = (int**)malloc(sizeof(int *) * (m+1));
    for(int i = 0; i < m + 1; i++){
        delta[i] = (int *)malloc(sizeof(int) * sig);
    }
    for(int i = 0; i < m + 1; i++){
        for(int j = 0; j < sig; j++)
        delta[i][j] = 0;
    }
    compute_transition_function(delta, m, sig, charset, P);

    string_matcher(T, P, n, m, delta);
}