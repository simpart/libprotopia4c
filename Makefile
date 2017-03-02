TARGET := protopia
CFILES := $(shell find * -name "*.c")
OFILES := $(shell find * -name "*.o")
OBJS   := $(patsubst %.c, %.o, $(CFILES))
SRCS   := $(filter-out .git% doc% bin%, $(CFILES))
DEPS   := $(shell find * -name "*.d")

CC       := gcc
CFLAGS   := -O3 -MMD -MP -Wall -Wextra
INCLUDES := -I./src/hdr
LDFLAGS  :=

all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) $(LDFLAGS)

clean: 
	@rm -rf $(TARGET) $(OFILES) $(DEPS)
