# 多文件包含头文件工程的编译
一共有四种方式

- 静态库

  - gcc src/*.c -o obj/\*.o

  - ar rcs arc/libmyxxx.a obj/*.o

  - gcc main.c -o main -L./arc -lmyxxx

    **-L 静态库所在路径**

- 动态库

  - gcc src/*.c -o obj/\*.o
  - gcc -shared obj/*.o -o ./so/libxxx.so
  - gcc main.c -o calc -L. -lxxx
  
  **可以把main.c *.h *so 放在同一个文件夹**
  - ？？ error while loading shared libraries: libCalc.so: cannot open shared object file: No such file or directory
  - && 配置系统环境变量或者当前用户环境变量
    - 系统环境变量
      - sudo vim /etc/profile **or** sudo vim /etc/environment
      - export LD_LIBRARY_PATH=&LD_LIBRARY_PATH:...
      - source /etc/profile **or** source /rtc/environment
    - 当前用户环境变量
      - vim ~/.profile **or** vim ~./bashrc
      - export LD_LIBRARY_PATH=&LD_LIBRARY_PATH:...
      - soucre ~/.profile **or** source ~/.bashrc

- gcc main.c obj/*.o -o main (-I./inc)

- makefile

  ```makefile
  .PHONY: main clear
  
  main:
  	gcc main.c obj/*.o -o main
  
  clean:
  	rm -rf obj/*.o
  ```

  