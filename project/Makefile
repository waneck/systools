
PROJECT:=systools

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	NDLL:=../ndll/Linux64/$(PROJECT).ndll
else
	NDLL:=../ndll/Linux/$(PROJECT).ndll
endif
OBJDIR=obj

SRC_PATHS:=src src/linux
C_SRCS:=$(foreach PATH,$(SRC_PATHS), $(wildcard $(PATH)/*.c))
CPP_SRCS:=$(foreach PATH,$(SRC_PATHS), $(wildcard $(PATH)/*.cpp))
C_OBJS:=${C_SRCS:.c=.o}
CPP_OBJS:=${CPP_SRCS:.cpp=.o}
OBJS:=$(C_OBJS) $(CPP_OBJS)

HEADERS:=$(foreach PATH,$(SRC_PATHS), $(wildcard $(PATH)/*.h))
HXCPP=$(shell haxelib path hxcpp | head -1)

CC:=g++ -Isrc
GTK_FLAGS:=$(shell pkg-config --libs --cflags gtk+-2.0)
GCONF_FLAGS:=$(shell pkg-config --libs --cflags gconf-2.0)
NEKO_FLAGS:=-fpic -fPIC -DHX_LINUX -DHXCPP_VISIT_ALLOCS -I$(HXCPP)/include -ldl -fvisibility=hidden -O2

CPPFLAGS += $(GTK_FLAGS) $(GCONF_FLAGS) $(NEKO_FLAGS)
CFLAGS += $(GTK_FLAGS) $(GCONF_FLAGS) $(NEKO_FLAGS)
LDFLAGS +=-fPIC -shared -L/usr/lib -lz -ldl -rdynamic -g3 -Xlinker --no-undefined $(GTK_FLAGS) $(GCONF_FLAGS)

all: $(NDLL)

clean:
	@- $(RM) $(NDLL)
	@- $(RM) $(OBJS)

$(NDLL): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NDLL) $(LDFLAGS)
