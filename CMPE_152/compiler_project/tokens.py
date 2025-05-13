from enum import Enum, auto

# Token types
class TokenType(Enum):
    KEYWORD = auto()
    IDENTIFIER = auto()
    OPERATOR = auto()
    LITERAL = auto()
    SEPARATOR = auto()
    PREPROCESSOR = auto()
    COMMENT = auto()
    WHITESPACE = auto()
    EOF = auto()
    UNKNOWN = auto()

class Token:
    """Represents a token in the C++ source code"""
    def __init__(self, token_type: TokenType, value: str, line: int, column: int):
        self.token_type = token_type
        self.value = value
        self.line = line
        self.column = column
    
    def __str__(self):
        return f"Token({self.token_type}, '{self.value}', line={self.line}, col={self.column})"
    
