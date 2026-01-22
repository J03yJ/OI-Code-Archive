{{ self.title() }}

{{ s('description') }}

> God is'nt in his heaven, all's wrong with the world.

上帝的信徒并非全部虔诚。

上帝的信徒有 $\frac{n\times (n+1)}{2}$ 个，其中只有 $k$ 个是虔诚的。

信徒排成 $n$ 层，第 $i$ 层有 $n-i+1$ 位信徒，即信徒们呈直角三角形排列（左对齐）。

上帝对人类的虚伪感到厌恶，TA决定对人类降下神罚，每次会选择一个全部由信徒构成的正方形降下神罚（单独一位信徒也是正方形）。

但为了不伤害虔诚的信徒，上帝不会选择包含虔诚信徒的正方形。

上帝想知道有多少种降下神罚的方案。

{{ s('input format') }} 

{{ self.input_file() }}

第一行两个数，$n$ 和 $k$，同题目描述。

接下来 $k$ 行，每行两个数，表示第 $k$ 个虔诚信徒在第 $i$ 列第 $j$ 层（$i+j\le n+1$）。

保证不会出现相同位置的信徒。

{{ s('output format') }}

{{ self.output_file() }}

一行一个数，表示上帝降下神罚的方案数，对 $998244353$ 取模。

{{ s('sample', 1) }}

{{ self.sample_text() }}

{{ img('1.png')}}

如图，黑点表示虔诚信徒，不包含黑点的正方形的个数为 $9$。

{{ s('sample', 2) }}

{{ self.sample_text() }}

{{ s('subtasks') }}

{{ tbl('data') }}
