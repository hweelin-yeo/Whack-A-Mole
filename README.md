# Whack-A-Mole
An Embedded Systems Project

Whack-a-Mole is a hardware game, equipped with a SNES controller and an LED board, where users can “whack” moles. Moles appear on the LED boards randomly and players have to hit the moles in the right position with a hammer, denoted by a green LED pointer, before they disappear to gain a point. Players use the SNES controller to move the hammer around, and click the 'A' button to whack the mole. Once the player reaches 9 points, the game ends. 


# Implementation
The FRDM-K64F board connects to two peripheral devices: the SNES controller and an Adafruit 16 X 32 RGB LED panel.  These devices are also connected to an external power supply.

To interact with the SNES Controller and the LED Matrix, we employ the use of libraries to help us communicate between the board and the devices. The RGB_matrix_Panel library allows us to write to and update the display on the matrix. The SNESController library allows the system to take in input from the controller to play the game. 

In our game.cpp file, we initialize the LED matrix and the SNES Controller and configure it to the different pins on the board. We used polling in order to retrieve input from the controller. Our decision to use polling was due to the difficulty of implementing interrupts in C++, which we needed to use in order to interact with the RGB_matrix_Panel library. However, the efficiency lost from using polling was minimal, as for our game it wasn't necessary to take in interrupts immediately from the user. We could instead check periodically whether certain buttons were pressed.


 
# Hardware
The SNES Controller and RGB LED Panel are connected to the ports of the FRDM-K64F board as stated in the block diagram. As both peripheral devices use 5V,  we connected the POWER and GROUND wires of the peripheral devices to a power source. 

Due to the large size of the pin outlets of the SNES Controller where conventional wires are too thin to connect it with the FRDM-K64F board, we stripped the external cable of the SNES and soldered the LATCH, DATA, POWER, GROUND and CLOCK wires onto five new wires, which are then used to connect to the respective ports on the FRDM-K64F board. To identify each of the five wires, we attached one end of a voltmeter to the pin outlet of the SNES controller and the other to the end of the cut wires. 

We connected our LED Matrix using jumper wires, as described in the Adafruit tutorial linked in reference. However, the Adafruit tutorial showed how to connect to an Arduino board. Thus, it was necessary for us to also look up diagrams of the FRDM board with the Arduino headers in order to understand where we should place each of the wires.


# References and Credits
Thank you to Professors Bruce Land and Joe Skovira for letting us use their labs and providing us with guidance. Thank you again to Professor Joe Skovira for letting us borrow his 16x32 LED Matrix.

Thank you to Dongze Yue, whose Rhythm Game helped inspire our project. He provided us with resources and links to help us get started after we reached out to him. We adapted some of his code when implementing our game logic.

https://yuedongze.github.io/projects.html#arm 
Thank you to Michael Xiao, whose report helped us understand how to properly connect with the 16x32 LED Matrix. Our function matrix_delay() was written based on the function written on his page to help update the display manually.

Medium 16x32 RGB LED matrix panel
Here is documentation about how the LED Matrix works and references to the Adafruit libraries:

https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/how-the-matrix-works

https://github.com/adafruit/RGB-matrix-Panel

https://learn.adafruit.com/adafruit-gfx-graphics-library

https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/connecting-with-jumper-wires

Here is documentation about the FRDM K64 board:

http://cache.freescale.com/files/microcontrollers/doc/ref_manual/K64P144M120SF5RM.pdf

https://os.mbed.com/platforms/FRDM-K64F/

http://cache.freescale.com/files/32bit/doc/user_guide/FRDMK64FUG.pdf

Here is documentation about the SNES Controller:

https://www.igorkromin.net/index.php/2013/02/15/converting-a-snes-controller-to-connect-to-a-nes-controller-port/
We used the following libraries for our project. The RGB_matrix_Panel library contained sample code, which we adapted and used in our code:

https://os.mbed.com/users/foolsday/code/SNESController/
https://os.mbed.com/teams/EIC_mbed/code/RGB_matrix_Panel/
Below are references to devices (16x8 LED Matrix and NES Controller) that we were planning to use for our project, but ultimately didn't:

http://www.robot-electronics.co.uk/i2c-tutorial
http://jcoppens.com/globo/gl_pre/t_common/data/c0302dc.pdf
https://cdn-shop.adafruit.com/datasheets/ht16K33v110.pdf
https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix
https://www.allaboutcircuits.com/projects/nes-controller-interface-with-an-arduino-uno/
