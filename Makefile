# Simple Makefile for quick compilation
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
LDFLAGS = -lGL -lGLEW -lglfw

SRCDIR = src
OBJDIR = obj
BINDIR = .

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/graphics-demo

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
