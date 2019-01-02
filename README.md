# mobile-robot-TivaC
Project on building mobile robot with TivaC

## Important link
1. [Linux setup for TivaC](http://chrisrm.com/howto-develop-on-the-ti-tiva-launchpad-using-linux/)
2. [Eclipse setup for Stellaris](http://kernelhacks.blogspot.com/2012/11/the-complete-tutorial-for-stellaris_25.html)
3. [Eclipse setup for TivaC on Mac](https://forum.43oh.com/topic/7278-complete-tiva-ide-using-eclipse-on-mac-including-flash-and-debug/)

## Note for Eclipse
- Compile **SW-TM4C** with *-mfloat-abi=softfp*
- Preprocessor: 
	- ARM_MATH_CM4
	- TARGET_IS_BLIZZARD_RA1
	- PART_TM4C123GH6PM
- Builder flags: *-c -fmessage-length=0 -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -mfloat-abi=softfp* 
- Linker flags: *-Wl,--static,--gc-sections,-T../TM4C.ld -mthumb -mcpu=cortex-m4*
- Add built libraries: *driver*, etc.
