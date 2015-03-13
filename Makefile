dist = $(ROOT_DIR)/dist/$(1)

bin = $(ROOT_DIR)/dist/bin/$(1)

src = $(ROOT_DIR)/src/$(1)

root = $(ROOT_DIR)/$(1)

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

CXX := g++

CXXFLAGS := -Wall -Wno-uninitialized

BINARIES := fb

FULL_PATH_BINARIES := $(call bin,$(BINARIES))

.PHONY: setup clean

all: setup $(BINARIES)

fb_depends := utils.o FBPainter.o fb.o
fb: $(foreach file,$(fb_depends),$(call src,$(file)))
	$(CXX) $(CXXFLAGS) $^ -o $(call bin,$@)

setup:
	mkdir -p $(call bin,)

clean:
	rm -f $(call src,*.o)
	rm -rf \#*\#