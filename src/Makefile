##
##
 
##SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
##OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
incdir := ../include
libdir := ../lib
bindir := ../bin
tstdir := ../test
##
##
##
###############################################################################
# Makefile for cpptest: socket test
CXX := g++
CC := gcc
AR := ar

CFLAGS := -I$(incdir) -g -Wall
CXXFLAGS :=-I$(incdir) -g -Wall
## additional:      for C++ compiler, standard threads: { -std=c++0x | -std=gnu++0x }
CPPFLAGS :=
LDFLAGS :=
LDLIBS :=
LDCCLIBS := 

## additional C, CXX FLAGS:   -fPIC
## additional LDFLAGS:        -D_REENTRANT -DGDD_DEBUG_O
## additional LDLIBS:         -lcppunit -lpthread -lm
## additional LDCCLIBS:       -lpthread

## -----------------------------------------------------------
## Setup exe targets with corresponding object files
PGM_C := $(bindir)/tst_hello
OBJS_1 := tst_hello.o hello.o

PGM_CC := $(bindir)/tst_regex
OBJS_CC := tst_regex.o gdd_regex.o


LSH_6 := $(libdir)/gddlib.so
OBJS_6 := gdd_regex.o


TST_7 := $(tstdir)/unittestname
OBJS_7 := unittestname.o anotherobj.o


exes := $(PGM_CC)
libs := $(LSH_6)
tests := $(TST_7)
## -----------------------------------------------------------
##cmdruntests := echo "running tests"$(foreach tst,$(tests),;LD_LIBRARY_PATH=../lib ./$(tst))
cmdruntests := echo "running tests"$(foreach tst,$(tests),; $(tst))
## -----------------------------------------------------------

bldexes: $(exes)
bldlibs: $(libs)
bldtests: $(tests)
all: $(exes)



## -----------------------------------------------------------
## build executable targets

$(PGM_C): $(OBJS_1)
	 @echo " $(CC) -o $@ $+ $(LDFLAGS) $(LDLIBS)"; $(CC) -o $@ $+ $(LDFLAGS) $(LDLIBS)

$(PGM_CC): $(OBJS_CC)
	 @echo " $(CXX) -o $@ $+ $(LDFLAGS) $(LDCCLIBS)"; $(CXX) -o $@ $+ $(LDFLAGS) $(LDCCLIBS)


$(TST_7): $(OBJS_7)
	@echo " $(CXX) -o $@ $+ $(LDFLAGS) $(LDLIBS)"; $(CXX) -o $@ $+ $(LDFLAGS) $(LDLIBS)


$(LSH_6): $(OBJS_6)
	@echo "$(CXX) -shared -Wl,-soname,$@ -o $@ $+"; $(CXX) -shared -Wl,-soname,$@ -o $@ $+


## -----------------------------------------------------------
## Build Object file targets ##

## compile c++ source:
%.o : %.c
	@echo " $(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<"; $(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

## compile c++ source:
%.o : %.cc
	@echo " $(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o $@ $<"; $(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

## -----------------------------------------------------------

clean:
	$(RM) *.o core $(tests)

realclean:
	$(RM) *.o core $(exes) $(libs) $(tests)

runtests:
	@$(cmdruntests)

print:
	echo "$(cmdruntests)"

.PHONY: clean realclean runtests
