import ply.lex as lex

tokens = (
    'INTEGER',
    'FLOAT',
)

def t_FLOAT(t):
    r'^[-+]?[0-9]*\.[0-9]+$'
    return t

def t_INTEGER(t):
    r'^[-+]?[0-9]+$'
    return t

def t_error(t):
    t.lexer.skip(1)

lexer = lex.lex()

def main():
    print("Enter a number to check (Ctrl+C to exit):")
    
    while True:
        try:
            user_input = input("> ").strip()
            
            lexer.input(user_input)
            
            tok = lexer.token()
            
            if tok and tok.type == 'INTEGER':
                print("Valid Integer number")
            elif tok and tok.type == 'FLOAT':
                print("Valid Float number")
            else:
                print("Not valid Integer/Float number")
                
        except KeyboardInterrupt:
            print("\nExiting...")
            break

if __name__ == "__main__":
    main()