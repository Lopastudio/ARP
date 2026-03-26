PROJECT     := ARP
BUILD_LINUX := build/linux
BUILD_WIN   := build/windows
JOBS        := $(shell nproc)
MAKE_BIN    := $(shell which make)
CCACHE      := $(shell which ccache 2>/dev/null)
ifdef CCACHE
    CCACHE_FLAGS := -DCMAKE_C_COMPILER_LAUNCHER=ccache \
                    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
else
    CCACHE_FLAGS :=
endif

.PHONY: all linux windows debug debug-win clean run run-win reconfigure reconfigure-debug reconfigure-win

all: linux


$(BUILD_LINUX)/CMakeCache.txt:
	@echo ">>> Configuring for Linux (Release)..."
	@cmake -S . -B $(BUILD_LINUX) \
	    -DCMAKE_BUILD_TYPE=Release \
	    -DBUILD_FOR_WINDOWS=OFF \
	    $(CCACHE_FLAGS)

linux: $(BUILD_LINUX)/CMakeCache.txt
	@cmake --build $(BUILD_LINUX) --parallel $(JOBS)
	@echo ">>> Done: $(BUILD_LINUX)/$(PROJECT)"


$(BUILD_LINUX)-debug/CMakeCache.txt:
	@echo ">>> Configuring for Linux (Debug)..."
	@cmake -S . -B $(BUILD_LINUX)-debug \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_FOR_WINDOWS=OFF \
	    $(CCACHE_FLAGS)

debug: $(BUILD_LINUX)-debug/CMakeCache.txt
	@cmake --build $(BUILD_LINUX)-debug --parallel $(JOBS)
	@echo ">>> Done: $(BUILD_LINUX)-debug/$(PROJECT)"


$(BUILD_WIN)/CMakeCache.txt:
	@echo ">>> Configuring for Windows (Release, MinGW cross)..."
	@cmake -S . -B $(BUILD_WIN) \
	    -G "Unix Makefiles" \
	    -DCMAKE_MAKE_PROGRAM=$(MAKE_BIN) \
	    -DCMAKE_BUILD_TYPE=Release \
	    -DBUILD_FOR_WINDOWS=ON \
	    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw-w64.cmake \
	    $(CCACHE_FLAGS)

windows: $(BUILD_WIN)/CMakeCache.txt
	@cmake --build $(BUILD_WIN) --parallel $(JOBS)
	@echo ">>> Done: $(BUILD_WIN)/$(PROJECT).exe"


$(BUILD_WIN)-debug/CMakeCache.txt:
	@echo ">>> Configuring for Windows (Debug, MinGW cross)..."
	@cmake -S . -B $(BUILD_WIN)-debug \
	    -G "Unix Makefiles" \
	    -DCMAKE_MAKE_PROGRAM=$(MAKE_BIN) \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_FOR_WINDOWS=ON \
	    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw-w64.cmake \
	    $(CCACHE_FLAGS)

debug-win: $(BUILD_WIN)-debug/CMakeCache.txt
	@cmake --build $(BUILD_WIN)-debug --parallel $(JOBS)
	@echo ">>> Done: $(BUILD_WIN)-debug/$(PROJECT).exe"

run: linux
	@./$(BUILD_LINUX)/$(PROJECT)

run-debug: debug
	@./$(BUILD_LINUX)-debug/$(PROJECT)

run-win: windows
	@wine $(BUILD_WIN)/$(PROJECT).exe


reconfigure:
	@rm -f $(BUILD_LINUX)/CMakeCache.txt \
	       $(BUILD_LINUX)-debug/CMakeCache.txt \
	       $(BUILD_WIN)/CMakeCache.txt \
	       $(BUILD_WIN)-debug/CMakeCache.txt
	@echo ">>> All CMakeCaches cleared. Run make <target> to reconfigure."

reconfigure-linux:
	@rm -f $(BUILD_LINUX)/CMakeCache.txt
	@echo ">>> Linux cache cleared."

reconfigure-debug:
	@rm -f $(BUILD_LINUX)-debug/CMakeCache.txt
	@echo ">>> Linux Debug cache cleared."

reconfigure-win:
	@rm -f $(BUILD_WIN)/CMakeCache.txt
	@echo ">>> Windows cache cleared."

reconfigure-debug-win:
	@rm -f $(BUILD_WIN)-debug/CMakeCache.txt
	@echo ">>> Windows Debug cache cleared."

clean:
	@rm -rf build/
	@echo ">>> Cleaned."
