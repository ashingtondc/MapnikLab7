CXXFLAGS = -g -std=c++14  $(shell mapnik-config --includes --defines --cxxflags --dep-includes)
LDFLAGS = $(shell mapnik-config --libs --dep-libs --ldflags)

OBJ = rundemo.o dataAQ.o demogState.o demogData.o raceDemogData.o psData.o psCombo.o parse.o psRaceDemogData.o

BIN = rundemo

all : $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $@

.c.o :
	$(CXX) -c $(CXXFLAGS) $<

gyp:
	rm -rf ./build
	gyp rundemo.gyp --depth=. -f make --generator-output=./build/
	make -C ./build
	build/out/Release/rundemo `mapnik-config --prefix`

.PHONY : clean

clean: 
	rm -f $(OBJ)
	rm -f $(BIN)
	rm -f ./build