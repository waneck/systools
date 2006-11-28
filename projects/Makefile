
PROJECT:=systools

NDLL:=../bin/linux/$(PROJECT).ndll

SRC_PATHS:=../src ../src/linux
SRCS:=$(foreach PATH,$(SRC_PATHS), $(wildcard $(PATH)/*.c))
HEADERS:=$(foreach PATH,$(SRC_PATHS), $(wildcard $(PATH)/*.h))

CC:=gcc -g -I../src
GTK_FLAGS:=$(shell pkg-config --libs --cflags gtk+-2.0)
NEKO_FLAGS:=-fPIC -shared -L/usr/lib -lneko -lz  -ldl


$(NDLL): $(SRCS) $(HEADERS)
	@echo srcs: $(SRCS), headers: $(HEADERS)
	$(CC) $(NEKO_FLAGS) $(GTK_FLAGS) -o $@ $(SRCS)
