############# CC FLAGS ###############################
NAME = digital_signature.out
CC = g++
CPPFLAGS = -Wall -Wextra -g -std=c++98
DEFS = -DFIPS

############# ENVIRONMENT ###############################
OPENSSL_PREFIX ?= /usr/local/ssl
OPENSSL_LIBDIR ?= $(OPENSSL_PREFIX)/lib
OPENSSL_INCLUDEDIR ?= $(OPENSSL_PREFIX)/include
LIBCRYPTOSEC_PREFIX ?= /usr/local
LIBCRYPTOSEC ?= $(LIBCRYPTOSEC_PREFIX)/lib64/libcryptosec.so
LIBCRYPTOSEC_INCLUDEDIR ?= $(LIBCRYPTOSEC_PREFIX)/include/libcryptosec/
LIBP11_PREFIX ?= /opt/libp11
LIBP11_INCLUDEDIR ?= $(LIBP11_PREFIX)/include/

POPPLER_INCLUDEDIR1 := /usr/include/poppler/cpp/
POPPLER_INCLUDEDIR2 := /usr/include/poppler/
POPPLER_LIBFLAGS := -lpoppler-cpp -lpoppler

############ DEPENDENCIES ############################
LIBS = $(LIBCRYPTOSEC) -L$(OPENSSL_LIBDIR) -Wl,-rpath,$(OPENSSL_LIBDIR) -lcrypto -pthread $(POPPLER_LIBFLAGS)
DEPS_INCLUDES = -I$(OPENSSL_INCLUDEDIR) -I$(LIBCRYPTOSEC_INCLUDEDIR) -I$(LIBP11_INCLUDEDIR) -I$(POPPLER_INCLUDEDIR1) -I$(POPPLER_INCLUDEDIR2)

########### PROJECT DIRS #########################
SRCDIR := src
INCLUDEDIR := ./include
BUILDDIR := build
BINDIR := bin

########### OBJECTS ##################################
TARGET := $(BINDIR)/$(NAME)
SRCS := $(shell find $(SRCDIR) -name *.cpp)
HDRS := $(shell find $(INCLUDEDIR) -name *.h)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

########### AUX TARGETS ##############################
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS) | $(BUILDDIR)
	@echo Compiling $<
	$(CC) $(CPPFLAGS) $(DEFS) $(DEPS_INCLUDES) -I$(INCLUDEDIR) -O0 -Wall -c -o "$(BUILDDIR)/$(notdir $@)" "$<"

$(TARGET): $(OBJS) | $(BINDIR)
	@echo Linking $@
	$(CC) $(CPPFLAGS) $(DEFS) -o $(TARGET) $(addprefix $(BUILDDIR)/,$(notdir $(OBJS))) $(LIBS)
	@echo 'Build complete!'

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

########### TARGETS ##################################
all: $(TARGET)

run: 
	@$(TARGET) DOCUMENTO-TESTE.pdf

checkmem:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt $(TARGET) DOCUMENTO-TESTE.pdf

check:
	@echo $(OBJS)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

cldata:
	rm -rf ./data

.PHONY: all check clean run

