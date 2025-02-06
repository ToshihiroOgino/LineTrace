CC = gcc
CFLAGS = -g -Wall -std=c99

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(BINDIR))

TARGET = $(BINDIR)/emulate

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

run:
	$(TARGET)
