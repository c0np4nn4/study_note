#include "table.h"
#include <stdlib.h>
#include <string.h>

Pair *mkEnv() {
  Pair *node = (Pair *)malloc(sizeof(Pair));
  node->d[0] = (Data){.tag = TDUO, .pval = 0};
  node->d[1] = (Data){.tag = TDUO, .pval = 0};
  return node;
}

int entry(Pair *table, str id, Data tint) {
  Pair *ptr = table;

  while (ptr->d[0].pval != 0) {
    if (strcmp(ptr->d[0].pval->d[0].sval, id) == 0) {
      ptr->d[0].pval->d[1] = tint;
      return 0;
    }
    ptr = ptr->d[1].pval;
  }

  Pair *temp_node = (Pair *)malloc(sizeof(Pair));
  temp_node->d[0] = (Data){.tag = TSTR, .sval = id};
  temp_node->d[1] = tint;

  ptr->d[0].pval = temp_node;
  ptr->d[1].pval = mkEnv();

  return 0;
}

Data *value(Pair *table, str id) {
  Pair *ptr = table;

  while (1) {
    if (strcmp(ptr->d[0].pval->d[0].sval, id) == 0) {
      return &(ptr->d[0].pval->d[1]);
    } else {
      ptr = ptr->d[1].pval;
    }
  }
}
