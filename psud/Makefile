#
#  $Id$
# 
PRG	= psud
CFLAGS	= -O2 -Wall

LDFLAGS	= -lgpio

HEADERS	= psud.h
SOURCES	= psud.c config.c
OBJECTS = psud.o config.o

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
