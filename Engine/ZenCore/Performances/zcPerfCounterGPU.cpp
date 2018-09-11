#include "zcCore.h"

namespace zcPerf
{

zArrayDynamic< EventBaseRef > garStackEventGPU;
static const zStringHash32 gaGPUCounterName[] = {
	zStringHash32("Cmd Draw Indexed"),		//keType_DrawIndexed
	zStringHash32("Cmd Compute"),			//keType_Compute
	zStringHash32("Cmd Clear Color"),		//keType_ClearColor
	zStringHash32("Cmd Clear Depth"),		//keType_ClearDepth
	zStringHash32("Cmd Update Index"),		//keType_UpdateIndex
	zStringHash32("Cmd Update Vertex"),		//keType_UpdateVertex
	zStringHash32("Cmd Update Buffer"),		//keType_UpdateBuffer
	zStringHash32("Cmd Update Texture"),	//keType_UpdateTexture
	zStringHash32("Cmd Query"),				//keType_Query
	zStringHash32("Cmd Invalid"),			//keType__Count
};

//=================================================================================================
// EventGPU Base
//=================================================================================================
EventGPU_Base::EventGPU_Base(const zStringHash32& _EventName) 
: Super(_EventName) 
{
}

void EventGPU_Base::GPUStart(const zcGfx::CommandListRef& _rDrawlist)
{
	zenAssertMsg( muTimeStart==0, "Event can only be used once");
	muTimeStart		= zenSys::GetTimeUSec();
	mbActive		= true;

	if (garStackEventGPU.IsEmpty() == false)
		(*garStackEventGPU.Last())->AddChild(*this);

	garStackEventGPU.Push(this);
}

void EventGPU_Base::GPUStop(const zcGfx::CommandListRef& _rDrawlist)
{
	zenAssertMsg( IsActive(), "Start Event before ending it");
	zenAssertMsg((*garStackEventGPU.Last()).GetSafe() == this, "Stop events in the reverse order they were started");
	mbActive = false;
	*garStackEventGPU.Last() = nullptr;
	garStackEventGPU.Pop();	
}

//=================================================================================================
// EventGPU
//=================================================================================================
EventBaseRef EventGPU::Create(const zStringHash32& _EventName)
{
	//static zenMem::zAllocatorPool sMemPool("Pool Event GPU", sizeof(EventGPU), 256, 256);
	EventGPU* pEventGpu = zenNewPool EventGPU(_EventName);
	return pEventGpu;
}

EventGPU::EventGPU(const zStringHash32& _EventName) 
: Super(_EventName) 
{
}

void EventGPU::GPUStart(const zcGfx::CommandListRef& _rDrawlist)
{
	Super::GPUStart(_rDrawlist);
}

void EventGPU::GPUStop(const zcGfx::CommandListRef& _rDrawlist)
{
	Super::GPUStop(_rDrawlist);	
}

//=================================================================================================
// EventGPU Counter
//=================================================================================================
EventBaseRef EventGPUCounter::Create(eType _eCounterType)
{
	zenStaticAssert( zenArrayCount(gaGPUCounterName)==EventGPUCounter::keType__Count+1 ); //Make sure Counter description array match enum
	//static zenMem::zAllocatorPool sMemPool("Pool Event GPU Counter", sizeof(EventGPUCounter), 256, 256);
	EventGPUCounter* pEventGpuCounter = zenNewPool EventGPUCounter(_eCounterType);
	pEventGpuCounter->CPUStart();
	return pEventGpuCounter;
}

EventGPUCounter::EventGPUCounter(eType _eCounterType)
: Super(gaGPUCounterName[_eCounterType])
, meCounterType(_eCounterType)
{
	zenAssert(_eCounterType != keType__Invalid);
}

void EventGPUCounter::CPUStart()
{
	Super::CPUStart();
	Super::CPUStop();
}

}
