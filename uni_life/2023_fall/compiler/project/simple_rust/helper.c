#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pair *mkEnv() {
  Pair *node = (Pair *)malloc(sizeof(Pair));
  node->d[0] = (Data){.tag = TDUO, .pval = 0};
  node->d[1] = (Data){.tag = TDUO, .pval = 0};
  return node;
}

int entry(Pair *table, str id, Data data) {
  Pair *ptr = table;

  while (ptr->d[0].pval != 0) {
    if (strcmp(ptr->d[0].pval->d[0].sval, id) == 0) {
      ptr->d[0].pval->d[1] = data;
      return 0;
    }
    ptr = ptr->d[1].pval;
  }

  Pair *temp_node = (Pair *)malloc(sizeof(Pair));
  temp_node->d[0] = (Data){.tag = TSTR, .sval = id};
  temp_node->d[1] = data;

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

str replace_format_specifier(str msg, Data *data) {
  char *placeholder = "{}";
  char *pos = strstr(msg, placeholder);

  if (pos == NULL) {
    return strdup(msg);
  }

  char *formatted_string =
      malloc(strlen(msg) + 256); // 256 is just a placeholder, you may want to
                                 // calculate the exact size
  strncpy(formatted_string, msg, pos - msg);
  formatted_string[pos - msg] = '\0';

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
    break;
  }
  }

  strcat(formatted_string, pos + strlen(placeholder));

  return formatted_string;
}

str replace_escapes(str msg) {
  char *p = msg;
  while ((p = strstr(p, "\\n")) != NULL) {
    memmove(p, p + 1, strlen(p + 1) + 1);
    *p = '\n';
  }

  p = msg;
  while ((p = strstr(p, "\\t")) != NULL) {
    memmove(p, p + 1, strlen(p + 1) + 1);
    *p = '\t';
  }

  p = msg;
  while ((p = strstr(p, "\\\"")) != NULL) {
    memmove(p, p + 1, strlen(p + 1) + 1);
    *p = '\"';
  }

  return msg;
}

int transfer_ownership(Pair *table, str new_id, str old_id,
                       Data *original_data) {

  Pair *new_data = (Pair *)malloc(sizeof(Pair));
  new_data->d[0] = (Data){.tag = TSTR, .sval = strdup(new_id)};

  switch (original_data->tag) {
  case TINT: {
    new_data->d[1].tag = TINT;
    new_data->d[1].ival = original_data->ival;
    break;
  }
  case TSTR: {
    new_data->d[1].tag = TSTR;
    new_data->d[1].sval = original_data->sval;
    break;
  }
  default: {
    break;
  }
  }

  Pair *ptr = table;
  while (ptr->d[0].pval != 0) {
    if (strcmp(ptr->d[0].pval->d[0].sval, old_id) == 0) {
      break;
    }
    ptr = ptr->d[1].pval;
  }

  ptr->d[0].pval = new_data;

  return 0;
}
