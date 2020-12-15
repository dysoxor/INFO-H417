
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
    int last = BUFFER_SIZE_3 - 1;
    off_t end_position = lseek(fd, 0, SEEK_END);
    lseek(fd, end_position, SEEK_SET);
    while (index < text.size())
    {
        do
        {
            buffer[index % BUFFER_SIZE_3] = text[index];
            index++;
        } while (index % BUFFER_SIZE_3 != 0 && index < text.size());
        if (index == text.size() && index % BUFFER_SIZE_3 != 0)
        {
            last = (index % BUFFER_SIZE_3);
        }

        _write(fd, &buffer[0], last * sizeof(char));
    }
}

void OutputStream3::close()
{
    _close(fd);
    delete buffer;
}