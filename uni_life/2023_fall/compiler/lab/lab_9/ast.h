// Define the Node structure
typedef struct Node {
  char *op;
  int ival;
  char *sval;
  struct Node *left;
  struct Node *right;
} Node;

// Function to create a new integer node
Node *mkIntNode(int n);

// Function to create a new symbol node
Node *mkSymNode(char *s);

// Function to create a new binary operation node
Node *mkBopNode(char *op, Node *left, Node *right);

// Function to create a new unary operation node
Node *mkUopNode(char *op, Node *son);

// Function to print the AST
void printTree(Node *root, int level);
