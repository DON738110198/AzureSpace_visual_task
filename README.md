# AzureSpace_visual_task
这是AzureSpace战队的视觉组任务

9.30 对任务有所了解，查看了各个组的学习路线，选择了视觉组这一更感兴趣的组，开始安装ubuntu，查看概论(csdn博客)。

10.1-10.4 节假日也有自己的亲戚要拜访，有对csdn的概论博客进行学习，到损失函数处，学习吴恩达深度学习，计算机视觉模块，p108-p118，对卷积网络这一块儿有个了解，同时在别的项目需要学习pytorch的内容，在b站的教程上也利用pytorch搭建神经网络有一点点认识。

10.5 完成了虚拟机上ubuntu的安装，暂时没有u盘，双系统的安装要等后续，暂时打算用windows先进行学习，以及招新任务的完成。且继续进行csdn概论博客的学习，感觉这个概论还挺有难度的，不是随意就能看完的，内容多且有一定难度。

10.6 受别的任务影响暂时休息

10.7 完成csdn上的概论博客的阅读

10.8-10.9 在B站看视频学习，链接如下：https://www.bilibili.com/video/BV1i54y1m7tw/?spm_id_from=333.337.search-card.all.click&vd_source=1d0a24ffce0fe2884625e6ca5538a425
但是觉得效果不是很好，而且讲课人水平确实不高，有些api根本也不讲就用了，决定换一下学习方式，想到了搜索OpenCV常用Api这种方式，找一下人家的博客，然后再遇到不会的就查相关的，同时记得要去实际操作写一下代码才行。
  
10.10-10.11 通过csdn掌握了常用api的使用，主要花了一些时间摸清楚了Mat的一些属性，之前比较迷惑的是Mat.depth()，返回的为什么不是深度，比如说8， 16，弄明白了返回的是一个宏定义的数字，而type()就是与channal()和depth向对应得到的一个宏定义的值，也不是想的那么简单。下一阶段准备开始着手招新任务了，最近也挺忙的。

10.12-10.13休息了两天

10.14-10.15 花了两天大概了解了一下任务提示给的二值化和HSV空间的内容，还了解了这个任务到底要怎么做，确定了是有相关的案例供参考的，说明解决这个问题应该不是特别难的事情，但是也不可能纯纯复制黏贴这么简单。
10.16 今天花了些时间终于把任务给完成了。尝试寻找直接的色块识别案例，但是csdn只找到python opencv的，找不到更理想的c++ opencv的案例，或许可以去阅读python的代码来找如何用c++来代替，但是我想先去GitHub上找找有没有c++的案例。GitHub上也没有C++的案例。
思路应该是这样的：先读取图片，将其转换为HSV格式，然后做二值化处理（先识别出色块在哪一块儿），然后再用函数(Canny二值化图像边缘检测函数，findContours查找轮廓函数)找到其轮廓，然后在原图上的位置画出来即可。
在操作过程中，本来是想利用Trackbar不断的动态调整HSV参数，来寻找最为合适的效果，但是在实现和测试Trackbar的功能的过程中，无意间调整出了极为合适的HSV值，但是想了想还是花多点时间把这个功能给完善了吧。
