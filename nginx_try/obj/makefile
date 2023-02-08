# obj/ 即是object的缩写，主要存放的就是目标文件，一些可重定向文件，如.o文件

# OBJ=$(wildcard *.o)

# $(PWD_DIR)/app: $(OBJ)
# 	$(CC) -o $@ $^



../app: *.o
	gcc -o ../app *.o

# 将所以的目标文件编译成可执行文件app放在PWD_DIR目录下.wildcard解释如下
