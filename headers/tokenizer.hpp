#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "file.h"
#include "TokenRec.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.hpp"

using namespace std;

class Tokenizer {
public:
    Tokenizer(int n_tokens);
    void train(const std::string& filename);
    vector<uint16_t> readInitialTokens(std::string input);
    vector<uint16_t> tokenize(vector<uint16_t> pretokenized);
    uint16_t getLeftBaseToken(uint16_t token);
    void recreateTokens();
    vector<uint16_t> recreateToken(uint16_t token);
private:
    int max_tokens;
    int n_tokens;
    TokenRec* tokensRec;
    Token* tokens;

    vector<uint16_t>* createStartMap();
};

#endif //TOKENIZER_HPP
