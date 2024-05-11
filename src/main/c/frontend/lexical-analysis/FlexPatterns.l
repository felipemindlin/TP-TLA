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

"False"                                     { return BooleanLexemeAction(createLexicalAnalyzerContext());/* boolean false */ }
"True"                                      { return BooleanLexemeAction(createLexicalAnalyzerContext());/* boolean true */ }
"None"                                      { return NoneLexemeAction(createLexicalAnalyzerContext());/* null value */ }

"class"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* class definition keyword */ }
"del"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* object deletion keyword */ }
"def"                                       { return DefineLexemeAction(createLexicalAnalyzerContext());/* function definition keyword */ }
"lambda"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* lambda function definition keyword */ }

"return"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* return keyword */ }
"yield"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* yield keyword */ }
"pass"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* pass keyword */ }

"if"                                        { return IfLexemeAction(createLexicalAnalyzerContext());/* if keyword */ }
"elif"                                      { return ElifLexemeAction(createLexicalAnalyzerContext());/* else if keyword */ }
"else"                                      { return ElseLexemeAction(createLexicalAnalyzerContext());/* else keyword */ }
"for"                                       { return ForLexemeAction(createLexicalAnalyzerContext());/* for keyword */ }
"while"                                     { return WhileLexemeAction(createLexicalAnalyzerContext());/* while keyword */ }
"break"                                     { return BreakLexemeAction(createLexicalAnalyzerContext());/* break keyword */ }
"continue"                                  { return ContinueLexemeAction(createLexicalAnalyzerContext());/* continue keyword */ }

"raise"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* raise keyword */ }
"try"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* try keyword */ }
"except"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* except keyword */ }
"finally"                                   { IgnoredLexemeAction(createLexicalAnalyzerContext());/* finally keyword */ }

"match"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* match keyword - - blocked in match statements */ }
"case"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* case keyword - blocked in match statements */ }
"type"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* type keyword - blocked in type statements */ }

[\n]                                        { return NewlineLexemeAction(createLexicalAnalyzerContext());/* new line */ }
[ ]{4}                                      { return TabLexemeAction(createLexicalAnalyzerContext());/* tab */}
"\t"                                        { return TabLexemeAction(createLexicalAnalyzerContext());/* tab */ }
":"                                         { return ColonLexemeAction(createLexicalAnalyzerContext());/* colon */ }
","                                         { return CommaLexemeAction(createLexicalAnalyzerContext());/* comma */ }
"("                                         { return ParenthesisLexemeAction(createLexicalAnalyzerContext());/* left parenthesis */ }
")"                                         { return ParenthesisLexemeAction(createLexicalAnalyzerContext());/* right parenthesis */ }
"["                                         { return BracketLexemeAction(createLexicalAnalyzerContext());/* left square bracket */ }
"]"                                         { return BracketLexemeAction(createLexicalAnalyzerContext());/* right square bracket */ }
"{"                                         { return BraceLexemeAction(createLexicalAnalyzerContext());/* left curly brace */ }
"}"                                         { return BraceLexemeAction(createLexicalAnalyzerContext());/* right curly brace */ }

"+"                                         { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* addition */ }
"-"                                         { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* subtraction */ }
"*"                                         { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* multiplication */ }
"/"                                         { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* division */ }
"%"                                         { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* modulus */ }
"**"                                        { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* exponentiation */ }
"//"                                        { return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext());/* floor division */ }

"="                                         { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* assignment */ }
"+="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* addition assignment */ }
"-="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* subtraction assignment */ }
"*="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* multiplication assignment */ }
"/="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* division assignment */ }
"%="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* modulus assignment */ }
"**="                                       { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* exponentiation assignment */ }
"//="                                       { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* floor division assignment */ }
"&="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise AND assignment */ }
"|="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise OR assignment */ }
"^="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR assignment */ }
">>="                                       { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise right shift assignment */ }
"<<="                                       { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise left shift assignment */ }
":="                                        { return AssignmentOperatorLexemeAction(createLexicalAnalyzerContext());/* walrus operator - assign then print */ }

"=="                                        { return ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* equality comparison */ }
"!="                                        { return ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* inequality comparison */ }
"<"                                         { return ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* less than comparison */ }
"<="                                        { return ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* less than or equal comparison */ }
">"                                         { return ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* greater than comparison */ }
">="                                        { return ComparisonOperatorLexemeAction(createLexicalAnalyzerContext());/* greater than or equal comparison */ }

"and"                                       { return ConditionalLexemeAction(createLexicalAnalyzerContext());/* logical AND */ }
"or"                                        { return ConditionalLexemeAction(createLexicalAnalyzerContext());/* logical OR */ }
"not"                                       { return ConditionalLexemeAction(createLexicalAnalyzerContext());/* logical NOT */ }

"is"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* identity comparison */ }
"is not"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* negated identity comparison */ }

"in"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* membership test */ }
"not in"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* negated membership test */ }

"^"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR */ }
"&"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise AND */ }
"|"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise OR */ }
"~"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise NOT */ }
"<<"                                        { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* zero fill left shift */ }
">>"                                        { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* signed right shift */ }

[+-]?[[:digit:]]+([.][[:digit:]]+)?[e][+-]?[[:digit:]]+ { return FloatLexemeAction(createLexicalAnalyzerContext());/* fp literal in sci notation */ }
[+-]?[[:digit:]]+[.][[:digit:]]+                        { return FloatLexemeAction(createLexicalAnalyzerContext());/* floating point literal */ }
[+-]?[[:digit:]]+                                       { return IntegerLexemeAction(createLexicalAnalyzerContext());/* integer literal */ }
[_[:alpha:]][[:alnum:]]*                                { return IdentifierLexemeAction(createLexicalAnalyzerContext());/* variable or function */ }
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
