prefix		= /usr/local
libdir		= ${prefix}/lib
pkglibdir	= ${libdir}/tmperamental

LIBS		= out/libtmperamental.so

all: build
build: ${LIBS}
clean:
	rm -rf out
install: all
	install -d ${DESTDIR}/${pkglibdir} ${DESTDIR}/${bindir}
	install -m 0644 ${LIBS} ${DESTDIR}/${pkglibdir}/

.PHONY: all build clean install

out/libtmperamental.so: out/tmperamental.o
	${CC} ${LDFLAGS} -shared -Wl,--no-as-needed -ldl -o $@ $<
out/tmperamental.o: src/tmperamental.c
	install -d out
	${CC} ${CFLAGS} -fPIC -DPIC -c -o $@ $<
