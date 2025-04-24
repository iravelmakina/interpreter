# Arithmetic Expression Interpreter (C++)

This repository contains a simple yet powerful interpreter implemented in C++ that supports evaluating arithmetic expressions and calling basic mathematical functions using a declarative, functional-style syntax.

---

## Features

- **Arithmetic expression parsing**
  - Supports operators: `+`, `-`, `*`, `/`
  - Proper operator precedence and grouping
- **Built-in function support**
  - Includes: `max(a, b)`, `min(a, b)`, `abs(x)`, `pow(x, y)`
- **Nested expressions**
  - Combine arithmetic with function calls
- **Cross-language testing**
  - Use `test_script.py` to validate behavior via Python

---

## Example Usage

```plaintext
> 5 + 3 * 2
11

> max(5, 2)
5

> min(3, 4)
3

> max(min(3 * 2, 2), 2)
6
```

---

## Repository Structure

```
interpreter/
├── interpreter.cpp      # Main C++ interpreter logic
├── interpreter.exe      # Precompiled binary (Windows only)
├── test_script.py       # Test harness for expression validation
├── LICENSE
├── .gitignore
├── .gitattributes
└── README.md
```

---

## Getting Started

### Prerequisites

- Windows OS (if using `interpreter.exe`)
- Python 3.x (for testing)

### Run the Interpreter

If using the prebuilt binary:
```bash
./interpreter.exe
```

> Input expressions directly into the console. Press Enter to evaluate.

---

## Testing

Use the included Python script to automatically validate expression results:
```bash
python test_script.py
```

This script feeds a series of expressions to the interpreter and compares output with expected results.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

## Contributor

- [@iravelmakina](https://github.com/iravelmakina)
