# 设置 C 语言的编译器
CC = gcc

# -g 增加调试信息
# -Wall 打开大部分警告信息
CFLAGS = -g -Wall

SRC = $(wildcard *.c)
# wildcard 获取工作目录下的所有的.c文件列表

MAINOBJS = $(patsubst %.c, %.o, $(SRC))
# 将文件列表中所以.c文件替换为.o文件

.PHONY: clean run

all: $(MAINOBJS)
	gcc $^ -o prog

%.o: %.c
	gcc -c $< -o $@
# 所有的.o文件依赖于对应的.c文件。我们可以使用模式规则来定义隐含规则。

clean:
	rm -f $(MAINOBJS) prog
run:
	./prog

# $(wildcard PATTERN...)
# 在Makefile中，它被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表
# 如果不存在任何符合此模式的文件，函数会忽略模式字符并返回空

# patsubst函数用于将文件模式进行替换
# $(patsubst 原模式, 目标模式, 文件列表)

# 自动变量:
# $< 第一个依赖文件的名称
# $@ 目标文件的完整名称
# $* 不包含拓展名的目标文件名称
# $^ 所有不重复的依赖文件

# .PHONY用于声明一些伪目标, 伪目标与普通的目标的主要区别是
# 伪目标不会被检查是否存在于文件系统中而默认不存在且不会应用默认规则生成它
