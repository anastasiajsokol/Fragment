# Makefile for Fragment

TARGET = Fragment
SRC_FILES = main.cpp lexer/lexstream.cpp utility/standardlibrary.cpp datatype/programstate.cpp datatype/token.cpp datatype/block.cpp expression/lambdaexpression.cpp expression/conditionalexpression.cpp expression/operatorexpression.cpp expression/atomicexpression.cpp expression/selfexpression.cpp expression/defineexpression.cpp expression/functionexpression.cpp value/numericvalue.cpp value/booleanvalue.cpp value/functionvalue.cpp value/stringvalue.cpp value/value.cpp value/valuetype.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
	Q = 
else
	DEL = rm -f
	Q = "
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ -c $<

clean:
	$(DEL) -f $(TARGET) $(OBJECTS) Makefile.bak

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend
