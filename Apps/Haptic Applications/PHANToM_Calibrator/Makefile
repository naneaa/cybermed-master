CC=g++
CFLAGS+= -DNDEBUG -Dlinux
LIBS = -lglut -lcybutil -lpthread -lcybcore -lcybview -lcybhaptics -lrt 
INCLUDES = -I/usr/include/cybermed/of

TARGET=Calibrator
HDRS=
SRCS=main.cpp MenuHandler.cpp
OBJS=$(SRCS:.cpp=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET)

