//
// Created by chen on 10/17/23.
//

#include "lib.h"
#include <iostream>
#include <fstream>
#include <regex>

std::string LibParser:: delete_leading_spaces(const std::string &input) {
    std::size_t firstNonSpace = input.find_first_not_of(' ');
    if (firstNonSpace == std::string::npos)
        return "";
    return input.substr(firstNonSpace);
}

std::vector<std::string> LibParser::tokenize_input_file(const std::string &filename) {
    std::ifstream input_file(filename);

    std::vector<std::string> output_lines;

    if (!input_file.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return output_lines;
    }

    std::regex pattern(R"(\w+|\(|\)|\{|\}|\;|\+|\-|\\|\,|\"|\:|\*|\d+\.\d+|\d+)");

    std::string line;


    while (std::getline(input_file, line)) {
        line = delete_leading_spaces(line);

        if ((line.c_str()[0] == '/' && line.c_str()[1] == '*')
            || (line.c_str()[0] == '/' && line.c_str()[1] == '/'))
            continue;

        size_t pos = line.find("//");
        if (pos != std::string::npos)
            line.erase(pos);

        std::smatch floatMatch;

        while (std::regex_search(line, floatMatch, std::regex(R"(\d+\.\d+)"))) {
            std::string floatToken = floatMatch.str(0);
            line.replace(floatMatch.position(), floatToken.length(), "FLOAT");
        }

        std::smatch match;
        std::string output_line;

        while (std::regex_search(line, match, pattern)) {
            std::string token = match.str(0);
            output_line += LibParser::process_token(token);
            line = match.suffix();
        }

        output_lines.push_back(output_line);
    }

    input_file.close();
    return output_lines;
}

std::string LibParser:: process_token(const std::string &token) {
    if (token == "(") {
        return "LBracket ";
    } else if (token == ")") {
        return "RBracket ";
    } else if (token == "{") {
        return "LBrace ";
    } else if (token == "}") {
        return "RBrace ";
    } else if (token == ":") {
        return "Colon ";
    } else if (token == "*") {
        return "Asterisks ";
    } else if (token == ";") {
        return "Semicolon ";
    } else if (token == "\\") {
        return "Tilt ";
    } else if (token == "+") {
        return "Plus ";
    } else if (token == "-") {
        return "Minus ";
    } else if (token == "\"") {
        return "Quotation ";
    } else if (token == ",") {
        return "Comma ";
    } else {
        return "String ";
    }
}


std::vector<LibParser::lib_token_t>  LibParser::parse_tokens(const std::vector<std::string> &token_strings) {

    for (const std::string &token_string : token_strings) {
        lib_token_t token;
        if (token_string == "LBracket") {
            token.type = lib_token_type_e::LBracket;
        } else if (token_string == "RBracket") {
            token.type = lib_token_type_e::RBracket;
        } else if (token_string == "LBrace") {
            token.type = lib_token_type_e::LBrace;
        } else if (token_string == "RBrace") {
            token.type = lib_token_type_e::RBrace;
        } else if (token_string == "Colon") {
            token.type = lib_token_type_e::Colon;
        } else if (token_string == "Semicolon") {
            token.type = lib_token_type_e::Semicolon;
        } else if (token_string == "String") {
            token.type = lib_token_type_e::String;
        } else if (token_string == "Comma") {
            token.type = lib_token_type_e::Comma;
        }else if (token_string == "Asterisks") {
            token.type = lib_token_type_e::Asterisks;
        }else if (token_string == "Tilt") {
            token.type = lib_token_type_e::Tilt;
        }else if (token_string == "Plus") {
            token.type = lib_token_type_e::Plus;
        }else if (token_string == "Minus") {
            token.type = lib_token_type_e::Minus;
        }
        else if (token_string == "Quotation") {
            token.type = lib_token_type_e::Quotation;
        }else {
            token.type = lib_token_type_e::Invalid;
        }
        token.value = token_string;

        parsed_tokens.push_back(token);
    }

    return parsed_tokens;
}

LibParser::lib_pair_t LibParser::parse_pairs(const std::vector<lib_token_t> &token) {
    lib_pair_t rootPair;
    lib_pair_t *currentPair = &rootPair;

    for (const lib_token_t &token : parsed_tokens) {
        if (token.type == lib_token_type_e::String) {
            if (currentPair->type == lib_pair_type_e::Empty_Pair) {
                currentPair->type = lib_pair_type_e::String_Single;
                currentPair->key = token.value;
            } else if (currentPair->type == lib_pair_type_e::String_Single) {
                // Create a new pair for String_Pair_Colon
                lib_pair_t newPair;
                newPair.type = lib_pair_type_e::String_Pair_Colon;
                newPair.key = token.value;
                currentPair->inner_layer.push_back(newPair);
                currentPair = &currentPair->inner_layer.back();
            } else if (currentPair->type == lib_pair_type_e::String_Pair_Colon) {
                currentPair->type = lib_pair_type_e::String_Pair_Quotation;
                currentPair->value = token.value;
            }
            // Handle other cases as needed
        } else if (token.type == lib_token_type_e::Colon) {
            if (currentPair->type == lib_pair_type_e::String_Single) {
                // Create a new pair for String_Pair_Colon
                lib_pair_t newPair;
                newPair.type = lib_pair_type_e::String_Pair_Colon;
                newPair.key = currentPair->key;
                currentPair->inner_layer.push_back(newPair);
                currentPair = &currentPair->inner_layer.back();
            }
            // Handle other cases as needed
        } else if (token.type == lib_token_type_e::Quotation) {
            if (currentPair->type == lib_pair_type_e::String_Pair_Quotation) {
                currentPair->type = lib_pair_type_e::String_Single;
            }
            // Handle other cases as needed
        }
        // Handle other token types and transitions here
    }

    return rootPair;
}


