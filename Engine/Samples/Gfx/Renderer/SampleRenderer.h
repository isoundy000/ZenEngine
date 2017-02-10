#pragma once
#ifndef __Sample_Renderer_h__
#define __Sample_Renderer_h__

//=================================================================================================
//! @example SampleGfxRenderer.cpp
//! Renderer initialization and test
//=================================================================================================

namespace sample
{

struct BufferColorUV
{
	zVec4U8	Color;
	zVec2F	UV;
};

class SampleRendererInstance : public zenSys::zEngineInstance
{
zenClassDeclare(SampleRendererInstance, zenSys::zEngineInstance);
public:
	virtual bool					Init();
	virtual void					Destroy();
	virtual void					Update();
	virtual bool					IsDone();
	virtual const char*				GetAppName()const;

protected:
	void									UpdateBackbuffers();
	zenMath::Matrix							matWorld[4];
	zenMath::Matrix							matView;
	zenMath::Matrix							matProjection;
	zenMath::Matrix							matProjectionRT;
	zenRes::zGfxStructBuffer<zVec3F>		mrVertexBufferPos;
	zenRes::zGfxStructBuffer<BufferColorUV>	mrVertexBufferColorUv;
	zenRes::zGfxIndex						mrCubeIndex;	
	zenRes::zGfxShaderVertex				mrShaderVS;	
	zenRes::zGfxShaderPixel					mrShaderPS;	
	zenRes::zGfxShaderPixel					mrShaderPS2Output;		
	zenRes::zGfxTexture2D					mrTexture;	
	zenRes::zGfxStateSampler						mrSampler;	
	zenRes::zGfxStateSampler						mrSampler2;		
	zenRes::zGfxShaderBinding				mrShaderBind;
	zenRes::zGfxShaderBinding				mrShader2OutputBind;
	zenRes::zGfxMeshStrip					mrCube1MeshStrip;
	zenRes::zGfxMeshStrip					mrCube2MeshStrip;
	zenRes::zGfxMeshStrip					mrCube3MeshStrip;
	zenRes::zGfxMesh						mrCube4Mesh;
	zenRes::zGfxTarget2D					mrRenderToTextureRT1;
	zenRes::zGfxTarget2D					mrRenderToTextureRT2;
	zenRes::zGfxTarget2D					mrRenderToTextureDepth;
	zenRes::zGfxTarget2D					mrBackbufferDepth;	
	zenRes::zGfxStateRaster					mrStateRaster;
	zenRes::zGfxRenderPass					mrRndPassTexture;
	zenRes::zGfxRenderPass					mrRndPassFinal;
};

}

#endif