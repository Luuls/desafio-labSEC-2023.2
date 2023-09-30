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
LIBP11_PREFIX ?= /opt/libp11/
LIBP11_INCLUDEDIR ?= $(LIBP11_PREFIX)/include/

############ DEPENDENCIES ############################
LIBS = $(LIBCRYPTOSEC) -L$(OPENSSL_LIBDIR) -Wl,-rpath,$(OPENSSL_LIBDIR) -lcrypto -pthread
INCLUDES = -I$(OPENSSL_INCLUDEDIR) -I$(LIBCRYPTOSEC_INCLUDEDIR) -I$(LIBP11_INCLUDEDIR)

########### PROJECT DIRS #########################
SRCDIR := src
INCLUDEDIR := include
BUILDDIR := build
BINDIR := bin

########### OBJECTS ##################################
TARGET := $(BINDIR)/$(NAME)
SRCS := $(shell find $(SRCDIR) -name *.cpp)
OBJS := $(SRCS:.cpp=.o)

########### AUX TARGETS ##############################
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(DEFS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"

.comp: $(OBJS)
	$(CC) $(CPPFLAGS) $(DEFS) -o $(NAME) $(OBJS) $(LIBS)
	@echo 'Build complete!'

########### TARGETS ##################################

all: .comp

check:
	@echo $(SRCS)

clean:
	rm -rf *.o $(NAME)

