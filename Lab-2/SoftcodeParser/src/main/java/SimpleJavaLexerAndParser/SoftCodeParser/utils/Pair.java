package SimpleJavaLexerAndParser.SoftCodeParser.utils;

public class Pair<K, T> {
    private K key;
    private T value;

    public Pair(K key, T value) {
        this.key = key;
        this.value = value;
    }

    public Pair() {}

    public void setKey(K key) {
        this.key = key;
    }

    public void setValue(T value) {
        this.value = value;
    }

    public K getKey() {
        return key;
    }

    public T getValue() {
        return value;
    }
}
