CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lglut -lGLU -lpthread -lcybcore -lcybview -lcybnetwork -lcybcollaboration -lrt -lcybutil
INCLUDES = -I/usr/include/cybermed/mf

TARGET=MouseCollaborationClient
HDRS=
SRCS=MouseCollaborationClient.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

