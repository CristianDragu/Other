all: lab4.hex sd.c

lab4.elf: lab4.c lcd.c pff.c
	avr-g++ -Wall -Wextra -mmcu=atmega324a -DF_CPU=16000000 -Os -o $@ $^ sd.c

lab4.hex: lab4.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $^

clean:
	rm -rf lab4.hex lab4.elf

.PHONY: all clean
