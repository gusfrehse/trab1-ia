CC 			:= gcc
CFLAGS 		:= -Wall
LDFLAGS		:=
RM			:= rm -rf

BINARY 		:= solve

SOURCEDIR	:= source
BUILDDIR 	:= build
INCLUDEDIR 	:= include

SOURCES 	:= $(shell find $(SOURCEDIR) -name '*.c')
OBJECTS		:= $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
BUILDSDIRS	:= $(sort $(patsubst $(SOURCEDIR)/%, $(BUILDDIR)/%, $(dir $(SOURCES))))

.PHONY : all clean purge

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c | $(BUILDSDIRS)
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -c $< -o $@

$(BUILDSDIRS):
	mkdir -p $@

debug: CFLAGS += -g
debug: all

clean:
	$(RM) $(OBJECTS)

purge:
	$(RM) $(OBJECTS) $(BINARY) $(BUILDDIR)

