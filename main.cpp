#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>


#include "file.h"
#include "tokenizer.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  Tokenizer tokenizer(270);
  string text = readFile("../test.txt");
  vector<uint16_t> tokens = tokenizer.readInitialTokens(text);

  cout << "Pretokenized : ";

  for (uint16_t token : tokens) {
      cout << token << " ";
  }

  tokenizer.train("../test.txt");

  tokens = tokenizer.tokenize(tokens);

  for (uint16_t token : tokens) {
      cout << token << " ";
  }

  return 0;
}


//int main() {
//    std::string content = readFile("../test.txt");
//
//    std::cout << "Content: " << content << std::endl;
//
//    vector<uint16_t> tokens;
//
//    for (int i = 0; i < content.size(); i++) {
//    	uint8_t c_int = static_cast<uint8_t>((unsigned char) content[i]);
//        uint32_t result_integer = c_int;
//        if ((c_int & 0x80) == 0) { // Si le premier bit est 0, c'est un caractère ASCII sur 1 octet (0xxxxxxx)
//    		tokens.push_back(c_int);
//        } else if ((c_int & 0xE0) == 0xC0) { // Si les trois premiers bits sont 110, c'est un caractère sur 2 octets (110xxxxx)
//    		tokens.push_back(c_int);
//            i++;
//            c_int = static_cast<uint8_t>((unsigned char) content[i]);
//           	tokens.push_back(c_int);
//        } else if ((c_int & 0xF0) == 0xE0) { // Si les quatre premiers bits sont 1110, c'est un caractère sur 3 octets (1110xxxx)
//			tokens.push_back(c_int);
//          	for (int j = 0; j < 2; j++) {
//                i++;
//            	c_int = static_cast<uint8_t>((unsigned char) content[i]);
//            	tokens.push_back(c_int);
//			}
//        } else if ((c_int & 0xF8) == 0xF0) { // Si les cinq premiers bits sont 11110, c'est un caractère sur 4 octets (11110xxx)
//       		tokens.push_back(c_int);
//          	for (int j = 0; j < 3; j++) {
//                i++;
//            	c_int = static_cast<uint8_t>((unsigned char) content[i]);
//            	tokens.push_back(c_int);
//			}
//        } else {
//        	std::cerr << "Unhandled char: " << static_cast<int>(c_int) << std::endl;
//    	}
//
//        std::cout << result_integer << std::endl;
//	}
//
//    cout << "Number of bytes : " << tokens.size() << endl;
//
//    //for (uint32_t i = 0; i < utf8_content.size(); i++) {
//    //    cout << static_cast<int>(utf8_content[i]) << endl;
//    //}
//
//    int n_tokens = 500;
//    int new_token = 256;
//    if (n_tokens < 256) {
//        cerr << "Number of tokens insufficient" << endl;
//        return EXIT_FAILURE;
//    }
//
//    for (int t = 0; t < 10; t++) {
//    	int* occurences = new int[n_tokens * n_tokens];
//
//        for (int i = 0; i < tokens.size() - 1; i++) {
//            int key = n_tokens * static_cast<int>(tokens[i]) + static_cast<int>(tokens[i + 1]);
//            occurences[key]++;
//        }
//
//        int max_occurences = 0;
//        int key_max_occ = 0;
//
//        for (int i = 0; i < n_tokens * n_tokens; i++) {
//            if (occurences[i] > max_occurences) {
//                max_occurences = occurences[i];
//                key_max_occ = i;
//            }
//        }
//
//        int i = 0;
//
//        while (i < tokens.size() - 1) {
//        	int key = n_tokens * static_cast<int>(tokens[i]) + static_cast<int>(tokens[i + 1]);
//
//            if (key == key_max_occ) {
//            	tokens[i] = new_token;
//                tokens.erase(tokens.begin() + i + 1);
//            }
//
//            i++;
//        }
//
//        cout << "Max occurences : " << max_occurences << endl;
//    	cout << "Key Max occurences : " << key_max_occ << endl;
//    	cout << "Corresponding pair : " << key_max_occ / n_tokens << " " << key_max_occ % n_tokens << endl;
//
//        for (int i = 0; i < n_tokens * n_tokens; i++) {
//        	occurences[i] = 0;
//        }
//
//        new_token++;
//        max_occurences = 0;
//
//    }
//
//    return EXIT_SUCCESS;
//}
//