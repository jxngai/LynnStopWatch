##########################################################
# Variables
##########################################################

CC=gcc
CC_CFLAGS =-c -Wall
CC_LFLAGS=
CC_INCLUDE_PATH=
CC_LIBRARIES=

CXX=g++
CXX_CFLAGS=-c -g -Wall
CXX_CFLAGS_EXTRA=`wx-config --cxxflags`
CXX_LFLAGS=

CXX_INCLUDE_PATH=

CXX_LIBRARIES=`wx-config --libs`

##########################################################
# Targets
##########################################################

OBJ_DIRECTORY=objs/
EXE=a.out

##########################################################
# Sources and Objects
##########################################################

vpath %.cpp .
vpath %.c .

CC_SOURCELIST = 

CXX_SOURCELIST = znApp.cpp
CXX_SOURCELIST += znDialogAbout.cpp
CXX_SOURCELIST += znFrame.cpp
CXX_SOURCELIST += znModel.cpp
CXX_SOURCELIST += znTimeThread.cpp
CXX_SOURCELIST += znControllerUi.cpp

CC_OBJECTLIST = $(addprefix $(OBJ_DIRECTORY), $(CC_SOURCELIST:.c=.o))

CXX_OBJECTLIST = $(addprefix $(OBJ_DIRECTORY), $(CXX_SOURCELIST:.cpp=.o))

##########################################################
# Compilation and Linking
##########################################################

$(EXE) : $(CXX_OBJECTLIST) $(CC_OBJECTLIST) $(CC_SOURCELIST)
	@echo ===============================================
	@echo === Linking $@
	@echo ===============================================
	$(CXX) -o $@ $(CXX_OBJECTLIST) $(CC_OBJECTLIST) $(CXX_LFLAGS) $(CXX_LIBRARIES)

$(OBJ_DIRECTORY)%.o : %.cpp %.h
	@echo ===============================================
	@echo === compiling $<
	@echo ===============================================
	@mkdir -p $(OBJ_DIRECTORY)
	$(CXX) $(CXX_CFLAGS) $(CXX_INCLUDE_PATH) $(CXX_CFLAGS_EXTRA) -o $@ $<

$(OBJ_DIRECTORY)%.o : %.c %.h
	@echo ===============================================
	@echo === compiling $<
	@echo ===============================================
	@mkdir -p $(OBJ_DIRECTORY)
	$(CC) $(CC_CFLAGS) $(CC_INCLUDE_PATH) $(CC_CFLAGS_EXTRA) -o $@ $<

##########################################################
# Clean
##########################################################
.PHONY : clean
clean:
	/bin/rm -f $(CXX_OBJECTLIST) $(CC_OBJECTLIST) $(EXE)
