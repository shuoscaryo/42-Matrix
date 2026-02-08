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
