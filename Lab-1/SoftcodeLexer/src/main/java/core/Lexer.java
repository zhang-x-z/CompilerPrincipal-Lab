package core;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class Lexer {
    private final DFA dfa = DFA.getInstance();
    private final String encoding = Configuration.getInstance().getSourceFileEncoding();
    private InputStreamReader reader = null;
    private final char[] buf = new char[Configuration.getInstance().getBufferSize()];
    private int currentLength;
    private int currentIndex = 0;
    private boolean isEnd = false;
    private StringBuilder currentWord = new StringBuilder();
    public Lexer() {
        openSourceCodeFile();
        readBuffer();
        if (currentLength == -1) {
            throw new RuntimeException("Empty source file.");
        }
    }

    public boolean hasNext() {
        return !isEnd;
    }

    // TODO: Just print the token currently. It should output a token when use with parser.
    public void next() throws RuntimeException {
        if (!isEnd) {
            boolean flag = true;
            while (flag) {
                if (currentIndex == currentLength) {
                    readBuffer();
                    currentIndex = 0;
                    if (currentLength == -1) {
                        isEnd = true;
                        closeSourceCodeFile();
                        String word = currentWord.toString();
                        if (dfa.isAcceptingState()) {
                            System.out.println("<" + Configuration.getInstance().acceptStateToSymbolName(dfa.getCurrentStateName()) + "," + word + ">");
                            break;
                        } else {
                            throw new RuntimeException("Wrong word: " + word);
                        }
                    }
                }
                String e = String.valueOf(buf[currentIndex]);
                if (!dfa.next(e)) {
                    String word = currentWord.toString();
                    if (dfa.isAcceptingState()) {
                        System.out.println("<" + Configuration.getInstance().acceptStateToSymbolName(dfa.getCurrentStateName()) + "," + word + ">");
                        flag = false;
                        currentWord = new StringBuilder();
                        dfa.returnToStart();
                    } else {
                        throw new RuntimeException("Wrong word: " + word + e);
                    }
                } else {
                    currentWord.append(e);
                    currentIndex++;
                }
            }
        } else {
            System.out.println("Has reached to the end of the source file.");
        }
    }

    private void openSourceCodeFile() {
        try {
            reader = new InputStreamReader(new FileInputStream(Configuration.getInstance().getSourceFileLocation()), encoding);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void readBuffer() {
        try {
            currentLength = reader.read(buf);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void closeSourceCodeFile() {
        if (reader != null) {
            try {
                reader.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
