
# NOTATION CONVERTER CLI

A command-line tool to convert arithmetic expressions between **infix**, **prefix**, and **postfix** notations using binary expression trees.

---

## HOW TO BUILD

### Linux (Ubuntu)
Ensure you have GCC installed. Compile the program using:
```bash
gcc -o notation-converter converter.c
```

### Windows (CMD with MinGW)
Use the following command:
```cmd
gcc -o notation-converter.exe converter.c
```

This will create an executable named `notation-converter` (Linux) or `notation-converter.exe` (Windows).

---

## HOW TO RUN (Linux)

### Syntax
```bash
./notation-converter --from <input_format> --to <output_format> "expression"
```

- `<input_format>`  : `infix`, `prefix`, or `postfix`  
- `<output_format>` : `infix`, `prefix`, or `postfix`  
- `"expression"`    : The arithmetic expression (quotes are required if it includes spaces)

### Examples
```bash
./notation-converter --from infix --to postfix "a+b*c"
./notation-converter --from prefix --to infix "+ a * b c"
./notation-converter --from postfix --to prefix "a b c * +"
```

---

## HOW TO RUN (Windows)

### Syntax
```cmd
notation-converter --from <input_format> --to <output_format> "expression"
```

### Examples
```cmd
notation-converter --from infix --to postfix "a+b*c"
notation-converter --from prefix --to infix "+ a * b c"
notation-converter --from postfix --to prefix "a b c * +"
```

---

## AVAILABLE COMMANDS

- `--h` or `--help`  : Display short usage instructions  
- `--guide`          : Show detailed usage, rules, and examples  

---

## FEATURES

- Converts expressions between **infix**, **prefix**, and **postfix**
- Builds a **binary expression tree** for validation and conversion
- Supports operators: `+`, `-`, `*`, `/`
- Accepts both spaced and unspaced expressions

---

## EXPRESSION RULES

To ensure successful conversion, follow these rules:

- ✅ Only **single-digit numbers** (`0-9`) or **single-letter variables** (`a-z`, `A-Z`)
- ❌ **No parentheses** allowed
- ✅ Supported operators: `+`, `-`, `*`, `/`
- ✅ Spaces between characters are optional
- ✅ Wrap expressions with quotes if they contain spaces (e.g., `"a + b"`)
- ❌ Negative numbers, floating-point values, or unary operations are not supported
- ❌ No implicit multiplication (e.g., `2a` is invalid)

---

## SCOPE AND LIMITATIONS

### Scope

- Converts between infix, prefix, and postfix notations
- Intended for learning, academic, and basic CLI usage
- Uses a binary expression tree to ensure structural integrity

### Limitations

- 🚫 No parentheses or precedence override support
- 🚫 No support for:
  - Multi-digit numbers
  - Multi-character variable names
  - Negative or unary operations
- ✅ Only binary operators: `+`, `-`, `*`, `/`
- ✅ Input must be valid; malformed expressions result in an error

---

## COMMON ERRORS & FIXES

| **Error Message**                         | **Cause**                                                                 | **Fix**                                                                      |
|------------------------------------------|---------------------------------------------------------------------------|-------------------------------------------------------------------------------|
| `Unknown option`                         | Unrecognized command-line flag                                            | Use only valid options: `--from`, `--to`, `--help`, `--guide`                |
| `Incorrect number of arguments`          | Missing or extra arguments                                                | Example: `./notation-converter --from infix --to postfix "a+b"`             |
| `Missing or incorrect --from`            | `--from` flag is missing or misspelled                                   | Ensure `--from` is spelled correctly and appears first                       |
| `Missing or incorrect --to`              | `--to` flag is missing or misspelled                                     | Check that `--to` follows the `--from` flag                                  |
| `Invalid format for --from or --to`      | Notation type is invalid (e.g., `infx`)                                   | Only use: `infix`, `prefix`, or `postfix`                                   |
| `Failed to build expression tree`        | Invalid expression structure or operator/operand mismatch                 | Recheck expression; ensure it follows the rules above                        |
| `Expression cannot end with an operator` | Last token is an operator (e.g., `+`)                                     | Ensure the last token is a number or variable                                |
| `Invalid operator on stack`              | Unrecognized or malformed operator used                                   | Use only `+`, `-`, `*`, or `/`                                               |

---

## DESIGN OVERVIEW

- **Parsing**: Input expressions are tokenized and validated.
- **Tree Construction**: An internal binary tree represents the expression.
- **Traversal**: Tree is traversed in the target notation format.
- **Infix Parsing**: Uses the **Shunting Yard Algorithm** for infix to postfix conversion before tree building.

---

## LANGUAGE & DEPENDENCIES

- **Language**: C  
- **Compiler**: GCC (Linux) / MinGW (Windows)  
- **Dependencies**: None (standard C libraries only)

---

## FOR MORE HELP

Run the built-in guide:
```bash
./notation-converter --guide
```
```bash
notation-converter --guide
```

This shows:
- Format and usage rules
- Expression examples
- Troubleshooting tips
