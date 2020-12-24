package SoftCodeLexer.core;

public class Token {
    private static Long ID = 1L;
    private final Long id;
    private String type;
    private String lexValue;

    public Token(String lexValue, String type) {
        this.id = ID;
        ID++;
        this.type = type;
        this.lexValue = lexValue;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getLexValue() {
        return lexValue;
    }

    public void setLexValue(String lexValue) {
        this.lexValue = lexValue;
    }

    public Long getId() {
        return id;
    }

    @Override
    public String toString() {
        return "<" + this.id + ", " + this.type + ", " + this.lexValue + ">";
    }
}
