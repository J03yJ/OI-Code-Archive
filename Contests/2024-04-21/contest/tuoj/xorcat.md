


**时间限制：** 3.0 秒 


**空间限制：** 512 MiB

**相关文件：** 题目目录




## 题目描述

给一个长度为 $n$ 的序列，有 $m$ 个询问，疑惑猫每次会拍走不多于 $2$ 个元素，并给你个数 $k$ ，这是猫猫在考验你。你需要回答剩下元素的所有非空子序列异或和所构成集合的第 $k$ 小元素（集合是不可重集合，即求严格第 $k$ 小）。

猫猫会把拍走的元素放回原位再进行下一次考验。如果你回答错误，猫猫会 WA 地大叫一声。

## 输入格式

从文件 *xorcat.in* 中读入数据。

测试包含多组数据，第一行一个正整数 $T$，表示数据组数。

每组数据第一行包含两个正整数 $n,m$。

第二行 $n$ 个数描述序列，编号为 $i$ 的元素为 $v_i$。

接下来 $m$ 行，每行三个正整数 $a,b,k$ ，表示拍走编号为 $a$ 和 $b$ 的元素求第 $k$ 小。如果 $a=0$，表示猫猫没有拍走这个元素，$b$ 同理。如果 $a\not=0$ ，保证 $a\not= b$ 。猫猫保证严格第 $k$ 小存在，$k\ge 1$。

## 输出格式

输出到文件 *xorcat.out* 中。

每组数据输出 $m$ 行表示答案。








## 样例1输入

```plain
1
5 3
1 2 4 3 1
0 0 3
2 4 4
2 0 3

```



## 样例1输出

```plain
2
5
2

```




## 样例2

见题目目录下的 *2.in* 与 *2.ans*。

## 子任务

 
	


<table class="table table-bordered"><thead><tr><th rowspan="1">测试点</th><th rowspan="1">$n,m$</th><th rowspan="1">$v_i$</th><th rowspan="1">$a$</th><th rowspan="1">分值</th></tr></thead><tbody><tr><td rowspan="1">$1$</td><td rowspan="3">$\le 10^3$</td><td rowspan="1">$\le 10^3$</td><td rowspan="6">$\le n$</td><td rowspan="2">$5$</td></tr><tr><td rowspan="1">$2$</td><td rowspan="1">$=2^{p_i}$</td></tr><tr><td rowspan="1">$3,4$</td><td rowspan="1">$\le 10^{12}$</td><td rowspan="2">$10$</td></tr><tr><td rowspan="1">$5,6$</td><td rowspan="3">$\le 10^4$</td><td rowspan="1">$\le 10^3$</td></tr><tr><td rowspan="1">$7$</td><td rowspan="1">$=2^{p_i}$</td><td rowspan="1">$5$</td></tr><tr><td rowspan="1">$8,9,10$</td><td rowspan="2">$\le 10^{12}$</td><td rowspan="1">$15$</td></tr><tr><td rowspan="1">$11,12$</td><td rowspan="4">$\le 10^5$</td><td rowspan="1">$=0$</td><td rowspan="3">$10$</td></tr><tr><td rowspan="1">$13,14$</td><td rowspan="1">$\le 10^2$</td><td rowspan="3">$\le n$</td></tr><tr><td rowspan="1">$15,16$</td><td rowspan="1">$=2^{p_i}$</td></tr><tr><td rowspan="1">$17,18,19,20$</td><td rowspan="1">$\le 10^{12}$</td><td rowspan="1">$20$</td></tr></tbody></table> 

对于 $100\%$ 的数据，$T\le 5$ ，$\sum n,\sum m \le 2\times 10 ^5$，$0\le v_i\le10^{12}$ ，$0\le a,b \le n$。