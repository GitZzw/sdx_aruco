## 使用matlab完成单目相机标定的方法


#### 使用相机直连电脑matlab中进行标定  [参考1](https://www.pianshen.com/article/75561503832/)  [参考2](https://blog.csdn.net/panpan_jiang1/article/details/80414737)

#### 使用获取到的图像进行标定  [参考](https://www.codetd.com/article/5655938)

> 由于matlab报错不支持该款usb相机，所以先在ubuntu下获取图像，如图，再拷贝到电脑matlab上进行标定
![image.png](https://i.loli.net/2020/11/22/gLkChP5x2BSEFR9.png)
> 注意填写的是棋盘格的每一格的实际物理尺寸

> 最后得到相机内参矩阵
![image.png](https://i.loli.net/2020/11/22/1skhvlmCLaQgN5E.png)
