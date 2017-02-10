#pragma once

namespace zcGfx 
{
//==================================================================================================
// Generic Command supported on all platforms
//==================================================================================================

class CommandDraw_DX11 : public zcGfx::CommandDraw				
{ 
zenClassDeclare(CommandDraw, CommandDraw)
public: 
	virtual void Invoke(zcGfx::GPUContext& _Context); 
};

class CommandClearColor_DX11 : public zcGfx::CommandClearColor			
{ 
zenClassDeclare(CommandClearColor, CommandClearColor)
public: 
	virtual void Invoke(zcGfx::GPUContext& _Context); 
};

class CommandClearDepthStencil_DX11	: public zcGfx::CommandClearDepthStencil	
{ 
zenClassDeclare(CommandClearDepthStencil, CommandClearDepthStencil)
public: 
	virtual void Invoke(zcGfx::GPUContext& _Context); 
};

//==================================================================================================
// Platform specific Commands
//==================================================================================================
class CommandUpdateIndex_DX11 : public zcGfx::Command
{
zenClassDeclare(CommandUpdateIndex_DX11, zcGfx::Command)
public:
	static zEngineRef<Command>	Create(const zcRes::GfxIndexRef& _rIndex, zU8* _pData, zUInt _uOffset=0, zUInt _uSize=0xFFFFFFFFFFFFFFFF);
	void						Invoke(zcGfx::GPUContext& _Context);
protected:	
	zcRes::GfxIndexRef			mrIndex;
	zU8*						mpData;
	zUInt						muOffset;
	zUInt						muSize;
};

class CommandUpdateBuffer_DX11 : public zcGfx::Command
{
zenClassDeclare(CommandUpdateBuffer_DX11, zcGfx::Command)
public:
	static zEngineRef<Command>	Create(const zcRes::GfxBufferRef& _rBuffer, zU8* _pUpdateData, zUInt _uOffset=0, zUInt _uSize=0xFFFFFFFFFFFFFFFF);
	void						Invoke(zcGfx::GPUContext& _Context);

protected:	
	zcRes::GfxBufferRef			mrBuffer;
	zU8*						mpUpdateData;
	zUInt						muOffset;
	zUInt						muSize;
};

}

