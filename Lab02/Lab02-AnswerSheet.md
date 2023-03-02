# Lab 02 Answer Sheet

> 姓名：周星达
> 学号：21373339

## 1. GCC

完成以下操作，每一个操作限用一条指令，且不能更改文件位置：

- 将 `./main.c` 编译为 `./main.o`（仅编译）

  > 指令：gcc -c ./main.c -I ./include

- 将 `./v1/dog.c` 编译为 `./v1/dog.o`（仅编译）

  > 指令：gcc -c ./v1/dog.c -I ./include -o ./v1/dog.o

- 将 `./v2/dog.c` 编译为 `./v2/dog.o`（仅编译）

  > 指令：gcc -c ./v2/dog.c -I ./include -o ./v2/dog.o

- 将 `./v1/dog.o` 与 `./main.o` 链接为 `./dog1`

  > 指令：gcc ./main.o ./v1/dog.o -o dog1

- 将 `./v2/dog.o` 与 `./main.o` 链接为 `./dog2`

  > 指令：gcc ./main.o ./v2/dog.o -o dog2

- 执行 `./dog1`

  > 指令：./dog1
  >
  > 输出结果：I'm a dog, my name is P-A-I-M-O-N.

- 执行 `./dog2`

  > 指令：./dog2
  >
  > 输出结果：I'm a really really beautiful dog, my holy name is P-A-I-M-O-N.

## 2. 静态和动态库的操作

#### 静态库

- 执行下面的命令

  ```shell
  ar cr libdog.a ./v1/dog.o
  gcc -o main main.o -L. -ldog
  ```

  说明上述两个命令完成了什么事？

  > ar cr libdog.a ./v1/dog.o:制作静态库
    gcc -o main main.o -L. -ldog:将目标代码文件 main.o 链接成最终可执行文件 main，并将当前目录添加至库文件搜索路径，编译时搜索dog库
  
- 查看`main`文件大小，并记录

  > -rwxr-xr-x 1 root root 16K  9月 19 19:30 main

- 执行`./main`
  
  > I'm a dog, my name is P-A-I-M-O-N.

- 执行以下命令：

  ```sh
  ar cr libdog.a ./v2/dog.o
  ./main
  ```

  和上面执行的结果有不同之处吗？

  > 重新生成main后结果为I'm a really really beautiful dog, my holy name is P-A-I-M-O-N.
    若不重新生成则和之前一样。

#### 动态库

- 执行下面的命令

  ```shell
  gcc -c -fPIC v1/dog.c -o v1/dog.o -I include
  gcc -c -fPIC v2/dog.c -o v2/dog.o -I include
  gcc -shared -fPIC -o libdog.so v1/dog.o
  gcc main.c libdog.so -o main -I include
  ```

- 查看 `main` 文件大小，并记录

  > -rwxr-xr-x 1 root root 16K  9月 19 19:45 main

- 执行`./main` 前，需要将库文件路径设置为当前路径：

  ```sh
  LD_LIBRARY_PATH=.
  export LD_LIBRARY_PATH
  ```

- 执行 `./main`
  > I'm a dog, my name is P-A-I-M-O-N.

- 执行以下命令：

  ```sh
  gcc -shared -fPIC -o libdog.so v2/dog.o
  ./main
  ```

  和上面执行的结果有不同之处吗？

  > I'm a really really beautiful dog, my holy name is P-A-I-M-O-N.

- 和静态库操作结果进行对比，同时分析 `main` 文件的大小，你能得出什么结论？

  > 连接动态库main更小，动态库可以节省空间且方便调试

## 3. GDB

（2）在 main 函数处设置断点（写出命令）

```
b 2
```

（7）在程序第 10 行加入断点（写出命令）

```
b 10
```

（10）使用 print 命令打印 i 和 factorial 的值（写出命令）

```
p i
p factorial
```

说明源程序中存在的错误。

> factorial未初始化

你更喜欢使用 printf 还是 gdb 调试？为什么？

> printf，因为方便且直观

## 4. make

`./Makefile` 文件内容：

```makefile
main: main.o fun2.o fun1.o ./lib/libdy.so
	gcc -o main ./src/main.o ./src/fun1.o ./src/fun2.o -L ./lib -ldy -I ./include

main.o: ./src/main.c 
	gcc -c ./src/main.c -I ./include -o ./src/main.o
fun1.o:./src/fun1.c ./include/fun1.h
	gcc -c ./src/fun1.c -o ./src/fun1.o -I ./include
fun2.o:./src/fun2.c ./include/fun2.h
	gcc -c ./src/fun2.c -o ./src/fun2.o -I ./include

clean:
	rm main
	rm ./src/main.o
	rm ./src/fun1.o
	rm ./src/fun2.o
```

`main` 可执行程序输出了什么？

```
hello world
this is fun1
this is fun2
HIDE AND SEEK, FIND YOU NEXT WEEK!
```



