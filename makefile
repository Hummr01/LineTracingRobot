

FILES = main.c iesmotors.c iessensors.c iesusart.c ieslights.c

all: compile flash clean

compile:
	avr-gcc $(FILES) -o tmpfile -mmcu=atmega328p -Os -D F_CPU=16E6
	avr-objcopy -O ihex tmpfile main.hex
	

flash:
	avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex:i


documentation:
	doxygen doxyfile

.PHONY: clean

clean:
	rm tmpfile main.hex


