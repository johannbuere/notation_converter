# Notation Converter (nota.c)

## 📌 Description
**`nota`** is a C program that converts arithmetic expressions between **infix**, **prefix**, and **postfix** notations. It uses **expression trees** to perform the conversion and display a **visual representation** of the tree. The program is designed with error handling, interactive mode, and suggestion features for user input.

---

## ⚙️ Features
- Supports **all 6** conversion directions:
  - Infix → Prefix, Postfix
  - Prefix → Infix, Postfix
  - Postfix → Infix, Prefix
- **Expression Tree** implementation
- **Traversal-based conversions**
- **ASCII tree visualization**
- **Command-line argument support**
- **Interactive mode** if no arguments are provided
- **Help and Guide** commands
- **Error handling** for:
  - Invalid characters/tokens
  - Mismatched parentheses
  - Incomplete expressions
  - Invalid notation types
  - Misspelled notation suggestions

---

## 🧪 Usage
### 🛠️ Compile
```bash
gcc -o nota notation.c
```

### ▶️ Run
```bash
./nota --from inf --to pos "( A + B ) * C"
```

### 📥 Arguments
```text
--from     Input notation type (inf, pre, pos)
--to       Output notation type (inf, pre, pos)
EXPR       Arithmetic expression (use quotes)
```

### 🧭 Example
```bash
./nota --from pre --to inf "+ A * B C"
```

---

## 🧑‍💻 Interactive Mode
If the program is run **without arguments**, it asks the user:
```bash
Enter --from [inf|pre|pos]:
Enter --to [inf|pre|pos]:
Enter expression in quotes:
```

---

## 📚 Commands
```bash
./nota --help     # Shows usage instructions
./nota --guide    # Shows detailed command guide
```

---

## 🌳 Visual Output
Example output for `--from inf --to pos "( A + B ) * C"`:
```
Converted (pos): A B + C *

Expression Tree (Visual):
    *
  +   C
A   B
```

---

## 📁 File Structure
```
nota.exe        # Executable file
notation.c      # Main program source
README.md       # This documentation
```

---

## ✅ Future Enhancements
- Expression evaluation (numeric)
- Variable assignment and parsing
- Exporting tree as Graphviz `.dot`

---

- Project for **Discrete Structures 2**

---



