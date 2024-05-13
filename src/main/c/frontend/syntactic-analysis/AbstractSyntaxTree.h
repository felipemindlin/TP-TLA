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
typedef enum FactorType FactorType;
typedef enum ConstantType ConstantType;
typedef enum DataType DataType;
typedef enum CondType CondType;
typedef enum ParametersType ParamType;
typedef enum SentenceType SentenceType;
typedef enum NewlineType NewlineType;
typedef enum BlockType BlockType;
typedef enum ComparisonCond ComparisonCond;
typedef enum BooleanCond BooleanCond;
typedef enum ObjectCond ObjectCond;
typedef enum ForType ForType;
typedef enum Which Which;
typedef enum MethodCallType MethodCallType;
typedef enum FieldGetterType FieldGetterType;

/* Every Block will be of the following types */
typedef struct Block Block;
typedef struct FunctionDefinition FunctionDefinition;
typedef struct ClassDefinition ClassDefinition;
typedef struct Conditional Conditional;
typedef struct While While;
typedef struct For For;

typedef struct Variable Variable;
typedef struct Constant Constant;
typedef struct Object Object;
typedef struct List List;
typedef struct List Tuple;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct Parameters Parameters;
typedef struct FunctionDefinition FunctionDefinition;
typedef struct MethodCall MethodCall;
typedef struct FieldGetter FieldGetter;
typedef struct FunctionCall FunctionCall;
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
};

enum CondType { // Non arithmetic
    BOOLEAN_COND,
    VARIABLE_AND_BOOLEAN_COND,
    VARIABLE_BOOLEAN_COND,
    COMPARISON_COND,
    VARIABLE_COMPARISON_COND,
    VARIABLE_AND_CONST_COMPARISON_COND,
    OBJECT_COMPARISON_COND,
    VARIABLE_OBJECT_COMPARISON_COND,
    VARIABLE_AND_OBJECT_COMPARISON_COND,
    EXPRESSION_COND,
    VARIABLE_COND,
    OBJECT_COND,
};

enum MethodCallType {
    OBJECT_TRIGGER,
    VARIABLE_TRIGGER,
};

enum FieldGetterType {
    FG_OBJECT_OWNER,
    FG_VARIABLE_OWNER,
};

enum ForType {
    FOR_FACTOR,
    FOR_FACTOR_AND_VARIABLE,
    FOR_VARIABLE,
};

enum Which {
    VARIABLE_ON_THE_LEFT,
    FACTOR_ON_THE_LEFT,
};

enum BooleanCond {
	LOGIC_AND,
	LOGIC_OR,
	LOGIC_NOT,
};

enum ComparisonCond {
	EQUALS_COMPARISON,
	NOT_EQUALS_COMPARISON,
	GREATER_THAN_COMPARISON,
	GREATER_THAN_OR_EQUALS_COMPARISON,
	LESS_THAN_COMPARISON,
	LESS_THAN_OR_EQUALS_COMPARISON,
    IN_COMPARISON,
    NOT_IN_COMPARISON,
};

enum ObjectCond {
    IS_COND,
    IS_NOT_COND,
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

enum DataType {
    DATA_OBJECT,
    DATA_INFERRED,
};

enum ConstantType {
	CONSTANT_INT,
    CONSTANT_FLOAT,
    CONSTANT_STRING,
    CONSTANT_BOOLEAN,
    CONSTANT_LIST,
    CONSTANT_TUPLE,
};

enum SentenceType {
	EXPRESSION_SENTENCE,
    VARIABLE_SENTENCE,
    BLOCK_SENTENCE
};

enum ParametersType {
	EMPTY,
	FINAL,
	NOT_FINAL
};

enum BlockType {
    FUNC_DEF,
    CLASS_DEF,
    CONDITIONAL,
    WHILE_BLOCK,
    FOR_BLOCK,
};

struct Object {
    char * className;
};

struct FunctionDefinition {
	const char * functionName;
	Parameters * functionArguments;
    DataType returnType;
    Object * objectReturnType;
};

struct MethodCall {
    union {
        Object * object;
        VariableCall * variableCall;
    };
    FunctionCall * functionCall;
    MethodCallType type;
};

struct FieldGetter {
    union {
        Object * object;
        VariableCall * variableCall;
    };
    VariableCall * field;
    FieldGetterType type;
};

struct ClassDefinition {
    char * className;
    ClassDefinition * parent;
    Variable ** fields;
};

struct Conditional {
	union {
		struct {
            Expression * leftExpression;
            Expression * rightExpression;
            ComparisonCond comparisonCond;
        };
        struct {
            VariableCall * leftExpressionVar;
            VariableCall * rightExpressionVar;
            ComparisonCond comprCondition;
        };
        struct {
            VariableCall * expressionVar;
            Expression * exp;
            ComparisonCond comprCond;
        };
		struct {
			Conditional * leftCond;
			Conditional * rightCond;
            BooleanCond booleanCond;
		};
		struct {
			Conditional * cond;
			VariableCall * condVar;
            BooleanCond boolConditon;
		};
		struct {
			VariableCall * leftCondVar;
			VariableCall * rightCondVar;
            BooleanCond boolCond;
		};
        Object * object;
        VariableCall * variable;
        struct {
            Object * leftObject;
            Object * rightObject;
            ObjectCond objectCond;
        };
        struct{
            VariableCall * variableLeftObj;
            VariableCall * variableRightObj;
            ObjectCond objCondition;
        };
        struct {
            VariableCall * variableObj;
            Object * obj;
            ObjectCond objCond;
        };
        Expression * expression;
	};
	CondType type;
};

struct While {
    Conditional * conditional;
};

struct For {
    union {
        struct {
            Factor * left;
            Factor * right;
        };
        struct {
            VariableCall * leftVar;
            VariableCall * rightVar;
        };
        struct {
            VariableCall * var;
            Factor * fact;
            Which which;
        };
    };
    ForType type;
};

struct Block {
    union {
        FunctionDefinition * functionDefinition;
        ClassDefinition * classDefinition;
        Conditional * conditional;
        While * whileBlock;
        For * forBlock;
    };
    BlockType type;
};
struct Constant {
	union{
        int integer;
        int boolean;
        float decimal;
        char * string;
        List * list;
        Tuple * tuple;
    };
    ConstantType type;
};


struct Variable {
	union {
        int integer;
        float decimal;
        int boolean;
        char * string;
        List * list;
        Tuple * tuple;
        Object * object;
    };
    char * identifier;
	DataType type;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
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

struct VariableCall {
	const char * variableName;
};

struct FunctionCall {
	const char * functionName;
	Parameters * functionArguments;
};

struct List {
    Parameters * elements;
    Object * objectType;
};

struct Parameters {
	struct {
		Expression * leftExpression;
		Parameters * rightParameters;
	};
	ParamType type;
};

struct Program {
    union {
        struct {
            Depth * depth;
            Sentence * sentence;
            Program * program;
        };
    };
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
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);
void releaseVariable(Variable * variable);
void releaseConditional(Conditional * condtional);
void releaseSentence(Sentence * sentence);
void releaseVariableCall(VariableCall * variableCall);
void releaseFunctionCall(FunctionCall * functionCall);
void releaseParameters(Parameters * parameters);
void releaseNewline(Newline * newline);
void releaseDepth(Depth * depth);

void releaseConditional(Conditional * conditional);
void releaseWhile(While * whileBlock);
void releaseFor(For * forBlock);
void releaseList(List * list);
void releaseTuple(Tuple * tuple);
void releaseFunctionDefinition(FunctionDefinition * functionDefinition);
void releaseClassDefinition(ClassDefinition * classDefinition);
void releaseObject(Object * object);

#endif
