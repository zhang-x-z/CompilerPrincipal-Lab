package SimpleJavaLexerAndParser.SoftCodeParser.core;

import SimpleJavaLexerAndParser.SoftCodeParser.config.ParserConfiguration;
import SimpleJavaLexerAndParser.SoftCodeParser.utils.Pair;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class LRTable {
    private static final LRTable lrtable;
    private Map<String, LRTableRow> rows = new HashMap<>();
    static {
        lrtable = new LRTable();
        try {
            lrtable.parserActionsTable();
            lrtable.parserGotoTable();
        } catch (IOException e) {
            throw new RuntimeException("Parser LR action table failed.");
        } catch (ArrayIndexOutOfBoundsException e) {
            throw new RuntimeException("In LR action table: the row in actions table must have tokenName, nextName, nextType");
        } catch (RuntimeException e) {
            throw new RuntimeException("Type in LR Actions table can only be 0, 1 or 2");
        }
    }

    private void parserActionsTable() throws IOException {
        parserHelper(true);
    }

    private void parserGotoTable() throws IOException {
        parserHelper(false);
    }

    private void parserHelper(boolean isActions) throws IOException {
        String location;
        if (isActions) {
            location = ParserConfiguration.getInstance().getLRActionsTableLocation();
        } else {
            location = ParserConfiguration.getInstance().getLRGoToTableLocation();
        }
        String encoding = ParserConfiguration.getInstance().getFileEncoding();
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(location), encoding));
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.trim().equals("")) {
                continue;
            }
            String[] params = line.trim().split(",");
            String name = params[0].trim();
            LRTableRow row;
            if (rows.containsKey(name)) {
                row = rows.get(name);
            } else {
                row = new LRTableRow(name);
                rows.put(name, row);
            }
            if (isActions) {
                for (int i = 1; i < params.length; i += 3) {
                    int type = Integer.parseInt(params[i + 2].trim());
                    if (type != 1 && type != 2 && type != 0) {
                        throw new RuntimeException("Type in LR Actions table can only be 0, 1 or 2");
                    }
                    row.setActions(params[i].trim(), params[i + 1].trim(), type);
                }
            } else {
                for (int i = 1; i < params.length; i += 2) {
                    row.setGoTo(params[i].trim(), params[i + 1].trim());
                }
            }
        }
        reader.close();
    }

    private LRTable() {}

    public static LRTable getInstance() {
        return lrtable;
    }

    public Pair<String, Integer> canReach(String name, String tokenName) {
        return rows.get(name).getActions().get(tokenName);
    }

    public String canGoto(String name, String noneTerminalSymbolName) {
        return rows.get(name).getGoTo().get(noneTerminalSymbolName);
    }
}
