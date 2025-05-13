from typing import List, Tuple

from parser import CppParser, SyntaxError
from lexer import CppLexer

class CppCompiler:
    """Main compiler class that orchestrates the compilation process"""
    
    def __init__(self):
        pass
    
    def compile(self, source_code: str) -> Tuple[bool, List[SyntaxError]]:
        """Compile the given source code and return success status and errors"""
        # Tokenize the source code
        lexer = CppLexer(source_code)
        tokens = lexer.tokenize()
        
        # Parse the tokens
        parser = CppParser(tokens)
        errors = parser.parse()
        
        return len(errors) == 0, errors
    
    def report_errors(self, errors: List[SyntaxError]) -> None:
        """Format and print the syntax errors"""
        if not errors:
            print("No syntax errors detected.")
            return
        
        # Group errors by line number
        errors_by_line = {}
        for error in errors:
            if error.line not in errors_by_line:
                errors_by_line[error.line] = []
            errors_by_line[error.line].append(error)
        
        # Report errors by line
        print("Syntax errors found:")
        for line_num in sorted(errors_by_line.keys()):
            print(f"Line {line_num}:")
            for error in errors_by_line[line_num]:
                print(f"  - {error.message}")
        
        print(f"Total errors: {len(errors)}")
