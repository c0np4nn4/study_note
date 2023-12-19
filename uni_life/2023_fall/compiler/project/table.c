#include "table.h"
#include <stdio.h>
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

char *replace_format_specifier(char *str, Data *data) {
  char *placeholder = "{}";
  char *pos = strstr(str, placeholder);

  if (pos == NULL) {
    return strdup(str);
  }

  char *formatted_string =
      malloc(strlen(str) + 256); // 256 is just a placeholder, you may want to
                                 // calculate the exact size
  strncpy(formatted_string, str, pos - str);
  formatted_string[pos - str] = '\0';

  switch (data->tag) {
  case TINT: {
    char value[256]; // Assuming the number won't exceed this length
    sprintf(value, "%d", data->ival);
    strcat(formatted_string, value);
    break;
  }
  case TSTR: {
    strcat(formatted_string, data->sval);
    break;
  }
  default: {
    // Handle other cases if necessary
    break;
  }
  }

  strcat(formatted_string, pos + strlen(placeholder));

  return replace_escapes(formatted_string);
  // return formatted_string;
}

char *replace_escapes(char *str) {
  // 문자열 내의 \n을 찾아 실제 개행 문자로 대체
  char *p = str;
  while ((p = strstr(p, "\\n")) != NULL) {
    memmove(p, p + 1, strlen(p + 1) + 1);
    *p = '\n';
  }

  // 문자열 내의 \t를 찾아 실제 탭 문자로 대체
  p = str;
  while ((p = strstr(p, "\\t")) != NULL) {
    memmove(p, p + 1, strlen(p + 1) + 1);
    *p = '\t';
  }

  return str;
}
