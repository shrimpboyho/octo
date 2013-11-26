%{
    #include<stdio.h>
    #include "y.tab.h"
    char *strclone(char *str);
    /*
    #define STRING "str"
    #define NUMBER "number"
    #define O_BEGIN "o_begin"
    #define O_END "o_end"
    #define A_BEGIN "a_begin"
    #define A_END "a_end"
    #define COMMA "comma"
    */
%}
DIGIT1to9 [1-9]
DIGIT [0-9]
DIGITS {DIGIT}+
INT {DIGIT}|{DIGIT1to9}{DIGITS}|-{DIGIT}|-{DIGIT1to9}{DIGITS}
FRAC [.]{DIGITS}
EXP {E}{DIGITS}
E [eE][+-]?
HEX_DIGIT [0-9a-f]
NUMBER {INT}|{INT}{FRAC}|{INT}{EXP}|{INT}{FRAC}{EXP}
UNESCAPEDCHAR [ -!#-\[\]-~]
ESCAPEDCHAR \\["\\bfnrt/]
UNICODECHAR \\u{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}
CHAR {UNESCAPEDCHAR}|{ESCAPEDCHAR}|{UNICODECHAR}
CHARS {CHAR}+
DBL_QUOTE ["]
%%
{DBL_QUOTE}{DBL_QUOTE} |
{DBL_QUOTE}{CHARS}{DBL_QUOTE} {
    yylval=strclone(yytext);
    return STRING;
};
{NUMBER} {
    yylval=strclone(yytext);
    return NUMBER;
}
true {
    return true;
};
false {
    return false;
};
null {
    return null;
};
\{ {
    return O_BEGIN;
};
 
\} {
    return O_END;
};
 
\[ {
    return A_BEGIN;
};
 
\] {
    return A_END;
};
 
, {
    return COMMA;
};
: {
    return COLON;
};
. {
    printf("Unexpected: %c\nExiting...\n",*yytext);
    exit(0);
}
%%
char *strclone(char *str)
{
    int len = strlen(str);
    char *clone = (char *)malloc(sizeof(char)*(len+1));
    strcpy(clone,str);
    return clone;
}