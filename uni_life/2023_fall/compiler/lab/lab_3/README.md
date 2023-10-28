# LAB3
- Parsing `Input String` to get *Tagged Data*

## Data Types
| Tag | Data | Description |
|----|----|----|
| *TINT* | `int` | Signed integer |
| *TSTR* | `char *` | String |
| *TSYM* | `char *` | Identifier |

## Example Code
- Code below shows how to use `Tag` to parse the data.

```c
#include <stddef.h>
#include <stdio.h>

typedef enum _Tag { TINT, TSTR } Tag;
typedef char *str;
typedef struct _Data {
  Tag tag;
  union {
    int ival;
    str sval;
  };
} Data;

int main() {
  Data d[] = {
      {TSTR, .sval = "Hello"}, //
      {TINT, .ival = 123}      //
  };

  size_t sz = sizeof d / sizeof *d;

  // printf("numerator  : %lu\n", sizeof d);
  // printf("denominator: %lu\n", sizeof *d);

  for (int i = 0; i < sz; i++) {
    switch (d[i].tag) {
    case TINT:
      printf("(INT, %d)\n", d[i].ival);
      break;
    case TSTR:
      printf("(STR, '%s')\n", d[i].sval);
      break;
    default:
      fputs("Error: unknown data type", stderr);
      break;
    }
  }

  return 0;
}
```
