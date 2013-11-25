#ifndef WUMBO_H
#define WUMBO_H

#include <stdio.h>
#include <stdlib.h>
#include "octo.h"

/* OPERATOR STRUCT */

typedef struct operators
{

    char add = '+';
    char sub = '-';
    char mul = '*';
    char div = '/';
    char exp = '^';
    char o_paren = '(';
    char c_paren = ')';

} OPERATORS;

/* OPERATOR FUNCTIONS */

char *wum_add(char *a, char *b)
{
    return intToString((parseInt(a, 10) + parseInt(b, 10)));
}
char *wum_sub(char *a, char *b)
{
    return intToString((parseInt(a, 10) - parseInt(b, 10)));
}
char *wum_mul(char *a, char *b)
{
    return intToString((parseInt(a, 10) * parseInt(b, 10)));
}
char *wum_div(char *a, char *b)
{
    return intToString((parseInt(a, 10) / parseInt(b, 10)));
}
char *wum_exp(char *a, char *b)
{
    return intToString((pow(parseInt(a, 10), parseInt(b, 10))));
}

/* LOGICAL FUNCTIONS */

bool isOp(char k)
{
    if (k == OPERATORS.add
            || k == OPERATORS.sub
            || k == OPERATORS.mul
            || k == OPERATORS.div
            || k == OPERATORS.exp
            || k == OPERATORS.o_paren
            || k == OPERATORS.c_paren)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Better number parser */

double parseNum(char *a)
{
    double d;
    sscanf(a, "%lf", &d);
    return d;
}

/* Main parser */
char* WUMBO_parse(char* expression)
{
    while (strchr(expression, '(') != NULL)
    {
        printf("Expression: %s\n", expression);
        int startPoint = strchr(expression, '(') - expression;
        printf("Start point: %d\n", startPoint)
        int endPoint;
        int i;
        for (i = startPoint + 1; i < len(expression); i++)
        {
            if (charAt(expression, i) == OPERATORS.o_paren)
            {
                startPoint = i;
            }
            if (charAt(expression, i) == OPERATORS.c_paren)
            {
                endPoint = i;
                break;
            }
        }
        char* subsec = slice(expression, startPoint, endPoint + 1); // the sub expression with the parenthesis (2 + 3)
        printf("Subsec: %s\n", subsec);
        char* subsecnoparen = slice(subsec, startPoint + 1, endPoint)// strip away parenthesis
        free(subsec);
        char* subsecsim = parseNoParen(subsecnoparen);
        char* finexpression = replaceBetween(expression, startPoint, endPoint + 1, subsecsim);
    }
    expression = parseNoParen(finexpression);
    return expression;
};

char* parseNoParen(char* expressionWithSpaces)
{
    // Remove all whitespaces
    char* expressionWithoutSpaces = strip(expressionWithSpaces);

    // Make the expression buffer bigger
    char* expression = (char*) malloc(sizeof(char) * 100);

    // Append +
    if (charAt(expressionWithoutSpaces, 0) != '-' && charAt(expressionWithoutSpaces, 0) != '+') 
        sprintf(expression, "%c%s", +, expressionWithoutSpaces);

    free(expressionWithoutSpaces);

    // Preproccess input (sign shifts)
    int j;
    for (j = 0; j < len(expression); j++)
    {
        if (charAt(expression,j) == '+' && charAt(expression,j + 1) == '+')
        {
            char* newexp = replaceBetween(expression, j, j + 2, "+");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression,j) == '-' && charAt(expression,j + 1) == '-')
        {
            char* newexp = replaceBetween(expression, j, j + 2, "+");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression,j) == '+' && charAt(expression,j + 1) == '-')
        {
            char* newexp = replaceBetween(expression, j, j + 2, "-");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression,j) == '-' && charAt(expression,j + 1) == '+')
        {
            char* newexp = replaceBetween(expression, j, j + 2, "-");
            free(expression);
            expression = newexp;
            j--;
        }
    }

    // Single pass lexer

    char* tokens = (char*) malloc(sizeof(char) * 100);
    char* tokenTypes = (char*) malloc(sizeof(char) * 100);

    int i, k;
    for (i = 0; i < len(expression); i++)
    {

        // multiply sign
        if (charAt(expression, i) == '*')
        {
            this.tokens.push('*');
            this.tokenTypes.push('MUL');
            continue;
        }

        // divide sign
        if (charAt(expression, i) == '/')
        {
            this.tokens.push('/');
            this.tokenTypes.push('DIV');
            continue;
        }

        // exponent sign
        if (charAt(expression, i) == '^')
        {
            this.tokens.push('^');
            this.tokenTypes.push('EXP');
            continue;
        }

        // any explicitly signed number
        if (charAt(expression, i) == '+' || charAt(expression,i) == '-')
        {
            for (k = i + 1; k < len(expression); k++)
            {
                if (charAt(expression,k) == '+' || charAt(expression,k) == '-' || charAt(expression,k) == '*' || charAt(expression,k) == '/' || charAt(expression,k) == '^')
                {
                    break;
                }
            }
            this.tokens.push(expression.slice(i, k));
            this.tokenTypes.push('NUM');
            i = k - 1;
            continue;
        }

        // any generic positive number
        else
        {
            for (k = i + 1; k < len(expression); k++)
            {
                if (charAt(expression,k) == = '+' || charAt(expression,k) == = '-' || charAt(expression,k) == = '*' || charAt(expression,k) == = '/' || charAt(expression,k) == = '^')
                {
                    break;
                }
            }
            this.tokens.push('+' + expression.slice(i, k));
            this.tokenTypes.push('NUM');
            i = k - 1;
            continue;
        }

    }

    // print tokens

    for (i = 0; i < this.tokens.coreArray.length; i++)
    {
        console.log('TOKENS: ' + this.tokens.at(i) + ' ' + this.tokenTypes.at(i));
    }

    /* begin traversing and simplifying the intermediate representation */

    // exponents
    for (i = 0; i < this.tokens.coreArray.length; i++)
    {
        if (this.tokenTypes.at(i) == 'EXP' && this.tokenTypes.at(i + 1) == = 'NUM' && this.tokenTypes.at(i - 1) == = 'NUM')
        {
            this.tokens.setAt(i - 1, wum_exp(this.tokens.at(i - 1), this.tokens.at(i + 1)));
            this.tokens.delete(i);
            this.tokens.delete(i);
            this.tokenTypes.setAt(i - 1, 'NUM');
            this.tokenTypes.delete(i);
            this.tokenTypes.delete(i);
            i = -1;
            continue;
        }
    }

    // multiplication and division
    for (i = 0; i < this.tokens.coreArray.length; i++)
    {
        if ((this.tokenTypes.at(i) == = 'MUL' || this.tokenTypes.at(i) == = 'DIV') && this.tokenTypes.at(i + 1) == = 'NUM' && this.tokenTypes.at(i - 1) == = 'NUM')
        {
            if (this.tokenTypes.at(i) == = 'MUL')
            {
                this.tokens.setAt(i - 1, wum_mul(this.tokens.at(i - 1), this.tokens.at(i + 1)));
                this.tokens.delete(i);
                this.tokens.delete(i);
                this.tokenTypes.setAt(i - 1, 'NUM');
                this.tokenTypes.delete(i);
                this.tokenTypes.delete(i);
                i = -1;
                continue;
            }
            if (this.tokenTypes.at(i) == = 'DIV')
            {
                this.tokens.setAt(i - 1, wum_div(this.tokens.at(i - 1), this.tokens.at(i + 1)));
                this.tokens.delete(i);
                this.tokens.delete(i);
                this.tokenTypes.setAt(i - 1, 'NUM');
                this.tokenTypes.delete(i);
                this.tokenTypes.delete(i);
                i = -1;
                continue;
            }
        }
    }

    // normal addition
    for (i = 0; i < this.tokens.coreArray.length; i++)
    {
        if (this.tokenTypes.at(i) == = 'NUM' && this.tokenTypes.at(i + 1) == = 'NUM')
        {
            this.tokens.setAt(i, wum_add(this.tokens.at(i), this.tokens.at(i + 1)));
            this.tokens.delete(i + 1);
            this.tokenTypes.setAt(i, 'NUM');
            this.tokenTypes.delete(i + 1);
            i = -1;
            continue;
        }
    }
    // assemble IR back to string

    for (i = 0; i < this.tokens.coreArray.length; i++)
    {
        console.log('TOKENS NEW: ' + this.tokens.at(i) + ' ' + this.tokenTypes.at(i));
    }
    expression = this.tokens.coreArray.join("");

    // Clear tokens and token types
    this.tokens.coreArray = [];
    this.tokenTypes.coreArray = [];
    return expression;
}

#endif /* WUMBO_H */
