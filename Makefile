CC ?= gcc
CFLAGS ?= -std=c89 -pedantic -Wall -Wextra

TARGET = hello
SRCS = main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean distclean mrproper run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(TARGET)

mrproper: distclean
