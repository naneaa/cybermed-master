CC=g++
CFLAGS+= -DNDEBUG -Dlinux -DCYBTRACKER_H
LIBS = -lcybcore -lpthread -lcybview -lcybnetwork -lcybcollaboration -lrt -lglut -lGLU -lcybglove -lcybhaptics
INCLUDES = -I/usr/include/cybermed/of

TARGET=ClientGlove
HDRS=
SRCS=ClientGloveCollaboration.cpp cybHandModel.cpp myViewMono.cpp cybUpdate5dt14Model.cpp cybUpdate5dt5Model.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

