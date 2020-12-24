package SoftCodeParser;

import SoftCodeParser.core.Parser;
import SoftCodeParser.core.ParserTreeNode;

import java.util.ArrayDeque;
import java.util.Deque;

public class Main {
    public static void main(String[] args) {
        Deque<ParserTreeNode> queue = new ArrayDeque<>();
        Parser parser = new Parser();
        parser.parse();
        queue.add(parser.getParserTree().getRoot());
        while (!queue.isEmpty()) {
            ParserTreeNode p = queue.peekFirst();
            String out = p.getSymbol();
            if (p.isLeaf()) {
                out += ", value: " + p.getValue();
            }

            System.out.println(out);

            queue.pollFirst();
            for (ParserTreeNode t: p.getAllNext()) {
                queue.offerLast(t);
            }
        }
    }
}
