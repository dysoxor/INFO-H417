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
  //cout << "position: " << position << " fill: " << bufferFill << endl;
  do
  {
    if (position >= bufferFill || bufferFill == 0)
    {
      seek(offset);
      bufferFill = _read(fd, buffer, bufferSize * sizeof(char));
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
  //result += temp;
  return line;
}