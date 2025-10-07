## this is where things get interasting
_i used linux and c_

<details>
Fedora Linux 41 (Workstation Edition) x86_64

packages:
avrdude-8.0-4.fc41.x86_64
avr-gcc-14.2.0-1.fc41.x86_64
avr-libc-2.2.0-2.fc41.noarch
</details>

if you planned on using a circuit board like arduino uno for a project and the arduino lang is too bad for you, here are some links and example on how to start baremetal

overall start of avr - https://github.com/m3y54m/start-avr

how to configure gcc-avr compiling in vscode - https://www.tonymitchell.ca/posts/use-vscode-with-avr-toolchain/

some examples of people coidng baremetal on arduino 
- https://www.youtube.com/watch?v=j4xw8QomkXs
- https://www.youtube.com/watch?v=tBq3sO1Z-7o&list=PLNyfXcjhOAwOF-7S-ZoW2wuQ6Y-4hfjMR

for seeing the arduino source code(recommanded to learn from) https://github.com/arduino/ArduinoCore-avr/tree/master

basically explaining registers(with a website emulator) -  https://www.youtube.com/watch?v=gJ_b4ura5Tw&list=PLKL6KBeCnI3X7cb1sznYuyScUesOxS-kL&index=6
https://www.youtube.com/watch?v=d86uuSt2OpE

and some more docs -  https://baremetalmicro.com/tutorial_avr_digital_io/05-Inputs.html

---
i started by adding the source files of arduino and commenting them for intellesense to work
![intellesense.png](https://github.com/shlomi8801-2/arduino_sim_proj/blob/main/intellesense.png?raw=true)

then made a script to auto compile and upload it to the board(make sure in linux to set the port to the correct permissions!)
```bash
#compile your code turn it into intel hex(supported by avrdude) and then upload

cd $PWD
#compile main.c to file main with math library(-lm) compatible with the board chip i use with cpu speed of 16Mhz
avr-gcc main.c -o main -lm -mmcu=atmega328 -DF_CPU=16000000UL -Os
#translate the file to ihex(intel hex) format
avr-objcopy main -O ihex main.hex
#avrdude to upload to the arduino which is at port /dev/ttyUSB0
avrdude -Cprog.conf -v -p atmega328p -carduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:./main.hex:i
```
next find your board mcu map like so
![mcu map atmega328p.png](https://github.com/shlomi8801-2/arduino_sim_proj/blob/main/mcu%20map%20atmega328p.png?raw=true)

if the intellesense still doesnt work try editing the c/c++ extention settings
![extention](https://github.com/shlomi8801-2/arduino_sim_proj/blob/main/extention.png?raw=true)


then from all you learned start coding for example this version of blink:
```c
int main()
{
	// Set built-in LED pin as output
	DDRB |= (1 << PB5); // just sets the pb register at bit 5 which is the led state to output for output
	while (1) {
		PORTB |= (1 << PB5); // LED on
		_delay_ms(500);
		PORTB &= ~(1 << PB5); // LED off
		_delay_ms(500);
	}
	return 0;
}
```
[credit](https://electronics.stackexchange.com/questions/67280/difference-between-reading-port-and-pin)
**DDRx** is the **Data Direction**
**PINx** is the **input buffer**
**PORTx** is the **output buffer**

here is some explaining on the random ``PORTB`` and ``DDRB`` names https://www.quora.com/What-are-DDRB-PORTB-and-PINB
but basiclly you set a pin mode to output by its bit and then set it bit to on for example for PD7
```c
//data direction at secion D (we want PD)
DDRD |= 1<<7; // which is in bin 1000 0000
PORTD |= 1<<7; // turnes on the bit we set to output


//we can also use
DDRD |= 1<<7;
PORTD = ~(0); // 1111 1111
//which will set all the pins at seciond D to high voltage but only PD7 is set to output so only it will output any current
```
