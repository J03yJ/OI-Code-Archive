


**时间限制：** 1.0 秒 


**空间限制：** 512 MiB

**相关文件：** 题目目录




## 题目描述

给定正整数 $n$，求对于所有 $0\sim n-1$ 的排列 $a$，$\sum\limits_{0\le l\le r\le n-1}\operatorname{mex}(a_l,\cdots,a_r)$ 的最小值和最大值。

$\operatorname{mex}$ 的定义为集合中未出现的最小非负整数。也就是说 $\operatorname{mex}(S)=\min(n:n\in\mathbb{Z}_{\geq0},n\notin S)$。

仅给出最小值或最大值不得分。

## 输入格式 

从文件 *mex.in* 中读入数据。

一行一个数表示 $n$ 。

## 输出格式

输出到文件 *mex.out* 中。

两行输出，分别为原式的最小，最大值。








## 样例输入

```plain
5

```



## 样例输出

```plain
9
22

```


## 子任务

 
	


<table class="table table-bordered"><thead><tr><th rowspan="1">测试点</th><th rowspan="1">$n\le $</th></tr></thead><tbody><tr><td rowspan="1">$1$</td><td rowspan="1">$10$</td></tr><tr><td rowspan="1">$2,3$</td><td rowspan="1">$15$</td></tr><tr><td rowspan="1">$4,5$</td><td rowspan="1">$1000$</td></tr><tr><td rowspan="1">$6,7,8,9,10$</td><td rowspan="1">$1000000$</td></tr></tbody></table> 