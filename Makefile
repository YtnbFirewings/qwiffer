SHELL := /bin/sh
.SUFFIXES:
.SUFFIXES: .c .cpp .o
BIN_DIR := bin/
SRC_DIR := src/
OBJ_DIR := obj/
QWIFFER_OBJS := BasicTypes BasicTypesReader SWFCompressor SWFReader SWFStruct SWFTags
ZLIB_DIR := $(SRC_DIR)zlib-1.2.8/
ZLIB_LIB := $(ZLIB_DIR)libz.a
LZMA_OBJS := 7zFile 7zStream Alloc LzFind LzmaDec LzmaEnc LzmaLib
LZMA_DIR := $(SRC_DIR)lzma920/C/Util/Lzma/
LZMA_LIB := $(LZMA_DIR)liblzma.a
LIBS := $(ZLIB_LIB) $(LZMA_LIB)
OBJS = $(OBJ_DIR)Main.o $(foreach obj,$(QWIFFER_OBJS),$(OBJ_DIR)$(obj).o)
CXX := g++
CC := gcc
DEBUG ?= 1
CXX_FLAGS := -Wall -std=c++11 -g
CC_FLAGS := -Wall -std=c++99 -g
L_FLAGS := -Wall -std=c++11 -g
MAKE_CXX_OBJ = $(CXX) $(CXX_FLAGS) -c $< -o $@
MAKE_CC_OBJ = $(CC) $(CC_FLAGS) -c $< -o $(OBJ_DIR)$@
MAKE_BIN = $(CXX) $(L_FLAGS) $(OBJS) $(LIBS) -o
ifeq ($(DEBUG),1)
OBJ_DIR := $(OBJ_DIR)Debug/
BIN_DIR := $(BIN_DIR)Debug/
else
OBJ_DIR := $(OBJ_DIR)Release/
BIN_DIR := $(BIN_DIR)Release/
CXX_FLAGS += -O3
CC_FLAGS += -O3
L_FLAGS += -O3
endif

ifeq ($(.DEFAULT_GOAL),)
.DEFAULT_GOAL := all
endif

all : check_dir $(BIN_DIR)Qwiffer

$(BIN_DIR)Qwiffer : $(OBJS)
	$(MAKE_BIN) $@

rebuild : clean all
rebuildAll : remake_static_libs rebuild

ifeq ($(OS),Windows_NT)
check_dir: obj\Debug obj\Release bin\Debug bin\Release
obj\Debug :
	mkdir obj\Debug
obj\Release :
	mkdir obj\Release
bin\Debug :
	mkdir bin\Debug
bin\Release :
	mkdir bin\Release
clean :
	del /F "obj\Debug\*.o"
	del /F "obj\Release\*.o"
ZLIB_LIB := $(SRC_DIR)zlib-1.2.8/zlib.lib
remake_static_libs :
	"C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\SetEnv.cmd" &\
	pushd "src\zlib-1.2.8" &\
	nmake /f "win32\Makefile.msc" clean &\
	nmake /f "win32\Makefile.msc" &\
	popd
else
check_dir: obj/Debug/ obj/Release/ bin/Debug/ bin/Release/
obj/Debug/ :
	mkdir -p obj/Debug/
obj/Release/ :
	mkdir -p obj/Release/
bin/Debug/ :
	mkdir -p bin/Debug/
bin/Release/ :
	mkdir -p bin/Release/
clean :
	rm -f obj/Debug/*.o
	rm -f obj/Release/*.o

remake_static_libs :
	make -C $(ZLIB_DIR) clean
	make -C $(ZLIB_DIR)
	make -C $(LZMA_DIR) -f makefile.gcc clean
	make -C $(LZMA_DIR) -f makefile.gcc
	ar -rcs $(LZMA_DIR)liblzma.a $(foreach obj,$(LZMA_OBJS),$(LZMA_DIR)$(obj).o)
endif

$(OBJ_DIR)Main.o : $(SRC_DIR)Main.cpp $(SRC_DIR)SWFReader.h
	$(MAKE_CXX_OBJ)

$(OBJ_DIR)BasicTypes.o : $(SRC_DIR)BasicTypes.cpp $(SRC_DIR)BasicTypes.h
	$(MAKE_CXX_OBJ)

$(OBJ_DIR)BasicTypesReader.o : $(SRC_DIR)BasicTypesReader.cpp $(SRC_DIR)BasicTypesReader.h
	$(MAKE_CXX_OBJ)

$(OBJ_DIR)SWFCompressor.o : $(SRC_DIR)SWFCompressor.cpp $(SRC_DIR)SWFCompressor.h $(SRC_DIR)zlib-1.2.8/zlib.h $(SRC_DIR)lzma920/C/LzmaLib.h
	$(MAKE_CXX_OBJ)

$(OBJ_DIR)SWFReader.o : $(SRC_DIR)SWFReader.cpp $(SRC_DIR)SWFReader.h $(SRC_DIR)BasicTypesReader.h $(SRC_DIR)SWFCompressor.h $(SRC_DIR)zlib-1.2.8/zlib.h
	$(MAKE_CXX_OBJ)

$(OBJ_DIR)SWFStruct.o : $(SRC_DIR)SWFStruct.cpp $(SRC_DIR)SWFStruct.h
	$(MAKE_CXX_OBJ)

$(OBJ_DIR)SWFTags.o : $(SRC_DIR)SWFTags.cpp $(SRC_DIR)SWFTags.h
	$(MAKE_CXX_OBJ)

$(SRC_DIR)BasicTypes.h :
$(SRC_DIR)BasicTypesReader.h : $(SRC_DIR)BasicTypes.h
$(SRC_DIR)SWFCompressor.h :
$(SRC_DIR)SWFReader.h : $(SRC_DIR)SWFStruct.h
$(SRC_DIR)SWFStruct.h : $(SRC_DIR)SWFTags.h
$(SRC_DIR)SWFTags.h : $(SRC_DIR)BasicTypes.h

