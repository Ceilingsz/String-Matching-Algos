#include <arithmetic_encoding.hpp>
using namespace boost::multiprecision;  
using namespace std;

#define MAX_ORDER 5

float128 ppm_encoder(string s){
    // if order = -1
    float128 start = 0, end = 1;
    for(int i = 0; i < s.size(); i++){
        for(int curr_order = MAX_ORDER; curr_order >= -1; curr_order--){
            if(i - curr_order < 0)continue;
            Node* ProbCurr = findProbability(s.substr(i-curr_order, curr_order));
            
            int table[27] = {};
            table[26] = 1;
            for(int i = 0; i < 26; i++){
                if(curr_order == -1)table[i] = 1;
                else table[i] = ProbCurr->end[i];
            }    
            if(curr_order != -1){
                if(table[s[i]-'a'] == 0){
                    encode('a' + 27, table, 27, start, end);
                }
            }        

            auto [x, y] = encode(s[i], table, 27, start, end);
            start = x; end = y;
        }
    }

    return (start + end)/2;
}

string ppm_decoder(float128 val, int size){
    float128 start = 0, end = 1;
    string s = "";

    for(int i = 0; i < size; i++){
        for(int curr_order = MAX_ORDER; curr_order >= -1; curr_order--){
            if(i - curr_order < 0)continue;
            Node* ProbCurr = findProbability(s.substr(i-curr_order, curr_order));

            int table[27] = {};
            table[26] = 1;
            for(int i = 0; i < 26; i++){
                if(curr_order == -1)table[i] = 1;
                else table[i] = ProbCurr->end[i];
            } 
            auto [x, y] = decode(table, 27, val, start, end);
            start = y.first; end = y.second;
            if(x == 'a' + 27){
                continue;
            } else {
                s += x;
                break;
            }
        }
    }
    return s;

}
