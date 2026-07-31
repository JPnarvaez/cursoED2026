CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
SRCS = src/avl.c src/destino.c src/menu.c src/pasajero.c src/viaje.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = terminal_portuario

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
