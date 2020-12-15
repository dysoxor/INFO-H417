#include "InputStream3.h"

bool InputStream3::open(string path)
{
  if ((fd = _open(path.c_str(), _O_RDONLY)) == -1)
  {
    perror("Open failed");
    return false;
  }
  index = 0;
  return true;
}

void InputStream3::seek(int pos)
{
  lseek(fd, pos, SEEK_SET);
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

int InputStream3::getIndex()
{
  return index;
}

string InputStream3::readln() {
  return "";
}

void InputStream3::read()
{
  do
  {
    index = _read(fd, buffer, BUFFER_SIZE_IS_3 * sizeof(char));
    for (int i = 0; i < index; i++)
    {
      cout << buffer[i];
    }
  } while (index == BUFFER_SIZE_IS_3);
  //result += temp;
}