#compile your code turn it into intel hex(supported by avrdude) and then upload
cd $PWD
avr-gcc main.c -o main -lm -mmcu=atmega328 -DF_CPU=16000000UL -Os
avr-objcopy main -O ihex main.hex
avrdude -Cprog.conf -v -p atmega328p -carduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:./main.hex:i 
