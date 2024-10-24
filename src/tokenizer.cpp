#include "tokenizer.hpp"
#include "Token.hpp"
#include "file.h"
#include <vector>

using namespace std;

Tokenizer::Tokenizer(int max_tokens) : max_tokens(max_tokens), n_tokens(256) {
    tokensRec = new TokenRec[max_tokens];

    if (max_tokens < 256) {
        std::cerr << "max_tokens must be greater than 256" << endl;
        exit(1);
    }

    for (int i = 0; i < n_tokens; i++) {
        tokensRec[i] = TokenRec((uint16_t) i);
    }
}

void Tokenizer::train(const std::string& filename) {
    std::string content = readFile("../test.txt");

    vector<uint16_t> tokenized_content = readInitialTokens(content);

    uint16_t new_token_value = n_tokens;


    while (new_token_value < max_tokens) {
        int* occurences = (int*) calloc(max_tokens * max_tokens, sizeof(int));
        for (int i = 0; i < tokenized_content.size() - 1; i++) {
            int key = max_tokens * static_cast<int>(tokenized_content[i]) + static_cast<int>(tokenized_content[i + 1]);
            occurences[key]++;
        }

        int max_occurences = 0;
        int key_max_occ = 0;

        for (int i = 0; i < max_tokens * max_tokens; i++) {
            if (occurences[i] > max_occurences) {
                max_occurences = occurences[i];
                key_max_occ = i;
            }
        }

        tokensRec[new_token_value] = TokenRec(new_token_value, &(tokensRec[key_max_occ / max_tokens]), &(tokensRec[key_max_occ % max_tokens]));

        int i = 0;

        while (i < tokenized_content.size() - 1) {
            int key = max_tokens * static_cast<int>(tokenized_content[i]) + static_cast<int>(tokenized_content[i + 1]);

            if (key == key_max_occ) {
                tokenized_content[i] = new_token_value;
                tokenized_content.erase(tokenized_content.begin() + i + 1);
            }

            i++;
        }

        cout << "Max occurences : " << max_occurences << endl;
        cout << "Key Max occurences : " << key_max_occ << endl;
        cout << "Corresponding pair : " << key_max_occ / max_tokens << " " << key_max_occ % max_tokens << endl;

        new_token_value++;
        n_tokens++;
        free(occurences);
    }

    tokens = (Token*) calloc(max_tokens * max_tokens, sizeof(Token));

    recreateTokens();

    for (int i = 0; i < n_tokens; i++) {
        cout << tokens[i].toString() << endl;
    }
}



vector<uint16_t> Tokenizer::readInitialTokens(std::string input) {
    vector<uint16_t> tokens;

    for (int i = 0; i < input.size(); i++) {
        uint8_t c_int = static_cast<uint8_t>((unsigned char) input[i]);
        if ((c_int & 0x80) == 0) { // Si le premier bit est 0, c'est un caractère ASCII sur 1 octet (0xxxxxxx)
            tokens.push_back((uint16_t) c_int);
        } else if ((c_int & 0xE0) == 0xC0) { // Si les trois premiers bits sont 110, c'est un caractère sur 2 octets (110xxxxx)
            tokens.push_back((uint16_t) c_int);
            i++;
            c_int = static_cast<uint8_t>((unsigned char) input[i]);
            tokens.push_back((uint16_t) c_int);
        } else if ((c_int & 0xF0) == 0xE0) { // Si les quatre premiers bits sont 1110, c'est un caractère sur 3 octets (1110xxxx)
            tokens.push_back((uint16_t) c_int);
            for (int j = 0; j < 2; j++) {
                i++;
                c_int = static_cast<uint8_t>((unsigned char) input[i]);
                tokens.push_back((uint16_t) c_int);
            }
        } else if ((c_int & 0xF8) == 0xF0) { // Si les cinq premiers bits sont 11110, c'est un caractère sur 4 octets (11110xxx)
            tokens.push_back((uint16_t) c_int);
            for (int j = 0; j < 3; j++) {
                i++;
                c_int = static_cast<uint8_t>((unsigned char) input[i]);
                tokens.push_back((uint16_t) c_int);
            }
        } else {
            std::cerr << "Unhandled char: " << static_cast<int>(c_int) << std::endl;
        }
    }

    return tokens;
}

vector<uint16_t>* Tokenizer::createStartMap() {
    vector<uint16_t>* start_map = (vector<uint16_t>*) calloc(256, sizeof(vector<uint16_t>));

    for (uint16_t i = 0; i < 256; i++) {
        for (int j = 0; j < n_tokens; j++) {
            Token token = tokens[j];
            if (token.getBaseToken(0) == i) {
                start_map[i].push_back(token.getTokenId());
            }
        }
    }

    return start_map;
}

vector<uint16_t> Tokenizer::tokenize(vector<uint16_t> pretokenized) {
    vector<uint16_t> tokenized;
    int i = 0;
    vector<uint16_t>* start_map = createStartMap();


    while (i < pretokenized.size()) {
        uint16_t chosen_token = pretokenized[i];
        vector<uint16_t> potential_token(start_map[pretokenized[i]]);

        int offset = 1;

        while (!potential_token.empty() && i + offset < pretokenized.size()) {
            for (int ii = 0; ii < potential_token.size(); ii++) {
                if (chosen_token != potential_token[ii]) {
                    if (tokens[potential_token[ii]].getBaseTokens().size() <= offset) {
                        potential_token.erase(potential_token.begin() + ii);
                    } else if (tokens[potential_token[ii]].getBaseToken(offset) != pretokenized[i + offset]) {
                        potential_token.erase(potential_token.begin() + ii);
                    } else if (tokens[potential_token[ii]].getBaseTokens().size() == offset + 1) {
                        chosen_token = potential_token[ii];
                    }
                }
            }
            offset++;
        }

        tokenized.push_back(chosen_token);
        i += tokens[chosen_token].getBaseTokens().size();
    }

    return tokenized;
}


uint16_t Tokenizer::getLeftBaseToken(uint16_t token) {
    if (tokensRec[token].getLeftToken() == nullptr) {
        return token;
    }
    return getLeftBaseToken(tokensRec[token].getLeftToken()->getValue());
}

void Tokenizer::recreateTokens() {
    for (uint16_t i = 0; i < n_tokens; i++) {
        vector<uint16_t> base_tokens = recreateToken(tokensRec[i].getValue());
        Token token(i, base_tokens);
        tokens[i] = token;
    }
}

vector<uint16_t> Tokenizer::recreateToken(uint16_t token) {
    if (tokensRec[token].getLeftToken() == nullptr) {
        vector<uint16_t> base_tokens = {token};
        return base_tokens;
    }
    vector<uint16_t> base_tokens_left = recreateToken(tokensRec[token].getLeftToken()->getValue());
    vector<uint16_t> base_token_right = recreateToken(tokensRec[token].getRightToken()->getValue());
    base_tokens_left.insert(base_tokens_left.end(), base_token_right.begin(), base_token_right.end());
    return base_tokens_left;
}