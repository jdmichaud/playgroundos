#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#define VIDEO_MEMORY       0xB8000
#define DEFAULT_X_RES      80
#define DEFAULT_Y_RES      24

#define BLACK     0
#define BLUE      1
#define GREEN     2
#define CYAN      3
#define RED       4
#define LIGHTGREY 7
#define WHITE     15

#define LIGHTGREY_ON_BLACK 0x07

#define VIDMEM_ADDRESS( x, y )				\
  ((char *) (VIDEO_MEMORY + (y * DEFAULT_X_RES + x) * 2))
  
struct cursor_s
{
  short x;
  short y;
};

class Console
{
public:
 Console(short xRes = DEFAULT_X_RES, 
	 short yRes = DEFAULT_Y_RES,
	 unsigned int vidMem = VIDEO_MEMORY) 
   : _xRes(xRes), _yRes(yRes), _vidMem(vidMem)
 {
   _cursor.x = 0;
   _cursor.y = 0;
 }

 void cls();
 void print(char *text, int forecolor = LIGHTGREY, int backcolor = BLACK);

private:
 short    _xRes;
 short    _yRes;
  
 cursor_s _cursor;
 unsigned int _vidMem;
};

extern "C" void clrscr();

extern "C" int write_string(char *string, 
			    int xposition, 
			    int yposition, 
			    int colour);

extern "C" void kprint(char *string);

#endif // ! _CONSOLE_H_
