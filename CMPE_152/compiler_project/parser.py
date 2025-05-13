from typing import List, Tuple, Optional
from tokens import TokenType, Token
from ast_nodes import *

class SyntaxError:
    def __init__(self, message: str, line: int, column: int):
        self.message = message
        self.line = line
        self.column = column

    def __str__(self):
        return f"Syntax Error at line {self.line}, column {self.column}: {self.message}"

class CppParser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.current_index = 0
        self.errors = []

    def parse(self) -> Tuple[ProgramNode, List[SyntaxError]]:
        program_node = ProgramNode()
        while self.current_token().token_type != TokenType.EOF:
            func = self.parse_function()
            if func:
                program_node.functions[func.name] = func
        return program_node, self.errors

    def parse_function(self) -> Optional[FunctionNode]:
        # Parse return type
        if self.current_token().token_type != TokenType.KEYWORD:
            self.error("Expected return type")
            return None
        return_type = self.current_token().value
        self.next_token()

        # Function name
        if not self.expect(TokenType.IDENTIFIER, "Expected function name"):
            return None
        func_name = self.previous_token().value

        # Parameters
        self.expect_value(TokenType.SEPARATOR, '(', "Expected '(' after function name")
        parameters = self.parse_parameters()
        self.expect_value(TokenType.SEPARATOR, ')', "Expected ')' after parameter list")

        # Function body
        body = self.parse_block()
        func_node = FunctionNode(func_name, return_type, parameters)
        func_node.set_body(body)
        return func_node

    def parse_parameters(self) -> List[ParameterNode]:
        params = []
        while self.current_token().token_type == TokenType.KEYWORD:
            param_type = self.current_token().value
            self.next_token()
            if self.current_token().token_type == TokenType.IDENTIFIER:
                name = self.current_token().value
                self.next_token()
                params.append(ParameterNode(name, param_type))
            if self.current_token().value == ',':
                self.next_token()
        return params

    def parse_block(self) -> BlockNode:
        self.expect_value(TokenType.SEPARATOR, '{', "Expected '{' for block")
        block = BlockNode()
        while not (self.current_token().token_type == TokenType.SEPARATOR and self.current_token().value == '}'):
            if self.current_token().token_type == TokenType.EOF:
                self.error("Unexpected EOF in block")
                break
            stmt = self.parse_statement()
            if stmt:
                block.add_child(stmt)
        self.expect_value(TokenType.SEPARATOR, '}', "Expected '}' at end of block")
        return block

    def parse_statement(self) -> Optional[ASTNode]:
        token = self.current_token()
        if token.token_type == TokenType.KEYWORD and token.value in ['int', 'float']:
            return self.parse_declaration()
        elif token.token_type == TokenType.KEYWORD and token.value == 'return':
            return self.parse_return()
        elif token.token_type == TokenType.KEYWORD and token.value == 'if':
            return self.parse_if()
        elif token.token_type == TokenType.KEYWORD and token.value == 'while':
            return self.parse_while()
        elif token.token_type == TokenType.KEYWORD and token.value == 'for':
            return self.parse_for()
        else:
            return self.parse_expression_statement()

    def parse_declaration(self) -> Optional[DeclarationNode]:
        var_type = self.current_token().value
        self.next_token()
        if not self.expect(TokenType.IDENTIFIER, "Expected variable name"):
            return None
        var_name = self.previous_token().value
        init_expr = None
        if self.current_token().token_type == TokenType.OPERATOR and self.current_token().value == '=':
            self.next_token()
            init_expr = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ';', "Expected ';' after declaration")
        return DeclarationNode(var_type, var_name, init_expr)

    def parse_return(self) -> Optional[ReturnNode]:
        self.expect_value(TokenType.KEYWORD, 'return', "Expected 'return'")
        expr = None
        if self.current_token().value != ';':
            expr = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ';', "Expected ';' after return")
        return ReturnNode(expr)
    
    def parse_if(self) -> Optional[IfNode]:
        self.expect_value(TokenType.KEYWORD, 'if', "Expected 'if'")
        self.expect_value(TokenType.SEPARATOR, '(', "Expected '(' after 'if'")
        condition = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ')', "Expected ')' after condition")
        then_stmt = self.parse_statement()

        else_stmt = None
        if self.current_token().token_type == TokenType.KEYWORD and self.current_token().value == 'else':
            self.next_token()
            else_stmt = self.parse_statement()

        return IfNode(condition, then_stmt, else_stmt)
    
    def parse_while(self) -> Optional[WhileNode]:
        self.expect_value(TokenType.KEYWORD, 'while', "Expected 'while'")
        self.expect_value(TokenType.SEPARATOR, '(', "Expected '(' after 'while'")
        condition = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ')', "Expected ')' after condition")
        body = self.parse_statement()
        return WhileNode(condition, body)

    def parse_for(self) -> Optional[ForNode]:
        self.expect_value(TokenType.KEYWORD, 'for', "Expected 'for'")
        self.expect_value(TokenType.SEPARATOR, '(', "Expected '(' after 'for'")

        # Parse init
        init = None
        if self.current_token().value != ';':
            if self.current_token().token_type == TokenType.KEYWORD:
                init = self.parse_declaration()
            else:
                init = self.parse_expression()
                self.expect_value(TokenType.SEPARATOR, ';', "Expected ';' after for-init")
        else:
            self.next_token()

        # Parse condition
        condition = None
        if self.current_token().value != ';':
            condition = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ';', "Expected ';' after for-condition")

        # Parse iteration
        iteration = None
        if self.current_token().value != ')':
            iteration = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ')', "Expected ')' after for-update")

        body = self.parse_statement()
        return ForNode(init, condition, iteration, body)

    def parse_expression_statement(self) -> Optional[ExpressionNode]:
        expr = self.parse_expression()
        self.expect_value(TokenType.SEPARATOR, ';', "Expected ';' after expression")
        return expr

    def parse_expression(self) -> ExpressionNode:
        # For now, just parse literal or variable
        token = self.current_token()
        if token.token_type == TokenType.LITERAL:
            self.next_token()
            return LiteralNode(token.value, "int")
        elif token.token_type == TokenType.IDENTIFIER:
            self.next_token()
            return VariableNode(token.value)
        else:
            self.error("Invalid expression")
            self.next_token()
            return LiteralNode(0, "int")

    def current_token(self) -> Token:
        return self.tokens[self.current_index] if self.current_index < len(self.tokens) else self.tokens[-1]

    def previous_token(self) -> Token:
        return self.tokens[self.current_index - 1]

    def next_token(self) -> Token:
        self.current_index += 1
        return self.current_token()

    def expect(self, token_type: TokenType, message: str) -> bool:
        if self.current_token().token_type == token_type:
            self.next_token()
            return True
        self.error(message)
        return False

    def expect_value(self, token_type: TokenType, value: str, message: str) -> bool:
        if self.current_token().token_type == token_type and self.current_token().value == value:
            self.next_token()
            return True
        self.error(message)
        return False

    def error(self, message: str):
        token = self.current_token()
        self.errors.append(SyntaxError(message, token.line, token.column))
