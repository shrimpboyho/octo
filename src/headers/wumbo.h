#ifndef WUMBO_H
#define WUMBO_H

#include <stdio.h>
#include <stdlib.h>
#include "octo.h"

/* DYNAMIC VECTOR STRUCTURE */

/* Token type constants */

#define NUM 1
#define MUL 2
#define EXP 3
#define DIV 4

/* String literals */

char* MUL_SIGN = "*";
char* DIV_SIGN = "/";
char* EXP_SIGN = "^";

/* Create a ghetto boolean data type */

typedef int bool;
#define TRUE  1
#define FALSE 0

/* NODE STRUCTURE */

typedef struct node
{

    char *tokenValue;
    int tokenType;

    int pos; /* Index of node */
    struct node *next; /* Pointer to next node */

} NODE;

/* Generates a single node */
NODE *generateNode();

/* Generates linked nodes and returns the first node */
NODE *generateNodes(int num);

/* Appends a node at the end of the list */
NODE *appendNode(NODE *start);

/* Gets a node at a certain index */
NODE *getNode(NODE *start, int index);

/* Returns the length of a list of nodes */
size_t getNodeListLength(NODE *start);

/* Removes a node at a certain index */
NODE *deleteNode(NODE *start, int index);

NODE *generateNode()
{
    NODE *newone = (NODE *) malloc(sizeof(NODE));
    newone -> pos = 0;
    newone -> next = NULL;
    return newone;
}

NODE *generateNodes(int num)
{
    NODE *one = generateNode();
    NODE *cpy = one;

    int i;

    for (i = 0; i < num - 1; i++)
    {

        NODE *next = generateNode();
        cpy -> next = next;
        cpy -> pos = i;
        cpy = next;

    }

    cpy -> pos = i;
    cpy -> next = NULL;

    return one;
}

NODE *getNode(NODE *start, int index)
{
    int i;
    for (i = 0; i < index; i++)
    {
        start = start -> next;
    }
    return start;
}

size_t getNodeListLength(NODE *start)
{
    size_t i = 1;
    while (start -> next != NULL)
    {
        start = start -> next;
        if (start == NULL)
            return NULL;
        i++;
    }
    return i;
}

NODE *deleteNode(NODE *start, int index)
{
    if (index + 1 == getNodeListLength(start))
    {
        NODE *r = getNode(start, index);
        NODE *c = getNode(start, index - 1);
        c -> next = NULL;
        free(r);
        return start;
    }
    if (index > 0)
    {
        NODE *f = getNode(start, index - 1);
        NODE *l = getNode(start, index + 1);
        NODE *d = getNode(start, index);
        f -> next = l;
        free(d);
        return start;
    }
    if (index == 0)
    {
        NODE *up = start -> next;
        free(start);
        return up;
    }
}

NODE *appendNode(NODE *start)
{
    int len = getNodeListLength(start);
    NODE *last = getNode(start, len - 1);
    NODE *n = generateNode();
    n -> pos = len;
    n -> next = NULL;
    last -> next = n;
    return n;
}

/* OPERATOR STRUCT */

typedef struct
{

    char add;
    char sub;
    char mul;
    char div;
    char exp;
    char o_paren;
    char c_paren;

} op;

op OPERATORS = {'+', '-', '*', '/', '^', '(', ')'};

/* Better number parser */

double parseNum(char *a, int radix)
{
    double d;
    sscanf(a, "%lf", &d);
    printf("\nConverted string %s to double %lf", a, d);
    return d;
}

char *doubleToString(double thing)
{
    char *str = (char *) malloc(sizeof(char) * 30);
    sprintf(str, "%lf", thing);
    printf("\nConverted double %lf to string %s", thing, str);
    return str;
}

/* Function to remove characters */

void remchars(char *str, char c)
{
    char *pos;
    while (pos = strchr(str, c))
        memmove(pos, pos + 1, strlen(pos));
}

/* OPERATOR FUNCTIONS */

char *wum_add(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) + parseNum(b, 10)));
}
char *wum_sub(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) - parseNum(b, 10)));
}
char *wum_mul(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) * parseNum(b, 10)));
}
char *wum_div(char *a, char *b)
{
    return doubleToString((parseNum(a, 10) / parseNum(b, 10)));
}
char *wum_exp(char *a, char *b)
{
    return doubleToString((pow(parseNum(a, 10), parseNum(b, 10))));
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
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

char *parseNoParen(char *expressionWithSpaces)
{

    printf("\nExpression given to parseNoParen(): %s", expressionWithSpaces);

    // Remove all whitespaces
    remchars(expressionWithSpaces, ' ');
    char *expressionWithoutSpaces = expressionWithSpaces;

    printf("\nExpression no whitespace: %s", expressionWithoutSpaces);

    char *tmpexp = makeCopy(expressionWithoutSpaces);

    // Make the expression buffer bigger
    char *expression = (char *) malloc(sizeof(char) * 100);

    // Append +
    if (charAt(tmpexp, 0) != '-' && charAt(tmpexp, 0) != '+')
        sprintf(expression, "%c%s", '+', tmpexp);
    else
        sprintf(expression, "%s", tmpexp);
    free(expressionWithSpaces);
    free(tmpexp);

    printf("\nExpression With + Signs: %s", expression);

    // Preproccess input (sign shifts)
    int j;
    for (j = 0; j < len(expression); j++)
    {
        if (charAt(expression, j) == '+' && charAt(expression, j + 1) == '+')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "+");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression, j) == '-' && charAt(expression, j + 1) == '-')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "+");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression, j) == '+' && charAt(expression, j + 1) == '-')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "-");
            free(expression);
            expression = newexp;
            j--;
        }
        if (charAt(expression, j) == '-' && charAt(expression, j + 1) == '+')
        {
            char *newexp = replaceBetween(expression, j, j + 2, "-");
            free(expression);
            expression = newexp;
            j--;
        }
    }

    printf("\nAfter Preproccessor: %s", expression);

    /* Single pass lexer */

    NODE *tokens = generateNode();
    tokens -> tokenValue = NULL;

    int i, k;
    for (i = 0; i < len(expression); i++)
    {

        // multiply sign
        if (charAt(expression, i) == '*')
        {
            printf("\nFound a multiplication sign.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = MUL_SIGN;
            newone -> tokenType = MUL;
            continue;
        }

        // divide sign
        if (charAt(expression, i) == '/')
        {
            printf("\nFound a division sign.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = DIV_SIGN;
            newone -> tokenType = DIV;
            continue;
        }

        // exponent sign
        if (charAt(expression, i) == '^')
        {
            printf("\nFound an exponentiation sign.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = EXP_SIGN;
            newone -> tokenType = EXP;
            continue;
        }

        // any explicitly signed number
        if (charAt(expression, i) == '+' || charAt(expression, i) == '-')
        {
            for (k = i + 1; k < len(expression); k++)
            {
                if (charAt(expression, k) == '+' || charAt(expression, k) == '-' || charAt(expression, k) == '*' || charAt(expression, k) == '/' || charAt(expression, k) == '^')
                    break;
            }
            printf("\nFound an explicitly signed number.");
            NODE *newone = appendNode(tokens);
            newone -> tokenValue = slice(expression, i, k - 1, 100);
            newone -> tokenType = NUM;
            i = k - 1;
            continue;
        }

        // any generic positive number
        else
        {
            for (k = i + 1; k < len(expression); k++)
            {
                if (charAt(expression, k) == '+' || charAt(expression, k) == '-' || charAt(expression, k) == '*' || charAt(expression, k) == '/' || charAt(expression, k) == '^')
                    break;
            }
            printf("\nFound a generic positive number.");
            NODE *newone = appendNode(tokens);
            char *buffer = malloc(sizeof(char) * 100);
            sprintf(buffer, "%s%s", "+", slice(expression, i, k, 100));
            newone -> tokenValue = buffer;
            newone -> tokenType = NUM;
            i = k - 1;
            continue;
        }

    }

    /* Print out the lexer tokens */

    tokens = deleteNode(tokens, 0);

    printf("\nFinished Lexing the Input:");
    printf("\nTOKEN\tTYPE");

    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        printf("\n%s\t%d", getNode(tokens, i) -> tokenValue, getNode(tokens, i) -> tokenType);
    }

    /* begin traversing and simplifying the intermediate representation */

    // exponents
    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        if (getNode(tokens, i) != NULL && getNode(tokens, i + 1) != NULL)
        {
            if (getNode(tokens, i) -> tokenType == EXP && getNode(tokens, i + 1) -> tokenType == NUM && getNode(tokens, i - 1) -> tokenType == NUM)
            {
                printf("\nExponentiating %s and %s", getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i - 1) -> tokenValue = wum_exp(getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i - 1) -> tokenType = NUM;
                deleteNode(tokens, i);
                deleteNode(tokens, i);
                printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                i = -1;
                continue;
            }
        }
    }

    // multiplication and division
    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        if (getNode(tokens, i) != NULL && getNode(tokens, i + 1) != NULL)
        {
            if ((getNode(tokens, i) -> tokenType == MUL || getNode(tokens, i) -> tokenType == DIV) && getNode(tokens, i + 1) -> tokenType == NUM && getNode(tokens, i - 1) -> tokenType == NUM)
            {
                if (getNode(tokens, i) -> tokenType == MUL)
                {
                    
                    /* TODO: Make this compact like the rest of the logic */
                    char* firstNum = getNode(tokens, i - 1) -> tokenValue;
                    char* secondNum = getNode(tokens, i + 1) -> tokenValue;
                    printf("\nMultiplying %s and %s", firstNum, secondNum);
                    getNode(tokens, i - 1) -> tokenValue = wum_mul(firstNum, secondNum);
                    getNode(tokens, i - 1) -> tokenType = NUM;
                    deleteNode(tokens, i);
                    deleteNode(tokens, i);
                    free(firstNum);
                    free(secondNum);
                    printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                    i = -1;
                    continue;
                }
                if (getNode(tokens, i) -> tokenType == DIV)
                {
                    printf("\nDividing: %s and %s", getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                    getNode(tokens, i - 1) -> tokenValue = wum_div(getNode(tokens, i - 1) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                    getNode(tokens, i - 1) -> tokenType = NUM;
                    deleteNode(tokens, i);
                    deleteNode(tokens, i);
                    printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                    i = -1;
                    continue;
                }
            }
        }
    }

    // normal addition
    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        if (getNode(tokens, i) != NULL && getNode(tokens, i + 1) != NULL)
        {
            if (getNode(tokens, i) -> tokenType == NUM && getNode(tokens, i + 1) -> tokenType == NUM)
            {
                printf("\nAdding: %s and %s", getNode(tokens, i) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i) -> tokenValue = wum_add(getNode(tokens, i) -> tokenValue, getNode(tokens, i + 1) -> tokenValue);
                getNode(tokens, i) -> tokenType = NUM;
                deleteNode(tokens, i + 1);
                printf("\nSolution: %s", getNode(tokens, i - 1) -> tokenValue);
                i = -1;
                continue;
            }
        }
    }
    // assemble IR back to string

    printf("\nConverting internal representation into a string.");

    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        printf("\nNEW TOKEN: %s \nNEW TOKEN TYPE: %d", getNode(tokens, i) -> tokenValue, getNode(tokens, i) -> tokenType);
    }

    char *buffy = (char *) malloc(sizeof(char) * 100);
    sprintf(buffy, "");

    for (i = 0; i < getNodeListLength(tokens); i++)
    {
        sprintf(buffy + strlen(buffy), "%s", getNode(tokens, i) -> tokenValue);
    }

    /* TODO: FREE ALL THE MEMORY USED BY THE NODE LIST */

    NODE* head = tokens;
    while(head -> next != NULL)
    {
        NODE* temp = head;
        head = head -> next;
        if(temp -> tokenType == NUM)
            free(temp -> tokenValue);
        free(temp);
    }

    return buffy;
}

/* Main parser */
double WUMBO_parse(char *expression)
{
    char *finexpression = makeCopy(expression);
    while (strchr(finexpression, '(') != NULL)
    {
        printf("Expression: %s\n", finexpression);
        int startPoint = strchr(finexpression, '(') - finexpression;
        printf("Start point: %d\n", startPoint);
        int endPoint;
        int i;
        for (i = startPoint + 1; i < len(expression); i++)
        {
            if (charAt(finexpression, i) == OPERATORS.o_paren)
            {
                startPoint = i;
            }
            if (charAt(finexpression, i) == OPERATORS.c_paren)
            {
                endPoint = i;
                break;
            }
        }
        char *subsec = slice(finexpression, startPoint, endPoint + 1, 0); // the sub expression with the parenthesis (2 + 3)
        printf("\nSubsection: %s", subsec);
        char *subsecnoparen = slice(finexpression, startPoint + 1, endPoint - 1, 0);// strip away parenthesis
        free(subsec);
        printf("\nSubsection after stripping parenthesis: %s", subsecnoparen);
        char *subsecsim = parseNoParen(subsecnoparen);
        char *temp = finexpression;
        finexpression = replaceBetween(finexpression, startPoint, endPoint + 1, subsecsim);
        free(temp);
    }
    finexpression = parseNoParen(finexpression);
    double answer = parseNum(finexpression, 10);
    free(finexpression);
    return answer;
};

#endif /* WUMBO_H */
