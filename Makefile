CC=gcc
CFLAGS =  -w#-Wno-all
LDFLAGS = -lm
TARGET = noddy
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)
