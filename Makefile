CC ?= gcc
CFLAGS ?= -std=c89 -pedantic -Wall -Wextra

TARGET = hello
SRCS = main.c
OBJS = $(SRCS:.c=.o)

TEST_TARGET = test_hello
TEST_SRCS = test_hello.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

.PHONY: all clean distclean mrproper run test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TARGET) $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS) *.tmp

distclean: clean
	rm -f $(TARGET) $(TEST_TARGET)

mrproper: distclean
