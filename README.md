# GameOfLife

## 介绍
使用 C++ 编写的 Conway 生命游戏，可以自定义地图。

## 使用方法
安装一个 C++ 编译器（支持 C++11），cmake（>= 2.6）
```bash
git clone https://github.com/cristime/GameOfLife.git
mkdir GameOfLife/build
cd GameOfLife/build
cmake ..
make
```
```
$ GameOfLife -?
usage: GameOfLife [options] ...
options:
  -l, --length    map length (int [=50])
  -h, --height    map height (int [=50])
  -t, --type      is rand map (bool [=1])
  -c, --config    config file path(if type is 0) (string [=])
  -?, --help      print this message
```

## 如何编写 Config 文件
每行两个正整数，分别代表活细胞所在的行和列

## 开源项目使用
<a href="https://github.com/tanakh/cmdline">tanakh/cmdline</a>

## TODO
* 使用队列优化空间复杂度
* 优化 Config Generator