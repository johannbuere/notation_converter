#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100

// ----------------- Expression Tree ----------------- //
typedef struct Node {
    char value[10];
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(const char* val) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->value, val);
    node->left = node->right = NULL;
    return node;
}

bool isOperator(const char* token) {
    return strlen(token) == 1 && strchr("+-*/", token[0]);
}

bool isOperand(const char* token) {
    return strlen(token) == 1 && isdigit(token[0]);
}

bool isValidToken(const char* token) {
    return isOperand(token) || isOperator(token);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// ------------- Stack for Tree Nodes ------------- //
typedef struct {
    Node* items[MAX];
    int top;
} NodeStack;

void initNodeStack(NodeStack* s) {
    s->top = -1;
}

bool isNodeStackEmpty(NodeStack* s) {
    return s->top == -1;
}

void pushNode(NodeStack* s, Node* n) {
    s->items[++(s->top)] = n;
}

Node* popNode(NodeStack* s) {
    if (isNodeStackEmpty(s)) return NULL;
    return s->items[(s->top)--];
}

Node* peekNode(NodeStack* s) {
    if (isNodeStackEmpty(s)) return NULL;
    return s->items[s->top];
}

// ----------------- Tree Construction ----------------- //
Node* buildTreeFromPostfix(const char* expr) {
    NodeStack stack;
    initNodeStack(&stack);

    char exprCopy[256];
    strcpy(exprCopy, expr);
    char* tok = strtok(exprCopy, " ");

    while (tok) {
  
        if (!isValidToken(tok)) {
            printf("Error: Invalid token '%s'.\n", tok);
            return NULL;
        }


        if (isOperator(tok)) {
            Node* right = popNode(&stack);
            Node* left = popNode(&stack);
            if (!left || !right) {
                printf("Error: Stack underflow. Incomplete postfix expression.\n");
                return NULL;
            }
            Node* op = createNode(tok);
            op->left = left;
            op->right = right;
            pushNode(&stack, op);
        } else {
            pushNode(&stack, createNode(tok));
        }
        tok = strtok(NULL, " ");
    }

    if (stack.top != 0) {
        printf("Error: Extra tokens in postfix expression.\n");
        return NULL;
    }

    return popNode(&stack);
}

Node* buildTreeFromPrefixUtil(char** tokens, int* index, int count) {
    if (*index >= count) return NULL;
    char* tok = tokens[*index];

    if (!isValidToken(tok)) {
        printf("Error: Invalid token '%s'.\n", tok);
        return NULL;
    }

    Node* node = createNode(tok);
    (*index)++;

    if (isOperator(tok)) {
        node->left = buildTreeFromPrefixUtil(tokens, index, count);
        node->right = buildTreeFromPrefixUtil(tokens, index, count);
        if (!node->left || !node->right) {
            printf("Error: Incomplete prefix expression.\n");
            return NULL;
        }
    }

    return node;
}

Node* buildTreeFromPrefix(const char* expr) {
    char exprCopy[256];
    strcpy(exprCopy, expr);
    char* tokens[MAX];
    int count = 0;

    char* tok = strtok(exprCopy, " ");
    while (tok) {
        tokens[count++] = tok;
        tok = strtok(NULL, " ");
    }

    int index = 0;
    Node* root = buildTreeFromPrefixUtil(tokens, &index, count);
    if (index != count) {
        printf("Error: Extra tokens in prefix expression.\n");
        return NULL;
    }
    return root;
}

Node* buildTreeFromInfix(const char* expr) {
    NodeStack ops, nodes;
    initNodeStack(&ops);
    initNodeStack(&nodes);

    char exprCopy[256];
    strcpy(exprCopy, expr);
    char* tok = strtok(exprCopy, " ");

    while (tok) {
        if (!isValidToken(tok) && strcmp(tok, "(") != 0 && strcmp(tok, ")") != 0) {
            printf("Error: Invalid token '%s'.\n", tok);
            return NULL;
        }

        if (isOperand(tok)) {
            pushNode(&nodes, createNode(tok));
        } else if (strcmp(tok, "(") == 0) {
            pushNode(&ops, createNode(tok));
        } else if (strcmp(tok, ")") == 0) {
            while (!isNodeStackEmpty(&ops) && strcmp(peekNode(&ops)->value, "(") != 0) {
                Node* op = popNode(&ops);
                Node* right = popNode(&nodes);
                Node* left = popNode(&nodes);
                if (!left || !right) {
                    printf("Error: Stack underflow. Incomplete infix expression.\n");
                    return NULL;
                }
                op->left = left;
                op->right = right;
                pushNode(&nodes, op);
            }
            if (isNodeStackEmpty(&ops)) {
                printf("Error: Mismatched parentheses.\n");
                return NULL;
            }
            popNode(&ops); // Remove "("
        } else if (isOperator(tok)) {
            while (!isNodeStackEmpty(&ops) && isOperator(peekNode(&ops)->value) &&
                   precedence(peekNode(&ops)->value[0]) >= precedence(tok[0])) {
                Node* op = popNode(&ops);
                Node* right = popNode(&nodes);
                Node* left = popNode(&nodes);
                if (!left || !right) {
                    printf("Error: Stack underflow. Incomplete infix expression.\n");
                    return NULL;
                }
                op->left = left;
                op->right = right;
                pushNode(&nodes, op);
            }
            pushNode(&ops, createNode(tok));
        }
        tok = strtok(NULL, " ");
    }

    while (!isNodeStackEmpty(&ops)) {
        Node* op = popNode(&ops);
        Node* right = popNode(&nodes);
        Node* left = popNode(&nodes);
        if (!left || !right) {
            printf("Error: Stack underflow. Incomplete infix expression.\n");
            return NULL;
        }
        op->left = left;
        op->right = right;
        pushNode(&nodes, op);
    }

    if (nodes.top != 0) {
        printf("Error: Extra tokens or mismatched expression.\n");
        return NULL;
    }

    return popNode(&nodes);
}

// ----------------- Traversals ----------------- //
void inorder(Node* root) {
    if (!root) return;
    if (root->left && root->right) printf("(");
    inorder(root->left);
    printf(" %s ", root->value);
    inorder(root->right);
    if (root->left && root->right) printf(")");
}

void preorder(Node* root) {
    if (!root) return;
    printf("%s ", root->value);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->value);
}

// ----------------- Visual Tree Print ----------------- //
void printTree(Node* root, int space) {
    if (!root) return;
    space += 5;
    printTree(root->right, space);
    for (int i = 5; i < space; i++) printf(" ");
    printf("%s\n", root->value);
    printTree(root->left, space);
}

// ----------------- Help & Guide ----------------- //
void printHelp() {
    printf("Usage: nota --from <infix|prefix|postfix> --to <infix|prefix|postfix> \"EXPRESSION\"\n");
    printf("Example: ./nota --from postfix --to infix \"3 4 + 5 *\"\n");
    printf("Use --guide for more details.\n");
}

void printGuide() {
    printf("\n--- nota Converter CLI Guide ---\n");
    printf("This program converts mathematical expressions between infix, prefix, and postfix notations.\n");
    printf("\nHOW IT WORKS:\n  Converts expressions by building an expression tree from the input\n");
    printf("  notation, then traverses the tree to generate the target notation.\n");
    printf("  Supports +, -, *, / operators\n");
    printf("  Operands must be single-digit non-negative integers (0-9)\n");
    printf("\nUSAGE:\n  nota --from <format> --to <format> \"EXPRESSION\"\n");
    printf("    Format: infix | prefix | postfix\n");
    printf("\nEXAMPLES:\n");
    printf("  nota --from infix --to postfix \"( 3 + 4 ) * 5\"\n");
    printf("  nota --from postfix --to infix \"3 4 +\"\n");
    printf("  nota --from prefix --to infix \"+ 3 4\"\n");

    printf("\nEnsure your input is space-separated.\n");
    printf("\n------------------------------------\n\n");
}

// ----------------- CLI Parser ----------------- //
int main(int argc, char* argv[]) {
    if (argc == 1) {
        printHelp();
        return 0;
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printHelp();
        return 0;
    }
    if (strcmp(argv[1], "--guide") == 0) {
        printGuide();
        return 0;
    }

    char* from = NULL;
    char* to = NULL;
    char expr[256] = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--from") == 0 && i + 1 < argc) {
            from = argv[++i];
        } else if (strcmp(argv[i], "--to") == 0 && i + 1 < argc) {
            to = argv[++i];
        } else if (argv[i][0] != '-') {
            strcat(expr, argv[i]);
            strcat(expr, " ");
        }
    }

    if (!from || !to || strlen(expr) == 0) {
        printf("Error: Missing required arguments.\n");
        printHelp();
        return 1;
    }
    

    Node* root = NULL;
    if (strcmp(from, "postfix") == 0) {
        root = buildTreeFromPostfix(expr);
    } else if (strcmp(from, "prefix") == 0) {
        root = buildTreeFromPrefix(expr);
    } else if (strcmp(from, "infix") == 0) {
        root = buildTreeFromInfix(expr);
    } else {
        printf("Error: Unsupported input format '%s'.\n", from);
        return 1;
    }

    if (!root) return 1;

    printf("\n--- Expression Tree ---\n");
    printTree(root, 0);

    printf("\n--- Converted Expression (%s) ---\n", to);
    if (strcmp(to, "infix") == 0) inorder(root);
    else if (strcmp(to, "prefix") == 0) preorder(root);
    else if (strcmp(to, "postfix") == 0) postorder(root);
    else printf("Error: Unsupported output format '%s'.\n", to);

    printf("\n");
    return 0;
}
