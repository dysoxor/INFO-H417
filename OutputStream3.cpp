
#include "OutputStream3.h"


OutputStream3::OutputStream3() {
    bufferSize = DEFAULT_BUFFER_SIZE;
    buffer = new char[bufferSize * sizeof(char)];
}

void OutputStream3::setBufferSize(int size){
    bufferSize = size;
    delete buffer;
    buffer = new char[bufferSize * sizeof(char)];
}

bool OutputStream3::create(string path)
{
    if ((fd = _open(path.c_str(), _O_RDWR | _O_CREAT | _O_TRUNC)) < 0)
    {
        perror("Open failed");
        return false;
    }
    return true;
}

void OutputStream3::writeln(string text)
{
    text += '\n';
    index = 0;
    int last = bufferSize ;
    off_t end_position = lseek(fd, 0, SEEK_END);
    lseek(fd, end_position, SEEK_SET);
    while (index < text.size())
    {
        do
        {
            buffer[index % bufferSize] = text[index];
            index++;
        } while (index % bufferSize != 0 && index < text.size());
        if (index == text.size() && index % bufferSize != 0)
        {
            last = (index % bufferSize);
        }

        _write(fd, &buffer[0], last * sizeof(char));
    }
}

void OutputStream3::close()
{
    _close(fd);
    delete buffer;
}