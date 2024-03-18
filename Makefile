# Compiler
CC = gcc
# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Liste des fichiers source
SRCS = main.c student.c books.c emprunt.c

# Liste des fichiers objets correspondants
OBJS = $(SRCS:.c=.o)

# Cibles
TARGET = proj

# Règles de compilation
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Règle générique de compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(TARGET)
