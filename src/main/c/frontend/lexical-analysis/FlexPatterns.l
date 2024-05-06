%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x MULTILINE_COMMENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

"#".*                               { IgnoredLexemeAction(createLexicalAnalyzerContext()); } 

"import"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* import keyword */ }
"from"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* from keyword */ }
"as"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* as keyword */ }
"with"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* with keyword */ }


"global"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* global keyword */ }
"nonlocal"                          { IgnoredLexemeAction(createLexicalAnalyzerContext());/* nonlocal keyword */ }

"assert"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* assert keyword */ }

"await"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* await keyword */ }
"async"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* async keyword */ }

"False"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* boolean false */ }
"True"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* boolean true */ }
"None"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* null value */ }

"class"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* class definition keyword */ }
"del"                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* object deletion keyword */ }
"def"                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* function definition keyword */ }
"lambda"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* lambda function definition keyword */ }

"return"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* return keyword */ }
"yield"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* yield keyword */ }
"pass"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* pass keyword */ }

"if"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* if keyword */ }
"elif"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* else if keyword */ }
"else"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* else keyword */ }
"for"                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* for keyword */ }
"while"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* while keyword */ }
"break"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* break keyword */ }
"continue"                          { IgnoredLexemeAction(createLexicalAnalyzerContext());/* continue keyword */ }

"raise"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* raise keyword */ }
"try"                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* try keyword */ }
"except"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* except keyword */ }
"finally"                           { IgnoredLexemeAction(createLexicalAnalyzerContext());/* finally keyword */ }

"match"                             { IgnoredLexemeAction(createLexicalAnalyzerContext());/* match keyword - - blocked in match statements */ }
"case"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* case keyword - blocked in match statements */ }
"type"                              { IgnoredLexemeAction(createLexicalAnalyzerContext());/* type keyword - blocked in type statements */ }

"\n"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* new line */ }
"\t"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* tab */ }
":"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* colon */ }
"("                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* left parenthesis */ }
")"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* right parenthesis */ }
"["                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* left square bracket */ }
"]"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* right square bracket */ }
"{"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* left curly brace */ }
"}"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* right curly brace */ }

"+"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* addition */ }
"-"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* subtraction */ }
"*"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* multiplication */ }
"/"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* division */ }
"%"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* modulus */ }
"**"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* exponentiation */ }
"//"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* floor division */ }

"="                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* assignment */ }
"+="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* addition assignment */ }
"-="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* subtraction assignment */ }
"*="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* multiplication assignment */ }
"/="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* division assignment */ }
"%="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* modulus assignment */ }
"**="                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* exponentiation assignment */ }
"//="                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* floor division assignment */ }
"&="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise AND assignment */ }
"|="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise OR assignment */ }
"^="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR assignment */ }
">>="                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise right shift assignment */ }
"<<="                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise left shift assignment */ }
":="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* walrus operator - assign then print */ }

"=="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* equality comparison */ }
"!="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* inequality comparison */ }
"<"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* less than comparison */ }
"<="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* less than or equal comparison */ }
">"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* greater than comparison */ }
">="                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* greater than or equal comparison */ }

"and"                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* logical AND */ }
"or"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* logical OR */ }
"not"                               { IgnoredLexemeAction(createLexicalAnalyzerContext());/* logical NOT */ }

"is"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* identity comparison */ }
"is not"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* negated identity comparison */ }

"in"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* membership test */ }
"not in"                            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* negated membership test */ }

"&"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise AND */ }
"|"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise OR */ }
"^"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR */ }
"~"                                 { IgnoredLexemeAction(createLexicalAnalyzerContext());/* bitwise NOT */ }
"<<"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* zero fill left shift */ }
">>"                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* signed right shift */ }

[_[:alpha:]][[:alnum:]]*            { IgnoredLexemeAction(createLexicalAnalyzerContext());/* variable or function */ }
[[:space:]]                         { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.                                   { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

/* LO ANTERIOR ESTA ABAJO - las dos lineas siguientes contenian los simbolos de comentario
""								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>""				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }
*/

#include "FlexExport.h"
