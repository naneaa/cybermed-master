CC=g++
CFLAGS+= -DNDEBUG -Dlinux -O3
LIBS = -lglut -lGLU -lpthread -lcybutil -lcybcore -lcybview -lcybcollision -lrt 
INCLUDES = -I/usr/include/cybermed/mf

TARGET=SimpleCollisionCheck
HDRS=
SRCS=SimpleCollisionCheck.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

