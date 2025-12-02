# notation converter

a lightweight command-line utility that converts mathematical expressions between infix, prefix, and postfix notations using expression tree algorithms.

> [!NOTE]
> all input must be space-separated. this is a requirement for proper parsing.

## features

- **three-way conversion**: infix ↔ prefix ↔ postfix
- **expression tree implementation**: builds and traverses trees for accurate conversion
- **variable support**: handles alphanumeric operands (e.g., `x`, `y1`, `var`)
- **basic operators**: supports `+`, `-`, `*`, `/` with proper precedence
- **zero dependencies**: pure C99 with standard library only

## getting started

### building

compile with any C99-compatible compiler:

```bash
gcc -o nota notation.c
```

### usage

```bash
./nota --from <infix|prefix|postfix> --to <infix|prefix|postfix> "EXPRESSION"
```

### examples

```bash
./nota --from infix --to postfix "( x + y ) * z"

./nota --from prefix --to infix "+ x y"

./nota --from postfix --to prefix "a b + c *"
```

### help

```bash
./nota --help     
./nota --guide    
```

## how it works

the converter uses a three-step process:

1. **parse** the input expression into tokens
2. **build** an expression tree based on the input notation
3. **traverse** the tree to generate the target notation

each notation format uses appropriate data structures:
- **postfix**: stack-based construction
- **prefix**: recursive descent parsing
- **infix**: shunting-yard algorithm with operator precedence

## limitations

- no unary operators (e.g., `-x`, `+5`)
- no function calls (e.g., `sin(x)`, `sqrt(y)`)
- parentheses only supported in infix notation
- requires well-formed input (no error recovery)
