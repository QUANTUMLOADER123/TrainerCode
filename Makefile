CC = zig c++
TARGET = x86_64-windows
CFLAGS = -O2 -Wl,--subsystem,windows -lgdi32 -lcomctl32 -lwinhttp -lole32 -luuid -lshell32 -lcomdlg32
SRC = src_win32/main.cpp
OUT = build/TrainerCode.exe

all: build

build:
	mkdir -p build
	$(CC) -target $(TARGET) $(CFLAGS) $(SRC) -o $(OUT)
	@echo "Build complete: $(OUT)"

run-preview:
	cd web_preview && node server.js

clean:
	rm -rf build/*.exe
