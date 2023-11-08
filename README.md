# MyWorldEdit

Forked from: [WorldEdit](https://github.com/firestaradmin/WorldEdit-No.1)

![微信图片_20231018185901](https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20231018185901.jpg)

![微信图片_20231105111314](https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20231105111314.jpg)



## 主要特点

按照个人习惯，使用了欧式大回车。保留了PageUp、PageDown、Home、End、F01-12、方向键等，可用于程序编码及调试。空格使用了两个2.25u按键，实际使用感受正常，没有局促感。右Shift在大回车情况下保留了惯用位置，影响了方向键原有的“山”字布局，变为倒“L”。实际使用需要适应。主要特点：

- USB、蓝牙双模；

- 分裂布局， 欧式大回车；

- 高特青柠轴（五脚轴，支持热插拔）；
- 使用钢珠缩短了键程（1.5mm触发键程），声音小；
- RGB灯效。



与原项目的不同：

- 重新设计了键列，按键数、按键排布均不同；

- 去掉Logo等效，按键灯效改为RGB灯珠。键盘正常使用中，RGB驱动代码有待完善；

- 键盘尺寸不同，宽度约为普通笔记本键盘宽度（具体尺寸可查看外壳3D模型），主要考虑办公桌布局的紧凑。



## 外观

定位板粘贴的是梵高的《星夜》局部，手动裁剪镂空的（也可用喷绘贴纸，需要设计图纸给商家制作）。

上盖板是透明的。为了表现完整的图案，可采用透明键帽+按键文字喷绘粘贴。

图示键帽为Eva初号机。



## 内部结构

内部结构简易设计，从底向上依次为：

外壳，电路板，定位板，键轴，键帽，透明上盖板

- 外壳、定位板、透明上盖板均设计了3D模型。

- Eva初号机XDA键帽一套。由于使用了两个2.25u空格，这套键帽不够用。提供了2.25u键帽的3D模型，可自行打印（光固化打印细腻一些）。也可购买散装2.25u键帽（XDA，15元）。

- 简便起见外壳使用Eva图案和纸封边。

机械键盘素来讲求敲击手感和声音。这套简易设计，完全依靠电路板和定位板缓冲敲击，实际上也有一定的弹性（其他比较有名的结构如Gasket）。声音上，不求动听；反而在键轴内加入钢珠，缩短了键程（大概是选用轴的最短触发键程，实在受不了长键程的机械轴），追求输入简洁明快，有剪刀脚按键的直爽。

追求精致的可以自行设计，3D打印各种结构件进行喷涂、组装。



## BOM

BOM套个娃，参考原BOM，不同如下：

- [高特青柠轴V2](https://s.click.taobao.com/t?e=m%3D2%26s%3DtKbL0qJKsY9w4vFB6t2Z2ueEDrYVVa64MljcGUdc4HdyINtkUhsv0EpwMQ354XKXxDQCrTVvs%2FEAoBAxpN3xFamlyyBMVmQ%2FQufxCFD6ZMi%2Fn%2FfA0hR8NJX%2B3e65p7B2OlGkMkr%2BSUUYmUGuVZn0uZfu1A2Skb7jxnD65IzEOnk56ZoUzm0cdngJMd2yjs373q5%2F6sUdbJLLri7Q0rsE5YV1e%2BOXuWE0H1AyRj8QnwkDFe%2FGR9FTRTEhRCycNlqjuMCdfWAoD%2BK0zvIVVx%2BPc2%2F51BzEHetfxglKFrfPmkzcL7X5oHxdwYWn14YY6K%2BAxBZpAxWPbHmiZ%2BQMlGz6FQ%3D%3D&union_lens=lensId%3APUB%401699358586%40213c9ff5_0db5_18ba9aa382d_3929%4001%40eyJmbG9vcklkIjozMTA2OSwiic3BtQiiI6Il9wb3J0YWxfdjJfdG9vbF9saW5rc19wYWdlX2hvbWVfaW5kZXhfaHRtIn0ie)（90颗75元）

- [凯华热插拔轴座](https://s.click.taobao.com/t?e=m%3D2%26s%3DVk8sZT5%2BZO1w4vFB6t2Z2ueEDrYVVa64Dm1dJ6eadalyINtkUhsv0EpwMQ354XKXo%2FW86nfUJtsAoBAxpN3xFamlyyBMVmQ%2FQufxCFD6ZMi%2Fn%2FfA0hR8NJX%2B3e65p7B2OlGkMkr%2BSUUYmUGuVZn0ufJMpambML4pLx7eJFO5qG2i1jMNxDhLMiTdqMDI4bn8A7nVLENk%2FnaraB%2BCkFT8P0gllb4ZEmR1vN38f%2B49U%2F0MOjc7Pu4gBVy3kYQPs4AO2sdAMu1BMwZweiXfaVH60dSopZirJ9MMCKlMHmtY2cGXgIVLfVsnfMYOae24fhW0&union_lens=lensId%3APUB%401699358449%4021083c5d_0d0c_18ba9a81ef0_dac0%4001%40eyJmbG9vcklkIjozMTA2OSwiic3BtQiiI6Il9wb3J0YWxfdjJfdG9vbF9saW5rc19wYWdlX2hvbWVfaW5kZXhfaHRtIn0ie)（100个60元）

- [Eva初号机XDA键帽](https://s.click.taobao.com/t?e=m%3D2%26s%3DO0AZ%2F829W%2Bxw4vFB6t2Z2ueEDrYVVa64MljcGUdc4HdyINtkUhsv0EpwMQ354XKXcEJyGEErK9AAoBAxpN3xFamlyyBMVmQ%2FQufxCFD6ZMi%2Fn%2FfA0hR8NJX%2B3e65p7B2OlGkMkr%2BSUUYmUGuVZn0ucMxv7P1pOZZQRyZ3xxTD7o56ZoUzm0cdngJMd2yjs373q5%2F6sUdbJIni%2FY7YcxT1G9F%2BClWRHECpl7CuhlrT91LCmX8dXvScpUj7cF6D9mTFfylQ%2BnXIf60zvIVVx%2BPc2%2F51BzEHetfi%2FWF8r7hEhOJogtH5z6nv89kxRRHfUqm&union_lens=lensId%3APUB%401699358257%40212c3e9e_0bec_18ba9a53030_4970%4001%40eyJmbG9vcklkIjozMTA2OSwiic3BtQiiI6Il9wb3J0YWxfdjJfdG9vbF9saW5rc19wYWdlX2hvbWVfaW5kZXhfaHRtIn0ie)（35元）

- [蓝牙模块](https://item.taobao.com/item.htm?spm=a1z10.3-c.w4002-3762557689.9.30383217tBDbVX&id=543840346810)（XM-04-HID-K，26元。原BOM型号找不到，实测可用）

- [直径1.3mm钢珠](https://s.click.taobao.com/t?e=m%3D2%26s%3D7Tjfx2PDBxpw4vFB6t2Z2ueEDrYVVa64Dm1dJ6eadalyINtkUhsv0EpwMQ354XKXgG5lVWr5qRUAoBAxpN3xFamlyyBMVmQ%2FQufxCFD6ZMi%2Fn%2FfA0hR8NJX%2B3e65p7B2OlGkMkr%2BSUUYmUGuVZn0uRWdpTjDP0nFMxsmiJWlZg2i1jMNxDhLMiTdqMDI4bn8A7nVLENk%2FnbYut6huiFrHhApBEubL1JRVlWA9YI5kfVW0L2mcBABBZCM0myIIplwKkWCUYfLo4tP7qa1tU3ZgS3jKrSQZrKgDyRZ4oVs79L3Bg7plXZ%2B4nEqY%2Bakgpmw&union_lens=lensId%3APUB%401699358698%40210810d8_0c8d_18ba9abebc5_37f5%4001%40eyJmbG9vcklkIjozMTA2OSwiic3BtQiiI6Il9wb3J0YWxfdjJfdG9vbF9saW5rc19wYWdlX2hvbWVfaW5kZXhfaHRtIn0ie)（改键程用。每个键轴需要2个，用[开轴器](https://s.click.taobao.com/t?e=m%3D2%26s%3D3BTua2fgN1Rw4vFB6t2Z2ueEDrYVVa64Dm1dJ6eadalyINtkUhsv0PRttJ5EH4vUoTX%2Fx%2Fte0DAAoBAxpN3xFamlyyBMVmQ%2FQufxCFD6ZMi%2Fn%2FfA0hR8NJX%2B3e65p7B2OlGkMkr%2BSUUYmUGuVZn0ueCPB9huRwv0o6LuHrMhPf%2Bi1jMNxDhLMiTdqMDI4bn8A7nVLENk%2FnZIJ5g6j46J%2B3eICuW3691W563%2B%2BPZPOsODvAOv16ZYur9KbWt1q2UOgkQCz1rKCgePgysBSxHfUOXVLEPDWL24nDKUyP%2B9AgMg%2B8%2B8b%2FI8miGFCzYOOqAQ&union_lens=lensId%3APUB%401699359087%402104fe10_14ca_18ba9b1db01_2ade%4001%40eyJmbG9vcklkIjozMTA2OSwiic3BtQiiI6Il9wb3J0YWxfdjJfdG9vbF9saW5rc19wYWdlX2hvbWVfaW5kZXhfaHRtIn0ie)开轴）

- [Eva初号机和纸](https://s.click.taobao.com/t?e=m%3D2%26s%3DmjkU1ivbj%2BVw4vFB6t2Z2ueEDrYVVa64Dm1dJ6eadalyINtkUhsv0EpwMQ354XKXPf5UY36GIs0AoBAxpN3xFamlyyBMVmQ%2FQufxCFD6ZMi%2Fn%2FfA0hR8NJX%2B3e65p7B2OlGkMkr%2BSUUYmUGuVZn0uQp2yuyvSLtOrwbHWKPC7eKMHuv7RoNv0YzeH%2FA0sTcbwojQWcmklDbtXVI0%2BNyrMiwqY%2B6cfbQT5wlruhbtXYMb0mghwtArPhjvnO7eDZqjk0qlf6P%2BqUWRmfcD0XF1fkPzJbJmoAt0Jvikr0oaNUb87xVc5XokVcYl7w3%2FA2kb&union_lens=lensId%3APUB%401699358969%40213cc8ed_0d02_18ba9b00ef5_82e8%4001%40eyJmbG9vcklkIjozMTA2OSwiic3BtQiiI6Il9wb3J0YWxfdjJfdG9vbF9saW5rc19wYWdlX2hvbWVfaW5kZXhfaHRtIn0ie)（13元）

- 外壳可交商家3D打印（80元）

- 定位板为亚克力板（平面开洞，20元）

- 上盖板为PVC透明板（平面开洞，40元）

- 电路板嘉立创制作（5块板130元）

电子元件参考电路图（eprj文件）。



## 组合键

FN+

- F6: USB/Bluetooth mode
- F7: VolumeDown
- F8: VolumeUp
- F9: Mute
- F10: PlayORPause
- F11: Stop

Menu+

- ScrollLock: Logo LED switch
- Delete: Delete Connect Info
- Insert: Pair Mode
- Home: Bluetooth Reset
- End: Bluetooth Sleep
- F12: LED Flash
- F11: LED Breath
- F3: LED Mode3
- F2: LED Mode2, wasd
- F1: LED Mode1, all
- +: LED Brightness+
- -: LED Brightness-
- Esc: LED turn off



## DIY Tips

可参考[知乎上一篇帖子](https://zhuanlan.zhihu.com/p/116182565)，客制化关键步骤：

- [设计键盘配列](http://www.keyboard-layout-editor.com/)
- 使用该配列[生成定位板](http://builder.swillkb.com/)（DXF文件）
- PCB电路板设计
- 使用该配列[生成固件](https://kbfirmware.com/)（QMK固件），或自行编写固件

通俗的理解是，`键盘配列`给出了你想要的键盘布局，包括每个按键的位置，每个按键的尺寸等。

根据`键盘配列`生成的`DXF文件` 给出了每个键轴的放置位置，也就是`定位板`。由于键轴要穿过`定位板`的开孔插在PCB电路板上，设计PCB时也需要该`DXF文件`，因为定位板的开孔与PCB的`轴座`位置是一一对应的。

使用配列生成[QMK固件](https://qmk.fm/zh-cn/)的步骤不是必须的，也可以自行编写固件。[QMK](https://qmk.fm/zh-cn/)是一个开源项目，[支持STM32和若干非STM32主控](https://docs.qmk.fm/#/platformdev_selecting_arm_mcu)。使用工具自动生成QMK固件需要用到`键盘配列`，用于生成键盘行列的连接（主控识别按键通常基于行列扫描）。

### 键盘配列

设计你的按键排布。

![image-20231107165947911](https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/image-20231107165947911.png)

设计输出可表示为文本形式的“Raw Data”，供后续步骤使用：

```
[{r:5,rx:8.75,ry:0.75,x:-7.25},"Esc","F1","F2","F3","F4","F5","F6"],
[{y:-0.5,x:-8.25},"Home"],
[{y:-0.5,x:-7.25},"~\n`","!\n1","@\n2","#\n3","$\n4","%\n5","^\n6"],
[{y:-0.5,x:-8.25},"Page\n\n\n\n\n\nUp"],
[{y:-0.5,x:-7.25,w:1.5},"Tab","Q","W","E","R","T"],
[{y:-0.5,x:-8.25},"Page\n\n\n\n\n\nDown"],
[{y:-0.5,x:-7.25,w:1.75},"Caps Lock","A","S","D","F","G"],
[{y:-0.5,x:-8.25},"End"],
[{y:-0.5,x:-7.25,w:2.25},"Shift","Z","X","C","V","B"],
[{y:-0.5,x:-8.25},"Win\n\n\n\n\n\nLock"],
[{y:-0.5,x:-7.25,w:1.25},"Ctrl",{w:1.25},"Win",{w:1.25},"Alt",{a:7,w:2.25},"",{a:4},"Menu"],
[{r:-5,rx:8.5,x:0.25},"F7","F8","F9","F10","F11","F12","PrtSc\nNmLk","Delete\nInsert"],
[{x:0.25},"&\n7","*\n8","(\n9",")\n0","_\n-","+\n=",{w:2},"Backspace"],
[{x:-0.25},"Y","U","I","O","P","{\n[","}\n]",{x:0.25,w:1.25,h:2,w2:1.5,h2:1,x2:-0.25},"Enter"],
["H","J","K","L",":\n;","\"\n'","|\n\\"],
[{x:0.5},"N","M","<\n,",">\n.","?\n/",{w:1.75},"Shift","↑"],
["Fn",{a:7,w:2.25},"",{a:4},"Alt","Ctrl","←","→","↓"]
```



### 定位板

这里使用的Switch Type是 `MX {_t: 1}`。不同Switch Type会影响开洞的尺寸和形状。

![image-20231107172618388](https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/image-20231107172618388.png)



### PCB电路板

嘉立创还是不错的，找元件、设计、打板一体化（也有贴片和3D打印等服务）。

注意，从电路设计就要注意按键轴座的设计了。通常有支持热插拔和非热插拔两种。热插拔轴座需要贴在电路板上，会增加键盘的厚度。非热插拔方式，键轴直接焊接在电路板上。

**不同厂家的轴（如高特、佳达隆、凯华等）通常不兼容**，特别是矮轴等特殊轴，不仅轴插座不兼容，键帽也不兼容（有十字、猪鼻子等）。这就意味着，如果想使用某种轴，**定位板、PCB轴座，从设计之初就应该确定**，找好配套。



### 固件

行列的硬件连接如下图，与PCB设计对应。

![image-20231108084853398](https://renhao-picgo.oss-cn-beijing.aliyuncs.com/img/image-20231108084853398.png)

基于原项目固件，按硬件连接做了对应改动。

在线配置生成QMK固件似乎也是可行方案。不建议新手使用这种方式。新手的主要问题是，各种细节的疏忽会导致DIY失败。围绕原项目或本项目进行微调，成功概率大。网络上公开的项目较多，但资源不完整，难以判断是否可用，难以学习和复现。至少这两个项目是证实可用的。
