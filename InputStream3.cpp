#include "InputStream3.h"

InputStream3::InputStream3()
{
  bufferSize = DEFAULT_BUFFER_SIZE;
  buffer = new char[bufferSize * sizeof(char)];
}

void InputStream3::setBufferSize(int size)
{
  bufferSize = size;
  delete buffer;
  buffer = new char[bufferSize * sizeof(char)];
}

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
  seek(0);
  return true;
}

int InputStream3::getBufferSize()
{
  return bufferSize;
}

void InputStream3::seek(int pos)
{
  lseek(fd, pos, SEEK_SET);
  position = position + pos - offset;
  if (position < 0 || position >= bufferFill)
  {
    bufferFill = 0;
  }
  offset = pos;
}

bool InputStream3::end_of_stream()
{
  return offset >= size;
}

bool InputStream3::close()
{
  delete buffer;
  return _close(fd) == 0;
}

long long int InputStream3::getSize()
{
  return size;
}

string InputStream3::readln()
{
  string line = "";
  bool endline = false;
  int readSize = bufferSize*sizeof(char);
  do
  {
    if (position >= bufferFill || bufferFill == 0)
    {
      bufferFill = _read(fd, buffer, readSize);
      position = 0;
    }
    while (position < bufferFill && !endline)
    {
      if (buffer[position] != '\n')
      {
        line += buffer[position];
        position++;
        offset++;
      }
      else
      {
        endline = true;
        position++;
        offset++;
      }
    }
  } while (bufferFill == bufferSize && !endline);
  return line;
}