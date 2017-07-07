#pragma once

namespace zcPerf 
{
	//! @brief Basic class for CPU event, code share by all platform
	class EventCPU_Base : public EventBase
	{
	zenClassDeclare(EventCPU_Base, EventBase)
	public:									
		virtual void	Start();
		virtual void	Stop();

	protected:
						EventCPU_Base(const zStringHash32& _EventName);
	};
}

#include zenHeaderPlatform(zcPerfCounterCPU)

namespace zcPerf 
{
	class EventCPU : public EventCPU_HAL
	{
	zenClassDeclare(EventCPU, EventCPU_HAL)
	public:						
		static zEngineRef<EventBase>	Create(const zStringHash32& _EventName);

	protected:
										EventCPU(const zStringHash32& _EventName) : Super(_EventName) {}
	};
}
