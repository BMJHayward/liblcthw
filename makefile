CFLAGS=-g -02 -Wall -Wextra -Imain/src -rdynamic -DNDEBUG $(OPTFLAGS) 
LIBS=$(OPTLIBS) 
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c, %.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))


PROGRAMS_SRC=$(wildcard bin/*.c)
PROGRAMS=$(patsubst %.c,%,$(PROGRAMS_SRC))

TARGET=build/libdevpkg.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) tests $(PROGRAMS) #//default target is library if no other target given

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS) #//reat target makes build dir and compile OBJECTS
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build: #//makes /build or /bin if not exist
	@mkdir -p build
	@mkdir -p bin

#The Unit Tests
.PHONY: tests
tests: CFLAGS += -l $(TARGET)
tests: CFLAGS = $(filter-out -Wextra, -Wall)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

#The Cleaner
clean: #//removes everything compilers and tools leave, build and dSYM dirs apple XCode leaves also
	rm -rf build $(OBJECTS) $(TESTS) $(PROGRAMS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

#The Install
install: all
	install -d $(DESTRDIR)/$(PREFIX)/lib/ #//creates target lib if not exist
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/ #//creates program in target lib

#The Checker
#big REGEX to find bad C funcs like strcpy
BADFUNCS='[^_.>a-zA-z0-9] (str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check: #//lets me run a check whenever needed
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

$(PROGRAMS): CFLAGS += $(TARGET)
