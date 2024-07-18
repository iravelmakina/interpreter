# Interpreter Implementation: Elements of Declarative and Functional Styles

## Purpose of Work
The purpose of this work is to gain experience in programming using multi-paradigm programming and preparing a declarative language that supports a basic functional style.

## Task
Implement a simple interpreter in C++ that can evaluate arithmetic expressions, define functions, and call functions. The interpreter should support the following features:

1. Basic arithmetic operations: `+`, `-`, `*`, `/`
2. Function definitions with two parameters (`pow`, `abs`, `max`, `min`)
3. Expression combinations

### Example Usage:
```plaintext
> 5 + 3 * 2
> 11

> max(5, 2)
> 5

> min(3, 4)
> 3

> max(min(3 * 2, 2), 2)
> 6


Here is the updated main README for your repository in markdown format with the specified sections:

markdown
Copy code
# Interpreter Implementation: Elements of Declarative and Functional Styles

## Purpose of Work
The purpose of this work is to gain experience in programming using multi-paradigm programming and preparing a declarative language that supports a basic functional style.

## Task
Implement a simple interpreter in C++ that can evaluate arithmetic expressions, define functions, and call functions. The interpreter should support the following features:

1. Basic arithmetic operations: `+`, `-`, `*`, `/`
2. Function definitions with two parameters (`pow`, `abs`, `max`, `min`)
3. Expression combinations
4. Function calls (combination of the above expressions with a dedicated name)
5. Variable saving for reusing them (e.g., `var a = pow(2, 4)`)

### Example Usage:
```plaintext
> 5 + 3 * 2
> 11

> max(5, 2)
> 5

> min(3, 4)
> 3

> max(min(3 * 2, 2), 2)
> 6

> var a = max(min(3 * 2, 2), 2)
> a + 3
> 5

> def myfunc(a, b) { min(a, b) + max(a, b) }
> myfunc(3, 4)
> 7

### How to Use
1. Clone the repository.
2. Ensure interpreter.exe is in the working directory.
3. Run the provided test script (test_script.py) with python test_script.py.
4. Verify the output matches the expected results for all test cases.

### Testing
To test the implemented interpreter, a Python script is provided to execute the program with different input combinations and verify the correctness of the results.

## Contributors
-@iravelmakina
