def is_delimiter(ch):
    return (
        ch == ' ' or ch == '+' or ch == '-' or ch == '*' or 
        ch == '/' or ch == ',' or ch == ';' or ch == '>' or 
        ch == '<' or ch == '=' or ch == '(' or ch == ')' or 
        ch == '[' or ch == ']' or ch == '{' or ch == '}'
        )

def is_operator(ch):
    return (
        ch == '+' or ch == '-' or ch == '*' or 
        ch == '/' or ch == '>' or ch == '<' or 
        ch == '='
        )

def valid_identifier(str_val):
    return not (
        str_val[0] == '0' or str_val[0] == '1' or str_val[0] == '2' or
        str_val[0] == '3' or str_val[0] == '4' or str_val[0] == '5' or 
        str_val[0] == '6' or str_val[0] == '7' or str_val[0] == '8' or 
        str_val[0] == '9' or is_delimiter(str_val[0]) == True
        )

def is_keyword(str_val):
    return str_val in ["if", "else", "while", "do", "break", "continue", 
                "int", "double", "float", "return", "char", "case", 
                "sizeof", "long", "short", "typedef", "switch", 
                "unsigned", "void", "static", "struct", "goto"]

def is_integer(str_val):
    if len(str_val) == 0:
        return False
    
    for i in range(len(str_val)):
        if (str_val[i] != '0' and str_val[i] != '1' and str_val[i] != '2'
            and str_val[i] != '3' and str_val[i] != '4' and str_val[i] != '5'
            and str_val[i] != '6' and str_val[i] != '7' and str_val[i] != '8'
            and str_val[i] != '9' or (str_val[i] == '-' and i > 0)):
            return False
    return True

def is_real_number(str_val):
    if len(str_val) == 0:
        return False
    
    has_decimal = False
    
    for i in range(len(str_val)):
        if (str_val[i] != '0' and str_val[i] != '1' and str_val[i] != '2'
            and str_val[i] != '3' and str_val[i] != '4' and str_val[i] != '5'
            and str_val[i] != '6' and str_val[i] != '7' and str_val[i] != '8'
            and str_val[i] != '9' and str_val[i] != '.' or 
            (str_val[i] == '-' and i > 0)):
            return False
        
        if str_val[i] == '.':
            has_decimal = True
    
    return has_decimal

def sub_string(str_val, left, right):
    return str_val[left:right+1]

def parse(str_val):
    left = 0
    right = 0
    length = len(str_val)
    
    while right <= length and left <= right:
        if right < length and is_delimiter(str_val[right]) == False:
            right += 1
        
        if (right == length or (is_delimiter(str_val[right]) == True and left == right)):
            if right < length and is_operator(str_val[right]) == True:
                print(f"'{str_val[right]}' IS AN OPERATOR")
            
            if right < length:
                right += 1
            left = right
            
        elif ((right == length or is_delimiter(str_val[right]) == True) and left != right):
            sub_str = sub_string(str_val, left, right - 1)
            
            if is_keyword(sub_str) == True:
                print(f"'{sub_str}' IS A KEYWORD")
            
            elif is_integer(sub_str) == True:
                print(f"'{sub_str}' IS AN INTEGER")
            
            elif is_real_number(sub_str) == True:
                print(f"'{sub_str}' IS A REAL NUMBER")
            
            elif valid_identifier(sub_str) == True and (right-1 < length and is_delimiter(str_val[right - 1]) == False):
                print(f"'{sub_str}' IS A VALID IDENTIFIER")
            
            elif valid_identifier(sub_str) == False and (right-1 < length and is_delimiter(str_val[right - 1]) == False):
                print(f"'{sub_str}' IS NOT A VALID IDENTIFIER")
            
            left = right

def main():
    str_val = "int a = b + 1c; "
    
    parse(str_val)

if __name__ == "__main__":
    main()