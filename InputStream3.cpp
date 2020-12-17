#include "InputStream3.h"

bool InputStream3::open(string path)
{
  if ((fd = _open(path.c_str(), _O_RDONLY)) == -1)
  {
    perror("Open failed");
    return false;
  }
  bufferFill = 0;
  position = 0;
  offset = 0;
  size = lseek(fd, 0, SEEK_END);
  return true;
}

void InputStream3::seek(int pos)
{
  lseek(fd, pos, SEEK_SET);
  offset = pos;
  bufferFill = 0;
}

bool InputStream3::end_of_stream()
{
  return offset >= size;
}

bool InputStream3::close()
{
  delete buffer;
  return _close(fd);
}

long long int InputStream3::getSize()
{
  return size;
}

string InputStream3::readln()
{
  string line = "";
  bool endline = false;
  do
  {
    if (position >= bufferFill - 1 || bufferFill == 0)
    {
      seek(offset);
      bufferFill = _read(fd, buffer, BUFFER_SIZE_IS_3 * sizeof(char));
      offset += BUFFER_SIZE_IS_3;
      position = 0;
    }
    while (position < bufferFill && !endline)
    {
      if (buffer[position] != '\n')
      {
        line += buffer[position];
        position++;
      }
      else
      {
        endline = true;
        position++;
      }
    }
  } while (position == BUFFER_SIZE_IS_3 && !endline);
  //result += temp;
  return line;
}
