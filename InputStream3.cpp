#include "InputStream3.h"

bool InputStream3::open(string path)
{
  if ((fd = _open(path.c_str(), _O_RDONLY)) == -1)
  {
    perror("Open failed");
    return false;
  }
  size = 0;
  position = 0;
  return true;
}

void InputStream3::seek(int pos)
{
  lseek(fd, pos, SEEK_SET);
  size = 0;
}

bool InputStream3::end_of_stream()
{
  return _eof(fd);
}

bool InputStream3::close()
{
  delete buffer;
  return _close(fd);
}

string InputStream3::readln()
{
  string line = "";
  bool endline = false;
  do
  {
    if (position >= size - 1 || size == 0)
    {
      size = _read(fd, buffer, BUFFER_SIZE_3 * sizeof(char));
      position = 0;
    }
    while (position < size && !endline)
    {
      if (position < size)
      {
        line += buffer[position];
        position++;
        if (buffer[position] == '\n')
        {
          endline = true;
        }
      }
    }
  } while (position == BUFFER_SIZE_3 && !endline);
  //result += temp;
  return line;
}