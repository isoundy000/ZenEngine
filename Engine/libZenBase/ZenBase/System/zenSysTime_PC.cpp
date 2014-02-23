#include "libZenBase.h"
#include <time.h>

namespace zen { namespace zenSys
{

static awU64 suStartTime = GetTimeUSec();

awU64 GetTimeUSec()
{
    //-----------------------------------------------------
    // Should be init by system instead
	static double sfFreqPerUSInv(0);
	if( sfFreqPerUSInv==0 )
	{
		LARGE_INTEGER frequency;        
		QueryPerformanceFrequency(&frequency); // ticks per second
		sfFreqPerUSInv = 1000000.0 / double(frequency.QuadPart);
	}
    //-----------------------------------------------------

    LARGE_INTEGER t1;
    QueryPerformanceCounter(&t1);
    return static_cast<awU64>(t1.QuadPart * sfFreqPerUSInv);
}

double GetElapsedUSec()
{
	return double(GetTimeUSec()-suStartTime);
}

double GetElapsedMSec()
{
	return double(GetTimeUSec()-suStartTime)/1000.0;
}

double GetElapsedSec()
{
	return double(GetTimeUSec()-suStartTime)/(1000.0*1000.0);
}

const awDateTime& GetDateTime()
{
	static awDateTime	DateTimeOut;
	time_t          rawtime;
	tm              datetime;

	time( &rawtime );
	localtime_s( &datetime, &rawtime );

	DateTimeOut.muYear          = datetime.tm_year+1900;
	DateTimeOut.muDayOfYear     = datetime.tm_yday;
	DateTimeOut.muDayOfMonth    = datetime.tm_mday;
	DateTimeOut.muDayOfWeek     = datetime.tm_wday;    
	DateTimeOut.muMonth         = datetime.tm_mon;
	DateTimeOut.muHour          = datetime.tm_hour;        
	DateTimeOut.muMinute        = datetime.tm_min;
	DateTimeOut.muSecond        = datetime.tm_sec;        
	return DateTimeOut;
}

awTimeStamp GetTimeStamp()
{
	time_t rawtime;
	time( &rawtime );
	return rawtime;
}

} } //namespace zen { namespace zenSys

