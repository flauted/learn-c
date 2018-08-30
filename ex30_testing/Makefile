CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LDFLAGS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
HEADERS=$(wildcard src/**/*.h src/*.h)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

PROGRAMS_SRC=$(wildcard bin/*.c)
PROGRAMS=$(patsubst %.c,%,$(PROGRAMS_SRC))

TARGET=build/libex29.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# Target
all: $(TARGET) $(SO_TARGET) tests $(PROGRAMS)

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TESTS): $(TARGET) $(SO_TARGET)

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rsc $@ $(OBJECTS)
	ranlib $@

# cc -ldl -shared -o build/libYOUR_LIBRARY.so src/libex29.o
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) $(LDFLAGS) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

$(TESTS):%:%.c
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(PROGRAMS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' 
check:
	@echo Files with potentially dangerous functions:
	@egrep $(BADFUNCS) $(SOURCES) || true

$(PROGRAMS): CFLAGS += $(TARGET)
