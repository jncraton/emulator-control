all: test

emulator: src/emulator.c src/emulator.h
	gcc -Wall -Wextra -Werror $< -o $@

assembler: src/assembler.c src/emulator.h
	gcc -Wall -Wextra -Werror $< -o $@

roms/%.bin: roms/%.asm assembler
	./assembler $< -o $@

run: emulator
	./emulator

test: emulator
	./emulator

clean:
	rm -f emulator assembler roms/*.bin
