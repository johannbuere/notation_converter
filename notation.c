// make utility an exevutable
//path into windows enviroment
// make a read.me
// unit testing
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack for strings
// Suggestion: use pre-order traversal as default tree expression

/* typedef struct Tree{
    char* right[MAX];
    char* left[MAX]; 
} Tree;

*/
typedef struct Stack {
    char* items[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, char* item) {
    s->items[++(s->top)] = strdup(item);
}

char* pop(Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->items[(s->top)--];
}

char* peek(Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->items[s->top];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


// create a guide func 
// show an expression tree
// change every command into accepting a '-' or '--' prefixed command notation
// add evaluation (optional)
// convert expression into a tree
// baisc error handling: add funcs for this
// detect, and report error
// checker of format


void printHelp() {  //change func to receving -help
    printf("nota: Notation conversion program \n");
    printf("Convert expressions between notations (infix, prefix, postfix).\n\n");

    printf("Change the expression notation format.\n\n");

    printf("The expression must be wrapped in double quotes.\n");
    printf("This ensures operators and parentheses are parsed properly.\n\n");

    printf("Usage:\n");
    printf("  nota [inf|pre|pos] to [inf|pre|pos] \"EXPRESSION\"\n\n");

    printf("Example:\n");
    printf("  nota inf to pos \"( A + B ) * C\"\n");
    printf("  nota pre to inf \"+ A * B C\"\n\n");

    printf("Supported Notations:\n");
    printf("  inf     convert from/to Infix notation\n");
    printf("  pre     convert from/to Prefix notation\n");
    printf("  pos     convert from/to Postfix notation\n\n");

    printf("Helper Commands:\n");
    printf("  help        show general help\n");
    printf("  help inf    show details about Infix\n");
    printf("  help pre    show details about Prefix\n");
    printf("  help pos    show details about Postfix\n\n");
}

void printSpecificHelp(const char* type) {
    if (strcmp(type, "inf") == 0) {
        printf("Infix Notation (inf):\n");
        printf("  Operators are placed between operands.\n");
        printf("  Example: ( A + B ) * C\n");
    } else if (strcmp(type, "pre") == 0) {
        printf("Prefix Notation (pre):\n");
        printf("  Operators are placed before their operands.\n");
        printf("  Example: * + A B C\n");
    } else if (strcmp(type, "pos") == 0) {
        printf("Postfix Notation (pos):\n");
        printf("  Operators are placed after their operands.\n");
        printf("  Example: A B + C *\n");
    } else {
        printf("Unknown notation type: %s\n", type);
        printf("Use: nota help\n");
    }
}

// ---------- Conversions ---------- //

void infixToPostfix(char* expr) {
    Stack s;
    init(&s);
    char output[MAX * 2] = "", token[100];
    int i = 0;

    while (*expr) {
        if (*expr == ' ') { expr++; continue; }

        if (isalnum(*expr)) {
            int j = 0;
            while (isalnum(*expr)) token[j++] = *expr++;
            token[j] = '\0';
            strcat(output, token); strcat(output, " ");
            continue;
        }

        if (*expr == '(') {
            char t[2] = {'(', '\0'};
            push(&s, t);
        } else if (*expr == ')') {
            while (!isEmpty(&s) && *peek(&s) != '(') {
                strcat(output, pop(&s)); strcat(output, " ");
            }
            pop(&s); // pop '('
        } else if (isOperator(*expr)) {
            char op[2] = {*expr, '\0'};
            while (!isEmpty(&s) && precedence(*peek(&s)) >= precedence(op[0])) {
                strcat(output, pop(&s)); strcat(output, " ");
            }
            push(&s, op);
        }
        expr++;
    }

    while (!isEmpty(&s)) {
        strcat(output, pop(&s)); strcat(output, " ");
    }

    printf("Result (Postfix): %s\n", output);
}

void infixToPrefix(char* expr) {
    int len = strlen(expr);
    // Reverse
    for (int i = 0; i < len / 2; ++i) {
        char t = expr[i];
        expr[i] = expr[len - i - 1];
        expr[len - i - 1] = t;
    }
    // Swap ( and )
    for (int i = 0; i < len; ++i) {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }

    // Use infix to postfix logic 
    Stack s;
    init(&s);
    char output[MAX * 2] = "", token[100];
    while (*expr) {
        if (*expr == ' ') { expr++; continue; }

        if (isalnum(*expr)) {
            int j = 0;
            while (isalnum(*expr)) token[j++] = *expr++;
            token[j] = '\0';
            strcat(output, token); strcat(output, " ");
            continue;
        }

        if (*expr == '(') {
            char t[2] = {'(', '\0'};
            push(&s, t);
        } else if (*expr == ')') {
            while (!isEmpty(&s) && *peek(&s) != '(') {
                strcat(output, pop(&s)); strcat(output, " ");
            }
            pop(&s);
        } else if (isOperator(*expr)) {
            char op[2] = {*expr, '\0'};
            while (!isEmpty(&s) && precedence(*peek(&s)) > precedence(op[0])) {
                strcat(output, pop(&s)); strcat(output, " ");
            }
            push(&s, op);
        }
        expr++;
    }

    while (!isEmpty(&s)) {
        strcat(output, pop(&s)); strcat(output, " ");
    }

    // Reverse again
    int o_len = strlen(output);
    for (int i = 0; i < o_len / 2; ++i) {
        char t = output[i];
        output[i] = output[o_len - i - 1];
        output[o_len - i - 1] = t;
    }

    printf("Result (Prefix): %s\n", output);
}

void prefixToInfix(char* expr) {
    Stack s;
    init(&s);
    char tokens[MAX][MAX];
    int count = 0;

    char* tok = strtok(expr, " ");
    while (tok) {
        strcpy(tokens[count++], tok);
        tok = strtok(NULL, " ");
    }

    for (int i = count - 1; i >= 0; --i) {
        if (isOperator(tokens[i][0]) && tokens[i][1] == '\0') {
            char* op1 = pop(&s);
            char* op2 = pop(&s);
            char buf[MAX * 2];
            sprintf(buf, "(%s %s %s)", op1, tokens[i], op2);
            push(&s, buf);
        } else {
            push(&s, tokens[i]);
        }
    }

    printf("Result (Infix): %s\n", pop(&s));
}

void postfixToInfix(char* expr) {
    Stack s;
    init(&s);
    char tokens[MAX][MAX];
    int count = 0;

    char* tok = strtok(expr, " ");
    while (tok) {
        strcpy(tokens[count++], tok);
        tok = strtok(NULL, " ");
    }

    for (int i = 0; i < count; ++i) {
        if (isOperator(tokens[i][0]) && tokens[i][1] == '\0') {
            char* op2 = pop(&s);
            char* op1 = pop(&s);
            char buf[MAX * 2];
            sprintf(buf, "(%s %s %s)", op1, tokens[i], op2);
            push(&s, buf);
        } else {
            push(&s, tokens[i]);
        }
    }

    printf("Result (Infix): %s\n", pop(&s));
}

void postfixToPrefix(char* expr) {
    Stack s;
    init(&s);
    char* tok = strtok(expr, " ");
    while (tok) {
        if (isOperator(tok[0]) && tok[1] == '\0') {
            char* op2 = pop(&s);
            char* op1 = pop(&s);
            char buf[MAX * 2];
            sprintf(buf, "%s %s %s", tok, op1, op2);
            push(&s, buf);
        } else {
            push(&s, tok);
        }
        tok = strtok(NULL, " ");
    }
    printf("Result (Prefix): %s\n", pop(&s));
}

void prefixToPostfix(char* expr) {
    Stack s;
    init(&s);
    char tokens[MAX][MAX];
    int count = 0;

    char* tok = strtok(expr, " ");
    while (tok) {
        strcpy(tokens[count++], tok);
        tok = strtok(NULL, " ");
    }

    for (int i = count - 1; i >= 0; --i) {
        if (isOperator(tokens[i][0]) && tokens[i][1] == '\0') {
            char* op1 = pop(&s);
            char* op2 = pop(&s);
            char buf[MAX * 2];
            sprintf(buf, "%s %s %s", op1, op2, tokens[i]);
            push(&s, buf);
        } else {
            push(&s, tokens[i]);
        }
    }

    printf("Result (Postfix): %s\n", pop(&s));
}

// ---------- MAIN ---------- //

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp(); // change this into instead printing help to printing a string telling the user to do -help [optional]
        return 0;
    }

    if (strcmp(argv[1], "help") == 0) { //change help into - help
        if (argc == 2) {
            printHelp();
        } else if (argc == 3) {
            printSpecificHelp(argv[2]);
        } else {
            printf("Too many arguments for help.\n");
            printf("Use: nota help [inf|pre|pos]\n");
        }
        return 0;
    }

    if (argc < 5 || strcmp(argv[2], "to") != 0) {
        printf("Invalid format. Use `nota help` for instructions.\n");
        return 1;
    }

    char* from = argv[1];
    char* to = argv[3];

    if (strcmp(from, to) == 0) {
        printf("Cannot convert the same notation type (%s to %s).\n", from, to);
        return 1;
    }

    // Join expression
    char expr[256] = "";
    for (int i = 4; i < argc; i++) {
        strcat(expr, argv[i]);
        if (i < argc - 1) strcat(expr, " ");
    }

    if (strcmp(from, "inf") == 0 && strcmp(to, "pos") == 0)
        infixToPostfix(expr);
    else if (strcmp(from, "inf") == 0 && strcmp(to, "pre") == 0)
        infixToPrefix(expr);
    else if (strcmp(from, "pre") == 0 && strcmp(to, "inf") == 0)
        prefixToInfix(expr);
    else if (strcmp(from, "pos") == 0 && strcmp(to, "inf") == 0)
        postfixToInfix(expr);
    else if (strcmp(from, "pos") == 0 && strcmp(to, "pre") == 0)
        postfixToPrefix(expr);
    else if (strcmp(from, "pre") == 0 && strcmp(to, "pos") == 0)
        prefixToPostfix(expr);
    else
        printf("Unsupported conversion: %s to %s\n", from, to);

    return 0;
}