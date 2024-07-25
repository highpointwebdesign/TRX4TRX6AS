# TRX4TRX6AS
An attempt at making dynamic suspension for my Traxxas trx6

Inspired from https://github.com/annoyinganime/OpenActiveSuspension/blob/master/ActiveSuspension/ActiveSuspension.ino

My plan is to make a web page that can be used to modify suspension settings on the esp32 so i dont have to reflash it  This would allow changes for different terrains. the dashboard will eventually show angles of pitch and roll. 

i also plan to add light control but delending on memory, that may be a separate module for that.  

Eventually a driver could save settings as profiles and share (waaaaay down the road).

Goals;
* buy servos
* buy esp32
* buy mpu6050
* buy eoller chassi for testing
* buy basic esc
* buy tx/rx
* win the lottery
* spell check this shit

Completed:
* setup reoo
* get foundation code (blink onbiard led and gonfeim there)
* code esp32 to act as a web server
* build web form to interface with esp32
* create default preferences library
* blunk onboard led with flash cides to determine whats happening with the code
    * 1 flash success
    * 5 oh shit somethingnbad hapoened
