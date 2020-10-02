src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

CPPFLAGS += -pedantic -Wall -Werror -lm -lcrypt -O2 -std=c++11

main: $(obj)
	${CXX} ${CPPFLAGS} -o $@ $^

clean:
	rm -f ${obj} main
