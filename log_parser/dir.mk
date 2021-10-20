
CXXSRCS = log_parser_server.cc log_parser_client.cc

DIR_CPPFLAGS = $(CORBA_CPPFLAGS)

CORBA_INTERFACES = log_parser

ifdef OSF1
ifeq ($(notdir $(CXX)),cxx)
NoTieExample = 1
endif
endif

log_parser_server    = $(patsubst %,$(BinPattern),log_parser_server)
log_parser_client    = $(patsubst %,$(BinPattern),log_parser_client)


all::  $(log_parser_server) $(log_parser_client)

clean::
	$(RM) $(log_parser_server) $(log_parser_client) 

$(log_parser_server): log_parser_server.o $(CORBA_STATIC_STUB_OBJS) $(CORBA_LIB_DEPEND)
	@(libs="$(CORBA_LIB_NODYN)"; $(CXXExecutable))

$(log_parser_client): log_parser_client.o $(CORBA_STATIC_STUB_OBJS) $(CORBA_LIB_DEPEND)
	@(libs="$(CORBA_LIB_NODYN)"; $(CXXExecutable))

