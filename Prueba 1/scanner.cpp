#include <iostream>
#include <cstring>
#include <fstream>
#include "token.h"
#include "scanner.h"

using namespace std;

// -----------------------------
// Constructor
// -----------------------------
Scanner::Scanner(const char *s) : input(s), first(0), current(0)
{
}

// -----------------------------
// Función auxiliar
// -----------------------------

bool is_white_space(char c)
{
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

// -----------------------------
// nextToken: obtiene el siguiente token
// -----------------------------

Token *Scanner::nextToken()
{
    Token *token;
    char c;
    state = 0;
    first = current;
    ;

    while (1)
    {
        switch (state)
        {
        case 0:
            c = nextChar();
            if (is_white_space(c))
            {
                first = current;
                state = 0;
            }
            else if (c == '\0' or c == '#')
                return new Token(Token::END);
            else if (c == '(')
                state = 1;
            else if (c == ')')
                state = 2;
            else if (c == '+')
                state = 3;
            else if (c == '-')
                state = 4;
            else if (c == '*')
                state = 5;
            else if (c == '/')
                state = 6;
            else if (c == '^')
                state = 7;
            else if (c == '<')
                state = 12;
            else if (c == '>')
                state = 13;
            else if (c == '=')
                state = 14;
            else if (c == '!')
                state = 14;
            else if (isdigit(c))
                if (c == '0')
                    state = 10;
                else
                    state = 8;
            else if (isalpha(c))
                state = 30;
            else
                return new Token(Token::ERR, c);
            break;

        case 1:
            return new Token(Token::LPAREN, c);
        case 2:
            return new Token(Token::RPAREN, c);
        case 3:
            return new Token(Token::PLUS, c);
        case 4:
            return new Token(Token::MINUS, c);
        case 5:
            return new Token(Token::MUL, c);
        case 6:
            return new Token(Token::DIV, c);
        case 7:
            return new Token(Token::POW, c);

        case 8:
            c = nextChar();
            if (isdigit(c))
                state = 8;
            else
                state = 9;
            break;

        case 9:
            rollBack();
            return new Token(Token::NUM, input, first, current - first);

        case 10:
            c = nextChar();
            if (c == 'b')
                state = 11;
            else if (isdigit(c))
                state = 8;
            else
                state = 9;
            break;

        case 11:
            c = nextChar();
            if (c == '0' or c == '1')
                state = 11;
            else
            {
                rollBack();
                return new Token(Token::BIN, input, first, current - first);
            }
            break;

        case 12:
            return new Token(Token::MINOR, c);
        case 13:
            return new Token(Token::MAYOR, c);
        case 14:
            c = nextChar();
            if (c == '=')
            {
                return new Token(Token::EQUAL, input, first, current - first);
            }
            else if (c == '!')
            {
                return new Token(Token::DIF, input, first, current - first);
            }
            else
            {
                return new Token(Token::ERR, c);
            }

        case 30:
            c = nextChar();
            if (isalpha(c))
                state = 30;
            else
                state = 31;
            break;

        case 31:
        {
            rollBack();
            string text = input.substr(first, current - first);

            while (!text.empty() && !isalpha(text.back()))
            {
                text.pop_back();
                current--;
            }

            if (text == "SIN" || text == "sin")
                return new Token(Token::SIN, input, first, current - first);
            else if (text == "COS" || text == "cos")
                return new Token(Token::COS, input, first, current - first);
            else if (text == "LOG" || text == "log")
                return new Token(Token::LOG, input, first, current - first);
            else if (text == "TRUE" || text == "true" || text == "True")
                return new Token(Token::TRUE, input, first, current - first);
            else if (text == "FALSE" || text == "false" || text == "False")
                return new Token(Token::FALSE, input, first, current - first);
            else
                return new Token(Token::ERR, input, first, current - first);
        }
        }
    }
}

void Scanner::rollBack()
{
    if (input[current] != '\0')
        current--;
}

char Scanner::nextChar()
{
    int c = input[current];
    if (c != '\0')
        current++;
    return c;
}

// -----------------------------
// Destructor
// -----------------------------
Scanner::~Scanner() {}

// -----------------------------
// Función de prueba
// -----------------------------

void ejecutar_scanner(Scanner *scanner, const string &InputFile)
{
    Token *tok;

    // Crear nombre para archivo de salida
    string OutputFileName = InputFile;
    size_t pos = OutputFileName.find_last_of(".");
    if (pos != string::npos)
    {
        OutputFileName = OutputFileName.substr(0, pos);
    }
    OutputFileName += "_tokens.txt";

    ofstream outFile(OutputFileName);
    if (!outFile.is_open())
    {
        cerr << "Error: no se pudo abrir el archivo " << OutputFileName << endl;
        return;
    }

    outFile << "Iniciando Scanner para archivo: " << InputFile << endl
            << endl;

    while (true)
    {
        tok = scanner->nextToken();

        if (tok->type == Token::END)
        {
            outFile << *tok << endl;
            delete tok;
            outFile << "\nScanner exitoso" << endl
                    << endl;
            outFile.close();
            return;
        }

        if (tok->type == Token::ERR)
        {
            outFile << *tok << endl;
            delete tok;
            outFile << "Caracter invalido" << endl
                    << endl;
            outFile << "Scanner no exitoso" << endl
                    << endl;
            outFile.close();
            return;
        }

        outFile << *tok << endl;
        delete tok;
    }
}
