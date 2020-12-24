package SoftCodeLexer.core;

import SoftCodeLexer.utils.Util;

import java.util.*;

public class State {
    private boolean isAcceptingState;
    private String name;
    private final List<String> specialEdge = new ArrayList<>();
    private final static Map<String, String> mapping2insteadName = new HashMap<>();
    private final static Set<String> insteadName = new HashSet<>();
    private final Map<String, String> mapping2statename = new HashMap<>();
    static {
        insteadName.add("cr");
        insteadName.add("lf");
        insteadName.add("tab");
        insteadName.add("comma");
        insteadName.add("space");
        mapping2insteadName.put("\r", "cr");
        mapping2insteadName.put("\n", "lf");
        mapping2insteadName.put("\t", "tab");
        mapping2insteadName.put(",", "comma");
        mapping2insteadName.put(" ", "space");
    }

    private void init(String[] args) throws RuntimeException {
        if (args.length < 2) {
            throw new RuntimeException("A state must have a name and a boolean variable which indicates whether this state is an accepting state.");
        }
        if (!(args[1].equals("0") || args[1].equals("1"))) {
            throw new RuntimeException("The boolean variable which indicates whether the state is accepting state must be 0 or 1.");
        }
        name = args[0];
        isAcceptingState = args[1].equals("1");
        for (int i = 2; i < args.length; i += 2) {
            String e = args[i];
            if (e == null || e.length() < 1) {
                throw new RuntimeException("DFA tables can not cations null. (like ..,,..)");
            }
            if (e.length() > 1) {
                if (!insteadName.contains(e)) {
                    if (Util.isEdgeCorrect(e)) {
                        specialEdge.add(e);
                    } else {
                        throw new RuntimeException("Special case in DFA table can only be lowerLetters, upperLetters and strings which begin with ^");
                    }
                }
            }

            if (mapping2statename.containsKey(e)) {
                throw new RuntimeException("Do not have same edge in one state.");
            }
            mapping2statename.put(args[i], args[i + 1]);
        }
    }

    public State(String[] args) throws RuntimeException {
        init(args);
    }

    public boolean isAccepting() {
        return isAcceptingState;
    }

    private String checkSpecialCase(String edge) throws RuntimeException {
        boolean flag = false;
        String a = null;
        for (String e: specialEdge) {
            if (Util.isMatch(e, edge)) {
                if (flag) {
                    throw new RuntimeException("Special case in DFA table can not be overlap.");
                } else {
                    flag = true;
                    a = e;
                }
            }
        }
        return a;
    }

    public String getNextStateName(String edge) throws RuntimeException {
        String instead = mapping2insteadName.get(edge);
        String n;
        if (instead == null) {
            n = mapping2statename.get(edge);
        } else {
            n = mapping2statename.get(instead);
        }
        if (n == null) {
            String e = checkSpecialCase(edge);
            if (e == null) {
                return null;
            }
            n = mapping2statename.get(e);
        }
        return n;
    }

    public String getName() {
        return name;
    }
}
