.PHONY: all run clean depend

all:
	$(MAKE) -C src

run: all
	$(MAKE) -C src run

clean:
	$(MAKE) -C src clean

depend:
	$(MAKE) -C src depend
