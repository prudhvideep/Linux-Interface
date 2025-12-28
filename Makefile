CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g

CFILE = tee.c
OFILE = tee

$(OFILE) : $(CFILE)
	$(CC) $(CFLAGS) $(CFILE) -o $(OFILE)

run:
	@./$(OFILE)

clean:
	rm -rf $(OFILE)
	rm -rf $(OFILE).dSYM