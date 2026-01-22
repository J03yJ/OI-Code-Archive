


**时间限制：** 2.0 秒 


**空间限制：** 512 MiB

**相关文件：** 题目目录




## 题目描述

> God is'nt in his heaven, all's wrong with the world.

上帝的信徒并非全部虔诚。

上帝的信徒有 $\frac{n\times (n+1)}{2}$ 个，其中只有 $k$ 个是虔诚的。

信徒排成 $n$ 层，第 $i$ 层有 $n-i+1$ 位信徒，即信徒们呈直角三角形排列（左对齐）。

上帝对人类的虚伪感到厌恶，TA决定对人类降下神罚，每次会选择一个全部由信徒构成的正方形降下神罚（单独一位信徒也是正方形）。

但为了不伤害虔诚的信徒，上帝不会选择包含虔诚信徒的正方形。

上帝想知道有多少种降下神罚的方案。

## 输入格式 

从文件 *kami.in* 中读入数据。

第一行两个数，$n$ 和 $k$，同题目描述。

接下来 $k$ 行，每行两个数，表示第 $k$ 个虔诚信徒在第 $i$ 列第 $j$ 层（$i+j\le n+1$）。

保证不会出现相同位置的信徒。

## 输出格式

输出到文件 *kami.out* 中。

一行一个数，表示上帝降下神罚的方案数，对 $998244353$ 取模。








## 样例1输入

```plain
4 2
2 3
3 1
```



## 样例1输出

```plain
9
```


 <img src="kami/1.png" alt="img"/> 

如图，黑点表示虔诚信徒，不包含黑点的正方形的个数为 $9$。








## 样例2输入

```plain
15 7
1 1
15 1
1 6
2 4
4 1
4 2
6 3
```



## 样例2输出

```plain
264
```


## 子任务

 
	


<table class="table table-bordered"><thead><tr><th rowspan="1">测试点</th><th rowspan="1">$n\le $</th><th rowspan="1">$k\le $</th></tr></thead><tbody><tr><td rowspan="1">$1,2$</td><td rowspan="1">$500$</td><td rowspan="1">$18$</td></tr><tr><td rowspan="1">$3,4,5$</td><td rowspan="1">$3000$</td><td rowspan="1">$15$</td></tr><tr><td rowspan="1">$6,7$</td><td rowspan="1">$300000$</td><td rowspan="1">$8$</td></tr><tr><td rowspan="1">$8,9$</td><td rowspan="1">$10^6$</td><td rowspan="2">$0$</td></tr><tr><td rowspan="1">$10,11$</td><td rowspan="3">$10^{12}$</td></tr><tr><td rowspan="1">$12\sim 17$</td><td rowspan="1">$20$</td></tr><tr><td rowspan="1">$18\sim 25$</td><td rowspan="1">$75$</td></tr></tbody></table> 