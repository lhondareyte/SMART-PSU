#
#  $Id$
# 
PRG	= buttond
CFLAGS	= -O2 -Wall 

LDFLAGS	= -lgpio

HEADERS	= $(shell ls *.h)
SOURCES	= $(shell ls *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))

$(PRG): $(OBJECTS)
	@printf "Linking   $@:"
	@$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $@
	@printf "\tdone.\n"

clean:
	@rm -f  $(OBJECTS) $(PRG) *~

.c.o:
	@printf "Compiling $<:"
	@$(CC) $(CFLAGS) -Os -c $< -o $@
	@printf "\tdone.\n"
