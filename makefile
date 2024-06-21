BIN_DIR = bin
SRC_DIR = src
TEST_DIR = tests

CFLAGS  = -I$(SRC_DIR) -g -O3 -Wall -Wextra -flto -std=c17 -march=native
SRCS = $(shell find $(SRC_DIR) -type f -iname '*.c')
OBJS = $(SRCS:.c=.o)

.build: $(OBJS)

.classify: .build
	$(CC) $(CFLAGS) -o classify $(BIN_DIR)/classify.c $(OBJS) -lm

.convert: .build
	$(CC) $(CFLAGS) -o convert $(BIN_DIR)/convert.c $(OBJS) -lm

.extract: .build
	$(CC) $(CFLAGS) -o extract $(BIN_DIR)/extract.c $(OBJS) -lm

all: build
build: .classify .convert .extract

for tbuild: CFLAGS += -fsanitize=address -D LOG_TRACE
tbuild: .classify .convert .extract

for dbuild: CFLAGS += -fsanitize=address -D LOG_DEBUG -O0
dbuild: .classify .convert .extract

for test: CFLAGS += -fsanitize=address -D LOG_DEBUG -O0
test: .build
	gcc $(CFLAGS) -o test_runner $(TEST_DIR)/*.c $(OBJS) -lcriterion -lm
	./test_runner

clean:
	rm -f classify
	rm -f convert
	rm -f extract
	rm -f test_runner
