import sys
import os

from lexer import CppLexer
from parser import CppParser
from codegen import AssemblyGenerator

class CppCompiler:
    
    def report_errors(self, errors):
        print(f"Found {len(errors)} syntax error(s):")
        for error in errors:
            print(f"  - {error}")


def run_test_case(code: str, test_case_name: str = "Test Case") -> None:
    print(f"\n===== {test_case_name} =====")
    print("Source code:")
    for i, line in enumerate(code.split('\n'), 1):
        print(f"{i:2d}: {line}")


def main():
    if len(sys.argv) > 1:
        try:
            filename = sys.argv[1]
            with open(filename, 'r') as file:
                source_code = file.read()

            lexer = CppLexer(source_code)
            tokens = lexer.tokenize()
            parser = CppParser(tokens)
            ast, errors = parser.parse()

            if not errors:
                print("Compilation successful! No syntax errors detected.")
                generator = AssemblyGenerator()
                asm_code = generator.generate(ast)
                print("\nGenerated Assembly:\n")
                print("\n".join(asm_code))

                # Save to asm
                asm_filename = os.path.splitext(filename)[0] + ".s"
                with open(asm_filename, "w") as out_file:
                    for line in asm_code:
                        out_file.write(line + "\n")
                print(f"\nAssembly saved to {asm_filename}")
            else:
                compiler = CppCompiler()
                compiler.report_errors(errors)

        except FileNotFoundError:
            print(f"Error: File '{sys.argv[1]}' not found.")
        except Exception as e:
            print(f"Error: {str(e)}")
    else:
        test_case1 = """
int main() {
    int x = 10;
    int y = 20;
    int sum = x + y;
    return 0;
}
"""

        test_case2 = """
int main() {
    int x = 10
    int y = 20;
    if (x > y {
        return x;
    } else {
        return y;
    }
}
"""

        run_test_case(test_case1, "Test Case 1 - Valid Code")
        run_test_case(test_case2, "Test Case 2 - Code with Errors")


if __name__ == "__main__":
    main()
    
