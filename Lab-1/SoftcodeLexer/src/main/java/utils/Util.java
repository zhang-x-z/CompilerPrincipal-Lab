package utils;

public class Util {
    public static boolean isEdgeCorrect(String e) {
        if (e.equals("lowerLetters")) {
            return true;
        }

        if (e.equals("upperLetters")) {
            return true;
        }

        return e.charAt(0) == '^';
    }

    public static boolean isMatch(String e, String a) {
        if (e.equals("lowerLetters")) {
            char t = a.charAt(0);
            return (t <= 'z' && t >= 'a');
        } else if (e.equals("upperLetters")) {
            char t = a.charAt(0);
            return (t <= 'Z' && t >= 'A');
        } else if (e.charAt(0) == '^') {
            char t = a.charAt(0);
            for (int i = 1; i < e.length(); i++) {
                if (e.charAt(i) == t) {
                    return false;
                }
            }
        }
        return true;
    }
}

