#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token FloatLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BooleanLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token NoneLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token IdentifierLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token NewlineLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TabLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ColonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token CommaLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BracketLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BraceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token DotLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ClassLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token IdentityEvaluationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token MembershipEvaluationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ConditionalLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token IfLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ElifLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ElseLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ForLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token WhileLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BreakLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ContinueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ReturnsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ReturnKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token PassKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token YieldKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token RaiseKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TryKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ExceptKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token FinallyKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token MatchKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token CaseKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token TypeKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token AssertKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token DefineLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token AssignmentOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ComparisonOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BitwiseOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif
