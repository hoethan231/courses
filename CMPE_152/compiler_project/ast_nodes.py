from typing import List, Optional, Any, Dict

class ASTNode:
    pass

class ExpressionNode(ASTNode):
    pass

class LiteralNode(ExpressionNode):
    def __init__(self, value: Any, type_name: str):
        self.value = value
        self.type = type_name

class VariableNode(ExpressionNode):
    def __init__(self, name: str):
        self.name = name

class BinaryOpNode(ExpressionNode):
    def __init__(self, left: ExpressionNode, operator: str, right: ExpressionNode):
        self.left = left
        self.operator = operator
        self.right = right

class UnaryOpNode(ExpressionNode):
    def __init__(self, operator: str, operand: ExpressionNode):
        self.operator = operator
        self.operand = operand

class AssignmentNode(ExpressionNode):
    def __init__(self, left: VariableNode, right: ExpressionNode):
        self.left = left
        self.right = right

class FunctionCallNode(ExpressionNode):
    def __init__(self, function_name: str, arguments: List[ExpressionNode]):
        self.function_name = function_name
        self.arguments = arguments

class StatementNode(ASTNode):
    """Base class for statements"""
    pass

class BlockNode(StatementNode):
    def __init__(self):
        self.children = []
    
    def add_child(self, child: ASTNode):
        self.children.append(child)

class DeclarationNode(StatementNode):
    def __init__(self, type_name: str, name: str, initializer: Optional[ExpressionNode] = None):
        self.type = type_name
        self.name = name
        self.initializer = initializer

class ReturnNode(StatementNode):
    def __init__(self, expression: Optional[ExpressionNode] = None):
        self.expression = expression

class IfNode(StatementNode):
    def __init__(self, condition: ExpressionNode, then_statement: ASTNode, else_statement: Optional[ASTNode] = None):
        self.condition = condition
        self.then_statement = then_statement
        self.else_statement = else_statement

class WhileNode(StatementNode):
    def __init__(self, condition: ExpressionNode, body: ASTNode):
        self.condition = condition
        self.body = body

class ForNode(StatementNode):
    def __init__(self, initializer: Optional[ASTNode], condition: Optional[ExpressionNode], 
                 update: Optional[ExpressionNode], body: ASTNode):
        self.initializer = initializer
        self.condition = condition
        self.update = update
        self.body = body

class ParameterNode(ASTNode):
    def __init__(self, name: str, type_name: str):
        self.name = name
        self.type = type_name

class FunctionNode(ASTNode):
    def __init__(self, name: str, return_type: str, parameters: List[ParameterNode]):
        self.name = name
        self.return_type = return_type
        self.parameters = parameters
        self.body = None
    
    def set_body(self, body: BlockNode):
        self.body = body

class ProgramNode(ASTNode):
    def __init__(self):
        self.functions: Dict[str, FunctionNode] = {}