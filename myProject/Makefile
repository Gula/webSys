makefile:
### Configuration. ####################################################
# Default C compiler options:
export CFLAGS = -Wall
export COMPILER = gcc

# List of header files included in webSysAPI.c, separated by spaces:
# e.g.: API_HEADER_FILES = header1.h header2.h header3.h
API_HEADER_FILES = demo.h
# Path to webSys source files:
WEBSYS_SRC_DIRECTORY = ../webSysSources
# Path to webSys bin files:
export WEBSYS_BIN_DIRECTORY = ../webSysBinaries
# The name you choose for the executable:
MY_EXECUTABLE_FILE = ../webSysDemo

### Rules. ############################################################

all: webSysAPI myProcess
	$(COMPILER) $(CFLAGS) ../webSysAPI.o ../demo.o -o \
	$(MY_EXECUTABLE_FILE) -L$(WEBSYS_BIN_DIRECTORY) -lwebSys

myProcess: demo.c demo.h 
	$(COMPILER) $(CFLAGS) -c demo.c -o ../demo.o -I$(WEBSYS_SRC_DIRECTORY)	
	
webSysAPI: webSysAPI.c $(WEBSYS_SRC_DIRECTORY)/webSysAPI.h $(API_HEADER_FILES)
	$(COMPILER) $(CFLAGS) -c webSysAPI.c -o ../webSysAPI.o -I$(WEBSYS_SRC_DIRECTORY)

webSysLib:
	$(MAKE) all -C $(WEBSYS_SRC_DIRECTORY)
	
#--Clean--
clean:
	-rm -f ./*.o $(MY_EXECUTABLE_FILE)
	$(MAKE) clean -C $(WEBSYS_SRC_DIRECTORY)