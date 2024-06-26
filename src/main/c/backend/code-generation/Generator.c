#include "Generator.h"
#include "../semantic-analysis/SymbolTable.h"
#include "../semantic-analysis/funcList.h"
#include "../semantic-analysis/utils.h"

/* MODULE INTERNAL STATE */
void generateVariableCall(VariableCall * variableCall);
void generateFunctionCall(FunctionCall * functionCall);

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
void _outputIndent(){
    for (int i = 0; i < indentLevel; i++) {
        _output("\t");
    }
}

void _outputBraceWithIndent(){
    _outputIndent();
    _output("}\n");
}
FILE * file = NULL;
FILE * write = NULL;

void generateConstant(Constant * constant){
    if (constant == NULL) {
        return;
    }
    switch (constant->type) {
        case CT_BOOLEAN:
            _output( (constant->boolean == true )? "true" : "false" );
            return;
        case CT_INTEGER:
            _output("%d", constant->integer);
            return;
        case CT_FLOAT:
            _output("%g", constant->decimal);
            return;
        case CT_STRING:
            _output("%s", constant->string);
            return;
        default:
            return;
    }
}

void generateExpression(Expression * expression) {
    if (expression == NULL) {
        return;
    }
     switch (expression->type) {
        case CONSTANT_EXPRESSION:
            generateConstant(expression->constant);
                break;
        case ADDITION:
            generateExpression(expression->leftExpression);
            _output(" + ");
            generateExpression(expression->rightExpression);
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
            return;
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
            generateFunctionCall(expression->functionCall);
            break;
        case METHOD_CALL_EXPRESSION:
        case FIELD_GETTER_EXPRESSION:
        default:
            return;
    }
}

void generateVariableCall(VariableCall * variableCall) {
    if (variableCall == NULL) {
        return;
    }
    _output(variableCall->variableName);
}

void generateFunctionCall(FunctionCall * functionCall){
    if (functionCall == NULL) {
        return;
    }
    _output(functionCall->functionName);
    _output("(");
    if (functionCall->functionArguments == NULL){
        _output(")");
        return;
    }
    while (functionCall->functionArguments->leftExpression != NULL){
        generateExpression(functionCall->functionArguments->leftExpression);

        if(functionCall->functionArguments->rightParameters != NULL){
            _output(", ");
        }
        else{
            break;
        }
        functionCall->functionArguments = functionCall->functionArguments->rightParameters;
    }
    _output(")");
}

void generateVariable(Variable * variable) {
    if (variable == NULL) {
        return;
    }
    struct value value;
    struct key key;
    bool declared = isDeclared(variable->identifier);
    bool inferType = false;
    if (variable->expression->type == FUNCTION_CALL_EXPRESSION){
        inferType = true;
        key.varname = variable->expression->functionCall->functionName;
    } else
        key.varname = variable->identifier;
    if (!declared) {
        symbolTableFind(&key, &value);
        switch (value.type) {
            case SA_BOOLEAN:
                _output("boolean  ");
                break;
            case SA_FLOAT:
                _output("double  ");
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
        markDeclared(variable->identifier);
    }

    _output(variable->identifier);
    _output(" = ");
    generateExpression(variable->expression);
}

void generateFunctionDef(FunctionDefinition * fdef){
    if (fdef == NULL) {
        return;
    }
    switch (fdef->type) {
        case FD_GENERIC:
        case FD_OBJECT_TYPE:
        case FD_VARIABLE_CALL_TYPE:
        case FD_LIST_TYPE:
        case FD_TUPLE_TYPE:
        case FD_BUILTIN_TYPE:
            _output("public static ");
            tValue retValue;
            tKey key = { .varname = fdef->functionName };
            boolean found = symbolTableFind(&key, &retValue);
            if ( found ) {
                switch (retValue.type) {
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
            } else {
                _output("Object ");
            }
            _output(fdef->functionName);
            _output("(");
            Parameters * currentParam = fdef->parameters;
            while (currentParam != NULL && currentParam->leftExpression != NULL) {
                if (isAlreadyArithmetic(currentParam->leftExpression->variableCall->variableName))
                    _output("double ");
                else if (isAlreadyBoolean(currentParam->leftExpression->variableCall->variableName))
                    _output("boolean ");
                else
                    _output("Object ");
                _output(currentParam->leftExpression->variableCall->variableName);
                currentParam = currentParam->rightParameters;
                if (currentParam != NULL) {
                    _output(", ");
                }
            }
            // while (fdef->parameters != NULL){
            //     _outputIndent();
            //     _output("Object ");
            //     _output(fdef->parameters->leftExpression->variableCall->variableName);
            //     if(fdef->parameters->rightParameters != NULL){
            //         _output(", ");
            //     }
            //     fdef->parameters = fdef->parameters->rightParameters;
            // }
            _output("){\n");
            indentLevel++;
    }
}

void generateConditionalBlock(ConditionalBlock * conditionalBlock){
    
    if (conditionalBlock == NULL)
        return;
    switch (conditionalBlock->type)
    {
    case CB_IF:
        _output("if (");
        generateExpression(conditionalBlock->expression);
        _output(") {\n");
        indentLevel++;
        break;
    case CB_ELSE:
        _outputIndent();
        _output("else {\n");
        indentLevel++;
        break;
    case CB_ELIF:
        _outputIndent();
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

void generateForBlock(ForBlock * forBlock){
    if (forBlock == NULL) {
        return;
    }
    // struct key key = {.varname = forBlock->left->variableCall->variableName};
    // struct value value;

    // symbolTableFind(&key, &value);
    // switch (value.type) {
    //     case SA_BOOLEAN:
    //         _output("boolean ");
    //         break;
    //     case SA_FLOAT:
    //         _output("double ");
    //         break;
    //     case SA_INTEGER:
    //         _output("int ");
    //         break;
    //     case SA_STRING:
    //         _output("String ");
    //         break;
    //     default:
    //         _output("Object ");
    // }


    _output("for ( Character ");
    generateExpression(forBlock->left);
    _output(" : ");
    generateExpression(forBlock->right);
    _output(".toCharArray() ) {\n");
    indentLevel++;
}


void generateBlock(Block * block){
    if (block == NULL) 
        return;
    switch (block->type)
    {
    case BT_FUNCTION_DEFINITION:
        funcListAdd(block);
        break;
    case BT_CLASS_DEFINITION:
    case BT_CONDITIONAL:
        generateConditionalBlock(block->conditional);
        generateSentence(block->nextSentence);
        indentLevel--;
        _outputBraceWithIndent();
        if (block->nextCond != NULL);{
                generateBlock(block->nextCond);
        }
        break;
    case BT_FOR:
        generateForBlock(block->forBlock);
        generateSentence(block->nextSentence);
        indentLevel--;
        _outputBraceWithIndent();
        break;
    case BT_WHILE:
        generateWhileBlock(block->whileBlock);
        generateSentence(block->nextSentence);
        indentLevel--;
        _outputBraceWithIndent();
    default:
        break;
    }
}

void generateSentence(Sentence * sentence) {
    if (sentence == NULL) {
        return;
    }
    _outputIndent();
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



void generateProgram(Program * program) {
     file = fopen("output.java", "wr");
     write = file;
    declaredVariablesCount = 0; // Reset declared variables
    _output("public class Main {\n\t");
    _output("public static void main(String[] args){\n");
    indentLevel = 2;
    generateSentence(program->sentence);
    _output("\n\t}\n");
    indentLevel = 1;
    int funcListLength = getFuncLength();

    Block * block;
    funcIterBegin();
    for (int i = 0; i < funcListLength; i++ ){
        block = getNextFunc();
        generateFunctionDef(block->functionDefinition);
        indentLevel++;
        generateSentence(block->nextSentence);
        indentLevel--;
        _outputBraceWithIndent();
        
    }
    _output("}\n\n");
    fclose(file);
}


/**
 * _outputs a formatted string to standard _output.
 */

static void _output(const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	vfprintf(write, format, arguments);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
    write=stdout;
	logDebugging(_logger, "Generating final _output...");
	generateProgram(compilerState->abstractSyntaxtTree);
	logDebugging(_logger, "Generation is done.");

}
