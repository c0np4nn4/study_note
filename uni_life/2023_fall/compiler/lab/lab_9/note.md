# Node

```c
typedef struct Node {
    enum Tag {TINT, TSTR, TSYM, TUOP, TBOP, ...} tag;
    union {
        int ival;
        char *sval;
    };
    struct Node *son, *bro;
} Node;
```

- Syntax-Directed Def, Syntax-Directed Trans, Syntax-Directed Trans Scheme.

---

# After constructing Tree
- Code 생성 (`compiler`)
- Pgm 실행 (`interpreter`)
- ID
    - Symbol Table 필요
    - 앞서 다뤘던 'Pair'를 이용할 수 있음

---

# Env. Helper Function

t = mkEnv();
T/F = entry(t, "a", 1);
d = value(t, "a");

---

# Grammar

Program -> {D}*E
D -> ID "=" E
E -> E '+' T | T
