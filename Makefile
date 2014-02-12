prefix		= /usr/
libdir		= ${prefix}/lib
pkglibdir	= ${libdir}/tmperamental
bindir		= ${prefix}/bin

LIBS		= out/libtmperamental.so
PROGRAMS	= out/tmperamental

all: build
build: ${LIBS} ${PROGRAMS}
clean:
	rm -rf out
install: all
	install -d ${DESTDIR}/${pkglibdir} ${DESTDIR}/${bindir}
	install -m 0644 ${LIBS} ${DESTDIR}/${pkglibdir}/
	install -m 0755 ${PROGRAMS} ${DESTDIR}/${bindir}/

.PHONY: all build clean install

out/libtmperamental.so: out/tmperamental.o
	${CC} ${LDFLAGS} -shared -Wl,--no-as-needed -ldl -o $@ $<
out/tmperamental.o: src/tmperamental.c
	install -d out
	${CC} ${CFLAGS} ${CPPFLAGS} -Wall -fPIC -DPIC -c -o $@ $<
out/tmperamental: src/tmperamental.in
	sed -e "s,@pkglibdir@,${pkglibdir},g" <$^ >$@
	chmod +x $@
