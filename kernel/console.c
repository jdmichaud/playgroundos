#include "console.h"

void Console::cls()
{
  char *video = (char *) _vidMem;
  for (int i = 0; i < _xRes; ++i)
    for (int j = 0; j < _yRes; ++j)
    {
      *video = short(0); // Clear character and color (2 * bytes)
      video += 2;
    }

  _cursor.x = 0;
  _cursor.y = 0;
}

void Console::print(char *text, int forecolor, int backcolor)
{
  /* [IBBBFFF]
   * I = intensity (blink)
   * B = background color
   * F = foreground color
   */
  unsigned char color = (backcolor << 4) | forecolor;

  while (*text)
  {
    char *video = VIDMEM_ADDRESS(_cursor.x, _cursor.y);
    switch (*text)
    {
    case '\n':
      ++_cursor.y;
      _cursor.x = 0;
      break;

    case '\t':
      _cursor.x += 8;
      break;

    case 0x8:
      --_cursor.x;
      break;

    default:
      *video = *text;
      ++video;
      *video = color;
      ++video;
      ++_cursor.x;
      break;
    }

    _cursor.y += (int) (_cursor.x / _xRes);
    _cursor.x = _cursor.x % _xRes;
    ++text;
  }
}

void clrscr()
{
  char *video = (char *) VIDEO_MEMORY;
  for (int i = 0; i < 80; ++i)
    for (int j = 0; j < 25; ++j)
    {
      *video = short(0);
      video += 2;
    }
    
}

int write_string(char *string, int xposition, int yposition, int colour)
{
  char *video = (char *) VIDEO_MEMORY;
  int  charcount = 0;

  video += (yposition * 80 * sizeof(char)) + (xposition * sizeof(char));
 
  while (*string != 0)
  {
    if (*string == '\n')
    {
      ++string;
      int shift = 80 - ((int (video - VIDEO_MEMORY) / 2) % 80);
      video += shift * 2;
      charcount += shift;
      continue;
    }
    *video = *string;
    string++;
    video++;
    charcount++;

    *video = colour;
    video++;
  }

  return charcount;
}

void kprint(char *string)
{
  static int line   = 0;
  static int column = 0;

  int charcount = write_string(string, column, line, LIGHTGREY_ON_BLACK);
  column = charcount % 80;
  line += charcount / 80 > 25 ? 25 : charcount / 80;
}
