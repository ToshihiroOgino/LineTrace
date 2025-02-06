CC = xc8-cc.exe
CFLAGS = -mcpu=18f2550 -std=c99

SRCDIR = ../src
OBJDIR = ./obj
BINDIR = ./bin

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(BINDIR))

TARGET = $(BINDIR)/emulate

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.p1)))
DEPENDS = $(OBJECTS:.p1=.d)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.p1: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: clean $(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
