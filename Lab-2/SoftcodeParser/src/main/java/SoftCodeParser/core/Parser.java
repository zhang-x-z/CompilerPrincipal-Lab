package SoftCodeParser.core;

import SoftCodeLexer.core.Lexer;
import SoftCodeLexer.core.Token;
import SoftCodeParser.config.ParserConfiguration;
import SoftCodeParser.utils.Pair;

import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class Parser {
    private final ParserConfiguration configuration = ParserConfiguration.getInstance();
    private final Grammar grammar = Grammar.getInstance();
    private final LRTable table = LRTable.getInstance();
    private final Lexer lexer = new Lexer();
    private ParserTree parserTree = null;

    public Parser() {}

    public ParserTree getParserTree() {
        return parserTree;
    }

    private void reduce(String id, Stack<String> stateStack, Stack<ParserTreeNode> symbolStack, Token token) {
        Expression exp = grammar.getExpressionById(id);
        List<String> rightPart = exp.getRightPart();
        ParserTreeNode newNode = new ParserTreeNode(exp.getLeftPart(), false);
        int len = rightPart.size();
        for (int i = len - 1; i >= 0; i--) {
            ParserTreeNode top = symbolStack.peek();
            if (!top.getSymbol().equals(rightPart.get(i))) {
                throw new RuntimeException("Wrong statement at: " + token.getLexValue());
            }
            newNode.setNextNode(top);
            symbolStack.pop();
            stateStack.pop();
        }
        symbolStack.push(newNode);
        stateStack.push(table.canGoto(stateStack.peek(), newNode.getSymbol()));
    }

    public void parse() throws RuntimeException {
        Stack<String> stateStack = new Stack<>();
        Stack<ParserTreeNode> symbolStack = new Stack<>();
        stateStack.push(configuration.getStartState());

        boolean isConsumed = true;
        Token token = null;
        while (lexer.hasNext() || !isConsumed) {
            if (isConsumed) {
                token = lexer.next();
            }

            if (configuration.isIgnoreWhiteSpace() && token.getType().equals(configuration.getWhiteSpaceTypeName()))
                continue;

            Pair<String, Integer> tmp = table.canReach(stateStack.peek(), token.getType());
            if (tmp == null)
                throw new RuntimeException("Wrong statement at: " + token.getLexValue());
            if (tmp.getValue() == 0) {
                stateStack.push(tmp.getKey());
                symbolStack.push(new ParserTreeNode(token.getType(), true, token.getLexValue()));
                isConsumed = true;
            } else if (tmp.getValue() == 1) {
                reduce(tmp.getKey(), stateStack, symbolStack, token);
                isConsumed = false;
            }
        }

        Pair<String, Integer> p = table.canReach(stateStack.peek(), "$");
        assert token != null;
        if (p.getValue() == 0 || p.getValue() == 2) {
            throw new RuntimeException("Wrong statement at: " + token.getLexValue());
        }

        while (p.getValue() != 2) {
            reduce(p.getKey(), stateStack, symbolStack, token);
            p = table.canReach(stateStack.peek(), "$");
            if (p.getValue() == 0) {
                throw new RuntimeException("Wrong statement at: " + token.getLexValue());
            }
        }

        Expression exp = grammar.getExpressionById("acc");
        String left = exp.getLeftPart();
        List<String> rightPart = exp.getRightPart();
        ParserTreeNode newNode = new ParserTreeNode(left, false);
        for (int i = rightPart.size() - 1; i >= 0; i--) {
            ParserTreeNode top = symbolStack.peek();
            if (!top.getSymbol().equals(rightPart.get(i))) {
                throw new RuntimeException("Wrong statement at: " + token.getLexValue());
            }
            newNode.setNextNode(top);
            symbolStack.pop();
            stateStack.pop();
        }
        parserTree = new ParserTree(newNode);
    }
}
