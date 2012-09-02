include version.mk

SUBDIRS = src lib
.PHONY: subdirs $(SUBDIRS)

all: build

lib: src

subdirs: clean $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ build

clean:
	rm -fv lib/*so*
	make -C src clean

build: subdirs

install: subdirs
	mkdir -p $(DESTDIR)/usr/include $(DESTDIR)/usr/lib
	cp -r lib/*so*  $(DESTDIR)/usr/lib/
