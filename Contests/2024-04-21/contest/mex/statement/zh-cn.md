{{ self.title() }}

{{ s('description') }}

给定正整数 $n$，求对于所有 $0\sim n-1$ 的排列 $a$，$\sum\limits_{0\le l\le r\le n-1}\operatorname{mex}(a_l,\cdots,a_r)$ 的最小值和最大值。

$\operatorname{mex}$ 的定义为集合中未出现的最小非负整数。也就是说 $\operatorname{mex}(S)=\min(n:n\in\mathbb{Z}_{\geq0},n\notin S)$。

仅给出最小值或最大值不得分。

{{ s('input format') }} 

{{ self.input_file() }}

一行一个数表示 $n$ 。

{{ s('output format') }}

{{ self.output_file() }}

两行输出，分别为原式的最小，最大值。

{{ s('sample') }}

{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data') }}
