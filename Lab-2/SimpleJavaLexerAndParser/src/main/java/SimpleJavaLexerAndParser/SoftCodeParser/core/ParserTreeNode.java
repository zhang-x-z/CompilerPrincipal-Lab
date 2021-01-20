package SimpleJavaLexerAndParser.SoftCodeParser.core;

import java.util.ArrayList;
import java.util.List;

public class ParserTreeNode {
    private static int ID = 1;
    private List<ParserTreeNode> next = new ArrayList<>();
    private int id;
    private String symbol;
    private boolean isLeaf;
    private String value = null;
    public ParserTreeNode(String symbol, boolean isLeaf) {
        this.id = ID;
        ID++;
        this.isLeaf = isLeaf;
        this.symbol = symbol;
    }

    public ParserTreeNode(String symbol, boolean isLeaf, String value) {
        this.id = ID;
        ID++;
        this.value = value;
        this.isLeaf = isLeaf;
        this.symbol = symbol;
    }

   public String getValue() {
       return value;
   }

    public List<ParserTreeNode> getAllNext() {
        return next;
    }

    public boolean isLeaf() {
        return isLeaf;
    }

    public String getSymbol() {
        return symbol;
   }

    public int getId() {
        return id;
    }

    public void setNextNode(ParserTreeNode n) {
        next.add(n);
    }
}
