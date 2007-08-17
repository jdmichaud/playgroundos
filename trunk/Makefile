# Makefile for Other kernel

ELF	= a.out
ISO	= other.iso
RFOLDER	= playground

all:
	cd kernel && make iso

clean:
	rm -fr other.iso
	rm -fr *~
	cd kernel && rm -fr *~ && rm -fr *.o &&	rm -fr a.out
	cd iso && rm -fr $(ELF)

re: clean all

tar: clean
	cd .. && \
	rm -i $(RFOLDER).tar.gz && \
	tar zcvf $(RFOLDER).tar.gz $(RFOLDER)