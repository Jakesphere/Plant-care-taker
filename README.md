This is my first Arduino project and my first personal project in embedded systems. 
I wanted to create a plant care-taker since my mom owns alot of plants at home and doesn't have time
to take care of them. 
My project consists of the Arduino MEGA 2560 board, a servo, photoresistor, thermistor, and DS3231 (real time clock).
The microcontroller will constantly sample the temperature and light intensity and check whether the two values fall 
under specified thresholds. 
If the temperature drops below its threshold, two blue LEDs will blink rapidly. 
If the light intensity drops below its threshold, the blue LEDs will stay lit.
The temperature takes precedence over light intensity, so the LEDs will blink even if light is adequate. 
A paper barrier is used to mitigate the affect of the LEDs on the photoresistor, since ambient light is what should be sampled not the blue LED light
The LEDs were chosen to be blue since plants absorb blue light very well compared to other colors
Every specified time period (etc. could be every 12 hours, could be every hour) the DS3231 will interrupt the microcontroller 
to lower the straw attached to the water bottle and feed the plant for 2 seconds, this is achieved using a servo. 

IMPORTANT: Please go to https://www.youtube.com/watch?v=RpGoBx-Lw0k&t=84s to view a demonstration of my project
