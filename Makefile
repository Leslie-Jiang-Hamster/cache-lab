csim: csim.o io.o util.o cachelab.o cache.o set.o

test-trans: test-trans.o trans.o cachelab.o

tracegen: tracegen.o trans.o cachelab.o

trans.o: trans.c

csim.o: csim.c common-types.h

io.o: io.c io.h common-types.h util.h

util.o: util.c util.h common-types.h cache.h

set.o: set.c set.h util.h common-types.h

cache.o: cache.c cache.h set.h util.h common-types.h

cachelab.o: cachelab.c cachelab.h

test-trans.o: test-trans.c

trans.o: trans.c

tracegen.o: tracegen.c

test: test.c util.c util.h io.c io.h common-types.h

clean:
	rm -rf *.o
	rm -f *.tar
	rm -f csim
	rm -f test-trans tracegen
	rm -f trace.all trace.f*
	rm -f .csim_results .marker
