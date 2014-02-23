#include "libZenEngine.h"

namespace sample
{	
	void SampleLog();
	void SampleAssert();
}

int main (int argc, char * const argv[])
{	
	if( FSys::EngineStart() )
	{
		sample::SampleLog();
		sample::SampleAssert();

		while( CSys::IsSystemActive() );
	}
	FSys::EngineStop();
	return 0;
}