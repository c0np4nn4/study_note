typedef enum { TNIL, TINT, TSTR, TDUO } Tag;
typedef char *str;
typedef struct _Pair *duo;
typedef struct _Data {
  Tag tag;
  union {
    signed int ival;
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
str replace_format_specifier(str, Data *);
str replace_escapes(str);
int transfer_ownership(Pair *table, str new_id, str old_id,
                       Data *original_data);
