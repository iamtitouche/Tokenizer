#ifndef TOKENREC_HPP
#define TOKENREC_HPP

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TokenRec {
public:
    TokenRec();
    TokenRec(uint16_t value);
    TokenRec(uint16_t value,  TokenRec* left, TokenRec* right);
    vector<uint16_t>& getLeftOfTokens();
    uint16_t getValue();
    TokenRec* getLeftToken();
    TokenRec* getRightToken();
private:
    uint16_t value;
    TokenRec* left_token;
    TokenRec* right_token;
    vector<uint16_t> left_of_tokens;
};

#endif //TOKENREC_HPP
