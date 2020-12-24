## 打包方法
- 在该项目下运行
```shell script
mvn package
```
> 注意：请使用JDK14及以上版本
## 使用方法
- 在SoftCodeLexer.jar所在文件夹下运行
```shell script
java -cp '.;SoftCodeLexer.jar' SoftCodeLexer.main.Main
```
## 配置说明
- 本程序必须要有名为lexer-config.properties的配置文件，并放置在classpath中
- 输入的dfa以csv文件格式存储，文件格式见后文
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