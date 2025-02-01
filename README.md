# TRX4TRX6AS
An attempt at making dynamic suspension for my Traxxas trx6

Inspired from https://github.com/annoyinganime/OpenActiveSuspension/blob/master/ActiveSuspension/ActiveSuspension.ino

I plan to make a web page that can be used to modify suspension settings on the esp32 so I don't have to reflash it. The UI would allow changes for different terrains. The dashboard will eventually show the angles of pitch and roll of the vehicle chassis. 

I also plan to add light control but depending on memory, that may be a separate module.  

Eventually, a driver could save settings as profiles and share (waaaaay down the road).

Goals;
* buy servos
* buy esp32
* buy mpu6050
* buy roller chassis for testing
* buy basic esc
* buy tx/rx
* win the lottery
* spell check this shit

Completed:
* setup repo
* get foundation code (blink onboard led and go from there)
* code esp32 to act as a web server
* Build web form to interface with esp32
* create default preferences library
* blunk onboard led with flash codes to determine what's happening with the code
    * 1 flash success
    * 5 Oh shit something bad happened
