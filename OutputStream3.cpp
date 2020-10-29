
#include "OutputStream3.h"

bool OutputStream3::create(string path)
{
    if ((fd = _open(path.c_str(), _O_RDWR | _O_CREAT)) < 0)
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
    int last = BUFFER_SIZE - 1;
    while (index < text.size() - 1)
    {
        do
        {
            buffer[index % BUFFER_SIZE] = text[index];
            index++;
        } while (index % BUFFER_SIZE != 0 && index < text.size() - 1);
        if (index == text.size() - 1 && index % BUFFER_SIZE != 0)
        {
            last = (index % BUFFER_SIZE);
        }

        _write(fd, &buffer[0], last * sizeof(char));
    }
}

void OutputStream3::close()
{
    _close(fd);
    delete buffer;
}