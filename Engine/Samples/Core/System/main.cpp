#include "libZenEngine.h"

namespace sample
{	
	void SampleThread();
}

int main (int argc, char * const argv[])
{	
	if( FSys::EngineStart() )
	{
		sample::SampleThread();		
		while( CSys::IsSystemActive() );
	}	
	return 0;	
}