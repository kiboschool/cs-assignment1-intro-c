import subprocess
import unittest
from gradescope_utils.autograder_utils.decorators import weight

executable_name = "assignment1"

compile_command = ["gcc", "assignment1.c", "-o", executable_name]

# Each test case is a tuple: (command-line arguments, expected output, weight)
test_cases = [
    ([f"./{executable_name}", "-x", "1a2b3"], "match\n", 1),
    ([f"./{executable_name}", "-x", "-v", "1a2b3"], "1-97-2-98-3\n", 1),
    ([f"./{executable_name}", "-y", "abc"], "nomatch\n", 1),
    ([f"./{executable_name}", "-y", "abb"], "match\n", 1),
    ([f"./{executable_name}", "-z", "1+2*3"], "match\n", 1),
    # Add more test cases as needed
]

# Compile the C program
def compile_program(executable_name):
    compile_command = ["gcc", "assignment1.c", "-o", executable_name]
    try:
        subprocess.check_call(compile_command)
        return True
    except subprocess.CalledProcessError:
        return False
    
# Function to create a test method
def create_test_method(args, expected, test_case_weight):
    @weight(test_case_weight)
    def test_method(self):
        if not self.compilation_success:
            self.fail("Compilation failed. Cannot run test cases.")

        try:
            output = subprocess.check_output(args, text=True)
            self.assertEqual(output, expected, f'Command: {" ".join(args)}')
        except subprocess.CalledProcessError as e:
            self.fail(f"Running the program failed: {e}")
    return test_method

class TestAssignment1(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.compilation_success = compile_program(executable_name)

# Dynamically create a test method for each test case
for i, (args, expected, test_case_weight) in enumerate(test_cases):
    test_method = create_test_method(args, expected, test_case_weight)
    test_method.__name__ = f'test_case_{i}'
    setattr(TestAssignment1, test_method.__name__, test_method)