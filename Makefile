.PHONY: clean

CC=clang
CFLAGS=-std=c99 -Wall -g 
OBJS=main.o list.o
TARGET=proj01

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	$(RM) $(OBJS) $(TARGET)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
