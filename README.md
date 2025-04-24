# Arithmetic Expression Interpreter (C++)

This repository contains a compact interpreter written in C++ that evaluates arithmetic expressions and supports functional-style built-in operations such as `min`, `max`, `abs`, and `pow`. The project also includes a Python-based test suite to validate interpreter behavior.

---

## Features

- Evaluate expressions with `+`, `-`, `*`, `/`
- Supports nested calls and parentheses
- Built-in functions: `min(x, y)`, `max(x, y)`, `abs(x)`, `pow(x, y)`
- Lightweight REPL-style interaction
- Includes a Python test script to validate output correctness
- Cross-paradigm learning: declarative, functional, and imperative styles

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

## Directory Structure

```
interpreter/
├── interpreter_implementation/     # C++ source and binary
│   ├── interpreter.cpp             # Main interpreter implementation
│   └── interpreter.exe             # Precompiled binary (Windows)
│
├── scripts/                        # Python-based testing
│   └── test_script.py              # Automated expression validator
│
├── .gitignore
├── .gitattributes
├── LICENSE
└── README.md
```

---

## Getting Started

### Requirements

- Windows OS (for using `interpreter.exe`)
- Python 3.x (for running `test_script.py`)

### Running the Interpreter

```bash
# Option 1: Run the prebuilt binary
./interpreter_implementation/interpreter.exe
```

You’ll see a prompt where you can enter expressions to evaluate.

---

## Testing the Interpreter

A simple Python script is provided to test various expressions against expected outputs.

```bash
python scripts/test_script.py
```

> The script automatically feeds expressions into `interpreter.exe` and compares actual vs expected results.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---

## Contributor

- [@iravelmakina](https://github.com/iravelmakina)
