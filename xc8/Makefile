XC = xc8-cc
XCFLAGS = -mcpu=18f2550 -std=c99 -mrom=default,-0-1FFF,-2006-2007,-2016-2017 -fasmfile -maddrqual=ignore -xassembler-with-cpp -Wa,-a -mcodeoffset=0x2000 -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -mstack=compiled:auto:auto:auto

SRCDIR = ../src
OBJDIR = ./obj
BINDIR = ./bin

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(BINDIR))

TARGET = $(BINDIR)/linetrace

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.p1)))
DEPENDS = $(OBJECTS:.p1=.d)

$(TARGET): $(OBJECTS)
	$(XC) $(XCFLAGS) -o $@ $^

$(OBJDIR)/%.p1: $(SRCDIR)/%.c
	$(XC) $(XCFLAGS) -c $< -o $@

all: clean $(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
