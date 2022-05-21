
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/lifeGame

SRC= main.c game.c model.c worldControl.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)
all:
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c game.h model.h worldControl.h
game.o:  game.c game.h model.h worldControl.h
model.o: model.c game.h model.h worldControl.h
worldControl.o: worldControl.c game.h model.h worldControl.h
