CC=g++
CFLAGS+= -DNDEBUG -Dlinux -O3
LIBS = -lGLU -lglut -lpthread -lcybutil -lcybcore -lcybview -lcybassess -lrt 
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleFNB.exe
HDRS=
SRCS=SimpleFNB.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

