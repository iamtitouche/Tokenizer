#include "TokenRec.hpp"

TokenRec::TokenRec() : value(0), left_token(nullptr), right_token(nullptr) {}

TokenRec::TokenRec(uint16_t value) : value(value), left_token(nullptr), right_token(nullptr) {}

TokenRec::TokenRec(uint16_t value, TokenRec* left, TokenRec* right) : value(value), left_token(left), right_token(right) {}

vector<uint16_t>& TokenRec::getLeftOfTokens() {
	return left_of_tokens;
}
uint16_t TokenRec::getValue() {
  return value;
}
TokenRec* TokenRec::getLeftToken() {
	return left_token;
}
TokenRec* TokenRec::getRightToken() {
	return right_token;
}