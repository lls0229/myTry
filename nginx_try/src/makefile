# .PHONY: all

# all:$(OBJ_DIR)/lls_alloc.o $(OBJ_DIR)/lls_log.o

# $(OBJ_DIR)/lls_alloc.o: lls_alloc.c
# 	$(CC) -c $^ -o $@ $(CFLAG)

# $(OBJ_DIR)/lls_log.o: lls_log.c
# 	$(CC) -c $^ -o $@ $(CFLAG)

all: ../obj/lls_alloc.o ../obj/lls_log.o

../obj/lls_alloc.o: lls_alloc.c
	gcc -c lls_alloc.c -o ../obj/lls_alloc.o -Wall -g -I ../inc

../obj/lls_log.o: lls_log.c
	gcc -c lls_log.c -o ../obj/lls_log.o -Wall -g -I ../inc

# 这里的意思是将lls_alloc.c和lls_log.c编译成目标文件存放在obj文件。
