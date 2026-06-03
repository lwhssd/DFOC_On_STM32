cmake_minimum_required(VERSION 4.3.3)   # 当前cmake要求最低版本号
project(demo C)    # hello生成的文件名 C代表工程所用的语言 
aux_source_directory(. SRCS)    # 搜索当前目录下所有源文件,保存到SRCS变量中
add_executable(demo ${SRCS})    # 最终生成的可执行文件以及其依赖