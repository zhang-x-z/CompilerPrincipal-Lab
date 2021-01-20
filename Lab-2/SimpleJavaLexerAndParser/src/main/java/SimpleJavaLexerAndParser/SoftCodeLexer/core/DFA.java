package SimpleJavaLexerAndParser.SoftCodeLexer.core;

import SimpleJavaLexerAndParser.SoftCodeLexer.config.LexerConfiguration;

import java.io.*;
import java.util.HashMap;
import java.util.Map;

public class DFA {
    private static final DFA dfa;
    private static State start;
    private static final Map<String, State> name2state = new HashMap<>();
    private State currentState;
    static {
        BufferedReader reader = null;
        try {
            String startName = LexerConfiguration.getInstance().getStartStateName();
            reader = new BufferedReader(new InputStreamReader(new FileInputStream(LexerConfiguration.getInstance().getDFAFileLocation()), LexerConfiguration.getInstance().getDFAFileEncoding()));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.trim().equals("")) {
                    continue;
                }
                String[] args = line.split(",");
                State s = new State(args);
                name2state.put(args[0].trim(), s);
                if (args[0].equals(startName)) {
                    start = s;
                }
            }
        } catch (IOException | RuntimeException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        dfa = new DFA();
    }

    public static DFA getInstance() {
        dfa.returnToStart();
        return dfa;
    }

    private DFA() {
        currentState = start;
    }

    public String getCurrentStateName() {
        return currentState.getName();
    }

    public boolean isAcceptingState() {
        return currentState.isAccepting();
    }

    public void returnToStart() {
        currentState = start;
    }

    public boolean next(String e) throws RuntimeException {
        if (e.length() != 1) {
            throw new RuntimeException("Must read one character at one time.");
        }
        String n = currentState.getNextStateName(e);
        if (n == null) {
            return false;
        }
        currentState = name2state.get(n);
        return true;
    }
}
