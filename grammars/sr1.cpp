/**************************************************************************************************************************************
E -> M <bool e = stack.top; stack.pop> {+ M <e = false;>} <stack.push(e);>

M -> F <bool m = stack.top; stack.pop> {* F <m = false;>} <stack.push(m);>

F -> ( E <bool f = stack.top; stack.pop; if (f) error();> ) <stack.push(true);> | num <stack.push(false);> | iden <stack.push(false);>
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

    std::stack<bool> computation_stack;

    void E();

    void M();

    void F();

    void E()
    {
        M();
        bool e = computation_stack.top();
        computation_stack.pop();
        while (lexer::cur_lex_type == PLUS) {
            lexer::next();
            M();
            e = false;
        }
        computation_stack.push(e);
    }

    void M()
    {
        F();
        bool m = computation_stack.top();
        computation_stack.pop();
        while (lexer::cur_lex_type == MULT) {
            lexer::next();
            F();
            m = false;
        }
        computation_stack.push(m);
    }

    void F()
    {
        if (lexer::cur_lex_type == OPEN) {
            lexer::next();
            E();
            bool f = computation_stack.top();
            computation_stack.pop();
            if (f) 
                throw std::logic_error("double bracket");
            if (lexer::cur_lex_type != CLOSE) {
                throw std::logic_error(
                        std::to_string(lexer::cur_lex_pos) + ": "
                        "unexpected token; ) is expected;"
                        " got <<" + lexer::cur_lex_text + ">>");
            }
            lexer::next();
            computation_stack.push(true);
        } else if (lexer::cur_lex_type == NUMBER) {
            lexer::next();
            computation_stack.push(false);
        } else if (lexer::cur_lex_type == IDEN) {
            lexer::next();
            computation_stack.push(false);
        } else {
            throw std::logic_error(
                        std::to_string(lexer::cur_lex_pos) + ": "
                        "unexpected token; ( or number are expected;"
                        " got <<" + lexer::cur_lex_text + ">>");
        }
    }
}

int main()
{
    try {
        loop_parser_actions::init();
        loop_parser_actions::E();
        if (lexer::cur_lex_type != END) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
        }
    } catch (const std::logic_error &e) {
    std::cout << "NO" << std::endl;
    }
}
