#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef enum _Tag { TNIL, TINT, TSTR, TDUO, TERROR } Tag;
typedef enum _Tag { TERROR, TNIL, TINT, TSTR, TDUO } Tag;
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

char *substr(char *input, int i_begin, int i_end) {
  int cnt = 0;
  int size = (i_end - i_begin) + 2;
  char *str = (char *)malloc(size);

  memset(str, 0, size);

  for (int i = i_begin; i <= i_end; i++) {
    str[cnt] = input[i];
    cnt++;
  }

  return str;
}

char buf[80];

// constructor for TINT
Data mkint(int i) {
  Data d = {.tag = TINT, .ival = i};

  return d;
}

// constructor for TSTR
Data mkstr(str s) {
  Data d = {.tag = TSTR, .sval = s};

  return d;
}

// constructor for TDUO
Data cons(Data a, Data b) {
  Pair p = {.d = {a, b}};

  Data d = {.tag = TDUO, .pval = &p};

  return d;
}

// constructor for TNIL
const Data nil = {.tag = TNIL, .pval = NULL};

void get_result_str(Data d, str s) {
  switch (d.tag) {
  case TINT:
    sprintf(s, "(INT, %d)", d.ival);
    break;
  case TSTR:
    sprintf(s, "(STR, \'%s\')", d.sval);
    break;
  case TNIL:
    sprintf(s, "NIL");
    break;
  default:
    sprintf(s, "Error: unknown data type");
    break;
  }

  s[strlen(s)] = '\0';
}

void print_duo(Data _d) {
  Data d_first = _d.pval->d[0];
  Data d_second = _d.pval->d[1];

  char res_first[80];
  char res_second[80];

  memset(res_first, 0, 80);
  memset(res_second, 0, 80);

  get_result_str(d_first, res_first);
  get_result_str(d_second, res_second);

  printf("(%s . %s)\n", res_first, res_second);
}

Data type_check(str msg) {
  Data res;

  // INT
  if (isdigit(msg[0])) {
    int val = 0;
    int idx = 0;

    while (msg[idx] != '\0') {
      val = val * 10 + (msg[idx++] - '0');
    }

    res = mkint(val);
  }

  // STR
  else if ('\"' == msg[0]) {
    int idx = 1;
    int b_idx = 0;

    while (msg[idx] != '\"') {
      if (msg[idx] == '\\' && msg[idx + 1] == '\"') {
        buf[b_idx++] = '\"';
        idx += 2;
        continue;
      }
      buf[b_idx++] = msg[idx++];
    }
    buf[b_idx] = '\0';

    res = mkstr(buf);
  }

  // NIL
  else if ('n' == msg[0]) {
    if (msg[1] == 'i') {
      if (msg[2] == 'l') {
        res = nil;
      }
    }
  }

  // ERROR
  else {
    Data dummy;
    res = dummy;
  }

  return res;
}

int main() {
  const size_t SZ = 80;
  char input[SZ + 1];
  Data d;

  while (fgets(input, 80, stdin) != NULL) {
    input[strlen(input) - 1] = '\0';

    // DUO
    if ('(' == input[0]) {

      Data d_first;
      Data d_second;

      str w_first = strtok(input, ".");
      str w_second = strtok(NULL, ".");

      str buf_first = substr(w_first, 1, strlen(w_first) - 2);
      str buf_second = substr(w_second, 1, strlen(w_second) - 2);

      d_first = type_check(buf_first);
      d_second = type_check(buf_second);

      d = cons(d_first, d_second);
    }

    // Simple Data
    else if (input[0] != '(') {
      d = type_check(input);
    }

    // ERROR
    else {
      Data dummy = {.tag = TERROR, .pval = NULL};
      d = dummy;
    }

    // print out
    switch (d.tag) {
    case TINT:
      printf("(INT, %d)\n", d.ival);
      break;
    case TSTR:
      printf("(STR, \'%s\')\n", d.sval);
      break;
    case TNIL:
      printf("NIL\n");
      break;
    case TDUO:
      print_duo(d);
      break;
    default:
      fputs("Error: unknown data type\n", stderr);
      break;
    }
  }
}
