#
#  $Id$
# 
PRG	= psud
CFLAGS	= -O2 -Wall -Werror

LDFLAGS	= -lgpio

HEADERS	= psud.h
SOURCES	= psud.c config.c
OBJECTS = psud.o config.o
BINDIR  = $(DESTDIR)$(PREFIX)/bin
ETCDIR  = $(DESTDIR)$(PREFIX)/etc
MANDIR  = $(DESTDIR)$(PREFIX)/share/man/man1

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

install:
	install -m 755 -s $(PRG) $(BINDIR)
#	install -m 755 etc/$(PRG) $(ETCDIR)/rc.d
	install -m 644 etc/$(PRG).conf $(ETCDIR)/$(PRG).conf.sample
