import re
from typing import List

from tokens import TokenType, Token

class CppLexer:
    """Converts C++ source code into a sequence of tokens"""
    
    # C++ keywords
    KEYWORDS = {
        'alignas', 'alignof', 'and', 'and_eq', 'asm', 'auto', 'bitand', 'bitor',
        'bool', 'break', 'case', 'catch', 'char', 'char8_t', 'char16_t', 'char32_t',
        'class', 'compl', 'concept', 'const', 'consteval', 'constexpr', 'constinit',
        'const_cast', 'continue', 'co_await', 'co_return', 'co_yield', 'decltype',
        'default', 'delete', 'do', 'double', 'dynamic_cast', 'else', 'enum',
        'explicit', 'export', 'extern', 'false', 'float', 'for', 'friend', 'goto',
        'if', 'inline', 'int', 'long', 'mutable', 'namespace', 'new', 'noexcept',
        'not', 'not_eq', 'nullptr', 'operator', 'or', 'or_eq', 'private', 'protected',
        'public', 'register', 'reinterpret_cast', 'requires', 'return', 'short',
        'signed', 'sizeof', 'static', 'static_assert', 'static_cast', 'struct',
        'switch', 'template', 'this', 'thread_local', 'throw', 'true', 'try',
        'typedef', 'typeid', 'typename', 'union', 'unsigned', 'using', 'virtual',
        'void', 'volatile', 'wchar_t', 'while', 'xor', 'xor_eq'
    }
    
    # Token patterns
    TOKEN_PATTERNS = [
        # Preprocessor directives
        (r'#\w+', TokenType.PREPROCESSOR),
        # Comments
        (r'//.*', TokenType.COMMENT),
        (r'/\*[\s\S]*?\*/', TokenType.COMMENT),
        # String literals
        (r'"(?:\\.|[^"\\])*"', TokenType.LITERAL),
        (r"'(?:\\.|[^'\\])*'", TokenType.LITERAL),
        # Number literals
        (r'\d+\.\d+[fFlL]?|\d+[fFlL]?', TokenType.LITERAL),
        (r'0[xX][0-9a-fA-F]+|\d+', TokenType.LITERAL),
        # Identifiers
        (r'[a-zA-Z_]\w*', None),
        # Operators
        (r'[+\-*/%=&|^~!<>?:]+', TokenType.OPERATOR),
        # Separators
        (r'[(){}\[\];,.]', TokenType.SEPARATOR),
        # Whitespace
        (r'\s+', TokenType.WHITESPACE),
    ]
    
    def __init__(self, source_code: str):
        self.source_code = source_code
        self.position = 0
        self.line = 1
        self.column = 1
        self.tokens = []
        
    def tokenize(self) -> List[Token]:
        """Process the source code and return a list of tokens"""
        lines = self.source_code.split('\n')
        
        for line_num, line in enumerate(lines, 1):
            column = 1
            remaining_line = line
            
            while remaining_line:
                match_found = False
                
                for pattern, token_type in self.TOKEN_PATTERNS:
                    regex = re.compile(f'^({pattern})')
                    match = regex.search(remaining_line)
                    
                    if match:
                        value = match.group(0)
                        
                        # Skip whitespace and comments
                        if token_type != TokenType.WHITESPACE and token_type != TokenType.COMMENT:
                            # Check if it's a keyword or identifier
                            if token_type is None:
                                if value in self.KEYWORDS:
                                    token_type = TokenType.KEYWORD
                                else:
                                    token_type = TokenType.IDENTIFIER
                            
                            self.tokens.append(Token(token_type, value, line_num, column))
                        
                        # Update position
                        value_len = len(value)
                        remaining_line = remaining_line[value_len:]
                        column += value_len
                        match_found = True
                        break
                
                if not match_found:
                    # Handle unrecognized token
                    self.tokens.append(Token(TokenType.UNKNOWN, remaining_line[0], line_num, column))
                    remaining_line = remaining_line[1:]
                    column += 1
        
        self.tokens.append(Token(TokenType.EOF, '', len(lines) + 1, 1))
        return self.tokens