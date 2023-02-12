# MD407 Utils Library
This library contains a collection of utilities and helpful functions, data structures, macros, etc.


## Usage
Include the headers like: `#include <md407/debug.h`, and link the desired stuff.


### Example
```c
#include <md407/gpio.h>
#include <md407/time.h>
#include <md407/debug.h>

int main() {
    // Set pins 7-15 as outputs.
    GPIO_E->moder_high = 0x5555;

    // Delay for 1 second.
    delay_milli(1000);

    // Write 'E' to the output.
    GPIO_E->odr_high = 'E';

    // Print a text to USART1 for debug.
    printc("Hello World!\n");

    return 0;
}
```


## Installation
Pick your system OS and follow the instructions:

<details open>
<summary><h3>*NIX (Linux, MacOS, ...)</h3></summary>

The destination directory (`DESTDIR`) should be `/usr/arm-none-eabi` on **Linux** *(maybe the same for other \*NIX... I haven't checked)*. If that does not work then do:
`$ make DESTDIR=(your dir here) install`.

```sh
git clone https://github.com/pythar-chalmers/libmd407 && cd libmd407 && sudo make install
```
Otherwise just copy-paste the above into your terminal and press enter.
	
</details>

<details>
<summary><h3>Windows</h3></summary>
	<details>
	<summary><h5>Option A</h5></summary>
		<ol>
		  <li> Go to <a href="https://distrochooser.de/" target="_blank">this website</a> and then install the recommended distribution. </li>
		  <li> Come back here and read the above. </li>
		</ol>
	</details>
	<details>
	<summary><h5>Option B</h5></summary>
		You're on your own lol
	</details>
</details>


## Authors
- [Elias Almqvist](https://github.com/almqv)
- [Ismail Sacic](https://github.com/ismail424)


## License
This project is licensed under the GNU v2 License - see the [LICENSE](LICENSE) file for details
