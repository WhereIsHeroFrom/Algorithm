#### 题意
* N ( N <= 300 ) 个键值对排成一排，相邻两个键值对能被取出的条件是他们的键是不互素的，取出以后边上两个数靠在一起，并且累加积分为取出的两个键值对的值，求所有取出的值最大；

##### 输入
* 8
* 11 3 3 75 2 2 75 11
* 1 1 1 1 1 1 1 1

##### 输出
* 8

#### 题解
* 记忆化搜索/区间 DP

#### 题目分析
* 预处理区间，用 fit[i][j] 表示 第i个和第j个数的gcd是大于1的，sum[i][j] 表示区间和，canearse[i][j] 表示区间里的数在不借助其它区间的情况下是否能够完全消除；
* 那么当 fit[i][j] 为 true 的时候，
```math
    canearse[i][j] = canearse[l + 1][r - 1];
```
* canearse[i][j] 还有一种情况，就是通过一些小的区间组合而成，即：

```math
    canearse[i][j] = canearse[l][k] 与 canearse[k+1][r];
```

* dp[i][j]表示区间 [i, j] 的最优值，则有状态转移方程：

```math
dp[l][r] =
\begin{cases}
   sum[l][r] &\text{if } {canearse[l][r]} \\
   dp[l][k] + dp[k + 1][r] &\text{if } !canearse[l][r]
\end{cases}
```

