%{
    #include<stdio.h>
%}

DIGIT[0-9]
NUMBER {DIGIT}*
REAL {DIGIT}*[.]{NUMBER}
TEXT [A-Za-z]
KEYWORDS "auto"|"break"|"enum"|"struct"|"typedef"
DATATYPE "int"|"float"|"double"|"long"|"void"|"unsigned char"
CONDTIONAL "if"|"else"|"else if"|"switch"|"case"
ITERATIVE "for"|"while"|"do"
SEMICOLAN ";"
IDENTIFIER {TEXT}({DIGIT}|{TEXT}|"_")*
NONIDENTIFIER {DIGIT}({TEXT}|{DIGIT}|"_")*
ARITHMATIC_OP "+"|"-"|"/"|"%"|"*";
LOGICAL_OP "&&"|"||"|"!"|"!="
RELEATIONAL_OP "<"|">"|"<="|">="|"=="
UNARY "++"|"--"
FUNCTION {ACCESS}{DATATYPE}{IDENTIFER}"("({DATATYPE}{IDENTIFIER})*")"

%%

[  \n ]+ ;
{CONDTIONAL} {printf("%s ==> CONDTIONAL \n",yytext);}
{ITERATIVE} {printf("%s ==> ITERATIVE \n",yytext);}
{DATATYPE} {printf("%s ==> DATATYPE\n",yytext);}
{KEYWORDS} {printf("%s ==> KEYWORDS \n",yytext);}
{IDENTIFIER} {printf("%s ==> IDENTIFIER \n",yytext);}
{REAL} {printf("%s ==> REAL \n",yytext);}
{NUMBER} {printf("%s ==> NUMBER \n",yytext);}
{NONIDENTIFIER} {printf("%S ==> NONIDENTIFIER \n",yytext);}
{SEMICOLAN} {printf("%s ==> SEMICOLAN \n",yytext);}
{UNARY} {printf("%s ==> UNARY \n",yytext);}
{ARITHMATIC_OP} {printf("%s ==> ARITHMATIC_OP \n",yytext);}
{LOGICAL_OP} {printf("%s ==> LOGICAL OP \n",yytext);}
{RELEATIONAL_OP} {printf("%s ==> RELEATIONAL OP \n",yytext);}
"=" {printf("%s ==> ASSIGNMENT OP \n",yytext);}
"{" {printf("%s ==> BLOCK BEGIN \n",yytext);}
"}" {printf("%s ==> BLOCK END \n",yytext);}
"(" {printf("%s ==> PARATHRSIS BEGIN \n",yytext);}
")" {printf("%s ==> PARATHRSIS END \n",yytext);}
. ;

%%

int yywrap(void){}

int main ( )
{ 
    printf("\nEnter any string: ");
    yylex();
    return 0;  
} 
