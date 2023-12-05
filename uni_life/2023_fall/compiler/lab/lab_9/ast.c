
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Function to create a new integer node
Node *mkIntNode(int n) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  node->op = NULL;
  node->ival = n;
  node->sval = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Function to create a new symbol node
Node *mkSymNode(char *s) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  node->op = NULL;
  node->ival = 0;
  node->sval = strdup(s);
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Function to create a new binary operation node
Node *mkBopNode(char *op, Node *left, Node *right) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  node->op = strdup(op);
  node->ival = 0;
  node->sval = NULL;
  node->left = left;
  node->right = right;
  return node;
}

// Function to create a new unary operation node
Node *mkUopNode(char *op, Node *son) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  node->op = strdup(op);
  node->ival = 0;
  node->sval = NULL;
  node->left = son;
  node->right = NULL;
  return node;
}

// Helper function for printing spaces for indentation
static void printSpaces(int level) {
  for (int i = 0; i < level; i++) {
    printf("    ");
  }
}

// Function to print the AST in a readable format
void printTree(Node *root, int level) {
  if (root == NULL) {
    return;
  }

  printSpaces(level);

  if (root->op != NULL) {
    if (root->right != NULL) {
      printf("Op(%s)\n", root->op);
    } else {
      printf("Uop(%s)\n", root->op);
    }
  } else if (root->sval != NULL) {
    printf("Sym('%s')\n", root->sval);
  } else {
    printf("Int(%d)\n", root->ival);
  }

  printTree(root->left, level + 1);
  printTree(root->right, level + 1);
}
