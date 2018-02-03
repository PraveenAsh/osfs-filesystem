COMPILER = gcc
FILESYSTEM_FILES = osfs.c

build: $(FILESYSTEM_FILES)
	$(COMPILER) $(FILESYSTEM_FILES) -o osfs `pkg-config fuse --cflags --libs`
	
clean:
	rm osfs
