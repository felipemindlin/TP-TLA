#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

typedef enum ExpressionType ExpressionType;
typedef enum ConstantType ConstantType;
typedef enum DepthType DepthType;
typedef enum DataType DataType;
typedef enum CondType CondType;
typedef enum ParametersType ParamType;
typedef enum SentenceType SentenceType;
typedef enum NewlineType NewlineType;
typedef enum VariableType VariableType;
typedef enum MethodCallType MethodCallType;
typedef enum FieldGetterType FieldGetterType;
typedef enum ObjectType ObjectType;
typedef enum ListType ListType;
typedef enum BlockType BlockType;
typedef enum FunctionDefinitionType FunctionDefinitionType;
typedef enum ClassDefinitionType ClassDefinitionType;
typedef enum BinaryComparatorType BinaryComparatorType;
typedef enum ComparableValueType ComparableValueType;
typedef enum LogicValueType LogicValueType;
typedef enum ConditionalType ConditionalType;

typedef struct Variable Variable;
typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Program Program;
typedef struct Parameters Parameters;
typedef struct FunctionCall FunctionCall;
typedef struct MethodCall MethodCall;
typedef struct FieldGetter FieldGetter;
typedef struct Object Object;
typedef struct List List;
typedef struct List Tuple;
typedef struct VariableCall VariableCall;
typedef struct Sentence Sentence;
typedef struct Block Block;
typedef struct WhileBlock WhileBlock;
typedef struct FunctionDefinition FunctionDefinition;
typedef struct ClassDefinition ClassDefinition;
typedef struct Depth Depth;
typedef struct Newline Newline;
typedef struct BinaryComparator BinaryComparator;
typedef struct ComparableValue ComparableValue;
typedef struct LogicValue LogicValue;
typedef struct ForBlock ForBlock;
typedef struct ConditionalBlock ConditionalBlock;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */
enum DepthType {
	TAB_DEPTH,
	END_DEPTH
};

enum ConstantType {
    CT_INTEGER,
    CT_BOOLEAN,
    CT_FLOAT,
    CT_STRING,
    CT_LIST,
    CT_TUPLE,
};

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION,
	EXPONENTIATION,
	TRUNCATED_DIVISION,
	MODULO,
	ASSIGNMENT,
	ADDITION_ASSIGNMENT,
	DIVISION_ASSIGNMENT,
	MULTIPLICATION_ASSIGNMENT,
	SUBTRACTION_ASSIGNMENT,
	EXPONENTIATION_ASSIGNMENT,
	TRUNCATED_DIVISION_ASSIGNMENT,
	MODULO_ASSIGNMENT,
	BITWISE_AND_ASSIGNMENT,
	BITWISE_OR_ASSIGNMENT,
	BITWISE_XOR_ASSIGNMENT,
	BITWISE_LEFT_SHIFT_ASSIGNMENT,
	BITWISE_RIGHT_SHIFT_ASSIGNMENT,
	RETURNED_ASSIGNMENT,
	IDENTITY,
	NOT_IDENTITY,
	MEMBERSHIP,
	NOT_MEMBERSHIP,
	BIT_ARITHMETIC_AND,
	BIT_ARITHMETIC_OR,
	BIT_ARITHMETIC_XOR,
	BIT_ARITHMETIC_NOT,
	BIT_ARITHMETIC_LEFT_SHIFT,
	BIT_ARITHMETIC_RIGHT_SHIFT,
    VARIABLE_CALL_EXPRESSION,
    FUNCTION_CALL_EXPRESSION,
    METHOD_CALL_EXPRESSION,
    FIELD_GETTER_EXPRESSION,
    CONDITIONAL_EXPRESSION,
    CONSTANT_EXPRESSION,
	LOGIC_AND,
	LOGIC_OR,
	LOGIC_NOT,
    COMPARISON_EXPRESSION,
};

enum SentenceType {
	EXPRESSION_SENTENCE,
    VARIABLE_SENTENCE,
    BLOCK_SENTENCE,
};

enum BlockType {
    BT_FUNCTION_DEFINITION,
    BT_CLASS_DEFINITION,
    BT_CONDITIONAL,
    BT_FOR,
    BT_WHILE,
};

enum FunctionDefinitionType {
    FD_GENERIC,
    FD_OBJECT_TYPE,
    FD_VARIABLE_CALL_TYPE,
    FD_LIST_TYPE,
    FD_TUPLE_TYPE
};

enum ClassDefinitionType {
    CDT_TUPLE_INHERITANCE,
    CDT_NOT_INHERITS,
};

enum MethodCallType {
    MCT_VARIABLE_TRIGGER,
    MCT_CONSTANT_TRIGGER,
};

enum FieldGetterType {
    FG_CONSTANT_OWNER,
    FG_VARIABLE_OWNER,
};

enum ObjectType {
  OT_BUILTIN,
};

enum ListType {
  LT_EMPTY_LIST,
  LT_TYPED_LIST,
  LT_PARAMETRIZED_LIST
};

enum ParametersType {
	EMPTY,
	FINAL,
	NOT_FINAL
};

enum BinaryComparatorType {
	BCT_EQU,
	BCT_NEQ,
	BCT_GT,
	BCT_GTE,
	BCT_LT,
	BCT_LTE,
	BCT_MEMBER,
	BCT_NMEMBER,
	BCT_IDENTITY,
	BCT_NIDENTITY,
};

enum ConditionalType {
    CB_IF,
    CB_ELIF,
    CB_ELSE,
};

struct Constant {
	union{
        int integer;
        boolean boolean;
        double decimal;
        char * string;
        List * list;
        Tuple * tuple;
    };
    ConstantType type;
};


struct Variable {
	Expression * expression;
	char * identifier;
};

struct Object {
  union {
    char * className;
  };
  ObjectType type;
};

struct List {
	union {
		Parameters * elements;
   	 	Object * objectType;
	};
    ListType type;
};

struct Expression {
	union {
        Constant * constant;
        VariableCall * variableCall;
        FunctionCall * functionCall;
        MethodCall * methodCall;
        FieldGetter * fieldGetter;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
		struct {
			Expression * leftCompExpression;
			Expression * rightCompExpression;
            BinaryComparatorType compType;
		};
        Expression * notExpression;
	};
	ExpressionType type;
};

struct Sentence {
	union {
		Expression * expression;
        Variable * variable;
        Block * block;
	};
	SentenceType type;
};

struct Block {
    union {
        FunctionDefinition * functionDefinition;
        ClassDefinition * classDefinition;
        struct {
            ConditionalBlock * conditional;
            Block * nextCond;
        };
        ForBlock * forBlock;
        WhileBlock * whileBlock;
    };
    Program * nextProgram;
    BlockType type;
};

struct ConditionalBlock {
    Expression * expression;
    ConditionalType type;
};

struct WhileBlock {
	Expression * expression;
};

struct ForBlock {
    Expression * left;
    Expression * right;
};

struct FunctionDefinition {
    union {
        Object * objectType;
        VariableCall * returnVariableType;
        List * listReturnType;
        Tuple * tupleReturnType;
    };
    Parameters * parameters;
    char * functionName;
    FunctionDefinitionType type;
};

struct ClassDefinition {
    Tuple * tuple;
    char * className;
    ClassDefinitionType type;
};

struct VariableCall {
	const char * variableName;
};

struct FunctionCall {
	const char * functionName;
	Parameters * functionArguments;
};

struct MethodCall {
	union {
        VariableCall * variableCall;
        Constant * constant;
    };
    FunctionCall * functionCall;
    MethodCallType type;
};

struct FieldGetter {
    union {
        VariableCall * variableCall;
        Constant * constant;
    };
    VariableCall * field;
    FieldGetterType type;
};

struct Parameters {
	struct {
		Expression * leftExpression;
		Parameters * rightParameters;
	};
	ParamType type;
};

struct Program {
	Depth * depth;
	Sentence * sentence;
	Program * nextProgram;
};

struct Depth {
	DepthType type;
};

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseProgram(Program * program);
void releaseVariable(Variable * variable);
void releaseSentence(Sentence * sentence);
void releaseVariableCall(VariableCall * variableCall);
void releaseMethodCall(MethodCall * methodCall);
void releaseFunctionCall(FunctionCall * functionCall);
void releaseParameters(Parameters * parameters);
void releaseDepth(Depth * depth);
void releaseTuple(Tuple * tuple);
void releaseFunctionDefinition(FunctionDefinition * functionDefinition);
void releaseClassDefinition(ClassDefinition * classDefinition);
void releaseBlock(Block * block);
void releaseWhileBlock(WhileBlock * wblock);
void releaseForBlock(ForBlock * fblock);
void releaseConditionalBlock(ConditionalBlock * cblock);
void releaseObject(Object * Object);
void releaseFieldGetter(FieldGetter * fieldGetter);
void releaseList(List * list);

#endif
