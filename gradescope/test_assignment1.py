import subprocess
import unittest
from gradescope_utils.autograder_utils.decorators import weight

executable_name = "assignment1"

compile_command = ["gcc", "assignment1.c", "-o", executable_name, "-lm"]

# Each test case is a tuple: (command-line arguments, expected output, weight)
test_cases = [
    # -x flag test cases
    (["./assignment1", "-x", "1a2b3"], "match\n", 2),
    (["./assignment1", "-x", "a1b2c"], "nomatch\n", 2),
    (["./assignment1", "-x", "123abc"], "nomatch\n", 3),
    (["./assignment1", "-x", "1a2B3"], "match\n", 3),
    (["./assignment1", "-x", "9s3j8l0p1m2n3b4v5c6h7G8"], "match\n", 3),
    (["./assignment1", "-x", "1"], "match\n", 2),
    (["./assignment1", "-x", "-v", "1a2b3"], "1-97-2-98-3\n", 1),
    (["./assignment1", "-x", "-v", "a1b2c"], "nomatch\n", 1),
    (["./assignment1", "-x", "-v", "123abc"], "nomatch\n", 1),
    (["./assignment1", "-x", "-v", "1a2B3"], "1-97-2-66-3\n", 1),
    (["./assignment1", "-x", "-v", "9s3j8l0p1m2n3b4v5c6h7G8"], "9-115-3-106-8-108-0-112-1-109-2-110-3-98-4-118-5-99-6-104-7-71-8\n", 1),
    
    # -y flag test cases
    (["./assignment1", "-y", "abc"], "nomatch\n", 2),
    (["./assignment1", "-y", "abd"], "nomatch\n", 2),
    (["./assignment1", "-y", "a"], "match\n", 3),
    (["./assignment1", "-y", "asdfkasdfasdavsd"], "nomatch\n", 3),
    (["./assignment1", "-y", "abb"], "match\n", 3),
    (["./assignment1", "-y", "Ab"], "match\n", 2),
    (["./assignment1", "-y", "-v", "abb"], "61-62-62\n", 1),
    (["./assignment1", "-y", "-v", "abd"], "nomatch\n", 1),
    (["./assignment1", "-y", "-v", "a"], "61\n", 1),
    (["./assignment1", "-y", "-v", "asdfkasdfasdavsd"], "nomatch\n", 1),
    
    # -z flag test cases
    (["./assignment1", "-z", "1+2*3"], "match\n", 3),
    (["./assignment1", "-z", "12/3-4"], "match\n", 3),
    (["./assignment1", "-z", "1++2"], "nomatch\n", 2),
    (["./assignment1", "-z", "1+3+4-"], "nomatch\n", 2),
    (["./assignment1", "-z", "1+2*"], "nomatch\n", 2),
    (["./assignment1", "-z", "12*3/4+5"], "match\n", 3),
    (["./assignment1", "-z", "-v", "1+2*3"], "1010\n", .25),
    (["./assignment1", "-z", "-v", "12/3-4"], "0101\n", .25),
    (["./assignment1", "-z", "-v", "1++2"], "nomatch\n", .25),
    (["./assignment1", "-z", "-v", "1-4+89-23*2342341-2341234/734234*23-1"], "1421\n", .25),
]


# Compile the C program
def compile_program(executable_name):
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