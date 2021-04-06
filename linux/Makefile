# Copyright (C) 2021 https://github.com/taviso/loadlibrary, GPLv2 License

# replace with the correct path to loadlibrary
LOADLIBRARY_DIR := ../../loadlibrary

INTERCEPTS_DIR  := $(LOADLIBRARY_DIR)/intercept
PELOADER_DIR    := $(LOADLIBRARY_DIR)/peloader

CFLAGS      := -O3 -march=native -ggdb3 -m32 -std=gnu99 -fshort-wchar -Wno-multichar -Iinclude -mstackrealign
CPPFLAGS    := -D_GNU_SOURCE -I. -I../common -I$(INTERCEPTS_DIR) -I$(PELOADER_DIR)
LDFLAGS     := $(CFLAGS) -m32 -lm
LDLIBS      := $(INTERCEPTS_DIR)/libdisasm.a -Wl,--whole-archive,$(PELOADER_DIR)/libpeloader.a,--no-whole-archive

.PHONY: clean peloader intercept

TARGETS := fpmatch | peloader

all: $(TARGETS)
	-mkdir -p faketemp

intercept:
	make -C $(INTERCEPTS_DIR) all

peloader:
	make -C $(PELOADER_DIR) all

$(INTERCEPTS_DIR)/hook.o: intercept

fpmatch: fpmatch.o $(INTERCEPTS_DIR)/hook.o | peloader
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) $(LDFLAGS)

clean:
	rm -f a.out core *.o core.* vgcore.* gmon.out fpmatch
	make -C $(INTERCEPTS_DIR) clean
	make -C $(PELOADER_DIR) clean
	rm -rf faketemp
