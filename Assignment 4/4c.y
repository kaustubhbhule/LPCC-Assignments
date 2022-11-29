%{
	#include<stdio.h>
	#include "y.tab.h"
%}

%token BUILTIN UD WS ID OPEN_SQ CLOSE_SQ EQ NEW SC COMMA DIGIT 

%%

start :    varlist WS varlist  {printf("invalid declaration \n\n");} 
        |  varlist UD DIGIT  {printf("valid declaration \n\n");}
        |  varlist  {printf("valid declaration \n\n");}
        |  varlist UD varlist {printf("valid declaration \n\n");}
        |  varlist : varlist COMMA ID | ID;
%%

int yywrap()
{ 
	return 1;
}

int main()
{
	printf("\nEnter variable declaration: ");
	yyparse();
	return 1;
}

int yyerror(char *s)
{
	fprintf(stderr,"invalid declaration\n\n",s);
	return 1;
}
