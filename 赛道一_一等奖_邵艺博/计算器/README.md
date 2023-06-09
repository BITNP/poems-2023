# 计算器

这是一个计算器，采用C++编程，命令行界面，能实现以下功能。

### 四则运算、乘方、开方

支持加（+）减（-）乘（*）除（/）乘方（^）开方（\^0.5）

### 支持括号

可通过括号改变运算优先级，没有括号或在括号内则采用算数优先级

### 预定义函数

预定义sin（正弦），cos（余弦），tan（正切），ln（自然对数）的计算

### 预定义常数

可直接输入e和pi，计算器将自动替换为2.718281和3.141592

### 输入验证

可以检查算式是否正确
可以检查算式是否无意义(如除以零，零乘方零)

### 输入用例

| 输入用例                                  | 输出结果           | 解释                                                         |
| ----------------------------------------- | ------------------ | ------------------------------------------------------------ |
| `4-3*2`                                   | `-2`               | 计算器可进行运算                                             |
| `co scossi nt an((3.6-ln8^0 .5)  )*-1+pi` | `0.856549`         | 计算器可省略空格，并支持在函数括号内进行运算                 |
| `2(5)`                                    | `请输入正确的算式` | 输入时不可省略乘号，如`5e`，`3pi`是错误的，而`5*e`，`3*pi`是正确的 |
| `(3*(0^0)-6)+7`                           | `算式无意义`       | 计算器可以检查算式是否无意义                                 |
| `4-(3-2)-2)`                              | `请输入正确的算式` | 计算器可以检查算式括号是否完整                               |