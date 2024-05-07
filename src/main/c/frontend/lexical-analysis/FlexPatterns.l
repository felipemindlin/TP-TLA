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

"#".*"\n"                                   { IgnoredLexemeAction(createLexicalAnalyzerContext()); } 

"import"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* import keyword */ }
"from"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* from keyword */ }
"as"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* as keyword */ }
"with"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* with keyword */ }


"global"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* global keyword */ }
"nonlocal"                                  { IgnoredLexemeAction(createLexicalAnalyzerContext());/* nonlocal keyword */ }

"assert"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* assert keyword */ }

"await"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* await keyword */ }
"async"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* async keyword */ }

"False"                                     { BooleanLexemeAction(createLexicalAnalyzerContext());/* boolean false */ }
"True"                                      { BooleanLexemeAction(createLexicalAnalyzerContext());/* boolean true */ }
"None"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* null value */ }

"class"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* class definition keyword */ }
"del"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* object deletion keyword */ }
"def"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* function definition keyword */ }
"lambda"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* lambda function definition keyword */ }

"return"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* return keyword */ }
"yield"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* yield keyword */ }
"pass"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* pass keyword */ }

"if"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* if keyword */ }
"elif"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* else if keyword */ }
"else"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* else keyword */ }
"for"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* for keyword */ }
"while"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* while keyword */ }
"break"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* break keyword */ }
"continue"                                  { IgnoredLexemeAction(createLexicalAnalyzerContext());/* continue keyword */ }

"raise"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* raise keyword */ }
"try"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* try keyword */ }
"except"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* except keyword */ }
"finally"                                   { IgnoredLexemeAction(createLexicalAnalyzerContext());/* finally keyword */ }

"match"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* match keyword - - blocked in match statements */ }
"case"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* case keyword - blocked in match statements */ }
"type"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* type keyword - blocked in type statements */ }

"\n"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* new line */ }
"\t"                                        { TabLexemeAction(createLexicalAnalyzerContext());/* tab */ }
":"                                         { ColonLexemeAction(createLexicalAnalyzerContext());/* colon */ }
"("                                         { ParenthesisLexemeAction(createLexicalAnalyzerContext());/* left parenthesis */ }
")"                                         { ParenthesisLexemeAction(createLexicalAnalyzerContext());/* right parenthesis */ }
"["                                         { BracketLexemeAction(createLexicalAnalyzerContext());/* left square bracket */ }
"]"                                         { BracketLexemeAction(createLexicalAnalyzerContext());/* right square bracket */ }
"{"                                         { BraceLexemeAction(createLexicalAnalyzerContext());/* left curly brace */ }
"}"                                         { BraceLexemeAction(createLexicalAnalyzerContext());/* right curly brace */ }

"+"                                         { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* addition */ }
"-"                                         { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* subtraction */ }
"*"                                         { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* multiplication */ }
"/"                                         { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* division */ }
"%"                                         { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* modulus */ }
"**"                                        { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* exponentiation */ }
"//"                                        { ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* floor division */ }

"="                                         { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* assignment */ }
"+="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* addition assignment */ }
"-="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* subtraction assignment */ }
"*="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* multiplication assignment */ }
"/="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* division assignment */ }
"%="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* modulus assignment */ }
"**="                                       { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* exponentiation assignment */ }
"//="                                       { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* floor division assignment */ }
"&="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise AND assignment */ }
"|="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise OR assignment */ }
"^="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR assignment */ }
">>="                                       { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise right shift assignment */ }
"<<="                                       { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise left shift assignment */ }
":="                                        { AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* walrus operator - assign then print */ }

"=="                                        { ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* equality comparison */ }
"!="                                        { ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* inequality comparison */ }
"<"                                         { ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* less than comparison */ }
"<="                                        { ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* less than or equal comparison */ }
">"                                         { ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* greater than comparison */ }
">="                                        { ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* greater than or equal comparison */ }

"and"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* logical AND */ }
"or"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* logical OR */ }
"not"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* logical NOT */ }

"is"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* identity comparison */ }
"is not"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* negated identity comparison */ }

"in"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* membership test */ }
"not in"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* negated membership test */ }

"^"                                         { BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR */ }
"&"                                         { BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise AND */ }
"|"                                         { BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise OR */ }
"~"                                         { BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise NOT */ }
"<<"                                        { BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* zero fill left shift */ }
">>"                                        { BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* signed right shift */ }

[+-]?[[:digit:]]+([.][[:digit:]]+)?[e][+-]?[[:digit:]]+ { FloatLexemeAction(createLexicalAnalyzerContext());/* fp literal in sci notation */ }
[+-]?[[:digit:]]+[.][[:digit:]]+                        { FloatLexemeAction(createLexicalAnalyzerContext());/* floating point literal */ }
[+-]?[[:digit:]]+                                       { IntegerLexemeAction(createLexicalAnalyzerContext());/* integer literal */ }
[_[:alpha:]][[:alnum:]]*                                { IgnoredLexemeAction(createLexicalAnalyzerContext());/* variable or function */ }
[[:space:]]                                             { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.                                                       { return UnknownLexemeAction(createLexicalAnalyzerContext()); }

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
