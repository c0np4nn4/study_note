#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef enum { TINT, TSTR, TPAIR, TNIL } DataType;

typedef struct Pair {
  struct Data *car, *cdr;
} Pair;

typedef struct Data {
  DataType tag;
  union {
    int ival;
    char *sval;
    Pair *pval;
  };
} Data;

Data nil = {TNIL};
char input[BUFFER_SIZE];
char *cursor;

Data *cons(Data *car, Data *cdr) {
  Pair *p = malloc(sizeof(Pair));
  p->car = car;
  p->cdr = cdr;
  Data *d = malloc(sizeof(Data));
  d->tag = TPAIR;
  d->pval = p;
  return d;
}

int prdata(Data *d);

int prlist(Data *d) {
  if (d->tag == TNIL)
    return 1;

  if (d->tag != TPAIR) {
    prdata(d);
    return 1;
  }

  prdata(d->pval->car);
  if (d->pval->cdr->tag != TNIL) {
    printf(" ");
    if (d->pval->cdr->tag == TPAIR) {
      prlist(d->pval->cdr);
    } else {
      prdata(d->pval->cdr);
    }
  }

  return 0;
}

int prdata(Data *d) {
  switch (d->tag) {
  case TINT:
    printf("%d", d->ival);
    break;
  case TSTR:
    printf("'%s'", d->sval);
    break;
  case TPAIR:
    printf("(");
    if (!prlist(d)) {
      printf(" . ");
      prdata(d->pval->cdr);
    }
    printf(")");
    break;
  case TNIL:
    printf("NIL");
    break;
  }
  return 0;
}

Data *rddata() {
  while (isspace(*cursor))
    cursor++; // Skip whitespaces

  if (*cursor == '(') {
    cursor++;
    if (*cursor == ')') {
      cursor++;
      return &nil;
    }
    Data *car = rddata();
    while (isspace(*cursor))
      cursor++; // Skip whitespaces
    if (*cursor == '.') {
      cursor++;
      Data *cdr = rddata();
      while (isspace(*cursor))
        cursor++; // Skip whitespaces
      if (*cursor != ')') {
        fprintf(stderr,
                "Error: Closing parenthesis ')' expected, but got '%c'\n",
                *cursor);
        exit(EXIT_FAILURE);
      }
      cursor++;
      return cons(car, cdr);
    } else {
      Data *cdr = rddata();
      while (isspace(*cursor))
        cursor++; // Skip whitespaces
      if (*cursor != ')') {
        fprintf(stderr,
                "Error: Closing parenthesis ')' expected, but got '%c'\n",
                *cursor);
        exit(EXIT_FAILURE);
      }
      cursor++;
      return cons(car, cdr);
    }
  } else if (isdigit(*cursor) || *cursor == '-') {
    char number[BUFFER_SIZE];
    int i = 0;
    while (isdigit(*cursor) || *cursor == '-') {
      number[i++] = *cursor;
      cursor++;
    }
    number[i] = '\0';
    Data *d = malloc(sizeof(Data));
    d->tag = TINT;
    d->ival = atoi(number);
    return d;
  } else if (*cursor == '"') {
    cursor++; // Skip the opening double quote
    char *start = cursor;
    while (*cursor != '"') {
      if (*cursor == '\0') {
        fprintf(stderr, "Error: Closing double quote expected\n");
        exit(EXIT_FAILURE);
      }
      cursor++;
    }
    *cursor = '\0';
    cursor++; // Skip the closing double quote
    Data *d = malloc(sizeof(Data));
    d->tag = TSTR;
    d->sval = strdup(start);
    return d;
  } else {
    fprintf(stderr, "Error: Unexpected character '%c'\n", *cursor);
    exit(EXIT_FAILURE);
  }
  return NULL;
}

int main() {
  while (fgets(input, BUFFER_SIZE, stdin) != NULL) {
    cursor = input;
    Data *data = rddata();
    prdata(data);
    printf("\n");
  }
  return 0;
}
