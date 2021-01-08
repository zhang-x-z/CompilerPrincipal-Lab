package SimpleJavaLexerAndParser.SoftCodeParser.core;

import SimpleJavaLexerAndParser.SoftCodeParser.config.ParserConfiguration;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

public class Grammar {
    private static final Grammar grammar;
    private Map<String, Expression> allExpression = new HashMap<>();
    static {
        grammar = new Grammar();
        try {
            grammar.init();
        } catch (DocumentException e) {
            throw new RuntimeException("Parser Grammar file failed.");
        }
    }

    private Grammar() {}

    @SuppressWarnings("all")
    private void init() throws DocumentException {
        SAXReader reader = new SAXReader();
        Document doc = reader.read(new File(ParserConfiguration.getInstance().getGrammarLocation()));
        Element root = doc.getRootElement();
        for (Object e: root.elements("expression")) {
            Element exp = (Element) e;
            String id = exp.attributeValue("id").trim();
            String left = exp.elementTextTrim("leftPart");
            String right = exp.elementTextTrim("rightPart");
            if (id == null)
                throw new RuntimeException("expression tag must have arrtibute id");
            if (left == null)
                throw new RuntimeException("expression tag must have child tag <leftPart>");
            if (right == null)
                throw new RuntimeException("expression tag must have child tag <rightPart>");
            String[] names = right.split("\\[|\\]");
            Expression expression = new Expression(id, left);
            for (String name: names) {
                if (name.length() == 0)
                    continue;
                expression.setRightPart(name);
            }
            allExpression.put(id, expression);
        }
    }

    public static Grammar getInstance() {
        return grammar;
    }

    public Expression getExpressionById(String id) {
        return allExpression.get(id);
    }
}
