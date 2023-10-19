//
// Created by chen on 10/17/23.
//

#ifndef MBIST_CLUSTER_PARSER_LIB_PARSER_H_
#define MBIST_CLUSTER_PARSER_LIB_PARSER_H_

#include <string>
#include <vector>
class LibParser{
public:
    static std::vector<std::string> tokenize_input_file(const std::string &filename);

    enum class lib_token_type_e {
        LBracket,         // (
        RBracket,         // )
        LBrace,           // {
        RBrace,           // }
        Colon,            // :
        Semicolon,        // ;
        Comma,            // ,
        Asterisks,        // *
        Tilt,             // "\"
        Plus,        // +
        Minus,       // -
        Quotation,  // "
        String,           // "string"
        Invalid           // invalid token
    };


    struct lib_token_t {
        lib_token_type_e type;
        std::string value;
    };

    enum class lib_pair_type_e {
        String_Pair_Colon,            // a : b
        String_Pair_Quotation,    //a:"b"
        String_Pair_Brackets,      //a(b)
        String_Single,          // a;
        List_Pair,              // a { list }
        String_List_Pair,        // a(b) { list }
        Empty_Pair
    };

    struct lib_pair_t {
        lib_pair_type_e type;
        std::string key;
        std::string value;
        std::vector<lib_pair_t> inner_layer;
        std::vector<lib_pair_t> *parent_layer;
    };
    std::vector<lib_token_t> parse_tokens(const std::vector<std::string> &token_strings);
    lib_pair_t parse_pairs(const std::vector<lib_token_t>&token);

private:


    std::vector<lib_token_t> parsed_tokens;
    static std::string delete_leading_spaces(const std::string &input);

    static std::string process_token(const std::string &token);



};


#endif  //MBIST_CLUSTER_PARSER_LIB_PARSER_H_
