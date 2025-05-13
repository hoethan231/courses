from typing import Dict, List, Optional, Set
from ast_nodes import *

class AssemblyGenerator:
    def __init__(self):
        self.assembly_code = []
        self.current_function = None
        self.label_counter = 0
        self.variable_offsets = {}
        self.current_stack_offset = 0
        self.used_registers = set()
        
    def generate(self, program: ProgramNode) -> List[str]:
        """Generate assembly code for the entire program."""
        self.assembly_code = []
        
        self._emit(".section .text")
        self._emit(".global main")
        
        for func_name, func_node in program.functions.items():
            self._generate_function(func_node)
            
        return self.assembly_code
    
    def _generate_function(self, function: FunctionNode):
        """Generate assembly code for a function."""
        self.current_function = function.name
        self.variable_offsets = {}
        self.current_stack_offset = 0
        self.used_registers = set()
        
        self._emit(f"{function.name}:")
        self._emit("  push %rbp")
        self._emit("  mov %rsp, %rbp")
        
        # Allocate space for local variables
        space_for_locals_index = len(self.assembly_code)
        self._emit("  # Reserve space for local variables")
        
        # Store them in the stack
        for i, param in enumerate(function.parameters):
            # Parameter registers
            reg = ["%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"][min(i, 5)]
            
            # Allocate space for the parameter on the stack
            self.current_stack_offset -= 8
            self.variable_offsets[param.name] = self.current_stack_offset
            
            # Store parameter from register to stack
            if i < 6:
                self._emit(f"  mov {reg}, {self.current_stack_offset}(%rbp)")
            else:  # Additional parameters on the stack
                stack_pos = (i - 6) * 8 + 16
                self._emit(f"  mov {stack_pos}(%rbp), %rax")
                self._emit(f"  mov %rax, {self.current_stack_offset}(%rbp)")
        
        # Generate code for function body
        if function.body:
            self._generate_block(function.body)
        
        # Update space allocation for local variables
        if self.current_stack_offset < 0:
            aligned_space = ((abs(self.current_stack_offset) + 15) & ~15)
            self.assembly_code[space_for_locals_index] = f"  sub ${aligned_space}, %rsp"
        
        if function.return_type == "void" or not self.assembly_code[-1].strip().startswith("ret"):
            self._emit("  mov %rbp, %rsp")
            self._emit("  pop %rbp")
            self._emit("  ret")
            
        self._emit("")
    
    def _generate_block(self, block: BlockNode):
        """Generate assembly code for a block of statements."""
        # Save current stack offset to restore it after the block
        start_offset = self.current_stack_offset
        
        for statement in block.children:
            if isinstance(statement, DeclarationNode):
                self._generate_declaration(statement)
            elif isinstance(statement, ReturnNode):
                self._generate_return(statement)
            elif isinstance(statement, IfNode):
                self._generate_if(statement)
            elif isinstance(statement, WhileNode):
                self._generate_while(statement)
            elif isinstance(statement, ForNode):
                self._generate_for(statement)
            elif isinstance(statement, ExpressionNode):
                self._generate_expression(statement)
    
    def _generate_declaration(self, decl: DeclarationNode):
        """Generate assembly code for a variable declaration."""
        # Allocate space for the variable
        var_size = 8
        self.current_stack_offset -= var_size
        self.variable_offsets[decl.name] = self.current_stack_offset
        
        # Initialize the variable if an initializer is provided
        if decl.initializer:
            self._generate_expression(decl.initializer)
            self._emit(f"  mov %rax, {self.current_stack_offset}(%rbp)")
    
    def _generate_return(self, ret: ReturnNode):
        """Generate assembly code for a return statement."""
        if ret.expression:
            # Evaluate the return expression and put result in %rax
            self._generate_expression(ret.expression)
        else:
            # Default return value 0 for void functions
            self._emit("  xor %rax, %rax")
        
        self._emit("  mov %rbp, %rsp")
        self._emit("  pop %rbp")
        self._emit("  ret")
    
    def _generate_if(self, if_node: IfNode):
        """Generate assembly code for an if statement."""
        else_label = self._get_unique_label("else")
        end_label = self._get_unique_label("endif")
        
        # Generate condition code
        self._generate_expression(if_node.condition)
        self._emit("  cmp $0, %rax")
        self._emit(f"  je {else_label}")
        
        # Generate code for the then branch
        self._generate_statement(if_node.then_statement)
        self._emit(f"  jmp {end_label}")
        
        # Generate code for the else branch if it exists
        self._emit(f"{else_label}:")
        if if_node.else_statement:
            self._generate_statement(if_node.else_statement)
        
        self._emit(f"{end_label}:")
    
    def _generate_while(self, while_node: WhileNode):
        """Generate assembly code for a while loop."""
        start_label = self._get_unique_label("while")
        end_label = self._get_unique_label("endwhile")
        
        self._emit(f"{start_label}:")
        
        # Generate condition code
        self._generate_expression(while_node.condition)
        self._emit("  cmp $0, %rax")
        self._emit(f"  je {end_label}")
        
        # Generate loop body
        self._generate_statement(while_node.body)
        self._emit(f"  jmp {start_label}")
        
        self._emit(f"{end_label}:")
    
    def _generate_for(self, for_node: ForNode):
        """Generate assembly code for a for loop."""
        start_label = self._get_unique_label("for")
        end_label = self._get_unique_label("endfor")
        update_label = self._get_unique_label("forupdate")
        
        # Initialize the loop variable
        if for_node.initializer:
            if isinstance(for_node.initializer, DeclarationNode):
                self._generate_declaration(for_node.initializer)
            else:
                self._generate_expression(for_node.initializer)
        
        self._emit(f"{start_label}:")
        
        # Check the condition
        if for_node.condition:
            self._generate_expression(for_node.condition)
            self._emit("  cmp $0, %rax")
            self._emit(f"  je {end_label}")
        
        # Generate loop body
        self._generate_statement(for_node.body)
        
        self._emit(f"{update_label}:")
        if for_node.update:
            self._generate_expression(for_node.update)
        
        self._emit(f"  jmp {start_label}")
        self._emit(f"{end_label}:")
    
    def _generate_expression(self, expr: ExpressionNode) -> None:
        """Generate assembly code for an expression."""
        if isinstance(expr, LiteralNode):
            self._emit(f"  mov ${expr.value}, %rax")
        
        elif isinstance(expr, VariableNode):
            if expr.name in self.variable_offsets:
                offset = self.variable_offsets[expr.name]
                self._emit(f"  mov {offset}(%rbp), %rax")
            else:
                self._emit(f"  # Error: Variable {expr.name} not found")
                self._emit("  xor %rax, %rax")
        
        elif isinstance(expr, BinaryOpNode):
            self._generate_binary_op(expr)
        
        elif isinstance(expr, UnaryOpNode):
            self._generate_unary_op(expr)
        
        elif isinstance(expr, AssignmentNode):
            self._generate_assignment(expr)
        
        elif isinstance(expr, FunctionCallNode):
            self._generate_function_call(expr)
    
    def _generate_binary_op(self, expr: BinaryOpNode):
        """Generate assembly code for a binary operation."""
        # Generate code for the right operand and push result to stack
        self._generate_expression(expr.right)
        self._emit("  push %rax")
        
        # Generate code for the left operand
        self._generate_expression(expr.left)
        
        # Pop right operand result into %rcx
        self._emit("  pop %rcx")
        
        # Perform the operation based on the operator
        if expr.operator == '+':
            self._emit("  add %rcx, %rax")
        elif expr.operator == '-':
            self._emit("  sub %rcx, %rax")
        elif expr.operator == '*':
            self._emit("  imul %rcx, %rax")
        elif expr.operator == '/':
            self._emit("  cqo")
            self._emit("  idiv %rcx")
        elif expr.operator in ['==', '!=', '<', '<=', '>', '>=']:
            self._emit("  cmp %rcx, %rax")
            if expr.operator == '==':
                self._emit("  sete %al")
            elif expr.operator == '!=':
                self._emit("  setne %al")
            elif expr.operator == '<':
                self._emit("  setl %al")
            elif expr.operator == '<=':
                self._emit("  setle %al")
            elif expr.operator == '>':
                self._emit("  setg %al")
            elif expr.operator == '>=':
                self._emit("  setge %al")
            self._emit("  movzx %al, %rax")
        elif expr.operator == '&&':
            # Logical AND
            self._emit("  and %rcx, %rax")
            self._emit("  cmp $0, %rax")
            self._emit("  setne %al")
            self._emit("  movzx %al, %rax")
        elif expr.operator == '||':
            # Logical OR
            self._emit("  or %rcx, %rax")
            self._emit("  cmp $0, %rax")
            self._emit("  setne %al")
            self._emit("  movzx %al, %rax")
    
    def _generate_unary_op(self, expr: UnaryOpNode):
        """Generate assembly code for a unary operation."""
        # Generate code for the operand
        self._generate_expression(expr.operand)
        
        # Apply the operator
        if expr.operator == '-':
            self._emit("  neg %rax")
        elif expr.operator == '!':
            self._emit("  cmp $0, %rax")
            self._emit("  sete %al")
            self._emit("  movzx %al, %rax")
    
    def _generate_assignment(self, expr: AssignmentNode):
        """Generate assembly code for an assignment."""
        # Generate code for the right-hand side
        self._generate_expression(expr.right)
        
        # Store the result in the variable's location
        if expr.left.name in self.variable_offsets:
            offset = self.variable_offsets[expr.left.name]
            self._emit(f"  mov %rax, {offset}(%rbp)")
        else:
            self._emit(f"  # Error: Variable {expr.left.name} not found")
    
    def _generate_function_call(self, expr: FunctionCallNode):
        """Generate assembly code for a function call."""
        self._emit("  push %rdi")
        self._emit("  push %rsi")
        self._emit("  push %rdx")
        self._emit("  push %rcx")
        self._emit("  push %r8")
        self._emit("  push %r9")
        
        # Evaluate and push arguments in reverse order
        arg_regs = ["%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"]
        
        for i in range(len(expr.arguments) - 1, 5, -1):
            self._generate_expression(expr.arguments[i])
            self._emit("  push %rax")
        
        # Load first 6 arguments into registers
        for i in range(min(len(expr.arguments), 6)):
            self._generate_expression(expr.arguments[i])
            self._emit(f"  mov %rax, {arg_regs[i]}")
        
        self._emit("  mov %rsp, %rax")
        self._emit("  and $0xF, %rax")
        self._emit("  jz .aligned")
        self._emit("  sub $8, %rsp")
        
        self._emit(".aligned:")
        # Call the function
        self._emit(f"  call {expr.function_name}")
        
        # Clean up the stack
        if len(expr.arguments) > 6 or True:
            extra_args = max(0, len(expr.arguments) - 6)
            stack_cleanup = extra_args * 8
            if stack_cleanup > 0:
                self._emit(f"  add ${stack_cleanup}, %rsp")
        
        # Restore saved registers
        self._emit("  pop %r9")
        self._emit("  pop %r8")
        self._emit("  pop %rcx")
        self._emit("  pop %rdx")
        self._emit("  pop %rsi")
        self._emit("  pop %rdi")
    
    def _generate_statement(self, stmt):
        """Generate code for a statement."""
        if isinstance(stmt, BlockNode):
            self._generate_block(stmt)
        elif isinstance(stmt, DeclarationNode):
            self._generate_declaration(stmt)
        elif isinstance(stmt, ReturnNode):
            self._generate_return(stmt)
        elif isinstance(stmt, IfNode):
            self._generate_if(stmt)
        elif isinstance(stmt, WhileNode):
            self._generate_while(stmt)
        elif isinstance(stmt, ForNode):
            self._generate_for(stmt)
        elif isinstance(stmt, ExpressionNode):
            self._generate_expression(stmt)
    
    def _get_unique_label(self, prefix: str) -> str:
        """Generate a unique label for jumps."""
        label = f".{prefix}_{self.current_function}_{self.label_counter}"
        self.label_counter += 1
        return label
    
    def _emit(self, instruction: str):
        """Add an assembly instruction to the output."""
        self.assembly_code.append(instruction)


# Extended AST nodes needed for proper code generation
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