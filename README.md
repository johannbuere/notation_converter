# Notation Converter

A command-line utility written in C that converts mathematical expressions between **infix**, **prefix**, and **postfix** notations using an **expression tree**. It supports alphanumeric operands and basic arithmetic operators: `+`, `-`, `*`, `/`.

## 🔧 How to Build

To compile the project, use a C compiler like `gcc`:

```bash
gcc -o nota notation_converter.c
```

This will generate an executable named `nota`.

## ▶️ How to Run

Use the following syntax:

```bash
./nota --from <infix|prefix|postfix> --to <infix|prefix|postfix> "EXPRESSION"
```

### ✅ Examples

```bash
./nota --from infix --to postfix "( x + y ) * z"
./nota --from prefix --to infix "+ x y"
./nota --from postfix --to prefix "a b + c *"
```

You can also view help and usage guides:

```bash
./nota --help     # Basic usage
./nota --guide    # Detailed usage with examples
```

## 🧠 Design Choices

- **Expression Tree**: The conversion is done by building an expression tree from the input, then traversing it into the target notation.
- **Space-separated input**: All tokens (operands, operators, parentheses) must be space-separated.
- **Stack-based Parsing**: Each notation type is parsed using appropriate stack logic.
- **Supports Variables**: Operands like `x`, `y1`, `var` are allowed.

## ⚠️ Limitations

- No support for unary operators or functions (e.g., `-x`, `sin(x)`).
- Parentheses are only handled in **infix** expressions.
- Input must be **well-formed**; no implicit error recovery.

## 💬 Language and Dependencies

- **Language**: C (Standard C99)
- **Dependencies**: Standard C Library only (`<stdio.h>`, `<stdlib.h>`, `<string.h>`, etc.)

---
