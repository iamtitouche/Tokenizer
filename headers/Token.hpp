#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <vector>
#include <string>

using namespace std;

class Token {
public:
    Token();
    Token(uint16_t token_id, uint16_t token);
    Token(uint16_t token_id,const vector<uint16_t>& tokens);
    void addToken(uint16_t token);
    std::string toString() const;
    vector<uint16_t>& getBaseTokens();
    uint16_t getBaseToken(size_t index);
    uint16_t getTokenId();
private:
    uint16_t token_id;
    vector<uint16_t> base_tokens;
};

#endif //TOKEN_HPP
