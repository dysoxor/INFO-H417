#include "InputStream1.h"

#include <iostream>

bool InputStream1::open(string path)
{
  if ((fd = _open(path.c_str(), _O_RDONLY)) == -1)
  {
    perror("Open failed");
    return false;
  }
  size = lseek(fd, 0, SEEK_END);
  seek(0);
  return true;
}

void InputStream1::seek(int pos)
{
  lseek(fd, pos, SEEK_SET);
}

bool InputStream1::end_of_stream()
{
  return _eof(fd);
}

bool InputStream1::close()
{
  return _close(fd) == 0;
}

long long int InputStream1::getSize()
{
  return size;
}

string InputStream1::readln()
{
  char buffer;
  string result = "";
  _read(fd, &buffer, sizeof(char));
  while (buffer != '\n')
  {
    result += buffer;
    _read(fd, &buffer, sizeof(char));
  }
  return result;
}