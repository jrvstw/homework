DIRS = $(sort $(dir $(wildcard /home/shiwulo/Dropbox/course/2017-sp/)))

all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done
show:
	echo ${DIRS}
