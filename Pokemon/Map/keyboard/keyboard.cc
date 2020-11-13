#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
struct termios tcsave;
int flsave;
#define UP    0x415b1b
#define DOWN  0x425b1b
#define LEFT  0x445b1b
#define RIGHT 0x435b1b
#define ENTER 0xa
#define ESC   0x1b
#define SPACE 0x20

int init_keyboard(void)
{
	int ret;
	struct termios tc;
	ret = tcgetattr(0, &tcsave);
	if(ret < 0)
		return -1;
	tc = tcsave;
	tc.c_lflag &= ~(ECHO|ICANON);
	ret = tcsetattr(0, TCSANOW, &tc);
	if(ret < 0)
		return -1;
	flsave = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, flsave|O_NONBLOCK);
	return 0;
}

void recover_keyboard(void)
{
	tcsetattr(0, TCSANOW, &tcsave);
	fcntl(0, F_SETFL, flsave);
}
char get_ch()
{
  char ch;
  while(1)
  {
   int r =read(0,&ch,1);
   if(r>=1)
   {
     break;
   }
  }
  return ch;
}
