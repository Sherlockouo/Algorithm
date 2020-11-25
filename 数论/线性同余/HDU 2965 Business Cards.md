[HDU 2965 Business Cards](http://acm.hdu.edu.cn/showproblem.php?pid=2965)
���⣺���� $a, b, c, d (1 <=a, b, c, d <= 10^9)$�����Ƿ��ܰ� $a \times b$ �Ŀ�Ƭ������ $c \times d$ ��ֽ�ϣ���ͼ��Ƭ�� $2 \times 3$��ֽ�Ŀ���� $9 \times 6$��
![���������ͼƬ����](https://img-blog.csdnimg.cn/img_convert/e7f9014c9abf4a92430d642d878ec202.png#pic_center)
��⣺��˿���룻
* 1����һ�������Ƿ��ֿ�Ƭ������ת����ô���ǿ��������άΪ $l ��long��$���̵�Ϊ $s��short��$���������һ��Ž�ȥ�Ŀ�Ƭһ���Ƕ������Ͻǵģ����Һ��ŷţ�Ȼ��ͨ��90����תֽ�ţ����Եõ��������������ͼ��ʾ��
![���������ͼƬ����](https://img-blog.csdnimg.cn/20201125082643791.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1doZXJlSXNIZXJvRnJvbQ==,size_16,color_FFFFFF,t_70#pic_center)
�ܹ��������������ʵ��һ������ $f(l, s, W, H);$ �����ж� $l \times s$ �Ŀ�Ƭ�Ƿ��ܹ��ŵ� $Width \times Height$ ��ֽ���棬��ô��ʵ���ǵ������������$f(max(a,b), min(a,b), c, d)$ �� $f(max(a,b), min(a,b), d, c)$ ����Ƭ���λ�ò��䣬��תֽ�ţ���

2���ڶ�������취����������䣬���Եó����¹�ʽ��
$$s*x + l*y = H\\
(x>=0,y>=0)$$
![���������ͼƬ����](https://img-blog.csdnimg.cn/20201125084238882.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1doZXJlSXNIZXJvRnJvbQ==,size_16,color_FFFFFF,t_70#pic_center)
3�����������������£�Ҳ����ͬ�����飬���Եó����¹�ʽ��
$$l*u + s*v = W\\
(u>=0,v>=0)$$
![���������ͼƬ����](https://img-blog.csdnimg.cn/20201125084730180.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1doZXJlSXNIZXJvRnJvbQ==,size_16,color_FFFFFF,t_70#pic_center)
4�����Ĳ���ʣ�¾�������ˣ��������Ͻǵ����½ǵ����Խ��߷�ʽ������䣬�ܹ�����ͼ���������
![���������ͼƬ����](https://img-blog.csdnimg.cn/20201125101328720.png#pic_center)
��1������ͼ��ʾ��$L$ �� $R$ ��ʵ��ͬһ�������Ҳ������Ҫ���� $W$ ������ $lcm(l,s)$ �ı������������� $lX+sY=H$ �зǸ������⣬�����������չŷ���������⣻
![���������ͼƬ����](https://img-blog.csdnimg.cn/20201125104239985.png#pic_center)

��2�������һ�������ֻ��Ҫ���� $H$ ������  $lcm(l,s)$ �ı�����
��3�������������ɫ�����沿��͹��Ĳ�����ƽ���ͱ������ ��2���������

#### �㷨
* 1��ֽ�ŵ�����ά�ȷֱ��ܹ�����Ƭ������ά����������ֱ����� $YES$��
* 2����������ֽ�ŵ�1��ά�� $W$ �ܹ��� $lcm(a,b)$ ����������һ��ά�� $H$ ���ڷ��̣�$ax+by=H$ �зǸ������⣬������չŷ��������󣬵õ���С�� x��y���ж� x �� y �Ƿ񶼴��ڵ��� 0������� YES������ NO��
