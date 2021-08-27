# GameOfLife

## Introduction
Conway life game written in C++, you can customize the map.

## Using instructions
Install a C++ compiler (support C++11), cmake (>= 2.8.12), ninja-build
```bash
git clone https://github.com/cristime/GameOfLife.git
mkdir GameOfLife/build
cd GameOfLife/build
cmake .. -G Ninja # Can be omitted in the second run
ninja
```

For specific use, see the command line parameter description
```
$ ./GameOfLife --help
usage: ./GameOfLife [options] ... 
options:
  -l, --length       map length (int [=50])
  -h, --height       map height (int [=50])
  -t, --type         is rand map (bool [=1])
  -c, --config       config file path(if rand map disabled) (string [=])
      --useSleep     Use sleep instead of getchar (bool [=0])
      --sleepTime    Sleep time(ms) (if useSleep option enabled) (unsigned int [=500])
  -?, --help         print this message
```

## How to write Config file
Two positive integers in each row, representing the row and column where the living cell is located.

## Thank to Open Source
<a href="https://github.com/tanakh/cmdline">tanakh/cmdline</a>

## TODO
* ~~Use STL queue to optimize space complexity (optimized with STL map)~~