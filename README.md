# MD407 Utils Library
This library contains a collection of utilities and helpful functions, data structures, macros, etc.

## Usage
Include the headers and link the *.c* files with your program.

### Example
```c
#include <md407/gpio.h>
#include <md407/debug.h>

void main() {
	// Set pins 7-15 as outputs.
	GPIO_E->moder_high = 0x5555;

    //Delay for 1 second.
    delay_milli(1000);

	// Write 'E' to the output.
	GPIO_E->odr_high = 'E';

	// Print a text to USART1 for debug.
    printc("Hello World!\n");
}
```

## Authors
- [Elias Almqvist](https://github.com/almqv)
- [Ismail Sacic](https://github.com/ismail424)

## License
This project is licensed under the GNU v2 License - see the [LICENSE](LICENSE) file for details
