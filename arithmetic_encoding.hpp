#include <boost/multiprecision/float128.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include<iostream>

using namespace boost::multiprecision;  
using namespace std;

// Make sure not to include the escape character in the table
// We assume that there is one occurence of the escape character in every node initially
// Fix ordering in the number line to be ascending order

pair<float128, float128> encode(char c, int* table, int size, float128 start, float128 end){
    float128 newStart = 0, newEnd = 0;
    float128 sumLess = 0;
    float128 sum = 1;
    for(int i = 0; i < size; i++){
        if((table[c - 'a'] != 0 ? i < c - 'a' : i < size))
        sumLess += table[i];

        sum += table[i];
    }

    float128 Prob = (table[c - 'a'] == 0 ? float128(1)/sum : float128(table[c - 'a'])/sum);
    newStart = start + (end - start) * (sumLess/sum);
    newEnd = start + (end - start) * (sumLess/sum + (Prob));
    return {newStart, newEnd};
}

pair<char,pair<float128, float128>> decode(int *table, int size, float128 num, float128 start, float128 end){
    float128 sum = 1;
    for(int i = 0; i < size; i++){
        sum += table[i];
    }
    float128 currStart = start;
    float128 currEnd = currStart;
    
    for(int i = 0; i < size; i++){
        currStart = currEnd;  
        currEnd = currStart + ((float128(table[i]))/sum)*(end - start);
        // cout << currStart << " " << currEnd << endl;
        if(num < currEnd && num >= currStart){
            return {char('a' + i), {currStart, currEnd}};
        }
    }

    return {'a' + 27, {currStart, currEnd}};
}

