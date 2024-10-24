# Introduction

This project is designed as an educational tool to demonstrate how a tokenizer works within a Large Language Model (LLM). Its purpose is to provide a clear and accessible explanation of the tokenizer’s functionality while helping me explore the intricacies of C++, a language I am learning through this project.

By breaking down the key concepts and processes involved in tokenization, this repository aims to benefit others who, like me, are new to the field of tokenization in LLMs.

# Introduction to UTF-8 encoding

To understand how tokenization works, it is essential to grasp how characters are encoded in computers. Most systems utilize UTF-8 encoding. In this encoding scheme, characters are represented using one, two, three, or four bytes, depending on their frequency of use in the language.

For example, characters such as digits, both lowercase and uppercase letters from the English alphabet, and common punctuation marks are encoded using just one byte.

## One byte UTF-8 characters

| Character | Scalar Value: Binary (Decimal) | Number of Bytes of the UTF-8 Encoding | UTF-8 Encoding: Binary (Hexadecimal) |
|-----------|--------------------------------|---------------------------------------|--------------------------------------|
| space     | 00100000 (32)                  | 1                                     | **0**0100000 (20)                    |
| -         | 00101101 (45)                  | 1                                     | **0**0101101 (2D)                    |
| .         | 00101110 (46)                  | 1                                     | **0**0101110 (2E)                    |
| 0         | 00110000 (48)                  | 1                                     | **0**0110000 (30)                    |
| 9         | 00111001 (57)                  | 1                                     | **0**0111001 (39)                    |
| A         | 01000001 (65)                  | 1                                     | **0**1000001 (41)                    |
| Z         | 01011010 (90)                  | 1                                     | **0**1011010 (5A)                    |
| a         | 01100001 (97)                  | 1                                     | **0**1100001 (61)                    |
| z         | 01111010 (122)                 | 1                                     | **0**1111010 (7A)                    |


### Explanation of the Table

The table above illustrates the UTF-8 encoding for a selection of characters. Each row represents a character, along with its scalar value in binary (and its corresponding decimal value), the number of bytes used for encoding, and its UTF-8 encoding in binary and hexadecimal forms.

- **Character**: The character being represented.
- **Scalar Value: Binary (Decimal)**: The binary representation of the character’s Unicode scalar value, along with its decimal equivalent.
- **Number of Bytes**: The amount of bytes used to encode the character in UTF-8. In this case, all characters listed use only one byte.
- **UTF-8 Encoding: Binary (Hexadecimal)**: The binary representation of the UTF-8 encoding, along with its hexadecimal equivalent, which is often used in programming and data representation.

This encoding scheme allows for efficient storage and transmission of characters, especially those that are frequently used in the English language.

## Multi-Bytes Characters

| Character | Scalar Value: Binary (Decimal)                  | Number of Bytes of the UTF-8 Encoding | UTF-8 Encoding: Binary (Hexadecimal)                              |
|-----------|-------------------------------------------------|-----------------|-------------------------------------------------------------------|
| ¿         | 00111111 (63)                                   | 2               | **110**00001 **10**111111 (C1 BF)                                 |
| é         | 01100101 (101)                                  | 2               | **110**00010 **10**100101 (C3 A9)                                 |
| あ         | 11100001 10000010 10000000 (12 354)             | 3               | **1110**0001 **10**000010 **10**000000 (E3 81 82)                 |
| ひ         | 11100001 10001101 10010000 (12 450)             | 3               | **1110**0001 **10**001101 **10**010000 (E3 81 8D)                 |
| 𝄞         | 11110000 10010000 10010000 10010010 (119 070)   | 4               | **11110**000 **10**010000 **10**010000 **10**010010 (F0 9D 84 B2) |
| 𠀀       | 11110000 10000000 10000000 10000000 (1 048 576) | 4               | **11110**000 **10**000000 **10**000000 **10**000000 (F0 80 80 80) |

The bold prefix in the binary of the UTF-8 value indicates the size of the encoding for the starting character (0 for one byte, 110 for 2, 1110 for 3 and 11110 for 4), and if it begins with 10, it signifies that the current byte is part of the encoding of a character starting with one of the previous byte.

### In C++

In C++, characters are encoded using the char type, which occupies one byte. Consequently, each character can be represented using one, two, three, or four char variables.

This is the reason why the following code will print the first byte of the string "a" as a but will print the first byte of the string "あ" as an undefined character.

```
string character = "a";
char first_byte = character[0];
cout << first_byte << endl;
character = "あ";
first_byte = character[0];
cout << first_byte << endl;
```

Output :
```
a
�
```



