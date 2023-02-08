# .PHONY: all clean

# ##
# # PWD_DIR=$(shell pwd)  # 这里是执行shell的pwd命令获取路劲作为PWD_DIR参数
# # PWD_DIR=.
# # SRC_DIR=$(PWD_DIR)/src
# # OBJ_DIR=$(PWD_DIR)/obj
# # MAIN_DIR=$(PWD_DIR)/main
# # LIB_DIR=$(PWD_DIR)/lib
# # INC_DIR=$(PWD_DIR)/inc
# SRC_DIR=../src
# OBJ_DIR=../obj
# MAIN_DIR=../main
# LIB_DIR=../lib
# INC_DIR=../inc


# ##
# CC=gcc
# CFLAG=-Wall -g -I $(INC_DIR)

# ##
# export SRC_DIR OBJ_DIR MAIN_DIR LIB_DIR INC_DIR CC CFLAG
# # 这条语句把所以的目录路径导出，给子Makefile使用。

# ##
# all:
# 	make -C $(SRC_DIR)
# 	make -C $(MAIN_DIR)
# 	make -C $(OBJ_DIR)
# # make -C 目录   -------》  这就代表执行指定目录下的makefile
# # 所以这几条语句就是依次执行以下几个目录下的makefile

# ##
# clean:
# 	$(RM) -rf $(OBJ_DIR)/*.o
# 	$(RM) app
# # 这几条语句删除编译生成的目标文件和可执行文件app


.PHONY: all clean

all:
	make -C ./src
	make -C ./main
	make -C ./obj

clean:
	rm -rf ./obj/*.o
	rm -r app
