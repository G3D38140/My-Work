#pragma once
#include <sys/timeb.h>  
#include <time.h>  


#if defined(_MSC_VER)
 
typedef unsigned __int64 uint64_t;

#endif

class Calcul_temps
{
public:
	Calcul_temps();
	 ~Calcul_temps();
	void	Start_time();
	void	Stop_time();
	uint64_t Read_time();

private :
	uint64_t Start;
	uint64_t Stop;
	uint64_t Build();
};

