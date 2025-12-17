#pragma once
#include <iostream>
#include <utility>

class Test
{
	public:
		// Default way of passing a random function with random params
		// use "typename ...Args" and "std::forward<Args>(args)..." 
		template <typename F, typename... Args>
		static void add(const std::string& title, F&& f, Args&&... args);
		// Prints a cool header to test parts and 
		static void header(const std::string& title, bool resetCounter = true);
	private:
		Test(void) = default;
		static size_t counter;
		static void printLine(const std::string& line, size_t start, size_t end, size_t lineWidth);
};
size_t Test::counter = 1;

template <typename F, typename... Args>
void Test::add(const std::string& title, F&& f, Args&&... args)
{
    std::cout << "[Test " << counter++ << "] " << title << "\n";
    try
    {
        std::forward<F>(f)(std::forward<Args>(args)...);
    } catch (const std::exception &e)
    {
        std::cout << "Oh no! Test " << counter - 1 << " crashed: " << e.what() << "\n";  
    }
    std::cout << std::endl;
}


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
