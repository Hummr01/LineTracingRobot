FILES = main.c iesmotors.c iessensor_lights.c iesusart.c iessensors.c


all: compile flash

compile:
	avr-gcc $(FILES) -o tmpfile -mmcu=atmega328p -Os -D F_CPU=16E6
	avr-objcopy -O ihex tmpfile tmpfile.hex

flash: tmpfile
	avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:tmpfile.hex:i
