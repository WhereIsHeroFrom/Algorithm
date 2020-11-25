[HDU 2965 Business Cards](http://acm.hdu.edu.cn/showproblem.php?pid=2965)
题意：给定 $a, b, c, d (1 <=a, b, c, d <= 10^9)$，问是否能把 $a \times b$ 的卡片放置在 $c \times d$ 的纸上，如图卡片是 $2 \times 3$，纸的宽高是 $9 \times 6$。
![在这里插入图片描述](https://img-blog.csdnimg.cn/img_convert/e7f9014c9abf4a92430d642d878ec202.png#pic_center)
题解：抽丝剥茧；
* 1）第一步，我们发现卡片可以旋转，那么我们可以令长的那维为 $l （long）$，短的为 $s（short）$，可以令第一块放进去的卡片一定是顶着左上角的，并且横着放，然后通过90度旋转纸张，可以得到两种情况，如下图所示：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201125082643791.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1doZXJlSXNIZXJvRnJvbQ==,size_16,color_FFFFFF,t_70#pic_center)
总共两种情况，可以实现一个函数 $f(l, s, W, H);$ 代表判定 $l \times s$ 的卡片是否能够放到 $Width \times Height$ 的纸上面，那么其实就是调用两种情况：$f(max(a,b), min(a,b), c, d)$ 和 $f(max(a,b), min(a,b), d, c)$ （卡片相对位置不变，旋转纸张）；

2）第二步，想办法从左往右填充，可以得出如下公式：
$$s*x + l*y = H\\
(x>=0,y>=0)$$
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201125084238882.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1doZXJlSXNIZXJvRnJvbQ==,size_16,color_FFFFFF,t_70#pic_center)
3）第三步，从上往下，也做相同的事情，可以得出如下公式：
$$l*u + s*v = W\\
(u>=0,v>=0)$$
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201125084730180.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1doZXJlSXNIZXJvRnJvbQ==,size_16,color_FFFFFF,t_70#pic_center)
4）第四步，剩下就是填充了，按照左上角到右下角的主对角线方式进行填充，总共如下图三种情况：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201125101328720.png#pic_center)
（1）如下图所示，$L$ 和 $R$ 其实是同一种情况，也就是需要满足 $W$ 必须是 $lcm(l,s)$ 的倍数；并且满足 $lX+sY=H$ 有非负整数解，这里可以用扩展欧几里得来求解；
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201125104239985.png#pic_center)

（2）类比上一种情况，只需要满足 $H$ 必须是  $lcm(l,s)$ 的倍数；
（3）的情况，把绿色块上面部分凸起的部分铺平，就变成了了 （2）的情况；

#### 算法
* 1）纸张的两个维度分别能够被卡片的两个维度整除，则直接输出 $YES$；
* 2）必须满足纸张的1个维度 $W$ 能够被 $lcm(a,b)$ 整除，且另一个维度 $H$ 对于方程：$ax+by=H$ 有非负整数解，利用扩展欧几里得求解后，得到最小的 x，y，判断 x 和 y 是否都大于等于 0，则输出 YES，否则 NO；
