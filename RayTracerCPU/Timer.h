#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class Timer
{
public :
	Timer() 
	{
		 M_Start =std::chrono::duration_cast<std::chrono::milliseconds>(
			 std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	
	};
	~Timer() 
	{
		uint64_t End = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();

		std::cout << (End - M_Start)<<std::endl;
	};

	uint64_t M_Start;
};


#endif // !TIMER_H
