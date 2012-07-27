/*
  Simple utility to control the A10 display devices
  see kernel file include/linux/drv_display_sun4i.h for mode definitions

  Copyright (c) 2012 Jeff Doozan

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/


#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define DISP_DEV      "/dev/disp"

#define DEV_LCD       0x140
#define DEV_TV        0x180
#define DEV_HDMI      0x1c0
#define DEV_VGA       0x200

#define CMD_ON        0
#define CMD_OFF       1
#define CMD_MODE      2


void help(int argc, char const *argv[])
{
  printf ("Usage %s: <hdmi|vga|tv|lcd> <on|off|mode> [mode_number]\n", argv[0]);
}

int main(int argc, char const *argv[])
{
  unsigned long args[4] = {0};

  int device;
  int command;
  int param=0;

  if (argc < 3 || argc > 4)
  {
    help(argc, argv);
    return 1;
  }

  if (!strncasecmp(argv[1], "lcd", 3))
    device = DEV_TV;
  else if (!strncasecmp(argv[1], "tv", 2))
    device = DEV_TV;
  else if (!strncasecmp(argv[1], "hdmi", 4))
    device = DEV_HDMI;
  else if (!strncasecmp(argv[1], "vga", 3))
    device = DEV_VGA;
  else
  {
    help(argc,argv);
    return 1;
  }

  if (!strncasecmp(argv[2], "on", 2))
    command=CMD_ON;
  else if (!strncasecmp(argv[2], "off", 3))
    command=CMD_OFF;
  else if  (!strncasecmp(argv[2], "mode", 4))
  {
    command=CMD_MODE;
    param = atoi(argv[3]);
  } 
  else
  {
    help(argc,argv);
    return 1;
  }

  args[1] = param; 

  int disp = open(DISP_DEV, O_RDWR, 0);
  if (disp < 0) {
    perror("open");
    return -1;
  }

  /* Turn off display before changing mode */
  if (command == CMD_MODE)
    if (ioctl(disp, device+CMD_OFF, args) < 0)
      perror("ioctl");

  if (ioctl(disp, device+command, args) < 0)
    perror("ioctl");

  /* Turn on display after changing mode */
  if (command == CMD_MODE)
    if (ioctl(disp, device+CMD_ON, args) < 0)
      perror("ioctl");

  close(disp);
  return 0;
}
