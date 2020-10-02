src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS += -Wall -Werror -pedantic -std=c99

main: $(obj)
	${CC} ${CFLAGS} -o $@ $^

clean:
	rm -f $(obj) main

run: main
	./main