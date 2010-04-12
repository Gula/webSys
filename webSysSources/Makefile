makefile:
### Configuration. ####################################################
# Default C compiler options:
CFLAGS = -Wall
COMPILER = gcc
WEBSYS_BIN_DIRECTORY = ../webSysBinaries

### Rules. ############################################################
all: webSysLib webSysClient

#--Client(CGI) and Server--
webSysClient: webSysClient.c cgiScriptHandle fileHandle localComms
	$(COMPILER) $(CFLAGS) webSysClient.c ../cgiScriptHandle.o ../fileHandle.o ../localComms.o \
	-o $(WEBSYS_BIN_DIRECTORY)/webSysClient.cgi

cgiScriptHandle: cgiScriptHandle.c cgiScriptHandle.h 
	$(COMPILER) $(CFLAGS) -c cgiScriptHandle.c -o ../cgiScriptHandle.o

webSysServer: webSysServer.c webSysAPI.h
	$(COMPILER) $(CFLAGS) -c webSysServer.c -o ../webSysServer.o
	
fileHandle: fileHandle.c fileHandle.h
	$(COMPILER) $(CFLAGS) -c fileHandle.c -o ../fileHandle.o
	
localComms: localComms.c localComms.h
	$(COMPILER) $(CFLAGS) -c localComms.c -o ../localComms.o

#--Custom Application--
webSysLib: fileHandle localComms webSysServer
	@ar	-cvq $(WEBSYS_BIN_DIRECTORY)/libwebSys.a ../fileHandle.o ../localComms.o ../webSysServer.o 			
	
#--Clean--
clean:
	-rm -f ../*.o $(WEBSYS_BIN_DIRECTORY)/libwebSys.a $(WEBSYS_BIN_DIRECTORY)/webSysClient.cgi 
