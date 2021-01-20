package SimpleJavaLexerAndParser.SoftCodeParser.core;

public class ParserTree {
    private final ParserTreeNode root;
    public ParserTree(ParserTreeNode root) {
        this.root = root;
    }

    public ParserTreeNode getRoot() {
        return root;
    }
}
