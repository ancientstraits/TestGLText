OBJS := $(patsubst src/%.c,obj/%.o,$(wildcard src/*.c))
CFLAGS = -g -ggdb -Iinclude -Llib -Wall
LDFLAGS = -lGLEW -lglfw -lGL
EXEC = main
DEPS = $(wildcard include/*.h)

all: $(EXEC)

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJS) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)