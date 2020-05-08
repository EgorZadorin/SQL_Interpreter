//1. H -> +P | -S | *M | (O | )C | [A-z]I | [0-9]N | ' 'H | '\n'H | '\0'_|_
//   P -> _|_
//   S -> _|_
//   M -> _|_
//   O -> _|_
//   C -> _|_
//   I -> [A-z]I | [0-9]I1 | _|_
//   I1 -> [0-9]I1 | _|_
//   N -> [0-9]N | _|_
//
//=============================================================================
//
//2. E -> MD
//   D -> +MD | -MD | END
//   M -> FK
//   K -> *FK | END
//   F -> (E) | num | iden
//
//=============================================================================
//
//3. first(+MD) && first(-MD) = {}
//   first((E)) && first(num) = {}
//   first(num) && first (iden) = {}
//   first((E)) && first (iden) = {}
//   first(D) && follow (D) = {}
//   first(K) && follow (K) = {}
//
//=============================================================================


#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include <stack>
#include <locale>

class Poliz_to_inf{
    std::string poliz;
    public:
        Poliz_to_inf(std::string str){poliz = str;}
        std::string to_inf() const;
};

class Poliz_simplify{
    std::string poliz;
    public:
        Poliz_simplify(std::string str){poliz = str;}
        std::string simplify();
};

std::string Poliz_to_inf::to_inf() const{
    std::stack <std::string> string_stack;
    std::stack <int> priority_stack;
    std::string num = "";
    std::string iden = "";
    std::string expr1;
    std::string expr2;
    int expr1_priority;
    int expr2_priority;
    int i = 0;
    char c = poliz[0];

    while(i < poliz.length()){
        if (std::isspace(c)){
            i++;
            if (i < poliz.length())
                c = poliz[i];
        } else if (std::isdigit(c) || std::isalpha(c)){
            while(!std::isspace(c) && i < poliz.length()){
                num += c;
                i++;
                if (i < poliz.length())
                    c = poliz[i];
            }
            string_stack.push(num);
            num = "";
            priority_stack.push(3);
        } else if (c == '*'){
            expr2 = string_stack.top();
            string_stack.pop();
            expr1 = string_stack.top();
            string_stack.pop();
            expr2_priority = priority_stack.top();
            priority_stack.pop();
            expr1_priority = priority_stack.top();
            priority_stack.pop();
            if (expr1_priority == 1 && expr2_priority != 1){
                string_stack.push("(" + expr1 + ")" + "*" + expr2);
                priority_stack.push(2);
            } else if (expr2_priority == 1 && expr1_priority != 1){
                string_stack.push(expr1 + "*" + "(" + expr2 + ")");
                priority_stack.push(2);
            } else if (expr2_priority == 1 && expr1_priority == 1){
                string_stack.push("(" + expr1 + ")" + "*" + "(" + expr2 + ")");
                priority_stack.push(2);
            } else {
                string_stack.push(expr1 + "*" + expr2);
                priority_stack.push(2);
            }
            i++;
            if (i < poliz.length())
                c = poliz[i];
        } else if (c == '+'){
            expr2 = string_stack.top();
            string_stack.pop();
            expr1 = string_stack.top();
            string_stack.pop();
            priority_stack.pop();
            priority_stack.pop();

            string_stack.push(expr1 + "+" + expr2);
            priority_stack.push(1);
            i++;
            if (i < poliz.length())
                c = poliz[i];
        } else if (c == '-'){
            expr2 = string_stack.top();
            string_stack.pop();
            expr1 = string_stack.top();
            string_stack.pop();
            priority_stack.pop();
            priority_stack.pop();
            string_stack.push(expr1 + "-" + expr2);
            priority_stack.push(1);
            i++;
            if (i < poliz.length())
                c = poliz[i];
        }
    }
    return string_stack.top();
}

std::string Poliz_simplify::simplify(){
    std::stack <std::string> string_stack;
    std::string num = "";
    std::string iden = "";
    std::string expr1;
    std::string expr2;
    int i = 0;
    char c = poliz[0];

    while(i < poliz.length()){
        if (std::isspace(c)){
            i++;
            if (i < poliz.length())
                c = poliz[i];
        } else if (std::isdigit(c) || std::isalpha(c)){
            while(!std::isspace(c) && i < poliz.length()){
                num += c;
                i++;
                if (i < poliz.length())
                    c = poliz[i];
            }
            string_stack.push(num);
            num = "";
        } else if (c == '*'){
            expr2 = string_stack.top();
            string_stack.pop();
            expr1 = string_stack.top();
            string_stack.pop();
            if (expr1 == "0" || expr2 == "0")
                string_stack.push(0);
            else 
                string_stack.push(expr1 + " " + expr2 + " *");
            i++;
            if (i < poliz.length())
                c = poliz[i];
        } else if (c == '+' || c == '-'){
            expr2 = string_stack.top();
            string_stack.pop();
            expr1 = string_stack.top();
            string_stack.pop();
            if (expr1 == "0"){
                string_stack.push(expr2);
            } else if (expr2 == "0"){
                string_stack.push(expr1);
            } else {
                if (c == '+')
                    string_stack.push(expr1 + " " + expr2 + " +");
                if (c == '-')
                    string_stack.push(expr1 + " " + expr2 + " -");
            i++;
            if (i < poliz.length())
                c = poliz[i];
            }
        }
    }
    return string_stack.top();
}

        

enum lex_type_t { PLUS, MINUS, MULT, NUMBER, OPEN, CLOSE, IDEN, END };


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
        enum state_t {H, D, P, M, O, C, N, A, B, OK} state = H;
        while (state != OK) {
            switch (state) {
            case H:
                if (c == '\n') {
                    cur_lex_type = END;
                    state = OK;
                } else if (std::isspace(c)) {
                    // stay in H
                } else if (c == '+') {
                    state = P;
                } else if (c == '*') {
                    state = M;
                } else if (c == '-') {
                    state = D;
                } else if (c == '(') {
                    state = O;
                } else if (c == ')') {
                    state = C;
                } else if (std::isdigit(c)) {
                    state = N;
                } else if (std::isalpha(c)) {
                    state = A;
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
            case D:
                cur_lex_type = MINUS;
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
            case A:
                if (std::isalpha(c)) {
                    //stay in I
                } else if (std::isdigit(c)) {
                    state = B;
                } else {
                    cur_lex_type = IDEN;
                    state = OK;
                }
                break;
            case B:
                if (std::isdigit(c)) {
                    //stay in A
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
                    ++cur_lex_pos;
                    ++cur_lex_end_pos;
                } else {
                    ++cur_lex_end_pos;
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
        while (lexer::cur_lex_type == PLUS || lexer::cur_lex_type == MINUS) {
            if (lexer::cur_lex_type == PLUS){
                lexer::next();
                estr = estr + " " + M() + " +";
            } else {
                lexer::next();
                estr = estr + " " + M() + " -";
            }
        }
        return estr;
    }

    std::string M()
    {
        std::string mstr = F();
        while (lexer::cur_lex_type == MULT) {
            lexer::next();
            mstr = mstr + " " + F() + " *";
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
    std::string poliz;
    try {
        loop_parser_actions::init();
        poliz = loop_parser_actions::E();
        if (lexer::cur_lex_type != END) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
            std::cout << poliz << std::endl;
        }
    } catch (const std::logic_error &e) {
        std::cout << "NO" << std::endl;
        return 1;
    }
    Poliz_to_inf infer(poliz);
    std::cout << infer.to_inf() << std::endl;
    Poliz_simplify simplifier(poliz);
    std::cout << simplifier.simplify() << std::endl;
}
