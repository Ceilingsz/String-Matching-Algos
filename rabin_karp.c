#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void rabinkarp_matcher(char* s, char * p, int mod, int base){
    int n = strlen(s);
    int m = strlen(p);

    int lar = 1;
    for(int i = 0; i < m - 1; i++){
        lar = (lar * base) % mod;
    }
    printf("%d\n", m);
    int hash1 = 0;
    int hash2 = 0;
    for(int i = 0; i < m; i++){
        hash2 = ((hash2 * base)%mod + (s[i]))%mod;
        hash1 = ((hash1 * base)%mod + (p[i]))%mod;
    }


    for(int i = m; i < n + 1; i++){
        printf("%d %d\n", hash1, hash2);
        if(hash1 == hash2){
            int flag = 1;
            for(int j = i - m; j < i; j++){
                if(s[j] != p[j-i+m]){
                    flag = 0;
                    break;
                }
            }

            if(flag){
                printf("Match found at %d\n", i-m+1);
            } else {
                printf("Spurious hit\n");
            }
        }
        if(i < n)
        hash2 = (((((hash2)%mod - lar*(s[i-m])%mod + mod)%mod)*base)%mod + (s[i]))%mod;
    }
}

int main(){
    char* s = "abaabasdash";   
    char* p = "baab";
    int n = strlen(s);
    int m = strlen(p);
    
    rabinkarp_matcher(s, p, 11, 26);
}