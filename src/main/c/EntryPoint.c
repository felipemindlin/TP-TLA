// #include "backend/code-generation/Generator.h"
// #include "backend/domain-specific/Calculator.h"
#include "backend/domain-specific/Test.h"
#include "frontend/lexical-analysis/FlexActions.h"
#include "frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "frontend/syntactic-analysis/BisonActions.h"
#include "frontend/syntactic-analysis/SyntacticAnalyzer.h"
#include "shared/CompilerState.h"
#include "shared/Environment.h"
#include "shared/Logger.h"
#include "shared/String.h"
#include "frontend/lexical-analysis/LexicalAnalyzerContext.h"
/**
 * The main entry-point of the entire application.
 */

extern LexicalAnalyzerContext * oldLexicalAnalyzerContext;

const int main(const int count, const char ** arguments) {
	Logger * logger = createLogger("EntryPoint");
	initializeFlexActionsModule();
	initializeBisonActionsModule();
	initializeSyntacticAnalyzerModule();
	initializeAbstractSyntaxTreeModule();
	initializeTestModule();
	// initializeCalculatorModule();
	// initializeGeneratorModule();

	// Logs the arguments of the application.
	for (int k = 0; k < count; ++k) {
		logDebugging(logger, "Argument %d: \"%s\"", k, arguments[k]);
	}

	// Begin compilation process.
	CompilerState compilerState = {
		.abstractSyntaxtTree = NULL,
		.succeed = false,
		.value = 0
	};
	const SyntacticAnalysisStatus syntacticAnalysisStatus = parse(&compilerState);
	CompilationStatus compilationStatus = SUCCEED;
	if (syntacticAnalysisStatus == ACCEPT) {
		Program * program = compilerState.abstractSyntaxtTree;
		logDebugging(logger, "Releasing AST resources...");
		releaseProgram(program);
	} else {
		logError(logger, "The syntactic-analysis phase rejects the input program.");
		compilationStatus = FAILED;
	}
	if (syntacticAnalysisStatus == ACCEPT) {
		logDebugging(logger, "Computing expression value...");
		Program * program = compilerState.abstractSyntaxtTree;
		logDebugging(logger, "program->%x", program);
		logDebugging(logger, "sentence->%x (TYPE %d)", program->sentence, program->sentence->type);
		logDebugging(logger, "expression->%x (type %d)", program->sentence->expression, program->sentence->expression);
		logDebugging(logger, "constant->%x", program->sentence->expression->constant);

		if (program == NULL || program->sentence == NULL || program->sentence->expression == NULL || program->sentence->expression->constant == NULL) {
			logError(logger, "The program is not well-formed.");
			compilationStatus = FAILED;
		} else {
			ComputationResult computationResult = computeConstant(program->sentence->expression->constant);
			logDebugging(logger, "The computation type is: %d", computationResult.type);
			logDebugging(logger, "The computation value is: %x", computationResult.integerValue);
		}
	}
	// if (syntacticAnalysisStatus == ACCEPT) {
	// 	logDebugging(logger, "Computing expression value...");
	// 	Program * program = compilerState.abstractSyntaxtTree;
	// 	ComputationResult computationResult = computeExpression(program->expression);
	// 	if (computationResult.succeed) {
	// 		compilerState.value = computationResult.value;
	// 		generate(&compilerState);
	// 	}
	// 	else {
	// 		logError(logger, "The computation phase rejects the input program.");
	// 		compilationStatus = FAILED;
	// 	}
	// 	logDebugging(logger, "Releasing AST resources...");
	// 	releaseProgram(program);
	// }
	// else {
	// 	logError(logger, "The syntactic-analysis phase rejects the input program.");
	// 	compilationStatus = FAILED;
	// }

	logDebugging(logger, "Releasing modules resources...");
	// shutdownGeneratorModule();
	// shutdownCalculatorModule();
	shutdownTestModule();
	shutdownAbstractSyntaxTreeModule();
	shutdownSyntacticAnalyzerModule();
	shutdownBisonActionsModule();
	shutdownFlexActionsModule();
	logDebugging(logger, "Compilation is done.");
	destroyLogger(logger);
	destroyLexicalAnalyzerContext(oldLexicalAnalyzerContext);
	return compilationStatus;
}
