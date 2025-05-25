
# NOTATION CONVERTER CLI

A command-line tool to convert arithmetic expressions between **infix**, **prefix**, and **postfix** notations using binary expression trees.

---

## HOW TO BUILD

### Linux (Ubuntu)
Ensure you have GCC installed. Compile the program using:
```bash
gcc -o notation-converter main.c
```

### Windows (CMD with MinGW)
Use the following command:
```cmd
gcc -o notation-converter.exe main.c
```

This will create an executable named `notation-converter` (Linux) or `notation-converter.exe` (Windows).

---

## HOW TO RUN (For LINUX)

### Syntax
```bash
./notation-converter --from <input_format> --to <output_format> "expression"
```

- `<input_format>`  : infix, prefix, or postfix  
- `<output_format>` : infix, prefix, or postfix  
- `"expression"`    : The arithmetic expression in quotes (if it contains spaces)

### Examples
```bash
./notation-converter --from infix --to postfix "a+b*c"
./notation-converter --from prefix --to infix "+ a * b c"
./notation-converter --from postfix --to prefix "a b c * +"
```

---
## HOW TO RUN (For WINDOWS)

### Syntax
```cmd
notation-converter --from <input_format> --to <output_format> "expression"
```

- `<input_format>`  : infix, prefix, or postfix  
- `<output_format>` : infix, prefix, or postfix  
- `"expression"`    : The arithmetic expression in quotes (if it contains spaces)

### Examples
```cmd
notation-converter --from infix --to postfix "a+b*c"
notation-converter --from prefix --to infix "+ a * b c"
notation-converter --from postfix --to prefix "a b c * +"
```

---
## AVAILABLE COMMANDS

- `--h` or `--help`    : Display short usage instructions  
- `--guide`           : Show detailed usage, rules, and examples  

---

## FEATURES

- Converts expressions between infix, prefix, and postfix
- Uses binary expression tree for structure and conversion
- Supports operators: `+`, `-`, `*`, `/`
- Allows spacing or no spacing in expressions

---

## LIMITATIONS

- No parentheses allowed in the expression
- Only single-digit numbers and single-letter variables supported
- Does not support negative numbers or unary operators

---

## DESIGN OVERVIEW

- **Parsing**: Expressions are tokenized and parsed.
- **Tree Construction**: An expression tree is built from the input.
- **Traversal**: Tree is traversed in the desired output format.
- **Infix Parsing**: Uses the Shunting Yard Algorithm to convert to postfix before building.

---

## LANGUAGE & DEPENDENCIES

- **Language**: C  
- **Compiler**: GCC (Linux) / MinGW (Windows)  
- **Dependencies**: None (standard libraries only)

---

## OPTIONAL: UNIT TESTING

You may add a `tests.c` file for:
- Tree structure validation
- Conversion correctness
- Error handling (e.g., invalid format or operator)

Test cases could include:
- `a+b*c` → `a b c * +`
- `+ a b` → `a b +`
- `a b + c *` → `* + a b c`

---

## OPTIONAL: BINARIES

You may include precompiled binaries for convenience:
- `notation-converter` (Linux)
- `notation-converter.exe` (Windows)

---

## FOR MORE HELP

Run the following for guidance:
```bash
./notation-converter --guide
```

This provides:
- Format rules
- Supported examples
- Common mistakes to avoid
