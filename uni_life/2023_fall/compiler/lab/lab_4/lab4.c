#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _Tag {
  TNIL,
  TINT,
  TSTR,
  TDUO,
} Tag;
typedef char *str;
typedef struct _Pair *duo;
typedef struct _Data {
  Tag tag;
  union {
    int ival;
    str sval;
    duo pval;
  };
} Data;

typedef struct _Pair {
  Data d[2];
} Pair;

char input_string[81];
Data result;
char *cursor;
Pair p;

void get_string(void);
void lex_string(void);

// Constructors
Data mkint(int);
Data mkstr(str);
Data cons(Data, Data);
const Data nil = {.tag = TNIL, .pval = NULL};

int main() {
  while (1) {
    get_string();
    lex_string();

    switch (result.tag) {
    case TNIL:
      printf("NIL\n");
      break;
    case TINT:
      printf("(INT, %d)\n", result.ival);
      break;
    case TSTR:
      printf("(STR, %s)\n", result.sval);
      break;
    case TDUO:
      printf("(");
      switch (result.pval->d[0].tag) {
      case TNIL:
        printf("NIL");
        break;
      case TINT:
        printf("(INT, %d)", result.pval->d[0].ival);
        break;
      case TSTR:
        printf("(STR, %s)", result.pval->d[0].sval);
        break;
      case TDUO:
        break;
      }
      printf(" . ");
      switch (result.pval->d[1].tag) {
      case TNIL:
        printf("NIL");
        break;
      case TINT:
        printf("(INT, %d)", result.pval->d[1].ival);
        break;
      case TSTR:
        printf("(STR, %s)", result.pval->d[1].sval);
        break;
      case TDUO:
        break;
      }
      printf(")\n");
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

Data mkint(int i) {
  Data res = {.tag = TINT, .ival = i};
  return res;
}

Data mkstr(str s) {
  Data res = {.tag = TSTR, .sval = strdup(s)};
  return res;
}

void lex_string() {
  cursor = input_string;

  while (*cursor != '\0') {
    int tmp_ival = 0;
    char i_sval[81];
    memset(i_sval, 0, 81);

    // 1. TNIL
    if (*cursor == 'n') {
      if (*(cursor + 1) == 'i') {
        if (*(cursor + 2) == 'l') {
          result = nil;
          break;
        }
      }
    }

    // 2. TINT
    if (isdigit(*cursor)) {
      tmp_ival = tmp_ival * 10 + (*cursor - '0');
      cursor++;

      while (isdigit(*cursor)) {
        tmp_ival = tmp_ival * 10 + (*cursor - '0');
        cursor++;
      }

      result = mkint(tmp_ival);

      break;
    }

    // 3. TSTR
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

      result = mkstr(i_sval);

      break;
    }

    // 4. TDUO
    else if (*cursor == '(') {
      // Data d1, d2;
      cursor++;

      while (!isspace(*cursor)) { // d1
        // 1. TNIL
        if (*cursor == 'n') {
          if (*(cursor + 1) == 'i') {
            if (*(cursor + 2) == 'l') {
              p.d[0] = nil;
              cursor += 3;
              break;
            }
          }
        }

        // 2. TINT
        if (isdigit(*cursor)) {
          tmp_ival = tmp_ival * 10 + (*cursor - '0');
          cursor++;

          while (isdigit(*cursor)) {
            tmp_ival = tmp_ival * 10 + (*cursor - '0');
            cursor++;
          }
          p.d[0] = mkint(tmp_ival);

          break;
        }

        // 3. TSTR
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

          p.d[0] = mkstr(i_sval);

          break;
        }
      }

      cursor += 3;
      tmp_ival = 0;
      memset(i_sval, 0, 81);

      while (!isspace(*cursor)) { // d2
        // 1. TNIL
        if (*cursor == 'n') {
          if (*(cursor + 1) == 'i') {
            if (*(cursor + 2) == 'l') {
              p.d[1] = nil;
              cursor += 3;
              break;
            }
          }
        }

        // 2. TINT
        if (isdigit(*cursor)) {
          tmp_ival = tmp_ival * 10 + (*cursor - '0');
          cursor++;

          while (isdigit(*cursor)) {
            tmp_ival = tmp_ival * 10 + (*cursor - '0');
            cursor++;
          }

          p.d[1] = mkint(tmp_ival);

          break;
        }

        // 3. TSTR
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

          p.d[1] = mkstr(i_sval);

          break;
        }
      }

      result.tag = TDUO;
      result.pval = &p;

      break;
    }
  }
}
