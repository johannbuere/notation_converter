*----------------------------------------------------------*
|                    NOTATION CONVERTER                    |
*----------------------------------------------------------*

A C program command-line tool that uses a EXPRESSION TREE to translate mathematical expressions between INFIX, PREFIX, and POSTFIX notations. The command-line tool supports arithmetic operators such as `+`, `-`, `*`, and `/`.

## HOW TO BUILD ##

To compile the programm, use a C compiler like `gcc`:

```cmd
gcc -o nota notation.c

This will generate an executable program named `nota`.


## HOW TO RUN ##

To run, use the following command line syntax:

```cmd
nota --from <infix|prefix|postfix> --to <infix|prefix|postfix> "EXPRESSION"


## EXAMPLES ##

```cmd
nota --from infix --to postfix "( x + y ) * z"
nota --from prefix --to infix "+ x y"
nota --from postfix --to prefix "a b + c *"

Confused? Not sure how to? You can also view usage and assistance guides:

```cmd
nota --help     # For basic usage
nota --guide    # For Detailed usage and instructions with examples


## DESGN CHOICES ## 

- Expression Tree: The conversion is done by building an expression tree from the input, then traversing it into the specified target notation by the user.
- Space-separated input: All tokens (operands, operators, parentheses) must be space-separated Ex. "a b + c".
- Stack-based Parsing  : Each notation type is parsed using appropriate stack logic.
- Supports Variables   : Operands like `x`, `y1`, `var` are allowed.

## LIMITATIONS ##

- No support for unary operators or functions (Ex., `-x`, `sin(x)`).
- Input must be **well-formed**; no implicit error recovery.

## LANGUAGE AND LIBRARIES USED ##

- Language: C language
- LIBRARIES: Standard C Library only (`<stdio.h>`, `<stdlib.h>`, `<string.h>`, etc.)

--------------------------------------------------------------------------------------------------------------------------

