# SimpleJavaLexerAndParser

- 使用maven，java 14开发

## 编译方法

- 在该项目下运行
```shell script
mvn compile
```
> 注意：请使用JDK14及以上版本
## 使用方法
- 使用Parser，在SimpleJavaLexerAndParser.jar所在文件夹下运行
```shell script
java -cp '.;SimpleJavaLexerAndParser.SoftCodeLexer.jar' SimpleJavaLexerAndParser.SoftCodeParser.main.Main
```
- 单独使用Lexer，在SimpleJavaLexerAndParser.jar所在文件夹下运行

```shell script
java -cp'.;SimpleJavaLexerAndParser.SoftCodeLexer.jar' SimpleJavaLexerAndParser.SoftCodeLexer.main.Main
```

## 配置说明

- 本程序必须要有名为lexer-config.properties，parser-config.properties的配置文件，并放置在classpath中
- 输入的dfa，LR Table以csv文件格式存储，文件格式见后文
- 输入的语法以xml格式存储，格式见后文
### lexer-config.properties可配置项
- dfa.location: dfa文件的位置（必需）
- dfa.encoding: dfa文件的编码格式（不配置默认utf8）
- dfa.startName: 其实状态的名称（必需，需要和dfa文件中的状态名称一样，区分大小写）
- sourcecode.location: 要进行词法分析的源代码文件位置（必需）
- sourcecode.encoding: 源代码文件的编码（不配置默认utf8）
- sourcecode.buffersize: 一次读入源代码文件的字符数目（不配置默认100）
- dfa.stateName: 其中stateName为用户dfa文件中的终结状态名，目的是让分析器知道该终结状态对应的是什么类别的词
### dfa文件
- 该文件为csv格式（以逗号为分隔符）
- 每行一个状态，第一个填写该状态的名称，第二个填写是否为终结状态（0非终结，1终结）
- 接下来一个出边，一个该出边到达的状态名称
- e.g. I0,0,a,I1,b,I0
- 对于, \t \n \r 空格，分别用comma, tab, lf, cr, space代替（区分大小写）
- 对于多个字符都对应同一个状态，或者除了某些字符外其余字符都可以到达同一个状态的特殊情况，提供了三种特殊方式：
    - lowerLetters: 代表从小写a到小写z
    - upperLetters: 代表从大写A到大写Z
    - ^... : 代表除了^后的字符以外的所有字符(必须含有其他字符，单独一个^将处理成普通字符)
- 注意：在运行时，程序读入一个字符优先判断特殊方式以外的情况，如有匹配则返回；特殊方式不能有重叠（如两种特殊方式都可以匹配同一个字符）；谨慎使用特殊方式

### parser-config.properties可配置项

- 该文件为csv文件
- lrTable.start：必需，指定LR Table中的开始状态名称
- lrActionTable.location：必需，指定LR Table的action表位置
- lrGotoTable.location：必需，指定LR Table的goto表位置
- grammar.location：必需，指定语法文件的位置
- ignoreWhiteSpace：是否忽略空格（指词法分析分析出的空格），不配置默认为false
- whiteSpace.name：如果配置了忽略空格，则需要指定词法分析器分析出的空格的Token的type名称，要与lexer-config.properties文件中的dfa.stateName配置项相符合，具体见上文
- fileEncoding：指定要解析的源文件的编码格式，不指定则默认UTF8

### LR Table

- Lr Action Table
  - 该文件为csv格式（以逗号为分隔符）
  - 每行一个状态，首先填写填写该状态的名称
  - 紧接着填写该状态经过哪些符号到达哪些状态，或者遇到哪些符号用什么来规约
    - 格式为：符号名，状态名或者语法名，1或者0或者2，（0表示移进，1表示规约，2表示accept状态）
    - e.g. I22,right-bracket,15,1,comma,I36,0
- Lr Goto Table
  - 该文件为csv格式（以逗号为分隔符）
  - 每行一个状态，首先填写该状态的名称
  - 紧接着填写该状态经过谁到哪些状态
    - e.g. I36,values,I41,value,I42,array,I28,object,I29

### Grammar文件

- 该文件为xml文件
- 根节点请使用\<grammar\>
- 每个表达式用\<expression\>标签

  - 需要为该标签配置id，用来在Lr Action Table中的规约项引用 (注意：对于增广的文法，最顶端的产生式的id固定设置为acc)

  - 该标签含有两个子标签

    - \<leftPart\>为产生式的左部
    - \<rightPart\>为产生式的右部
      - 其中右部的产生式中的终结符和非终结符请用[]包裹起来
- e.g. 

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<grammar>
    <expression id="acc">
        <leftPart>
            S
        </leftPart>
        <rightPart>
            [object]
        </rightPart>
    </expression>
    <expression id="1">
        <leftPart>
            object
        </leftPart>
        <rightPart>
            [left-brace][right-brace]
        </rightPart>
    </expression>
    <expression id="2">
        <leftPart>
            object
        </leftPart>
        <rightPart>
            [left-brace][objects][right-brace]
        </rightPart>
    </expression>
</grammar>
```

