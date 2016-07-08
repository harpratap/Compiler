%{
#include "myscanner.h"
%}

%%
:	return COLON;
";" return COLON;
"db_type" return TYPE;
"db_name"	return NAME;
"db_table_prefix"	return TABLE_PREFIX;
"db_port"	return PORT;

"#include" return INCLUDE;
">" return GREATER_THAN;
"<" return LESS_THAN;
"int" return INT;
"main()" return MAIN;
"{" return OB;
"printf" return PRINTF;
"(" return OP;
")" return CP;
"}" return CB;

[a-zA-Z][_a-zA-Z0-9]*	return IDENTIFIER;
[1-9][0-9]*	return INTEGER;
[ \t\n]	;
\"(\\.|[^"])*\" return KEYWORD;
.	printf("unexpected character\n");

%%
int yywrap(void)
{
	return 1;
}

