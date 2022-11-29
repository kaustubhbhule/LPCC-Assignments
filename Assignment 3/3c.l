%{
	#include<stdio.h>
%}

%%

[\t ]+

is |
am |
are |
were |
was |
be |
being |
been |
do |
does |
did |
will |
would |
should |
can |
could |
has |
have |
had |
go { printf("%s: is a verb\n", yytext); }
 
very |
simply |
gently |
quietly |
calmly |
angrily { printf("%s: is an adverb\n", yytext); }
 
to |
from |
behind |
above |
below |
between { printf("%s: is a preposition\n", yytext); }
 
if |
then |
and |
but |
or { printf("%s: is a conjunction\n", yytext); }
 
alive |
better |
clever |
careful |
dead |
easy |
gifted |
hallowed | 
helpful |
important |
inexpensive | 
mealy |
good | 
famous { printf("%s: is an adjective\n", yytext); }
 
I |
you |
he |
their |
my |
your |
his |
her |
she |
we |
they { printf("%s: is a pronoun\n", yytext); }

[a-zA-Z]+ {	printf("%s: don't recognize, might be a noun\n", yytext); }

.|\n { ECHO; }

%%

int yywrap(void){}

int main ( )
{ 
	printf("\nEnter any string: ");
	yylex();
	return 0;  
}

