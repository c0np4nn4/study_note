#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _Tag { TINT, TSTR, TSYM } Tag;
typedef char *str;
typedef struct _Data {
  Tag tag;
  union {
    int ival;
    str sval;
  };
} Data;

char input_string[81];
Data d[81];
int d_idx = 0;

void get_string(void);
void parse_string(void);

int main() {
  get_string();
  parse_string();

  for (int i = 0; i < d_idx; i++) {
    switch (d[i].tag) {
    case TINT:
      printf("(INT, %d)\n", d[i].ival);
      break;
    case TSTR:
      printf("(STR, '%s')\n", d[i].sval);
      break;
    case TSYM:
      printf("(SYM, %s)\n", d[i].sval);
      break;
    default:
      fputs("Error: unknown data type", stderr);
      break;
    }
  }

  for (int i = 0; i < d_idx; i++) {
    if (d[i].tag == TSTR || d[i].tag == TSYM) {
      free(d[i].sval);
    }
  }

  return 0;
}

void get_string() {
  if (fgets(input_string, sizeof(input_string), stdin) != NULL) {
    size_t length = strlen(input_string);
    if (length > 0 && input_string[length - 1] == '\n') {
      input_string[length - 1] = '\0';
    }
  }
}

void parse_string() {
  char *cursor = input_string;

  while (*cursor != '\0') {
    if (isspace(*cursor)) {
      cursor++;
      continue;
    }

    int tmp_ival = 0;
    char i_sval[81];
    memset(i_sval, 0, 81);

    // 1. TINT
    if (isdigit(*cursor)) {
      tmp_ival = tmp_ival * 10 + (*cursor - '0');
      cursor++;

      while (isdigit(*cursor)) {
        tmp_ival = tmp_ival * 10 + (*cursor - '0');
        cursor++;
      }

      d[d_idx].tag = TINT;
      d[d_idx].ival = tmp_ival;
      d_idx++;
      continue;
    }

    // 2. TSTR
    else if (*cursor == '\"') {
      int ts_idx = 0;
      cursor++;

      while (*cursor != '\"') {
        if (*cursor == '\\' && *(cursor + 1) == '\"') {
          i_sval[ts_idx++] = '\"';

          cursor += 2;
        } else {
          i_sval[ts_idx++] = *cursor;

          cursor++;
        }
      }

      i_sval[ts_idx] = '\0';
      cursor++;

      d[d_idx].tag = TSTR;
      d[d_idx].sval = strdup(i_sval);
      d_idx++;
      continue;
    }

    // 3. TSYM
    else {
      int ts_idx = 0;

      while (*cursor != '\0') {
        if (*cursor == '\"') {
          break;
        }

        else if (isspace(*cursor)) {
          cursor++;
          break;
        }

        i_sval[ts_idx++] = *cursor;
        cursor++;
      }

      d[d_idx].tag = TSYM;
      d[d_idx].sval = strdup(i_sval);
      d_idx++;
      continue;
    }
  }
}
