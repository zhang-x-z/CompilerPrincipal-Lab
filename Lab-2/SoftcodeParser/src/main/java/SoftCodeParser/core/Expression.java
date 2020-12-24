package SoftCodeParser.core;

import java.util.ArrayList;
import java.util.List;

public class Expression {
    private String id;
    private String leftPart;
    private List<String> rightPart = new ArrayList<>();
    public Expression(String id, String leftPart) {
        this.id = id;
        this.leftPart = leftPart;
    }

    public void setRightPart(String name) {
        rightPart.add(name);
    }

    public List<String> getRightPart() {
        return rightPart;
    }

    public String getLeftPart() {
        return leftPart;
    }
}
