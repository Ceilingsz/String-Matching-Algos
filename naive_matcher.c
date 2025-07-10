#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char T[] = "abbaahabahabbhsahabaha";
    char P[] = "baha";

    int n = strlen(T);
    int m = strlen(P);

    for(int i = 0; i < n - m + 1; i++){
        int flag = 1;
        for(int j = 0; j < m; j++){
            if(T[i + j] != P[j]){
                flag = 0;
                break;
            }
        }
        if(flag){
            printf("Found match at i = %d\n", i);
        }
    }
}