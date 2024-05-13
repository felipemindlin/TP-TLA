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

typedef enum DepthType DepthType;
typedef enum ExpressionType ExpressionType;
typedef enum ConstantType ConstantType;
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



typedef struct Variable Variable;
typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Conditional Conditional;
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
typedef struct Depth Depth;
typedef struct Newline Newline;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */
enum DepthType {
	TAB_DEPTH,
	END_DEPTH
};

enum NewlineType {
	FINAL_NEWLINE,
	NOT_FINAL_NEWLINE
};

enum ConstantType {
    CT_INTEGER,
    CT_BOOLEAN,
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
    IN_PARENTHESIS_EXPRESSION,
    CONSTANT_EXPRESSION
};

enum CondType { // Non arithmetic
	LOGIC_AND,
	LOGIC_OR,
	LOGIC_NOT,
	EQUALS_COMPARISON,
	NOT_EQUALS_COMPARISON,
	GREATER_THAN_COMPARISON,
	GREATER_THAN_OR_EQUALS_COMPARISON,
	LESS_THAN_COMPARISON,
	LESS_THAN_OR_EQUALS_COMPARISON,
};

enum DataType {
	DATA_INT,
};

enum SentenceType {
	EXPRESSION_SENTENCE,
    VARIABLE_SENTENCE,
    BLOCK_SENTENCE
};

enum VariableType {
	VT_EXPRESSION_VARIABLE,
	VT_FUNCCALL_VARIABLE,
	VT_METHODCALL_VARIABLE,
	VT_FIELDGETTER_VARIABLE,
	VT_OBJECT_VARIABLE,
	VT_LIST_VARIABLE,
	VT_TUPLE_VARIABLE,
	VT_VARIABLECALL_VARIABLE
};

enum MethodCallType {
    MCT_OBJECT_TRIGGER,
    MCT_VARIABLE_TRIGGER,
};

enum FieldGetterType {
    FG_OBJECT_OWNER,
    FG_VARIABLE_OWNER,
};

enum ObjectType {
  OT_OBJECT,
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

struct Constant {
	union{
        int integer;
        boolean boolean;
        char * string;
        List * list;
        Tuple * tuple;
    };
    ConstantType type;
};


struct Variable {
	union {
		Expression * expression;
		FunctionCall * functionCall;
		MethodCall * methodCall;
		FieldGetter * fieldGetter;
		Object * object;
        List * list;
        Tuple * tuple;
		// VariableCall * variableCall;
	};
	char * identifier;
	VariableType type;
};

struct Object {
  union {
    char * className;
    // List * list;
    // Tuple * tuple;
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
		Expression * expression;
        Constant * constant;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
	};
	ExpressionType type;
};

struct Conditional {
	union {
		struct {
			Conditional * leftCond;
			Conditional * rightCond;
		};
	};
	CondType type;
};

struct Sentence {
	union {
		Expression * expression;
        Variable * variable;
        // Block * block;
	};
	SentenceType type;
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
        // Object * object;
        VariableCall * variableCall;
    };
    FunctionCall * functionCall;
    MethodCallType type;
};

struct FieldGetter {
    union {
        // Object * object;
        VariableCall * variableCall;
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

struct Newline {
	NewlineType type;
};

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseProgram(Program * program);
void releaseVariable(Variable * variable);
void releaseConditional(Conditional * condtional);
void releaseSentence(Sentence * sentence);
void releaseVariableCall(VariableCall * variableCall);
void releaseMethodCall(MethodCall * methodCall);
void releaseFunctionCall(FunctionCall * functionCall);
void releaseParameters(Parameters * parameters);
void releaseNewline(Newline * newline);
void releaseDepth(Depth * depth);





#endif
