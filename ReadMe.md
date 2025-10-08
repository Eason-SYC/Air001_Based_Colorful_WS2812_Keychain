# 基于Air001的彩灯钥匙扣

<h1 style="margin-bottom:0.5em"><strong>个人主页</strong></h1>
<div style="background-color:#f3e5f5;border-left:5px solid #ab47bc;padding:15px;margin-top:0;margin-bottom:1.5em;border-radius:14px">
<p style="margin:0">
<a href="https://space.bilibili.com/106438109">B站-沈已成</a><br />
<a href="https://github.com/Eason-SYC">Github-Eason-SYC</a>
</p>
</div>

<h1 style="margin-bottom:0.5em"><strong>💌 项目介绍</strong></h1>
<div style="background-color:#f3f8ff;border-left:5px solid #4285F4;padding:15px;margin-top:0;margin-bottom:1.5em;border-radius:14px">
<p style="margin-top:0">这不仅是一个可以亮灯的钥匙扣，还实现了炫酷的动画效果，你甚至可以在上面玩游戏！</p>
该项目基于极具性价比的Air001芯片，整体尺寸（含3D外壳）仅有**2.5cm * 3.5cm**，小巧便携，软件基于 Arduino IDE 开发，拥有极低的入门门槛，代码结构清晰，对初学者和小白非常友好。

* 硬件成本低，将更多的注意力放在了软件上。它不仅仅可以亮灯，还实现了炫酷的动画效果，甚至可以在上面玩游戏。

* 小巧便携，该钥匙扣的大小仅为2.5cm * 3.5cm（包含3D外壳）

* 电源管理：精确检测电池电量，而且充电可触发充电动画

* 二次开发：资料完善，软硬件全开源，喜欢什么图案可以自己DIY设计，非常浪漫的礼物

  </div>
# **🕹 项目功能**
<div style="background-color:#eaf7ed;border-left:5px solid #2e8b57;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>💡 动画效果</strong></h2>

* 火焰效果：实现动态逼真的火焰燃烧效果。
* 流星雨：随机生成颜色各异的流星，带有优雅的拖尾渐隐效果。
* 彩虹渐变：丝滑的全屏彩虹渐变，色彩过渡自然，且性能经过优化。
* 彩虹心形：在正确的心形图案上实现整体彩虹色的平滑呼吸渐变。
* 跳动的心：经典的大小交替心形图案，模拟心跳效果。

<div style="display:flex;justify-content:center;gap:15px">
  <img src="https://image.lceda.cn/oshwhub/pullImage/522570defc4a4bd5a022bd61314b6bbc.gif" alt="火焰.gif" style="max-width:45%" />
  <img src="https://image.lceda.cn/oshwhub/pullImage/47d46da7596d4fe299c1eb5eb5f977b1.gif" alt="流星雨.gif" style="max-width:45%" />
</div>

## **🎮 复古游戏 (Game)**

* 动态菜单图标：所有游戏在选择菜单中都设计了独特的动态Logo
* 贪吃蛇 (Snake)：经典的贪吃蛇游戏，支持四向控制，详细操作方法参照 **使用手册** 章节
* 弹珠游戏 (Pinball)：可控制的挡板，物理反弹的小球，每次被挡板反弹后小球都会加速
* 生命游戏 (Game of Life)：康威生命游戏的经典模拟，可作为一种程序化的屏保。

<div align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/4b86e0e3fd4541359bd9f2ab4a3fa66d.gif" alt="贪吃蛇.gif" />
</div>

## **🖼️ 静态图片 (Picture)**

内置多种像素画

* 修猫
* 桃子
* 爱心
* 小鸭
* 剑
* 修勾


<div style="display:flex;justify-content:center;gap:15px">
  <img src="https://image.lceda.cn/oshwhub/pullImage/2e0e03bf36b0409d9edced0787a4b3c6.jpg" alt="桃子" style="max-width:45%" />
  <img src="https://image.lceda.cn/oshwhub/pullImage/309dec38575145f38b8ecec7cfc23da3.jpg" alt="剑" style="max-width:45%" />
</div>

## **🆎 字母 (Letter)**

显示26个字母

<div align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/8ace738f6fc04653b632d39415c43363.gif" alt="字母.gif" />
</div>

## **🔢 数字 (Letter)**

显示10个数字

<div align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/32a219786d014a3ab9d2284d280da356.gif" alt="数字.gif" />
</div>

## **🔧 工具 (Tool)**

* 亮度调节：支持五级亮度调节，拥有直观的UI界面。
* EEPROM掉电保存：亮度设置后会自动保存在EEPROM中，断电重启后无需重新设置。

<div align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/7a61c2f348944233ae06a22b0a75d0e5.gif" alt="工具.gif" />
</div>

## **🔋 电源管理 (Power Management)**

* 电量检测：ADC电池检测电路。
* 充电动画：基于硬件引脚状态变化检测，接入USB即显示充电动画。
* 电量显示：在非游戏状态下，可随时通过左右组合键查看当前电量，不同电量等级对应不同电量格数。

<div style="display:flex;justify-content:center;gap:15px">
  <img src="https://image.lceda.cn/oshwhub/pullImage/8b83b443706f40809d464b6ba033d38a.gif" alt="火焰.gif" style="max-width:45%" />
  <img src="https://image.lceda.cn/oshwhub/pullImage/ddcc6f776ea34bb1b99d95f9728af69d.gif" alt="流星雨.gif" style="max-width:45%" />
</div>

</div>

# **🔍 原理解析（硬件说明）**

<div style="background-color:#fff3e0;border-left:5px solid #f39c12;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>主控Air001</strong></h2>

钥匙扣主控选择的是Air001，我一直对这个芯片很感兴趣，合宙公司的 **32位芯片**，虽然引脚少了一点，但成本这么低而且功能齐全，还要啥自行车。

* **成本巨低** 在淘宝上可以单买，不算上邮费的话大概是五毛钱一颗芯片，现在好像涨价了。
* **易焊接** 芯片封装为TSSOP-20，焊接难度很低。
* **开发** 主流可以使用Keil、Arduino开发，资料很齐全，即使是初学者也可以很快的上手，[官方资料链接](https://wiki.luatos.com/chips/air001/index.html)

![Air001.png](https://image.lceda.cn/oshwhub/pullImage/c005e3e3e11e47caa797fe1742e106b4.png)

## **灯珠矩阵**
钥匙扣的主体是由64颗WS2812彩灯（2020封装）组成的8x8矩阵，焊接的时候有点难度，可以用低温锡膏配合热风枪。

* **供电方案：** 整个灯珠矩阵由3.7V锂电池直接供电。经过实测，在这一电压下，WS2812灯珠能够被有效驱动，亮度表现出色，同时也简化了电源部分的电路设计，无需额外的升压（Boost）电路。

* **驱动协议与控制：** 控制引脚选择了PA7，使用SPI协议驱动，彩灯的驱动代码我封装到了Arduino库中，可以直接调用使用，库的名称是 [WS2812_SYC_Air001](https://github.com/Eason-SYC/WS2812_SYC_Air001)，想要学习底层驱动的可以通过链接直接参考代码源文件

* **PCB布局：** 在PCB设计阶段，灯珠矩阵的物理排布采用了特定的 “Z”字形布局。这种布局决定了从灯珠0到灯珠63的线性索引与其在二维矩阵中的 (x, y) 坐标之间的映射关系，二次开发时需要特别注意，这样才能在代码中精确控制亮起哪些灯。

![8x8灯珠.png](https://image.lceda.cn/oshwhub/pullImage/3ce1ccf3529f4e60b6c99adee68f44c6.png)

## **调试接口**
为了节省体积，选了ZX-SH1.0-6P封装，调试的时候需要一条转接线

![转接线.jpg](https://image.lceda.cn/oshwhub/pullImage/c153c22e423341fd82ed73c50a2cf550.jpg)

<p align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/ed9fb3bcbf8148daac6b595f1ed427b7.png" alt="调试接口" width="300" />

## **单开关电路**

使用拨动开关非常容易损坏，使用自锁开关又有点占体积，因此最后选择了使用单开关电路，效果还不错
![开关.png](https://image.lceda.cn/oshwhub/pullImage/e55419722b52433f988b326114c5117e.png)

## **Type-c**
选择了6pin贴片Type-c，现在最常用的接口，方便充电，使用6pin也比较好焊接。
</p><p align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/d9536dbeb0c84872a665ac0577790e24.png" alt="Type-C 接口图" width="500" />
</p>

## **按键**

钥匙扣有左右两个按键，电路中并没有过多的处理。因此在代码中需要配置为上拉输入
<p align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/94002f6b18fd4ef3b102b9e0225b0aeb.png" alt="按键" width="500" />
</p>

## **锂电池充电电路**

使用CL4064M，封装为SOT-23-5，焊接难度低，还有一个引脚可以检测是否在充电
<p align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/70218eab73324cc897232661a46685d8.png" alt="充电电路" />
</p>

</div>

# **📖 使用手册**

钥匙扣有三个开关，分别是左按键、电源开关、右按键
按键只设置了单击和长按这两种方式

<div style="background-color:#fffbeb;border-left:5px solid #d97706;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>主菜单</strong></h2>

在主菜单中可以切换不同的一级菜单，分别为动画、游戏、图片、字母、数字、工具

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：确认
    - 长按：无效果
    

</div>
    

<div style="background-color:#fce7f3;border-left:5px solid #db2777;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>💡 动画效果</strong></h2>

可以切换不同的动画效果，分别为火焰、彩虹灯、跳动的心、流星雨

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：无效果
    - 长按：退回到主菜单

</div>

<div style="background-color:#e0e7ff;border-left:5px solid #4f46e5;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>🎮 复古游戏</strong></h2>

可以切换不同的游戏，分别为弹珠游戏、贪吃蛇、康威生命游戏

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：无效果
    - 长按：退回到主菜单

### **弹珠游戏**
游戏失败时，点击任意键重新开始

* 左键：
    - 单击：挡板左移一格
    - 长按：无效果
* 右键：
    - 单击：挡板右移一格
    - 长按：退回到主菜单

### **贪吃蛇**
游戏失败时，点击任意键重新开始
以下描述的方向的参考系均为钥匙扣本身
**当蛇头朝左时**
* 左键：
    - 单击：蛇头朝下转
    - 长按：无效果
* 右键：
    - 单击：蛇头朝上转
    - 长按：退回到主菜单

**当蛇头朝右时**
* 左键：
    - 单击：蛇头朝下转
    - 长按：无效果
* 右键：
    - 单击：蛇头朝上转
    - 长按：退回到主菜单

**当蛇头朝上时**
* 左键：
    - 单击：蛇头朝左转
    - 长按：无效果
* 右键：
    - 单击：蛇头朝右转
    - 长按：退回到主菜单

**当蛇头朝下时**
* 左键：
    - 单击：蛇头朝左转
    - 长按：无效果
* 右键：
    - 单击：蛇头朝右转
    - 长按：退回到主菜单
    
### **康威生命游戏**

康威的生命游戏无需操作，会在最后趋向于一个平衡的状态
    
* 左键：
    - 单击：无效果
    - 长按：无效果
* 右键：
    - 单击：无效果
    - 长按：退回到主菜单
    

</div>

<div style="background-color:#fdf2f8;border-left:5px solid #f472b6;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>🖼️ 静态图片</strong></h2>

可以切换不同的图片，分别为修猫、桃子、爱心、小鸭、剑、修勾

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：无效果
    - 长按：退回到主菜单

</div>

<div style="background-color:#fefce8;border-left:5px solid #facc15;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>🆎 字母</strong></h2>

可以切换不同的字母，共26个

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：无效果
    - 长按：退回到主菜单

</div>
    
<div style="background-color:#f0fdfa;border-left:5px solid #14b8a6;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>🔢 数字</strong></h2>

可以切换不同的数字，共10个

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：无效果
    - 长按：退回到主菜单

</div>
    
<div style="background-color:#fff7ed;border-left:5px solid #fb923c;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>🔧 工具</strong></h2>

可以切换不同的亮度，共5档

* 左键：
    - 单击：切换
    - 长按：无效果
* 右键：
    - 单击：确认并保存亮度
    - 长按：退回到主菜单，不保存

</div>

<div style="background-color:#fafde8;border-left:5px solid #8ca107;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>🔋 电量检测</strong></h2>

在非游戏运行中的状态下时，同时按下左右键可以显示当前电量，共有5档，电量显示3s后恢复之前的状态
    
</div>

# **注意事项**

<div style="background-color:#fdfaf6;border-left:5px solid #a16207;padding:15px;margin:1.5em 0;border-radius:14px">

<h2 style="margin-top:0"><strong>锂电池</strong></h2>

<p style="margin-top:0">电池推荐购买602025,3.7V锂电池</p>

有三种方法连接电池，都需要有一定的动手能力

1、购买带接头的电池，购买对应的母线，将母线焊接在PCB上并连接电池
2、购买不带接头的电池，购买对应的母线和公线，将公线焊接在电池上，并将母线焊接在PCB上并连接电池
3、购买不带接头的电池，并直接将电池焊接在PCB上，最方便但不推荐，线容易断，打个胶的话那就没问题

记得把电池线中裸露的金属部位用电工胶布捆一捆，避免出现短路情况
    
## **遮光板**

实际上使用的时候，灯光会比较闪，因此可以买1mm厚的遮光板来让效果更好（照片中没有安装），遮光板的厚度在设计外壳时有考虑到，会有一个槽

</div>

# **实物图**

<div style="background-color:#f7fee7;border-left:5px solid #84cc16;padding:15px;margin:1.5em 0;border-radius:14px">

<div style="display:flex;justify-content:center;gap:15px">
  <img src="https://image.lceda.cn/oshwhub/pullImage/7ad3733a0219443faafaa42838bb6f50.jpg" alt="结构图" style="max-width:45%" />
  <img src="https://image.lceda.cn/oshwhub/pullImage/f792a43bbdfb4c58ae9e57d4fccb2671.jpg" alt="实物图" style="max-width:45%" />
</div>

<div align="center">
  <img src="https://image.lceda.cn/oshwhub/pullImage/9cedc78f9a1d415e9c8c32e98090d87b.gif" alt="实物图.gif" />

</div>
</div>

# **硬件清单**

<div style="background-color:#eaf7ed;border-left:5px solid #2e8b57;padding:15px;margin:1.5em 0;border-radius:14px">

遮光板（1mm）、钥匙扣、602025锂电池、PCB、3D外壳（表壳）、3D外壳（背壳）
    
</div>

# **烧录步骤**

<div style="background-color:#f3e5f5;border-left:5px solid #ab47bc;padding:15px;margin-top:0;margin-bottom:1.5em;border-radius:14px">

持续更新中
    
</div>

# **脚本使用方法**

<div style="background-color:#f3f8ff;border-left:5px solid #4285F4;padding:15px;margin-top:0;margin-bottom:1.5em;border-radius:14px">
持续更新中
</div>

