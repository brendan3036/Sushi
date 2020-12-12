SOURCE = $(wildcard *.c)
OBJS = $(SOURCE:.c=.o)
HEADER = $(wildcard *.h)
OUT = sush
ZIP = submission.zip
ZIP_INC = Makefile $(HEADER) $(SOURCE)
CC = gcc
FLAGS = -g -Wall

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUT)

clean:
	rm -f $(OBJS) $(OUT) $(ZIP)

zip:
	zip $(ZIP) $(ZIP_INC)
