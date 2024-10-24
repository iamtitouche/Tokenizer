#include "Token.hpp"
#include <sstream>

Token::Token() : token_id(0), base_tokens() {}

Token::Token(uint16_t token_id, uint16_t token) : token_id(token_id), base_tokens({token}) {}

Token::Token(uint16_t token_id, const vector<uint16_t>& tokens) : token_id(token_id), base_tokens(tokens) {}

void Token::addToken(uint16_t token) {
    base_tokens.push_back(token);
}

std::string Token::toString() const {
    std::ostringstream oss;

    oss << "Token ID : " << token_id;

    oss << " Base Tokens: [";
    for (size_t i = 0; i < base_tokens.size(); i++) {
        oss << base_tokens[i];
        if (i != base_tokens.size() - 1) {
            oss << ", ";
        }
    }
    oss << "]";

    return oss.str();
}

vector<uint16_t>& Token::getBaseTokens() {
    return base_tokens;
}

uint16_t Token::getBaseToken(size_t index) {
    return base_tokens[index];
}

uint16_t Token::getTokenId() {
    return token_id;
}