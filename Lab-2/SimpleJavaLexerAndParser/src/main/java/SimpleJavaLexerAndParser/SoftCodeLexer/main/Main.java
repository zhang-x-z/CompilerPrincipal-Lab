package SimpleJavaLexerAndParser.SoftCodeLexer.main;

import SimpleJavaLexerAndParser.SoftCodeLexer.core.Lexer;

public class Main {
    public static void main(String[] args) {
        try {
            Lexer lexer = new Lexer();
            while (lexer.hasNext()) {
                System.out.println(lexer.next());
            }
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }
    }
}
