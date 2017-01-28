all: lab2.lss lab2.hex

lab2.hex: lab2.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@
	avr-size $@

lab2.lss: lab2.elf
	avr-objdump -t -h -S -C $^ > $@

lab2.elf: *.c *.h
	avr-g++ -mmcu=atmega324a -DF_CPU=16000000 -O3 -Wall -o $@ $^

clean:
	rm -rf lab2.elf lab2.hex lab2.lss

.PHONY: all clean
