#ifndef S_DES_H
#define S_DES_H
#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class S_Des
{
public:
    S_Des();
    static bitset<10> key;

    // 初始置换IP
    static int IP[8];

    // 逆初始置换IP^-1
    static int IP_inv[8] ;

    // 扩展置换E/P
    static int EP[8] ;

    // P4 置换
    static int P4[4] ;

    // P8 置换
    static int P8[8] ;

    // P10 置换
    static int P10[10] ;

    // Left Shifts
    static int leftShift1[5] ;
    static int leftShift2[5] ;

    // S-盒
    static int S0[4][4];

    static int S1[4][4] ;

    // 左移位数
     static int const shift[2];

    static bitset<8> initialPermutation(bitset<8> plaintext);
    static bitset<8> inverseInitialPermutation(bitset<8> ciphertext);
    static bitset<8> expandPermute(bitset<4> input);
    static bitset<4> permute4(bitset<4> input);
    static bitset<8> permute8(bitset<10> input);
    static bitset<10> permute10(bitset<10> input);
    static bitset<2> sBoxSubstitution(bitset<4> input, int sBox[][4]);
    static vector<bitset<8>> generateSubKeys(bitset<10> key);
    static bitset<4> roundFunction(bitset<4> right, bitset<8> subKey);
    static bitset<8> sDesEncrypt(bitset<8> plaintext, bitset<10> key);
    static bitset<8> sDesDecrypt(bitset<8> ciphertext, bitset<10> key);
    static void convertToASCII(const char* str, bitset<8>* asciiArray, int length);
    static void convertToDes(bitset<8>* desArray,bitset<8>* asciiArray, int length);
    static void decryptDes(bitset<8>* desArray, bitset<8>* asciiArray,int length);
    static void convertToChar(bitset<8>* asciiArray, char* charArray, int length);
    static void asciiDes(char* str,int length);
    static void figureOut(bitset<8> plaintext,bitset<8> ciphertext,int lenKey,bitset<10>* result,int* count=0);


};

#endif // S_DES_H

