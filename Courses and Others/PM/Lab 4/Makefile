all: lab5.hex

lab5.hex: lab5.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $^

lab5.elf: main.c game.c T6963c.c
	avr-g++ -mmcu=atmega324a -DF_CPU=16000000 -Wall -Wextra -Wl,-u,vfprintf -lprintf_flt -Os -lm -o $@ $^ -lm

clean:
	rm -rf lab5.hex lab5.elf

.PHONY: all clean
