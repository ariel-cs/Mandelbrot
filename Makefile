CC = gcc
CFLAGS = -Wall -Wextra -fopenmp
SRC = $(wildcard source/*.c)
OBJDIR = objects
OBJ = $(patsubst source/%.c, $(OBJDIR)/%.o, $(SRC))
TARGET = mandelbrot

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: source/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o *.pgm times.txt

.PHONY: all clean
