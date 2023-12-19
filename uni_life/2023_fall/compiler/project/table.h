typedef enum { TNIL, TINT, TSTR, TDUO } Tag;
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

Pair *mkEnv();
int entry(Pair *, str, Data);
Data *value(Pair *, str);
char *replace_format_specifier(str, Data *);
char *replace_escapes(str);
