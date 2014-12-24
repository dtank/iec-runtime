EXECUTABLE := ../bin/generate_obj # 可执行文件名
INCLUDES := ../include # 头文件目录
LIBDIR := # 静态库目录
LIBS := # 静态库文件名
SRCDIR := # 除了当前目录外，其他的源代码文件目录

CC = g++
CXX = g++
CFLAGS = -std=c++0x
CPPFLAGS += $(CFLAGS) $(addprefix -I,$(INCLUDES))

RM-F = rm -f

SRCS := main_genobj.cc generator.cc
OBJS := $(patsubst %.cc,%.o,$(SRCS))


.PHONY : all clean rebuild

all: $(EXECUTABLE)

clean :
	@$(RM-F) *.o
	@$(RM-F) $(EXECUTABLE)

rebuild: clean all

$(EXECUTABLE) : $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
