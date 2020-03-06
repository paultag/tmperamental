prefix		= /usr/
libdir		= ${prefix}lib
pkglibdir	= ${libdir}/tmperamental
bindir		= ${prefix}bin
mandir          = ${prefix}share/man

LIBS		= out/libtmperamental.so
PROGRAMS	= out/tmperamental

ifneq "$(filter Linux GNU%,$(shell uname))" ""
LDLIBS         += -ldl
endif

all: build
build: ${LIBS} ${PROGRAMS}
clean:
	rm -rf out tests/out
install: all
	install -d ${DESTDIR}/${pkglibdir} ${DESTDIR}/${bindir}
	install -m 0644 ${LIBS} ${DESTDIR}/${pkglibdir}/
	install -m 0755 ${PROGRAMS} ${DESTDIR}/${bindir}/
	install -d ${DESTDIR}/${pkglibdir} ${DESTDIR}/${mandir}/man1
	install -m 0644 doc/tmperamental.1 ${DESTDIR}/${mandir}/man1/

.PHONY: all build clean install

out:
	install -d out
out/libtmperamental.so: out/tmperamental.o out
	${CC} ${LDFLAGS} -shared -Wl,--no-as-needed ${LDLIBS} -o $@ $<
out/tmperamental.o: src/tmperamental.c out
	${CC} ${CFLAGS} ${CPPFLAGS} -Wall -fPIC -DPIC -c -o $@ $<
out/tmperamental: src/tmperamental.in out
	sed -e "s,@pkglibdir@,${pkglibdir},g" <$< >$@
	chmod +x $@
