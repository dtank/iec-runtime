EXECUTABLE := ../bin/iec-runtime    # 可执行文件名
LIBDIR := ../lib/xenomai            # 静态库目录
LIBS := native xenomai pthread_rt           # 静态库文件名
INCLUDES := ../include ../include/xenomai # 头文件目录
SRCDIR := ./libsys# 除了当前目录外，其他的源代码文件目录

CC = arm-none-linux-gnueabi-g++
CXX = arm-none-linux-gnueabi-g++
CFLAGS := -std=c++0x
CPPFLAGS += $(CFLAGS) $(addprefix -I,$(INCLUDES))

RM-F := rm -f

SRCS := $(wildcard *.cc) $(wildcard $(addsuffix /*.cc, $(SRCDIR)))
OBJS := $(patsubst %.cc,%.o,$(SRCS))

.PHONY : all clean rebuild

all: $(EXECUTABLE)

clean :
	@$(RM-F) *.o
	@$(RM-F) $(EXECUTABLE)

rebuild: clean all

$(EXECUTABLE) : $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
