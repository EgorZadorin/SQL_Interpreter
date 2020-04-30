/**************************************************************************************************************************************
E -> <string estr => M {+ <estr = "+(" + estr + "," +> M <+ ")";>} <return estr;>
M -> <string mstr => F {* <mstr = "*(" + mstr + "," +> F <+ ")";>} <return mstr;>
F -> <string fstr;> ( <fstr => E ) <return fstr;> | num <fstr = cur_lex_text;> <return fstr;> | iden <fstr = cur_lex_text;> <return fstr;>
****************************************************************************************************************************************/


#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include <stack>
#include <locale>

enum lex_type_t { PLUS, MULT, NUMBER, OPEN, CLOSE, IDEN, END };

namespace lexer {
    int cur_lex_pos {0};
    int cur_lex_end_pos {0};
    enum lex_type_t cur_lex_type;
    std::string cur_lex_text;

    int c;
    void init()
    {
        c = std::cin.get();
    }

    void next()
    {
        cur_lex_text.clear();
        cur_lex_pos = cur_lex_end_pos;
        enum state_t {H, N, P, M, O, C, I, OK} state = H;
        while (state != OK) {
            switch (state) {
            case H:
                if (c == '+') {
                    state = P;
                } else if (c == '*') {
                    state = M;
                } else if (c == '(') {
                    state = O;
                } else if (c == ')') {
                    state = C;
                } else if (std::isdigit(c)) {
                    state = N;
                } else if (std::isalpha(c)) {
                    state = I;
                } else if (c == '\n') {
                    cur_lex_type = END;
                    state = OK;
                } else if (std::isspace(c)){
                   // stay in H
                } else {
                    throw std::logic_error(
                            std::to_string(cur_lex_end_pos) + ": "
                            "unexpected character with code " + std::to_string(c));
                }
                break;

            case N:
                if (std::isdigit(c)) {
                    // stay in N
                } else {
                    cur_lex_type = NUMBER;
                    state = OK;
                }
                break;

            case P:
                cur_lex_type = PLUS;
                state = OK;
                break;

            case M:
                cur_lex_type = MULT;
                state = OK;
                break;

            case O:
                cur_lex_type = OPEN;
                state = OK;
                break;

            case C:
                cur_lex_type = CLOSE;
                state = OK;
                break;
            
            case I:
                if (std::isalpha(c) || std::isdigit(c)){
                    //stay in I
                } else {
                    cur_lex_type = IDEN;
                    state = OK;
                }
            break;
           
            case OK:
                break;
            }

            if (state != OK) {
                if (std::isspace(c)) {
                    ++ cur_lex_pos;
                    ++ cur_lex_end_pos;
                } else {
                    ++ cur_lex_end_pos;
                }

                if (!std::isspace(c) && cur_lex_type != END) {
                    cur_lex_text.push_back(c);
                }

                c = std::cin.get();
           }
        }
    }
}

namespace loop_parser_actions {

    void init()
    {
        lexer::init();
        lexer::next();
    }

    std::string E();

    std::string M();

    std::string F();

    std::string E()
    {
        std::string estr = M();
        while (lexer::cur_lex_type == PLUS) {
            lexer::next();
            estr = "+(" + estr + "," + M() + ")";
        }
        return estr;
    }

    std::string M()
    {
        std::string mstr = F();
        while (lexer::cur_lex_type == MULT) {
            lexer::next();
            mstr = "*(" + mstr + "," + F() + ")";
        }
        return mstr;
    }

    std::string F()
    {
        std::string fstr;
        if (lexer::cur_lex_type == OPEN) {
            lexer::next();
            fstr = E();
            if (lexer::cur_lex_type != CLOSE) {
                throw std::logic_error(
                        std::to_string(lexer::cur_lex_pos) + ": "
                        "unexpected token; ) is expected;"
                        " got <<" + lexer::cur_lex_text + ">>");
            }
            lexer::next();
        } else if (lexer::cur_lex_type == NUMBER) {
            fstr = lexer::cur_lex_text;
            lexer::next();
        } else if (lexer::cur_lex_type == IDEN) {
            fstr = lexer::cur_lex_text;
            lexer::next();
        } else {
            throw std::logic_error(
                        std::to_string(lexer::cur_lex_pos) + ": "
                        "unexpected token; ( or number are expected;"
                        " got <<" + lexer::cur_lex_text + ">>");
        }
        
        return fstr;
    }
}

int main(){
    std::string ans;
    try {
        loop_parser_actions::init();
        ans = loop_parser_actions::E();
        if (lexer::cur_lex_type != END) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
            std::cout << ans << std::endl;
        }
    } catch (const std::logic_error &e) {
    std::cout << "NO" << std::endl;
    }
}
