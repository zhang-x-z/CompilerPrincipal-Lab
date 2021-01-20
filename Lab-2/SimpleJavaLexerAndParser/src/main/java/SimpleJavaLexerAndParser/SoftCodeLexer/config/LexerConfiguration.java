package SimpleJavaLexerAndParser.SoftCodeLexer.config;

import java.io.IOException;
import java.util.Properties;

public class LexerConfiguration {
    private static final LexerConfiguration configuration;
    private static String dfaFileLocation;
    private static String sourceFileLocation;
    private static String startStateName;
    private static String sourceFileEncoding;
    private static String dfaFileEncoding;
    private static String lrTableFileLocation;
    private static int bufferSize = 100;
    private static final Properties properties;
    static {
        properties = new Properties();
        try {
            properties.load(Thread.currentThread().getContextClassLoader().getResourceAsStream("lexer-config.properties"));
            dfaFileLocation = properties.getProperty("dfa.location");
            if (dfaFileLocation == null) {
                throw new RuntimeException("DFA table file location must be given.");
            }
            startStateName = properties.getProperty("dfa.startName");
            if (startStateName == null) {
                throw new RuntimeException("Start state must be given.");
            }
            sourceFileLocation = properties.getProperty("sourcecode.location");
            if (sourceFileLocation == null) {
                throw new RuntimeException("Source file location must be given.");
            }
            dfaFileEncoding = properties.getProperty("dfa.encoding");
            if (dfaFileEncoding == null) {
                dfaFileEncoding = "utf8";
            }
            sourceFileEncoding = properties.getProperty("sourcecode.encoding");
            if (sourceFileEncoding == null) {
                sourceFileEncoding = "utf8";
            }
            String bs = properties.getProperty("sourcecode.buffersize");
            if (bs != null) {
                bufferSize = Integer.parseInt(bs);
            }
        } catch (IOException | RuntimeException e) {
            e.printStackTrace();
        }
        configuration = new LexerConfiguration();
    }

    private LexerConfiguration() {
    }

    public static LexerConfiguration getInstance() {
        return configuration;
    }

    public String getDFAFileLocation() {
        return dfaFileLocation;
    }

    public String getSourceFileLocation() {
        return sourceFileLocation;
    }

    public String getStartStateName() {
        return startStateName;
    }

    public String getSourceFileEncoding() {
        return sourceFileEncoding;
    }

    public String getDFAFileEncoding() {
        return dfaFileEncoding;
    }

    public int getBufferSize() {
        return bufferSize;
    }

    public String acceptStateToSymbolName(String stateName) {
        return properties.getProperty("dfa." + stateName);
    }
}
