# Koch Interpreter
```py
from turtle import Turtle, exitonclick
import sys

# ======[Engine]========
def interpret(pgm):
    t = Turtle()
    for instr in pgm:
        if instr == 'F':
            t.forward(10)
        elif instr == 'L':
            t.left(60)
        elif instr == 'R':
            t.right(120)
        else:
            # print('Syntax error near "{}"'.format(instr))
            print(f'Syntax error near "{instr}"')
    t.hideturtle()
    exitonclick()

# ======[Driver]========
if len(sys.argv) < 2:
    # print("Usage: {} {}".format(sys.argv[0], ))
    print(f"Usage: {sys.argv[0]} Koch_File")
else:
    infile = open(sys.argv[1], 'r')
    pgm = infile.readline().strip()
    interpret(pgm)
    infile.close()


```

---

# Koch Compiler
```py
from turtle import Turtle, exitonclick
import sys

# ======[Interpreter Engine]========
def interpret(pgm):
    t = Turtle()
    for instr in pgm:
        if instr == 'F':
            t.forward(10)
        elif instr == 'L':
            t.left(60)
        elif instr == 'R':
            t.right(120)
        else:
            # print('Syntax error near "{}"'.format(instr))
            print(f'Syntax error near "{instr}"')
    t.hideturtle()
    exitonclick()

# ======[Translate Engine]========
def translate(ofile, pgm):
    cmd = ''
    for instr in pgm:
        if instr == 'F':
            cmd += 't.forward(10)\n'
        elif instr == 'L':
            cmd += 't.left(60)\n'
        elif instr == 'R':
            cmd += 't.right(120)\n'
        else:
            print(f'Syntax error near "{instr}"')
    # exitonclick()
    ofile.write(f"  {cmd}")


# ======[Driver]========
if len(sys.argv) < 2:
    # print("Usage: {} {}".format(sys.argv[0], ))
    print(f"Usage: {sys.argv[0]} Koch_File")
else:
    infile = open(sys.argv[1], 'r')
    pgm = infile.readline().strip()
    interpret(pgm)
    infile.close()


if __name__ == "__main__":
    prologue = '''
    from turtle import Turtle, exitonclick
    def main():
        t = Turtle
    '''

    epilogue = '''
        t.hideturtle()
        exitonclick()
    main()
    '''

    import sys

    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} Koch_File")
    else:
        ifile = open(sys.argv[1], 'r')
        ofile = open('a.py', 'w')

        pgm = ifile.readline().strip()
        ofile.write(prologue)

        translate(ofile, pgm)

        ofile.write(epilogue)
        ofile.close()
        ifile.close()

```

---

# note
# An Ultra Simple Interpreter and Compiler

- Fractal 이야기 (Koch 눈송이)

인터프리터를 만들고 컴파일러를 만드는게 간단하다고 함

---

- Koch Curve
    - [wiki](https://en.wikipedia.org/wiki/Koch_snowflake)
- Sierpinski Carpet

- 코드를 해석할 때,  if-else 뿐만 아니라 parallel 도 활용할 수 있음
