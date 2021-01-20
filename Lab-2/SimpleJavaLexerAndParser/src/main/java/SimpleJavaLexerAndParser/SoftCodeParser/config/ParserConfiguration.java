package SimpleJavaLexerAndParser.SoftCodeParser.config;

import java.io.IOException;
import java.util.Properties;

public class ParserConfiguration {
    private static final ParserConfiguration configuration;
    private String fileEncoding = null;
    private String LRActionsTableLocation = null;
    private String LRGoToTableLocation = null;
    private String grammarLocation = null;
    private String startState = null;
    private boolean ignoreWhiteSpace = false;

    public String getFileEncoding() {
        return fileEncoding;
    }

    public String getLRActionsTableLocation() {
        return LRActionsTableLocation;
    }

    public String getLRGoToTableLocation() {
        return LRGoToTableLocation;
    }

    public String getGrammarLocation() {
        return grammarLocation;
    }

    public String getStartState() {
        return startState;
    }

    public boolean isIgnoreWhiteSpace() {
        return ignoreWhiteSpace;
    }

    public String getWhiteSpaceTypeName() {
        return whiteSpaceTypeName;
    }

    private String whiteSpaceTypeName = null;
    static {
        configuration = new ParserConfiguration();
        Properties properties = new Properties();
        try {
            properties.load(Thread.currentThread().getContextClassLoader().getResourceAsStream("parser-config.properties"));
        } catch (IOException ioException) {
            throw new RuntimeException("Open parser-config.properties failed.");
        }

        configuration.startState = properties.getProperty("lrTable.start");
        if (configuration.startState == null)
            throw new RuntimeException("In parser-config.properties: Must has lrTable.start");
        configuration.LRActionsTableLocation = properties.getProperty("lrActionTable.location");
        if (configuration.LRActionsTableLocation == null)
            throw new RuntimeException("In parser-config.properties: Must has lrActionTable.location");
        configuration.LRGoToTableLocation = properties.getProperty("lrGotoTable.location");
        if (configuration.LRGoToTableLocation == null)
            throw new RuntimeException("In parser-config.properties: Must has lrGotoTable.location");
        configuration.grammarLocation = properties.getProperty("grammar.location");
        if (configuration.grammarLocation == null)
            throw new RuntimeException("In parser-config.properties: Must has grammar.location");
        String tmp = properties.getProperty("ignoreWhiteSpace");
        if (tmp != null) {
            if (tmp.equals("true") || tmp.equals("false") || tmp.equals("True") || tmp.equals("False"))
                configuration.ignoreWhiteSpace = Boolean.parseBoolean(tmp);
            else
                throw new RuntimeException("In parser-config.properties: ignoreWhiteSpace must be true or false");
        }
        if (configuration.ignoreWhiteSpace) {
            configuration.whiteSpaceTypeName = properties.getProperty("whiteSpace.name");
            if (configuration.whiteSpaceTypeName == null) {
                throw new RuntimeException("In parser-config.properties: Must has whiteSpace.name, because the value of ignoreWhiteSpace is true");
            }
        }

        configuration.fileEncoding = properties.getProperty("fileEncoding");
        if (configuration.fileEncoding == null)
            configuration.fileEncoding = "UTF8";
    }

    private ParserConfiguration() {}

    public static ParserConfiguration getInstance() {
        return configuration;
    }
}
