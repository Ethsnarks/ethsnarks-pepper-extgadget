all: build

build:
	mkdir -p build && cd build && cmake ../

git-submodules:
	git submodule update --init --recursive

