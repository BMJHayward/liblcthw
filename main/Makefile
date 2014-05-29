CFLAGS=-g -O2 -Wall -Wextra -Isrc -Imain/src -rdynamic -DNDEBUG $(OPTFLAGS) 
#//optflags lets people augment build options
LIBS=-ldl $(OPTLIBS) 
# //options for linking libraries
PREFIX?=/usr/local
#//check this next line later to ex28 page
SOURCES=$(wildcard src/**/*.c src/*.c)
#//dynamically creates SOURCES variable
OBJECTS=$(patsubst %.c, %.o,$(SOURCES))
#//takes .c then conv to .o then assigns to OBJECTS

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))
#//same as line 6

PROGRAMS_SRC=$(wildcard bin/*.c)
PROGRAMS=$(patsubst %.c,%,$(PROGRAMS_SRC))

TARGET=build/libdevpkg.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))
#//same as line 6

# The Target Build
all: $(TARGET) $(SO_TARGET) tests $(PROGRAMS) #//default target is library if no other target given

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS) #//lack of NDEBUG gives me debug data from dbg.h
dev: all

$(TARGET): CFLAGS += -fPIC #//builds target library
$(TARGET): build $(OBJECTS) #//reat target makes build dir and compile OBJECTS
	ar rcs $@ $(OBJECTS) #//ar makes target
	ranlib $@ #//ranlib makes library

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build: #//makes /build or /bin if not exist
	@mkdir -p build
	@mkdir -p bin

#The Unit Tests
.PHONY: tests #//phony used so make will ignore any files named tests and run anyway
tests: CFLAGS += -l $(TARGET) #//links each test program to target library
tests: $(TESTS) #//builds tests
	sh ./tests/runtests.sh #//runs tests so you can see results

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

#The Checker//big REGEX to find bad C funcs like strcpy
BADFUNCS='[^_.>a-zA-z0-9] (str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check: #//lets me run a check whenever needed
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true 
#	//egrep to print output and not its command ||true prevents make from reporting failure if egrep doesn't find anything

$(PROGRAMS): CFLAGS += $(TARGET)
