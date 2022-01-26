# VU MIF PS group 4 subgroup 2
# Student nr. 2110640
# mantas.vadopalas@mif.stud.vu.lt

CC = gcc 
CFLAGS = -Wall -Wextra
COMPILE = $(CC) $(CFLAGS) -c

PROGRAM = main
OBJS = m_io.o crossword.o m_string.o

INPUT_DIR_1 = input/1

build: $(PROGRAM).o $(OBJS)
	$(CC) $^ -o $(PROGRAM).exe

$(PROGRAM).o: $(PROGRAM).c
	$(COMPILE) $^ -o $@

m_io.o: m_io.c
	$(COMPILE) $^ -o $@

crossword.o: crossword.c
	$(COMPILE) $^ -o $@

m_string.o: m_string.c
	$(COMPILE) $^ -o $@

clean:
	rm -rf *.o *.exe

rebuild: clean build

run: build
	./$(PROGRAM).exe $(INPUT_DIR_1)/dictionary.txt $(INPUT_DIR_1)/matrix.txt

rerun: rebuild run