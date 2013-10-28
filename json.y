%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #define YYSTYPE char*
    char *strconcat(char *str1, char *str2);
%}
%token NUMBER
%token STRING
%token true false null
%left O_BEGIN O_END A_BEGIN A_END
%left COMMA
%left COLON
%%
START: ARRAY {
    printf("%s",$1);
  }
| OBJECT {
    printf("%s",$1);
  }
;
OBJECT: O_BEGIN O_END {
    $$ = "{}";
  }
| O_BEGIN MEMBERS O_END {
    $$ = (char *)malloc(sizeof(char)*(1+strlen($2)+1+1));
    sprintf($$,"{%s}",$2);
  }
;
MEMBERS: PAIR {
    $$ = $1;
  }
| PAIR COMMA MEMBERS {
    $$ = (char *)malloc(sizeof(char)*(strlen($1)+1+strlen($3)+1));
    sprintf($$,"%s,%s",$1,$3);
  }
;
PAIR: STRING COLON VALUE {
    $$ = (char *)malloc(sizeof(char)*(strlen($1)+1+strlen($3)+1));
    sprintf($$,"%s:%s",$1,$3);
  }
;
ARRAY: A_BEGIN A_END {
    $$ = (char *)malloc(sizeof(char)*(2+1));
    sprintf($$,"[]");
  }
| A_BEGIN ELEMENTS A_END {
    $$ = (char *)malloc(sizeof(char)*(1+strlen($2)+1+1));
    sprintf($$,"[%s]",$2);
}
;
ELEMENTS: VALUE {
    $$ = $1;
  }
| VALUE COMMA ELEMENTS {
    $$ = (char *)malloc(sizeof(char)*(strlen($1)+1+strlen($3)+1));
    sprintf($$,"%s,%s",$1,$3);
  }
;
VALUE: STRING {$$=yylval;}
| NUMBER {$$=yylval;}
| OBJECT {$$=$1;}
| ARRAY {$$=$1;}
| true {$$="true";}
| false {$$="false";}
| null {$$="null";}
;
%%
int main()
{
   printf("\n");
   yyparse();
   printf("\n");
   return 0;
}
int yywrap()
{
   return 1;
}
void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}
char *strconcat(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *str3 = (char *)malloc(sizeof(char)*(len1+len2+1));
    strcpy(str3,str1);
    strcpy(&(str3[len1]),str2);
    return str3;
}

