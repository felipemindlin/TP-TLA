#include "Generator.h"
#include "../semantic-analysis/SymbolTable.h"
/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;

static Logger * _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

static int indentLevel = 0;
static void _output(const char * const format, ...); 

/** PRIVATE FUNCTIONS */

void generateConstant(Constant * constant){
    switch (constant->type) {
        case CT_BOOLEAN:
            _output( (constant->boolean == true )? "True" : "False" );
            return;
        case CT_INTEGER:
            _output("%d", constant->integer);
            return;
        case CT_FLOAT:
            _output("%g", constant->decimal);
            return;
        case CT_STRING:
            _output(constant->string);
            return;
        default:
            return;
    }
}

void generateExpression(Expression * expression) {
     switch (expression->type) {
        case CONSTANT_EXPRESSION:
            generateConstant(expression->constant);
                break;
        case ADDITION:
            generateExpression(expression->leftExpression);
            _output(" + ");
            generateExpression(expression->rightExpression);
            return;
                break;
        case MULTIPLICATION:
            generateExpression(expression->leftExpression);
            _output(" * ");
            generateExpression(expression->rightExpression);
                break;
        case SUBTRACTION:
            generateExpression(expression->leftExpression);
            _output(" - ");
            generateExpression(expression->rightExpression);
                break;
        case DIVISION:
            generateExpression(expression->leftExpression);
            _output(" / ");
            generateExpression(expression->rightExpression);
                break;
        case TRUNCATED_DIVISION:
            generateExpression(expression->leftExpression);
            _output(" // ");
            generateExpression(expression->rightExpression);
                break;
        case MODULO:
            generateExpression(expression->leftExpression);
            _output(" \% ");
            generateExpression(expression->rightExpression);
                break;
        case EXPONENTIATION:
            generateExpression(expression->leftExpression);
            _output(" ** ");
            generateExpression(expression->rightExpression);
                break;
        case LOGIC_AND:
            generateExpression(expression->leftExpression);
            _output(" && ");
            generateExpression(expression->rightExpression);
                break;
        case LOGIC_OR:
            generateExpression(expression->leftExpression);
            _output(" || ");
            generateExpression(expression->rightExpression);
                break;
        case LOGIC_NOT:
            _output("! ");
            generateExpression(expression);
                break;
        case COMPARISON_EXPRESSION:
            switch (expression->compType) {
                case BCT_EQU:
                generateExpression(expression->leftExpression);
                _output(" == ");
                generateExpression(expression->rightExpression);
                break;
                case BCT_NEQ:
                generateExpression(expression->leftExpression);
                _output(" != ");
                generateExpression(expression->rightExpression);
                break;
                case BCT_GT:
                generateExpression(expression->leftExpression);
                _output(" > ");
                generateExpression(expression->rightExpression);
                break;
                case BCT_GTE:
                generateExpression(expression->leftExpression);
                _output(" >= ");
                generateExpression(expression->rightExpression);
                break;
                case BCT_LT:
                generateExpression(expression->leftExpression);
                _output(" < ");
                generateExpression(expression->rightExpression);
                break;
                case BCT_LTE:
                generateExpression(expression->leftExpression);
                _output(" <= ");
                generateExpression(expression->rightExpression);
                break;
                case BCT_MEMBER:
                generateExpression(expression->rightExpression);
                _output(".contains(");
                generateExpression(expression->rightExpression);
                _output(")");
                break;
                case BCT_NMEMBER:
                    _output("!");
                    generateExpression(expression->rightExpression);
                    _output(".contains(");
                    generateExpression(expression->rightExpression);
                    _output(")");
                    break;
                case BCT_IDENTITY:
                case BCT_NIDENTITY:
                break;

            }
        case MEMBERSHIP:
        case NOT_MEMBERSHIP:
        case BIT_ARITHMETIC_AND:
        case BIT_ARITHMETIC_OR:
        case BIT_ARITHMETIC_XOR:
        case BIT_ARITHMETIC_NOT:
        case BIT_ARITHMETIC_LEFT_SHIFT:
        case BIT_ARITHMETIC_RIGHT_SHIFT:
            return CT_BOOLEAN;
        case ASSIGNMENT:
        case ADDITION_ASSIGNMENT:
        case DIVISION_ASSIGNMENT:
        case MULTIPLICATION_ASSIGNMENT:
        case SUBTRACTION_ASSIGNMENT:
        case EXPONENTIATION_ASSIGNMENT:
        case TRUNCATED_DIVISION_ASSIGNMENT:
        case MODULO_ASSIGNMENT:
        case BITWISE_AND_ASSIGNMENT:
        case BITWISE_OR_ASSIGNMENT:
        case BITWISE_XOR_ASSIGNMENT:
        case BITWISE_LEFT_SHIFT_ASSIGNMENT:
        case BITWISE_RIGHT_SHIFT_ASSIGNMENT:
        case RETURNED_ASSIGNMENT:
        case IDENTITY:
        case VARIABLE_CALL_EXPRESSION:
            generateVariableCall(expression->variableCall);
            break;
        case FUNCTION_CALL_EXPRESSION:
            return expression->functionCall->type;
        case METHOD_CALL_EXPRESSION:
            return expression->methodCall->type;
        case FIELD_GETTER_EXPRESSION:
            return expression->fieldGetter->type;
        default:
            generateVariable(expression->variableCall->variableName);
            return;
    }
}

void generateVariableCall(VariableCall * variableCall) {
    
    _output(variableCall->variableName);
}

void generateVariable(Variable * variable) {
    struct key key = {.varname = variable->identifier};
    struct value value;

    symbolTableFind(&key,&value);
    switch ( value.type ){
        case SA_BOOLEAN:
            _output("boolean ");
            break;
        case SA_FLOAT:
            _output("double ");
            break;
        case SA_INTEGER:
            _output("int ");
            break;
        case SA_STRING:
            _output("String ");
            break;
        default:
            _output("Object ");
    }
    _output(variable->identifier);
    _output(" = ");
    generateExpression(variable->expression);
}

void generateFunctionDef(FunctionDefinition * fdef){
    switch (fdef->type) {
        case FD_GENERIC:
        case FD_OBJECT_TYPE:
        case FD_VARIABLE_CALL_TYPE:
        case FD_LIST_TYPE:
        case FD_TUPLE_TYPE:
        case FD_BUILTIN_TYPE:
            _output("public Object ");
            _output(fdef->functionName);
            _output("(){\n");
            indentLevel++;
    }
}

void generateConditionalBlock(ConditionalBlock * conditionalBlock){
    switch (conditionalBlock->type)
    {
    case CB_IF:
        _output("if (");
        generateExpression(conditionalBlock->expression);
        _output(") {\n");
        indentLevel++;
        break;
    case CB_ELSE:
        _output("else {\n");
        indentLevel++;
        break;
    case CB_ELIF:
        _output("else if (");
        generateExpression(conditionalBlock->expression);
        _output(") {\n");
        indentLevel++;
        break;
    default:
        break;
    }
}

void generateWhileBlock(WhileBlock * whileBlock){
    _output("while (");
    generateExpression(whileBlock->expression);
    _output(") {\n");
    indentLevel++;
}

void generateBlock(Block * block){
    switch (block->type)
    {
    case BT_FUNCTION_DEFINITION:
        generateFunctionDef(block->functionDefinition);
        generateSentence(block->nextSentence);
        break;
    case BT_CLASS_DEFINITION:
    case BT_CONDITIONAL:
        generateConditionalBlock(block->conditional);
        generateSentence(block->nextSentence);
        indentLevel--;
        break;
    case BT_FOR:
    case BT_WHILE:
        generateWhileBlock(block->whileBlock);
        generateSentence(block->nextSentence);
        indentLevel--;
    default:
        break;
    }
    for (int i = 0; i < indentLevel ; i++){
                _output("\t");
    }
    _output("}");
}

void generateSentence(Sentence * sentence){
    
    if (sentence == NULL){
        return;
    }
    for (int i = 0; i < indentLevel ; i++){
                _output("\t");
    }
    switch (sentence->type) {
        case EXPRESSION_SENTENCE:
            generateExpression(sentence->expression);
            _output(";");
            generateSentence(sentence->nextSentence);
            return;
        case VARIABLE_SENTENCE:
            generateVariable(sentence->variable);
            _output(";");
            _output("\n");
            generateSentence(sentence->nextSentence);
            return;
        case BLOCK_SENTENCE:
            generateBlock(sentence->block);
            generateSentence(sentence->nextSentence);
            return;
        case RETURN_SENTENCE:
            _output("return ");
            generateExpression(sentence->expression);
            _output(";\n");
            indentLevel--;
            return;
        default:
            return;
    }
}


void generateProgram(Program * program){
    _output("import java.io.IOException;\n");
    _output("public class Main {\n\t");
    _output("public static void main(String[] args) throws IOException {\n");
    indentLevel = 2;
    generateSentence(program->sentence);
    _output("\n\t}\n");
    _output("}\n");
}

/**
 * _outputs a formatted string to standard _output.
 */
static void _output(const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	vfprintf(stdout, format, arguments);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final _output...");
	generateProgram(compilerState->abstractSyntaxtTree);
	logDebugging(_logger, "Generation is done.");
}
