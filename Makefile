dist = $(ROOT_DIR)/dist/$(1)

bin = $(ROOT_DIR)/dist/bin/$(1)

src = $(ROOT_DIR)/src/$(1)

root = $(ROOT_DIR)/$(1)

ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

CXX := g++

CXXFLAGS := -Wall -Wno-uninitialized

BINARIES := fb

FULL_PATH_BINARIES := $(call bin,$(BINARIES))

all: $(BINARIES)

fb_depends := fb.o utils.o
fb: $(foreach file,$(fb_depends),$(call src,$(file)))
	$(CXX) $(CXXFLAGS) $^ -o $(call bin,$@)

clean:
	rm -f $(call src,*.o)
	rm -rf \#*\#