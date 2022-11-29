%{
	#include<stdio.h>

	enum {
		LOOKUP = 0,
		TEXT,
		KEYWORD,
		DATATYPE,
		CONDTIONAL,
		ITERATIVE,
		ARITHMATIC_OP
	};

	int state;
	int add_word(int type, char *word) ;
	int lookup_word(char *word) ;
%}

%%

\n 	{ state = LOOKUP; }
^text { state =TEXT; }
^keyword { state = KEYWORD; }
^datatype { state = DATATYPE; }
^condtional { state = CONDTIONAL; }
^iterative { state = ITERATIVE; }
^arithmatic_op { state = ARITHMATIC_OP; }

[a-zA-Z]+ {
if (state!=LOOKUP) {
	add_word(state, yytext); 
} 
 else 
 {
   switch ( lookup_word(yytext) )
    {
		case TEXT: printf("%s: text \n", yytext); break;
		case KEYWORD: printf("%s: keyword \n", yytext); break;
		case DATATYPE: printf("%s: datatype\n", yytext); break;
		case CONDTIONAL: printf("%s: condtional\n", yytext); break;
		case ITERATIVE: printf("%s: iterative \n", yytext); break;
		case ARITHMATIC_OP: printf("%s: arithmatic_op \n", yytext); break;
		default:
			printf ( "%s: don't recognize\n" , yytext) ;
  	}
  }
}
. 
%%

int yywrap(void){}

int main()
{ 
	printf("\nEnter any string: \n\n");
	yylex();
	return 0;  
}

struct word {
	char *word_name;
	int word_type;
	struct word *next;
};

struct word *word_list; 
extern void *malloc() ;

int add_word(int type, char *word)
{
	struct word *wp;
	if(lookup_word(word) != LOOKUP) {
		printf("!!! warning: word %s already defined \n", word);
	return 0;
	}

	wp = (struct word *) malloc(sizeof(struct word) ) ;
	wp->next=word_list;
	wp->word_name = (char *)malloc(strlen (word)+1);
	strcpy (wp->word_name, word);
	wp->word_type = type;
	word_list = wp;
	return 1; 
}

int lookup_word (char *word)
{
	struct word *wp = word_list;
	for(; wp; wp = wp->next) {
		if(strcmp(wp->word_name, word) == 0)
			return wp->word_type;
	}
	return LOOKUP;
}
