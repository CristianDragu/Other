all: lab1.hex

lab1.elf: lab1.c lcd.c usart.c
	avr-g++ -mmcu=atmega324p -DF_CPU=16000000 -Wall -Os -o $@ $^

lab1.hex: lab1.elf
	avr-objcopy -j .text -j .data -O ihex lab1.elf lab1.hex
	avr-size lab1.elf

clean:
	rm -rf lab1.elf lab1.hex

.PHONY: all clean

