package main;

import core.Lexer;

public class Main {
    public static void main(String[] args) {
        try {
            Lexer lexer = new Lexer();
            while (lexer.hasNext()) {
                lexer.next();
            }
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }
    }
}
