#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <ostream>

using namespace std;

class Token
{
public:
    // Tipos de token
    enum Type
    {
        PLUS,   // +
        MINUS,  // -
        MUL,    // *
        DIV,    // /
        POW,    // ^
        LPAREN, // (
        RPAREN, // )
        MINOR,  // <
        MAYOR,  // >
        EQUAL,  // ==
        DIF,    // !=
        NUM,    // Número
        ERR,    // Error
        BIN,    // Binary
        SIN,    // sin
        COS,    // cos
        LOG,    // log
        TRUE,   // True
        FALSE,  // False
        END     // Fin de entradaso
    };

    // Atributos
    Type type;
    string text;

    // Constructores
    Token(Type type);
    Token(Type type, char c);
    Token(Type type, const string &source, int first, int last);

    // Sobrecarga de operadores de salida
    friend ostream &operator<<(ostream &outs, const Token &tok);
    friend ostream &operator<<(ostream &outs, const Token *tok);
};

#endif // TOKEN_H