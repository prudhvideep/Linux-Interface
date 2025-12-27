CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g

CFILES = $(wildcard *.c)
OFILE = my_tee

$(OFILE) : $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(OFILE)

run:
	@./$(OFILE)

clean:
	rm -rf $(OFILE)
	rm -rf $(OFILE).dSYM