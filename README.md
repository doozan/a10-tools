a10-tools
=========

misc tools for A10 devices by [Jeff](http://forum.doozan.com/read.php?6,9002).

I've created a very simple utility to turn on/off the various displays. Source here, binary here. 

Usage 
----
    a10_display <hdmi|vga|tv|lcd> <on|off|mode> [mode_number]

Modes 
----

HDMI has no settable modes that I could find in the header. This utility will not prevent you from setting HDMI modes, but you do so at your own risk. 

**VGA Modes:** 
* 0 = 1680x1050 
* 1 = 1440x900 
* 2 = 1360x768 
* 3 = 1280x1024 
* 4 = 1024x768 
* 5 = 800x600 
* 6 = 640x480 
* 7 = 1440x900 RB (not yet supported, according to header comments) 
* 8 = 1680x1050 RB (not yet supported, according to header comments) 
* 9 = 1920x1080 RB 
* 10 = 1920x1080 
* 11 = 1280x720 

**LCD Modes:**   
0-15 (brightness control) 

**TV Modes:**
> according to the header, anyhow. I'm pretty sure analog component out can't push 1080p

* 0 = 480i 
* 1 = 576i 
* 2 = 480p 
* 3 = 576p 
* 4 = 720p x 50hz 
* 5 = 720p x 60hz 
* 6 = 1080i x 50hz 
* 7 = 1080i x 60hz 
* 8 = 1080p x 24hz 
* 9 = 1080p x 50hz 
* 10 = 1080p x 60hz 
* 11 = PAL 
* 12 = PAL SVIDEO 
* 14 = NTSC 
* 15 = NTSC SVIDEO 
* 17 = PAL M 
* 18 = PAL M SVIDEO 
* 20 = PAL NC 
* 21 = PAL NC SVIDEO 
* 23 = 1080P x 24HZ x 3D 
* 24 = 720P x 50HZ x 3D 
* 25 = 720P x 60HZ x 3D
