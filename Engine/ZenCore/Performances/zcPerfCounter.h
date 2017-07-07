#pragma once

namespace zcPerf 
{

class EventBase : public zRefCounted
{
zenClassDeclare(EventBase, zRefCounted)
protected:	
	zListLink				mlnkChild;
public:		
	typedef zList<EventBase, &EventBase::mlnkChild, false> TypeListChild;
	
									EventBase(const zStringHash32& _zEventName);
	virtual							~EventBase();
	virtual void 					Start() = 0;
	virtual void 					Stop() = 0;
	virtual double					GetElapsedMs();

	bool							IsActive()const;
	void							AddChild(EventBase& _Child);	
	void							ShowStats( const zEngineRef<EventBase>& _rParent, double _fTotalTime, zUInt& _uItemCount, zUInt _uDepth );
	zenInline const zStringHash32&	GetName()const;
	zenInline zEngineRef<EventBase>	GetFirstChild()const;

protected:	
	zStringHash32					mzEventName		= zStringHash32("Unassigned");
	zU64							muTimeStart		= 0;
	zU64							muTimeElapsed	= 0;
	bool							mbActive		= false;
	TypeListChild					mlstChilds;
};

const zStringHash32& EventBase::GetName()const
{
	return mzEventName;
}

zEngineRef<EventBase> EventBase::GetFirstChild()const
{
	return mlstChilds.GetHead();
}

}
