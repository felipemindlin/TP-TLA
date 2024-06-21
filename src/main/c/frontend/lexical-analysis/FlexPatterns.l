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
%x STRINGS
%x INDENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */


/*
<INDENT>[ ]{4}                              { currIndent++; bkupIndent = currIndent; IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<INDENT>[\t]                                { currIndent++; bkupIndent = currIndent; IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<INDENT>.                                   {
                                              unput(*yytext);
                                              if (currIndent == prevIndent+1) { currIndent--; return IndentLexemeAction(createLexicalAnalyzerContext()); }
                                              else if (currIndent < prevIndent) { currIndent++; return DedentLexemeAction(createLexicalAnalyzerContext()); }
                                              else if (currIndent == prevIndent) { BEGIN(INITIAL); }
                                              else { currIndent = prevIndent; return UnknownLexemeAction(createLexicalAnalyzerContext()); }
                                            }
<INDENT><<EOF>>                             {
                                              if (currIndent < prevIndent) { currIndent++; return DedentLexemeAction(createLexicalAnalyzerContext()); }
                                              else { BEGIN(INITIAL); }
                                            } */

%%

"#".*"\n"                                   { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"\"".*"\""                                  { return StringLexemeAction(createLexicalAnalyzerContext()); }

"import"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* import keyword */ }
"from"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* from keyword */ }
"as"                                        { IgnoredLexemeAction(createLexicalAnalyzerContext());/* as keyword */ }
"with"                                      { IgnoredLexemeAction(createLexicalAnalyzerContext());/* with keyword */ }


"global"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* global keyword */ }
"nonlocal"                                  { IgnoredLexemeAction(createLexicalAnalyzerContext());/* nonlocal keyword */ }

"assert"                                    { return AssertKeywordLexemeAction(createLexicalAnalyzerContext());/* assert keyword */ }

"await"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* await keyword */ }
"async"                                     { IgnoredLexemeAction(createLexicalAnalyzerContext());/* async keyword */ }

"False"                                     { return BooleanLexemeAction(createLexicalAnalyzerContext());/* boolean false */ }
"True"                                      { return BooleanLexemeAction(createLexicalAnalyzerContext());/* boolean true */ }
"None"                                      { return NoneLexemeAction(createLexicalAnalyzerContext());/* null value */ }

"class"                                     { return ClassLexemeAction(createLexicalAnalyzerContext());/* class definition keyword */ }
"del"                                       { IgnoredLexemeAction(createLexicalAnalyzerContext());/* object deletion keyword */ }
"def"                                       { return DefineLexemeAction(createLexicalAnalyzerContext());/* function definition keyword */ }
"lambda"                                    { IgnoredLexemeAction(createLexicalAnalyzerContext());/* lambda function definition keyword */ }
"->"                                        { return ReturnsLexemeAction(createLexicalAnalyzerContext()); /* function return type keyword */}

"return"                                    { return ReturnKeywordLexemeAction(createLexicalAnalyzerContext());/* return keyword */ }
"yield"                                     { return YieldKeywordLexemeAction(createLexicalAnalyzerContext());/* yield keyword */ }
"pass"                                      { return PassKeywordLexemeAction(createLexicalAnalyzerContext());/* pass keyword */ }

"if"                                        { return IfLexemeAction(createLexicalAnalyzerContext());/* if keyword */ }
"elif"                                      { return ElifLexemeAction(createLexicalAnalyzerContext());/* else if keyword */ }
"else"                                      { return ElseLexemeAction(createLexicalAnalyzerContext());/* else keyword */ }
"for"                                       { return ForLexemeAction(createLexicalAnalyzerContext());/* for keyword */ }
"while"                                     { return WhileLexemeAction(createLexicalAnalyzerContext());/* while keyword */ }
"break"                                     { return BreakLexemeAction(createLexicalAnalyzerContext());/* break keyword */ }
"continue"                                  { return ContinueLexemeAction(createLexicalAnalyzerContext());/* continue keyword */ }

"raise"                                     { return RaiseKeywordLexemeAction(createLexicalAnalyzerContext());/* raise keyword */ }
"try"                                       { return TryKeywordLexemeAction(createLexicalAnalyzerContext());/* try keyword */ }
"except"                                    { return ExceptKeywordLexemeAction(createLexicalAnalyzerContext());/* except keyword */ }
"finally"                                   { return FinallyKeywordLexemeAction(createLexicalAnalyzerContext());/* finally keyword */ }

"match"                                     { return MatchKeywordLexemeAction(createLexicalAnalyzerContext());/* match keyword - - blocked in match statements */ }
"case"                                      { return CaseKeywordLexemeAction(createLexicalAnalyzerContext());/* case keyword - blocked in match statements */ }
"type"                                      { return TypeKeywordLexemeAction(createLexicalAnalyzerContext());/* type keyword - blocked in type statements */ }

"@{"                                        { return IndentLexemeAction(createLexicalAnalyzerContext());/* indent */ }
"@}"                                        { return DedentLexemeAction(createLexicalAnalyzerContext()); }
[\t]                                        { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
[ ]{4}                                      { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
[\n]                                        { prevIndent = bkupIndent; currIndent = 0;
                                              IgnoredLexemeAction(createLexicalAnalyzerContext());
                                              //return NewlineLexemeAction(createLexicalAnalyzerContext());/* new line */
                                            }
":"                                         { return ColonLexemeAction(createLexicalAnalyzerContext());/* colon */ }
","                                         { return CommaLexemeAction(createLexicalAnalyzerContext());/* comma */ }
"("                                         { return ParenthesisLexemeAction(createLexicalAnalyzerContext());/* left parenthesis */ }
")"                                         { return ParenthesisLexemeAction(createLexicalAnalyzerContext());/* right parenthesis */ }
"["                                         { return BracketLexemeAction(createLexicalAnalyzerContext());/* left square bracket */ }
"]"                                         { return BracketLexemeAction(createLexicalAnalyzerContext());/* right square bracket */ }
"{"                                         { return BraceLexemeAction(createLexicalAnalyzerContext());/* left curly brace */ }
"}"                                         { return BraceLexemeAction(createLexicalAnalyzerContext());/* right curly brace */ }
"."                                         { return DotLexemeAction(createLexicalAnalyzerContext()); /* dots for method calls */ }

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

"is"                                        { return IdentityEvaluationLexemeAction(createLexicalAnalyzerContext());/* identity comparison */ }
"is not"                                    { return IdentityEvaluationLexemeAction(createLexicalAnalyzerContext());/* negated identity comparison */ }

"in"                                        { return MembershipEvaluationLexemeAction(createLexicalAnalyzerContext());/* membership test */ }
"not in"                                    { return MembershipEvaluationLexemeAction(createLexicalAnalyzerContext());/* negated membership test */ }

"^"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise XOR */ }
"&"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise AND */ }
"|"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise OR */ }
"~"                                         { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* bitwise NOT */ }
"<<"                                        { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* zero fill left shift */ }
">>"                                        { return BitwiseOperatorLexemeAction(createLexicalAnalyzerContext());/* signed right shift */ }

[+-]?[[:digit:]]+([.][[:digit:]]+)?[e][+-]?[[:digit:]]+ { return FloatLexemeAction(createLexicalAnalyzerContext());/* fp literal in sci notation */ }
[+-]?[[:digit:]]+[.][[:digit:]]+                        { return FloatLexemeAction(createLexicalAnalyzerContext());/* floating point literal */ }
[+-]?[[:digit:]]+                                       { return IntegerLexemeAction(createLexicalAnalyzerContext());/* integer literal */ }
[_[:alpha:]][_[:alnum:]]*                               { return IdentifierLexemeAction(createLexicalAnalyzerContext());/* variable or function */ }
[[^:alnum:]]"abs"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ABS); /* Builtin Classes */}
[[^:alnum:]]"aiter"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_AITER); /* Builtin Classes */}
[[^:alnum:]]"all"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ALL); /* Builtin Classes */}
[[^:alnum:]]"anext"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ANEXT); /* Builtin Classes */}
[[^:alnum:]]"any"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ANY); /* Builtin Classes */}
[[^:alnum:]]"ascii"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ASCII); /* Builtin Classes */}
[[^:alnum:]]"bin"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_BIN); /* Builtin Classes */}
[[^:alnum:]]"bool"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_BOOL); /* Builtin Classes */}
[[^:alnum:]]"breakpoint"[[^:alnum:]]                    { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_BREAKPOINT); /* Builtin Classes */}
[[^:alnum:]]"bytearray"[[^:alnum:]]                     { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_BYTEARRAY); /* Builtin Classes */}
[[^:alnum:]]"bytes"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_BYTES); /* Builtin Classes */}
[[^:alnum:]]"callable"[[^:alnum:]]                      { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_CALLABLE); /* Builtin Classes */}
[[^:alnum:]]"classmethod"[[^:alnum:]]                   { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_CLASSMETHOD); /* Builtin Classes */}
[[^:alnum:]]"compile"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_COMPILE); /* Builtin Classes */}
[[^:alnum:]]"complex"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_COMPLEX); /* Builtin Classes */}
[[^:alnum:]]"delattr"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_DELATTR); /* Builtin Classes */}
[[^:alnum:]]"dict"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_DICT); /* Builtin Classes */}
[[^:alnum:]]"dir"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_DIR); /* Builtin Classes */}
[[^:alnum:]]"divmod"[[^:alnum:]]                        { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_DIVMOD); /* Builtin Classes */}
[[^:alnum:]]"enumerate"[[^:alnum:]]                     { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ENUMERATE); /* Builtin Classes */}
[[^:alnum:]]"eval"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_EVAL); /* Builtin Classes */}
[[^:alnum:]]"exec"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_EXEC); /* Builtin Classes */}
[[^:alnum:]]"filter"[[^:alnum:]]                        { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_FILTER); /* Builtin Classes */}
[[^:alnum:]]"float"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_FLOAT); /* Builtin Classes */}
[[^:alnum:]]"format"[[^:alnum:]]                        { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_FORMAT); /* Builtin Classes */}
[[^:alnum:]]"frozenset"[[^:alnum:]]                     { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_FROZENSET); /* Builtin Classes */}
[[^:alnum:]]"getattr"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_GETATTR); /* Builtin Classes */}
[[^:alnum:]]"globals"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_GLOBALS); /* Builtin Classes */}
[[^:alnum:]]"hasattr"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_HASATTR); /* Builtin Classes */}
[[^:alnum:]]"hash"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_HASH); /* Builtin Classes */}
[[^:alnum:]]"help"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_HELP); /* Builtin Classes */}
[[^:alnum:]]"hex"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_HEX); /* Builtin Classes */}
[[^:alnum:]]"id"[[^:alnum:]]                            { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ID); /* Builtin Classes */}
[[^:alnum:]]"input"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_INPUT); /* Builtin Classes */}
[[^:alnum:]]"int"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_INT); /* Builtin Classes */}
[[^:alnum:]]"isinstance"[[^:alnum:]]                    { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ISINSTANCE); /* Builtin Classes */}
[[^:alnum:]]"issubclass"[[^:alnum:]]                    { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ISSUBCLASS); /* Builtin Classes */}
[[^:alnum:]]"iter"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ITER); /* Builtin Classes */}
[[^:alnum:]]"len"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_LEN); /* Builtin Classes */}
[[^:alnum:]]"list"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_LIST); /* Builtin Classes */}
[[^:alnum:]]"locals"[[^:alnum:]]                        { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_LOCALS); /* Builtin Classes */}
[[^:alnum:]]"map"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_MAP); /* Builtin Classes */}
[[^:alnum:]]"memoryview"[[^:alnum:]]                    { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_MEMORYVIEW); /* Builtin Classes */}
[[^:alnum:]]"min"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_MIN); /* Builtin Classes */}
[[^:alnum:]]"next"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_NEXT); /* Builtin Classes */}
[[^:alnum:]]"object"[[^:alnum:]]                        { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_OBJECT); /* Builtin Classes */}
[[^:alnum:]]"oct"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_OCT); /* Builtin Classes */}
[[^:alnum:]]"open"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_OPEN); /* Builtin Classes */}
[[^:alnum:]]"ord"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ORD); /* Builtin Classes */}
[[^:alnum:]]"pow"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_POW); /* Builtin Classes */}
[[^:alnum:]]"print"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_PRINT); /* Builtin Classes */}
[[^:alnum:]]"range"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_RANGE); /* Builtin Classes */}
[[^:alnum:]]"repr"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_REPR); /* Builtin Classes */}
[[^:alnum:]]"reversed"[[^:alnum:]]                      { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_REVERSED); /* Builtin Classes */}
[[^:alnum:]]"round"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ROUND); /* Builtin Classes */}
[[^:alnum:]]"set"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_SET); /* Builtin Classes */}
[[^:alnum:]]"setattr"[[^:alnum:]]                       { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_SETATTR); /* Builtin Classes */}
[[^:alnum:]]"slice"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_SLICE); /* Builtin Classes */}
[[^:alnum:]]"sorted"[[^:alnum:]]                        { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_SORTED); /* Builtin Classes */}
[[^:alnum:]]"staticmethod"[[^:alnum:]]                  { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_STATICMETHOD); /* Builtin Classes */}
[[^:alnum:]]"str"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_STR); /* Builtin Classes */}
[[^:alnum:]]"sum"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_SUM); /* Builtin Classes */}
[[^:alnum:]]"super"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_SUPER); /* Builtin Classes */}
[[^:alnum:]]"tuple"[[^:alnum:]]                         { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_TUPLE); /* Builtin Classes */}
[[^:alnum:]]"type"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_TYPE); /* Builtin Classes */}
[[^:alnum:]]"vars"[[^:alnum:]]                          { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_VARS); /* Builtin Classes */}
[[^:alnum:]]"zip"[[^:alnum:]]                           { return BuiltinIdentifierLexemeAction(createLexicalAnalyzerContext(), BI_ZIP); /* Builtin Classes */}

[[:space:]]                                             { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.                                                       { return UnknownLexemeAction(createLexicalAnalyzerContext()); }
%%

static int currentIndent = 0;
static int backupIndent = 0;
static int previousIndent = 0;

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
