#include "s_des.h"

S_Des::S_Des()
{

}

bitset<10> S_Des::key = std::bitset<10>("1010101010");


// 初始置换IP
int S_Des::IP[8] = { 2, 6, 3, 1, 4, 8, 5, 7 };

// 逆初始置换IP^-1
int S_Des::IP_inv[8] = { 4, 1, 3, 5, 7, 2, 8, 6 };

// 扩展置换E/P
int S_Des::EP[8] = { 4, 1, 2, 3, 2, 3, 4, 1 };

// P4 置换
int S_Des::P4[4] = { 2, 4, 3, 1 };

// P8 置换
int S_Des::P8[8] = { 6, 3, 7, 4, 8, 5, 10, 9 };

// P10 置换
int S_Des::P10[10] = { 3, 5, 2, 7, 4, 10, 1, 9, 8, 6 };

// Left Shifts
//int S_Des::leftShift1[5] = { 2, 3, 4, 5, 1 };
//int S_Des::leftShift2[5] = { 3, 4, 5, 1, 2 };

// S-盒
int S_Des::S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 0, 2}
};

int S_Des::S1[4][4] = {
    {0, 1, 2, 3},
    {2, 3, 1, 0},
    {3, 0, 1, 2},
    {2, 1, 0, 3}
};

// 左移位数
int const S_Des::shift[2] = { 1, 2 };



// 初始置换IP
bitset<8> S_Des::initialPermutation(bitset<8> plaintext) {
    bitset<8> result;
    for (int i = 0; i < 8; i++) {
        result[i] = plaintext[IP[i] - 1];
    }
    return result;
}

// 逆初始置换IP-1
bitset<8> S_Des::inverseInitialPermutation(bitset<8> ciphertext) {
    bitset<8> result;
    for (int i = 0; i < 8; i++) {
        result[i] = ciphertext[IP_inv[i]-1];
    }
    return result;
}

// 扩展置换E/P
bitset<8> S_Des::expandPermute(bitset<4> input) {
    bitset<8> result;
    for (int i = 0; i < 8; i++) {
        result[i] = input[EP[i] - 1];
    }
    return result;
}

// P4 置换
bitset<4> S_Des::permute4(bitset<4> input) {
    bitset<4> result;
    for (int i = 0; i < 4; i++) {
        result[i] = input[P4[i] - 1];
    }
    return result;
}

// P8 置换
bitset<8> S_Des::permute8(bitset<10> input) {
    bitset<8> result;
    for (int i = 0; i < 8; i++) {
        result[i] = input[P8[i] - 1];
    }
    return result;
}

// P10 置换
bitset<10> S_Des::permute10(bitset<10> input) {
    bitset<10> result;
    for (int i = 0; i < 10; i++) {
        result[i] = input[P10[i] - 1];
    }
    return result;
}

// S-盒替代
bitset<2> S_Des::sBoxSubstitution(bitset<4> input, int sBox[][4]) {
    int row = input[3] * 2 + input[1];
    int col = input[2] * 2 + input[1];
    int value = sBox[row][col];
    return bitset<2>(value);
}

// 生成子密钥，包括P10置换
vector<bitset<8>> S_Des::generateSubKeys(bitset<10> key) {
    vector<bitset<8>> subKeys;
    bitset<10> permutedKey = permute10(key);

    bitset<5> leftKey;
    bitset<5> rightKey;

    //将10bit的密钥分为两部分
    for (int i = 0; i < 5; i++) {
        leftKey[i] = permutedKey[i];
        rightKey[i] = permutedKey[i + 5];
    }

    //生成两把子密钥
    for (int i = 0; i < 2; i++) {
        leftKey = (leftKey << shift[i]) | (leftKey >> (5 - shift[i]));
        rightKey = (rightKey << shift[i]) | (rightKey >> (5 - shift[i]));
        bitset<10> roundKey = (leftKey.to_ulong() << 5) | rightKey.to_ulong();

        // P8 置换，将子密钥缩减为8位
        bitset<8> roundKey1 = permute8(roundKey);

        // 将 roundKey 添加到 subKeys 向量中
        subKeys.push_back(roundKey1);
    }
    /*cout << "两把子密钥分别为:" << endl;
    for (const bitset<8>&roundKey : subKeys) {
        cout << roundKey << endl;
    }*/
    return subKeys;
}

// 轮函数F
bitset<4> S_Des::roundFunction(bitset<4> right, bitset<8> subKey) {
    // 扩展置换E/P
    bitset<8> expandedRight = expandPermute(right);

    // 异或操作
    expandedRight ^= subKey;

    // 获取S-盒输入
    bitset<4> sBoxInput0;
    bitset<4> sBoxInput1;
    sBoxInput0[0] = expandedRight[0];
    sBoxInput0[1] = expandedRight[1];
    sBoxInput0[2] = expandedRight[2];
    sBoxInput0[3] = expandedRight[3];
    sBoxInput1[0] = expandedRight[4];
    sBoxInput1[1] = expandedRight[5];
    sBoxInput1[2] = expandedRight[6];
    sBoxInput1[3] = expandedRight[7];

    // S-盒替代
    bitset<2> sBoxOutputS0 = sBoxSubstitution(sBoxInput0, S0); // 使用S0盒
    bitset<2> sBoxOutputS1 = sBoxSubstitution(sBoxInput1, S1); // 使用S1盒

    // 合并S-盒输出
    bitset<4> sBoxOutput;
    sBoxOutput[0] = sBoxOutputS0[0];
    sBoxOutput[1] = sBoxOutputS0[1];
    sBoxOutput[2] = sBoxOutputS1[0];
    sBoxOutput[3] = sBoxOutputS1[1];


    // P4 置换
    bitset<4> permutedSBoxOutput = permute4(sBoxOutput);

    return permutedSBoxOutput;
}


// S-DES加密
bitset<8> S_Des::sDesEncrypt(bitset<8> plaintext, bitset<10> key) {
    vector<bitset<8>> subKeys = generateSubKeys(key);
    bitset<8> ipResult = initialPermutation(plaintext);
    //cout << "加密的初始置换：" << ipResult << endl ;

    bitset<4> left = (ipResult >> 4).to_ulong();
    bitset<4> right = (ipResult & bitset<8>(0x0F)).to_ulong();


    bitset<4> rightTemp = right;
    right = left ^ roundFunction(right, subKeys[0]);
    left = rightTemp;
    left = left ^ roundFunction(right, subKeys[1]);


    bitset<8> ciphertext = (left.to_ulong() << 4) | right.to_ulong();
    //cout << "加密最终置换前：" << ciphertext << endl;
    return inverseInitialPermutation(ciphertext);
}

// S-DES解密
bitset<8> S_Des::sDesDecrypt(bitset<8> ciphertext, bitset<10> key) {
    vector<bitset<8>> subKeys = generateSubKeys(key);
    bitset<8> ipResult = initialPermutation(ciphertext);
   cout << "解密的初始置换：" <<  ipResult <<endl;

    bitset<4> left = (ipResult >> 4).to_ulong();
    bitset<4> right = (ipResult & bitset<8>(0x0F)).to_ulong();

    bitset<4> rightTemp = right;
    right = left ^ roundFunction(right, subKeys[1]);
    left = rightTemp;
    left = left ^ roundFunction(right, subKeys[0]);

    bitset<8> plaintext = (left.to_ulong() << 4) | right.to_ulong();
    cout << "解密最终置换前：" << plaintext << endl;
    return inverseInitialPermutation(plaintext);
}



//把str转换为ascii-bit
void S_Des::convertToASCII(const char* str, bitset<8>* asciiArray, int length) {
    for (int i = 0; i < length; ++i) {
        asciiArray[i] = static_cast<int>(str[i]);
    }
}

//把ascii-bit进行des加密
void S_Des::convertToDes(bitset<8>* desArray,bitset<8>* asciiArray, int length){
    for (int i=0;i<length;i++){
        desArray[i]=sDesEncrypt(asciiArray[i],key);
    }
}

//对des进行解密成ascii-bit
void S_Des::decryptDes(bitset<8>* desArray, bitset<8>* asciiArray,int length){
    for (int i=0;i<length;i++){
        asciiArray[i]=sDesDecrypt(desArray[i],key);
    }
}

//将ascii-bit再转换成des
void S_Des::convertToChar(bitset<8>* asciiArray, char* charArray, int length) {
    for (int i = 0; i < length; ++i) {
        charArray[i] = static_cast<char>((asciiArray[i].to_ulong()));
    }
}

//总函数
void S_Des::asciiDes(char* str,int length){
    //初始化
    bitset<8> asciiArray[length];
    bitset<8> desArray[length];


    cout<<"asciiArray: ";
    convertToASCII(str,asciiArray,length);
    for(int i=0;i<length;i++){
        cout<<asciiArray[i]<<" ";
    }
    cout<<endl;


    convertToDes(desArray,asciiArray,length);
    cout<<"desArray: ";
    for(int i=0;i<length;i++){
        cout<<desArray[i]<<" ";
    }
    cout<<endl;

    decryptDes(desArray,asciiArray,length);
    convertToASCII(str,asciiArray,length);
    cout<<"asciiArray: ";
    for(int i=0;i<length;i++){
        cout<<asciiArray[i]<<" ";
    }
    cout<<endl;

    convertToChar(asciiArray,str,length);
    cout<<str<<endl;
}


//暴力破解des
void S_Des::figureOut(bitset<8> plaintext,bitset<8> ciphertext,int lenKey,bitset<10>* result,int* count){

        for(int i=0;i<(pow(2,lenKey)) -1;i++){
            bitset<10> key(i);
            if(sDesEncrypt(plaintext,key) == ciphertext){
                result[*count]=key;
                (*count)++;
            }
        }
}
