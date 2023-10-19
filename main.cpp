#include <iostream>
#include "lib.h"

//int main() {
//
//    std::vector<std::string> outputLines = LibParser::tokenize_input_file("test.txt");
//
//    for (const std::string &outputLine : outputLines) {
//        std::cout << outputLine << std::endl;
//    }
//
//    return 0;
//}
void printPairs(const LibParser::lib_pair_t &pair, int indentLevel) {
    // 打印键和值
    std::cout << std::string(indentLevel, ' ') << "Key: " << pair.key << ", Value: " << pair.value << std::endl;

    // 递归打印内部键值对
    for (const LibParser::lib_pair_t &innerPair: pair.inner_layer) {
        printPairs(innerPair, indentLevel + 2);
    }
}
int main() {
    LibParser parser;

    // 解析 tokens
    std::vector<std::string> tokenStrings = parser.tokenize_input_file("test.txt");
    std::vector<LibParser::lib_token_t> tokens = parser.parse_tokens(tokenStrings);

    // 解析键值对
    LibParser::lib_pair_t rootPair = parser.parse_pairs(tokens);

    // 输出键值对
    printPairs(rootPair, 0);

    return 0;
}

