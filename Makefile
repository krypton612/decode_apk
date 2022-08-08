IDIR =include 
CC=c++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm -lncurses -lpthread

_DEPS=menu.h Menu.h MenuBar.h

DEPS= $(patsubst %,$(idir)/%,$(_deps))

_OBJ=main.o Menu.o MenuBar.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

decoder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
	rm -rf decoder $(ODIR)/*.o *~ core $(INCDIR)/*~

run: decoder
	./decoder
