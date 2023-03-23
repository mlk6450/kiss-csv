RM=rm -f
CXX=g++
AR=ar
ARFLAGS=rcs
CPPFLAGS=

TEST_SRCS=test.cpp
TEST_OBJS=$(subst .cpp,.o,$(TEST_SRCS))
SRCS=csv.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
LIB=libcsv.a
INSTALL=/usr/local

.PHONY: all
all: lib

# Building

.PHONY: lib
lib: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

test: $(TEST_OBJS) $(OBJS)
	$(CXX) $(CPPFLAGS) $^ -o $@

# Installing

.PHONY: install
install: $(LIB)
	cp $(LIB) $(INSTALL)/lib
	cp csv.hpp $(INSTALL)/include

.PHONY: uninstall
uninstall:
	$(RM) $(INSTALL)/lib/$(LIB)
	$(RM) $(INSTALL)/include/csv.hpp

# Cleaning

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) $(TEST_OBJS)
	$(RM) $(LIB)
	$(RM) test

.PHONY: distclean
distclean: clean
	$(RM) *~ .depend

# Dependencies

.PHONY: depend
depend: .depend

.depend: $(SRCS) $(TEST_SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $(SRCS) >> ./.depend;
	$(CXX) $(CPPFLAGS) -MM $(TEST_SRCS) >> ./.depend;

include .depend