# 物理实验数据处理器

该物理实验数据处理器可以进行不确定度ua，ub计算，以及线性拟合等基本物理实验数据处理功能

### 计算不确定度，实验标准差，平均值

进入界面后输入1进入该功能，依次输入想要处理的数据，输入任意非数字后可进行运算。运算结果包括（所有结果均保留六位小数）：

> 		平均值 	
>
> 	实验标准差 	
> 	A类标准不确定度ua 	
> 	B类标准不确定度ub 	
> 	合成标准不确定度uc
>
> 	完成后，可输入b退出到主界面。

### 通过最小二乘法线性回归

进入界面后输入2进入该功能，依次输入x的值，输入任意非数字后依次输入y的值，输入任意非数字后将显示运算结果。运算结果包括（所有结果均保留六位小数）：

> 斜率 
> y轴截距

完成后，可输入b退出到主界面。

#### 输入验证：

若x的数量和y的数量不一致时，会提示`x,y数量不相等`需退出后重新输入正确内容