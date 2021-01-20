package SimpleJavaLexerAndParser.SoftCodeParser.core;

import SimpleJavaLexerAndParser.SoftCodeParser.utils.Pair;

import java.util.HashMap;
import java.util.Map;


public class LRTableRow {
    private String name;
    /**
     * First String: Token type name
     * Pair(String, Boolean):
     *  - String: Grammar generator name or LRTableRow name
     *  - Integer:
     *      - 0: shift in
     *      - 1: reduce
     *      - 2: accepted
     */
    private Map<String, Pair<String, Integer>> actions = new HashMap<>();
    /**
     * First String: None terminal symbol name
     * Second String: LRTableRow name
     */
    private Map<String, String> goTo = new HashMap<>();

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Map<String, Pair<String, Integer>> getActions() {
        return actions;
    }

    public void setActions(String token, String name, int type) {
        actions.put(token, new Pair<>(name, type));
    }

    public Map<String, String> getGoTo() {
        return goTo;
    }

    public void setGoTo(String noneTerminal, String name) {
        goTo.put(noneTerminal, name);
    }

    public LRTableRow(String name) {
        this.name = name;
    }
}
