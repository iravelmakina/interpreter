import subprocess


def run_program(input_data):
    process = subprocess.Popen(
        ['../interpreter_implementation/interpreter.exez'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()


def test_program():
    tests = [
        {
            "input": "2 + 3 * 4\n",
            "expected_output": "14"
        },
        {
            "input": "(2 +3)* 4\n",
            "expected_output": "20"
        },
        {
            "input": "10 / (2+3)\n",
            "expected_output": "2"
        },
        {
            "input": "2+ +3\n",
            "expected_output": "Error: Incorrect syntax"
        },
        {
            "input": "10/0\n",
            "expected_output": "Error: Division by zero"
        },
        {
            "input": "(2 + 3 * 4\n",
            "expected_output": "Error: Mismatched parentheses"
        },
        {
            "input": "\n",
            "expected_output": "Error: Empty input"
        },
        {
            "input": " \n",
            "expected_output": "Error: Invalid expression"
        },
        {
            "input": "2@ 3\n",
            "expected_output": "Error: Unknown character"
        },
        {
            "input": "-5 +3\n",
            "expected_output": "-2"
        },
        {
            "input": "-5+(-3)\n",
            "expected_output": "-8"
        },
        {
            "input": "-5+-3\n",
            "expected_output": "-8"
        },
        {
            "input": "pow(2, 3)\n",
            "expected_output": "8"
        },
        {
            "input": "abs(-5)\n",
            "expected_output": "5"
        },
        {
            "input": "max(5, 3)\n",
            "expected_output": "5"
        },
        {
            "input": "min(5, 3)\n",
            "expected_output": "3"
        },
        {
            "input": "pow(-2, 3)\n",
            "expected_output": "-8"
        },
        {
            "input": "pow(2,-3)\n",
            "expected_output": "0.125"
        },
        {
            "input": "max(-5, abs(-3))\n",
            "expected_output": "3"
        },
        {
            "input": "min(-5, abs(-3))\n",
            "expected_output": "-5"
        },
        {
            "input": "max(2 + 3, pow(2, 3))\n",
            "expected_output": "8"
        },
        {
            "input": "min(abs(-10), pow(2, 2) + 1)\n",
            "expected_output": "5"
        },
        {
            "input": "max(pow(2, 3), min(10, 5))\n",
            "expected_output": "8"
        },
        {
            "input": "abs(pow(min(3 * max(-10, -2), 2), 3))\n",
            "expected_output": "216"
        },
        {
            "input": "5 +\n",
            "expected_output": "Error: Incorrect syntax"
        },
        {
            "input": "max(2, 3\n",
            "expected_output": "Error: Mismatched parentheses"
        },
        {
            "input": "unknownFunc(2, 3)\n",
            "expected_output": "Error: Unknown function"
        },
        {
            "input": "pow(2, 3, 4)\n",
            "expected_output": "Error: Invalid expression"
        },
        {
            "input": "2 + abs\n",
            "expected_output": "Error: Incorrect syntax"
        },
        {
            "input": "pow(2,)\n",
            "expected_output": "Error: Incorrect syntax"
        },
        {
            "input": "abs\n",
            "expected_output": "Error: Incorrect syntax"
        },
    ]

    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_program(input_data)

        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")


if __name__ == "__main__":
    test_program()
