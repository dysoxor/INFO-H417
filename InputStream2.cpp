#include "InputStream2.h"

InputStream2::InputStream2()
{
  bufferSize = DEFAULT_BUFFER_SIZE;
  buffer = new char[bufferSize];
}

InputStream2::~InputStream2()
{
  delete buffer;
}

void InputStream2::setBufferSize(int size)
{
  bufferSize = size;
  delete buffer;
  buffer = new char[bufferSize];
}

void InputStream2::setFile(string f)
{
  file = f;
}

bool InputStream2::open()
{
  if ((fd = fopen(file.c_str(), "r")) == NULL)
  {
    perror("Open failed");
    return false;
  }
  seek(0);
  return true;
}

bool InputStream2::open(string path)
{
  if ((fd = fopen(path.c_str(), "r")) == NULL)
  {
    perror("Open failed");
    return false;
  }
  seek(0);
  return true;
}

int InputStream2::getBufferSize()
{
  return bufferSize;
}

void InputStream2::seek(int pos)
{
  fseek(fd, pos, SEEK_SET);
}

bool InputStream2::end_of_stream()
{
  return feof(fd);
}

bool InputStream2::close()
{
  return fclose(fd) == 0;
}

long long int InputStream2::getSize()
{
  long long int curr = fseek(fd, 0L, SEEK_CUR);
  fseek(fd, 0L, SEEK_END);
  long long int s = ftell(fd);
  seek(curr);
  return s;
}

string InputStream2::readln()
{
  string result = "";
  string tempRes = "";
  do
  {
    IOCounter++;
    if (fgets(buffer, bufferSize, fd) == NULL)
    {
      break;
    }
    tempRes = buffer;
    result += tempRes;
  } while (tempRes.size() + 1 == bufferSize && buffer[bufferSize - 1] != '\n');
  result = result.substr(0, result.size() - 1);
  return result;
}