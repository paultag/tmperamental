c_files = $(wildcard *.c)
ok_files = $(addprefix out/,$(c_files:.c=.ok32) $(c_files:.c=.ok64))

preload = LD_PRELOAD=../out/libtmperamental.so
assert_aborted = [ $$? -eq 134 ]

.PHONY: all
all: $(ok_files)

%.ok32: %.exe32
	$(preload) $<; $(assert_aborted)
	touch $@

%.ok64: %.exe64
	$(preload) $<; $(assert_aborted)
	touch $@

out/%.exe32: %.c
	mkdir -p out
	$(CC) $(CFLAGS) $(CPPFLAGS) -U_FILE_OFFSET_BITS -Wall -o $@ $<

out/%.exe64: %.c
	mkdir -p out
	$(CC) $(CFLAGS) $(CPPFLAGS) -D_FILE_OFFSET_BITS=64 -Wall -o $@ $<

.PHONY: clean
clean:
	rm -rf out

.PRECIOUS: out/%.exe32 out/%.exe64
