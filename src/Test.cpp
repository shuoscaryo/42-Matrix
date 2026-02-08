#include "Test.tpp"

size_t Test::counter = 1;

void Test::printLine(const std::string& line, size_t start, size_t end, size_t lineWidth)
{
    std::string str(lineWidth, ' ');
    for (size_t i = 0; i < 3; ++i)
        str[lineWidth - 1 - i] = str[i] = '#';
    size_t len = end - start;
    for (size_t i = 0; i < len; ++i)
        str[lineWidth/2 - len/2 + i] = line[start + i];
    std::cout << str << "\n";
}


void Test::header(const std::string& title, bool resetCounter)
{
    if (resetCounter)
        counter = 1;
    // ### Text ### (lineWidth 80 - 4 -4 = 72)
    const size_t lineWidth = 80;
    const size_t textWidth = lineWidth - 8;
    std::string hashtags(lineWidth, '#');
    std::cout << hashtags << "\n";
    size_t start = 0;
    size_t lastCharPos = title.find_last_not_of(" ");
    if (lastCharPos == std::string::npos)
        return;
    while (start <= lastCharPos)
    {
        start = title.find_first_not_of(" ", start);
        if (start == std::string::npos)
            break;
        size_t end = title.find_last_of(" ", start + textWidth - 1);
        if (end == std::string::npos or end < start)
            end = start + textWidth;
        end = end > lastCharPos + 1 ? lastCharPos + 1 : end;
        if (start + textWidth > lastCharPos)
            end = lastCharPos + 1;
        printLine(title, start, end, lineWidth);
        start = end;
    }
    std::cout << hashtags << "\n";
}
