CXX = g++
CXXFLAGS_DEBUG = -g
CXXFLAGS_RELEASE = -O3 -DNDEBUG

all: debug release

debug: Assembler.cpp SymbolTable.cpp Code.cpp Parser.cpp
	$(CXX) $(CXXFLAGS_DEBUG) Assembler.cpp SymbolTable.cpp Code.cpp Parser.cpp -o assembler-debug

release: Assembler.cpp SymbolTable.cpp Code.cpp Parser.cpp
	$(CXX) $(CXXFLAGS_RELEASE) Assembler.cpp SymbolTable.cpp Code.cpp Parser.cpp -o assembler-release

start_hack_release: assembler-release
	./assembler-release ./add/Add.asm
	./assembler-release ./max/Max.asm
	./assembler-release ./max/MaxL.asm
	./assembler-release ./rect/Rect.asm
	./assembler-release ./rect/RectL.asm
	./assembler-release ./pong/Pong.asm
	./assembler-release ./pong/PongL.asm

start_hack_debug: assembler-debug
	./assembler-debug ./add/Add.asm
	./assembler-debug ./max/Max.asm
	./assembler-debug ./max/MaxL.asm
	./assembler-debug ./rect/Rect.asm
	./assembler-debug ./rect/RectL.asm
	./assembler-debug ./pong/Pong.asm
	./assembler-debug ./pong/PongL.asm

reset_hack:
	find . -name "*.hack" -type f -delete
