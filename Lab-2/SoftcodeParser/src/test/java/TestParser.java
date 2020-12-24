import SoftCodeParser.Main;
import SoftCodeParser.core.Parser;
import SoftCodeParser.core.ParserTree;
import org.junit.Test;

public class TestParser {
    @Test
    public void testParser() {
        Parser parser = new Parser();
        parser.parse();
        ParserTree tree = parser.getParserTree();
    }

    @Test
    public void testMain() {
        Main.main(null);
    }
}
