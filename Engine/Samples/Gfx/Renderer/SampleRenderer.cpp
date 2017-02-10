#include "zenEngine.h"
#include "SampleRenderer.h"

int main (int argc, char * const argv[])
{
	sample::SampleRendererInstance EngineInstance;
	zenSys::LaunchEngine( &EngineInstance, argc, argv );	
	return 0;	
}

//=================================================================================================
//! @example SampleGfxRenderer.cpp
//! Renderer initialization and test
//=================================================================================================
namespace sample
{

const zArrayStatic<zVec3F> aCubeVerticesPos =
{
	zVec3F( -1.0f, 1.0f, -1.0f ),	zVec3F( 1.0f, 1.0f, -1.0f ),	zVec3F( 1.0f, 1.0f, 1.0f ),		zVec3F( -1.0f, 1.0f, 1.0f ),
	zVec3F( -1.0f, -1.0f, -1.0f ),	zVec3F( 1.0f, -1.0f, -1.0f ),	zVec3F( 1.0f, -1.0f, 1.0f ),	zVec3F( -1.0f, -1.0f, 1.0f ),
	zVec3F( -1.0f, -1.0f, 1.0f ),	zVec3F( -1.0f, -1.0f, -1.0f ),	zVec3F( -1.0f, 1.0f, -1.0f ),	zVec3F( -1.0f, 1.0f, 1.0f ),
	zVec3F( 1.0f, -1.0f, 1.0f ),	zVec3F( 1.0f, -1.0f, -1.0f ),	zVec3F( 1.0f, 1.0f, -1.0f ),	zVec3F( 1.0f, 1.0f, 1.0f ),
	zVec3F( -1.0f, -1.0f, -1.0f ),	zVec3F( 1.0f, -1.0f, -1.0f ),	zVec3F( 1.0f, 1.0f, -1.0f ),	zVec3F( -1.0f, 1.0f, -1.0f ),
	zVec3F( -1.0f, -1.0f, 1.0f ),	zVec3F( 1.0f, -1.0f, 1.0f ),	zVec3F( 1.0f, 1.0f, 1.0f ),		zVec3F( -1.0f, 1.0f, 1.0f ),
};

const zArrayStatic<BufferColorUV> aCubeVerticesColorUV =
{
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 1.0f ) }, //Face 0
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 1.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 1.0f ) }, //Face 1
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 1.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 1.0f ) }, //Face 2
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 1.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 1.0f ) }, //Face 3
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 1.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 1.0f ) }, //Face 4
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 1.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 1.0f ) }, //Face 5
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 1.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 1.0f, 0.0f ) },
	{ zVec4U8( 0xFF, 0xFF, 0xFF, 0xFF ), zVec2F( 0.0f, 0.0f ) },
};

zU16 CubeIndices[] =
{
	3,1,0,		2,1,3,
	6,4,5,		7,4,6,
	11,9,8,		10,9,11,
	14,12,13,	15,12,14,
	19,17,16,	18,17,19,
	22,20,21,	23,20,22
};

const char* SampleRendererInstance::GetAppName() const
{
	return "Sample Renderer";
}

bool SampleRendererInstance::IsDone()
{
	return false;
}

bool SampleRendererInstance::Init()
{
	Super::Init();
	CreateGfxWindow( zVec2U16(1280, 800), zVec2U16(0,0) );

	//-----------------------------------------------------------
	// Prepare some data for asset creation
	zArrayStatic<zU8>			aTexRGBA;
	zVec2U16					vTexSize(256,256);
	zenConst::eTextureFormat	eTexFormat = zenConst::keTexFormat_RGBA8;
	aTexRGBA.SetCount( vTexSize.x*vTexSize.y*4 );
	zU8*						pTexCur = aTexRGBA.First();
	for(zUInt line=0; line<vTexSize.y; ++line)
	{
		for(zUInt col=0; col<vTexSize.x; ++col)
		{
			*pTexCur++ = (line/16+col/16) % 2 == 0 ? 0xFF : 0x10;
			*pTexCur++ = (line/16+col/16) % 2 == 0 ? 0xFF : 0x10;
			*pTexCur++ = (line/16+col/16) % 2 == 0 ? 0xFF : 0xFF;
			*pTexCur++ = 1;
		}
	}

	zArrayStatic<zenRes::zShaderDefine> aShaderDefines			= {	zenRes::zShaderDefine("DEFINETEST", "1"), zenRes::zShaderDefine("DEFINETEST1", "0")};
	zArrayStatic<const zenRes::zShaderParameter*> aParamAll		= {	&zenRes::zShaderFloat4(zHash32("vMeshColor"),	zVec4F(.7f,.7f,.7f,1)),
																	&zenRes::zShaderFloat4(zHash32("vColor"),		zVec4F(1,1,1,1)) };

	//---------------------------------------------------------------------
	// Create rendering resources		
	//---------------------------------------------------------------------	
	mrShaderPS											= zenRes::zGfxShaderPixel::Create( "Shader/Tutorial07.fx", "PS", aShaderDefines );		
	mrShaderPS2Output									= zenRes::zGfxShaderPixel::Create( "Shader/Tutorial07.fx", "PS2Output", aShaderDefines );		
	mrShaderVS											= zenRes::zGfxShaderVertex::Create( "Shader/Tutorial07.fx", "VS");	
	mrCubeIndex											= zenRes::zGfxIndex::Create( zArrayStatic<zU16>(CubeIndices, zenArrayCount(CubeIndices), TRUE), zenConst::kePrimType_TriangleList );
	mrVertexBufferPos									= zenRes::zGfxStructBuffer<zVec3F>::Create(aCubeVerticesPos, (zU32)aCubeVerticesPos.Count() /*, zFlagResUse()*/ ); 
	mrVertexBufferColorUv								= zenRes::zGfxStructBuffer<BufferColorUV>::Create(aCubeVerticesColorUV, (zU32)aCubeVerticesColorUV.Count() /*, zFlagResUse()*/ ); 	
	mrTexture											= zenRes::zGfxTexture2D::Create(zenConst::keTexFormat_RGBA8, vTexSize, aTexRGBA );
	mrSampler											= zenRes::zGfxStateSampler::Create(zenConst::keTexFilter_Trilinear, zenConst::keTexFilter_Bilinear, zenConst::keTexWrap_Clamp, zenConst::keTexWrap_Clamp, 0);
	mrSampler2											= zenRes::zGfxStateSampler::Create(zenConst::keTexFilter_Point, zenConst::keTexFilter_Point, zenConst::keTexWrap_Clamp, zenConst::keTexWrap_Clamp, 0);	

	// Some bindings of render resource together
	mrShaderBind										= zenRes::zGfxShaderBinding::Create(mrShaderVS, mrShaderPS);
	mrShader2OutputBind									= zenRes::zGfxShaderBinding::Create(mrShaderVS, mrShaderPS2Output);
	mrCube1MeshStrip									= zenRes::zGfxMeshStrip::Create( mrCubeIndex, mrShader2OutputBind );
	mrCube2MeshStrip									= zenRes::zGfxMeshStrip::Create( mrCubeIndex, mrShaderBind );
	mrCube3MeshStrip									= zenRes::zGfxMeshStrip::Create( mrCubeIndex, mrShaderBind );

	zenRes::zGfxMeshStrip rCube4MeshStripA				= zenRes::zGfxMeshStrip::Create( mrCubeIndex, mrShaderBind, 0, 12 );
	zenRes::zGfxMeshStrip rCube4MeshStripB				= zenRes::zGfxMeshStrip::Create( mrCubeIndex, mrShaderBind, 12, 0xFFFFFFFF );
	zArrayStatic<zenRes::zGfxMeshStrip> aMesh4Strip		= {rCube4MeshStripA, rCube4MeshStripB};
	mrCube4Mesh											= zenRes::zGfxMesh::Create( aMesh4Strip );

	zenRes::zGfxStateRaster::Config	DefaultRasterConfig;
	mrStateRaster										= zenRes::zGfxStateRaster::Create(DefaultRasterConfig);
	
	
	zArrayStatic<zenRes::zGfxRenderPass::ConfigColorRT>	aRenderToTextureColorRTConfig;
	zenRes::zGfxRenderPass::ConfigDepthRT				RenderToTextureDepthRTConfig;
	mrRenderToTextureRT1								= zenRes::zGfxTarget2D::Create(zenConst::keTexFormat_RGBA8, zVec2U16(512,512) );
	mrRenderToTextureRT2								= zenRes::zGfxTarget2D::Create(zenConst::keTexFormat_RGBA8, zVec2U16(512,512) );
	mrRenderToTextureDepth								= zenRes::zGfxTarget2D::Create(zenConst::keTexFormat_D32, zVec2U16(512,512) );
	aRenderToTextureColorRTConfig.SetCount(2);	
	aRenderToTextureColorRTConfig[0].mrTargetSurface	= mrRenderToTextureRT1;
	aRenderToTextureColorRTConfig[1].mrTargetSurface	= mrRenderToTextureRT2;
	aRenderToTextureColorRTConfig[1].mWriteMask			= zColorMask(zenConst::keColor_R, zenConst::keColor_G);
	RenderToTextureDepthRTConfig.mrTargetSurface		= mrRenderToTextureDepth;
	RenderToTextureDepthRTConfig.mbDepthEnable			= true;
	RenderToTextureDepthRTConfig.mbDepthWrite			= true;
	mrRndPassTexture									= zenRes::zGfxRenderPass::Create("RenderToTexture",0,aRenderToTextureColorRTConfig,RenderToTextureDepthRTConfig,mrStateRaster, zVec2U16(256, 256), zVec2S16(256,0) );

	//-------------------------------------------------
	// Init some shader values
	//---------------------------------------------------------------------
	for(int i=0; i<zenArrayCount(matWorld); ++i)
		matWorld[i].SetIdentity();

//	zArrayStatic<> arResources = {mrVertexBufferPos, mrVertexBufferColorUv, mrTexture, mrSampler};
	zenMath::V4 vEye	= zenMath::simdXYZW( 0.0f, 0.0f,-2.5f, 0.0f );
	zenMath::V4 vAt		= zenMath::simdXYZW( 0.0f, 0.0f, 0.0f, 0.0f );
	zenMath::V4 vUp		= zenMath::simdXYZW( 0.0f, 1.0f, 0.0f, 0.0f );
	zenMath::MatrixLookAtLH(matView, vEye, vAt, vUp );
	zenMath::MatrixProjectionLH( matProjectionRT, 60, float(mrRenderToTextureRT1.GetDim().y)/float(mrRenderToTextureRT1.GetDim().x), 0.01f, 100.f );
	mrCube1MeshStrip.SetValue( aParamAll );
	mrCube1MeshStrip.SetValue( zHash32("World"),				matWorld[0] );
	mrCube1MeshStrip.SetValue( zHash32("View"),					matView );
	mrCube1MeshStrip.SetValue( zHash32("Projection"),			matProjectionRT );
	mrCube1MeshStrip.SetResource( zHash32("txColor.mTexture"),	mrTexture);
	mrCube1MeshStrip.SetResource( zHash32("txColor.mSampler"),	mrSampler);
	mrCube1MeshStrip.SetResource( zHash32("VInputPosition"),	mrVertexBufferPos);
	mrCube1MeshStrip.SetResource( zHash32("VInputColorUV"),		mrVertexBufferColorUv);
	
	vEye				= zenMath::simdXYZW( 0.0f, 0.0f, -5.0f, 0.0f );
	zenMath::MatrixLookAtLH(matView, vEye, vAt, vUp );		
	matWorld[1].SetPos(zenMath::simdXYZW(-3.0f, 0.0f, 0.0f, 1.0f));
	matWorld[1].SetRotationY( zenMath::kfPI2x );		
	mrCube2MeshStrip.SetValue( aParamAll );		
	mrCube2MeshStrip.SetValue( zHash32("View"),					matView );				
	mrCube2MeshStrip.SetValue( zHash32("World"),				matWorld[1] );
	mrCube2MeshStrip.SetValue( zHash32("vColor"),				zVec4F(1,1,1,1));
	mrCube2MeshStrip.SetResource( zHash32("txColor.mTexture"),	mrRenderToTextureRT1.GetTexture2D());
	mrCube2MeshStrip.SetResource( zHash32("txColor.mSampler"),	mrSampler);	
	mrCube2MeshStrip.SetResource( zHash32("VInputPosition"),	mrVertexBufferPos);
	mrCube2MeshStrip.SetResource( zHash32("VInputColorUV"),		mrVertexBufferColorUv);

	matWorld[2].SetPos(zenMath::simdXYZW(3.0f, 0.0f, 0.0f, 1.0f));
	mrCube3MeshStrip.SetValue( aParamAll );
	mrCube3MeshStrip.SetValue( zHash32("View"),					matView );
	mrCube3MeshStrip.SetValue( zHash32("Projection"),			matProjection );		
	mrCube3MeshStrip.SetValue( zHash32("World"),				matWorld[2] );	
	mrCube3MeshStrip.SetValue( zHash32("vColor"),				zVec4F(1,1,1,1));	
	mrCube3MeshStrip.SetResource( zHash32("txColor.mTexture"),	mrTexture);
	mrCube3MeshStrip.SetResource( zHash32("txColor.mSampler"),	mrSampler2);
	mrCube3MeshStrip.SetResource( zHash32("VInputPosition"),	mrVertexBufferPos);
	mrCube3MeshStrip.SetResource( zHash32("VInputColorUV"),		mrVertexBufferColorUv);

	matWorld[3].SetPos(zenMath::simdXYZW(0.0f, 0.0f, 0.0f, 1.0f));
	mrCube4Mesh.SetValue(aParamAll);
	mrCube4Mesh.SetValue( zHash32("View"),						matView );
	mrCube4Mesh.SetValue( zHash32("Projection"),				matProjection );		
	mrCube4Mesh.SetValue( zHash32("World"),						matWorld[3] );		
	mrCube4Mesh.SetResource( zHash32("txColor.mTexture"),		mrTexture);
	mrCube4Mesh.SetResource( zHash32("txColor.mSampler"),		mrSampler);
	mrCube4Mesh.SetResource( zHash32("VInputPosition"),			mrVertexBufferPos);
	mrCube4Mesh.SetResource( zHash32("VInputColorUV"),			mrVertexBufferColorUv);

	rCube4MeshStripA.SetValue( zHash32("vColor"),				zVec4F(1,0.2f,0.2f,1));
	rCube4MeshStripB.SetValue( zHash32("vColor"),				zVec4F(0.2f,1,0.2f,1));	

	return true;
}

void SampleRendererInstance::UpdateBackbuffers()
{
	if( !mrRndPassFinal.IsValid() || mrMainWindowGfx.PerformResize() )
	{	
		zenRes::zGfxRenderPass::ConfigColorRT	FinalColorRTConfig;
		zenRes::zGfxRenderPass::ConfigDepthRT	FinalDepthRTConfig;		
		zVec2U16 vBackbufferDim					= mrMainWindowGfx.GetBackbuffer().GetDim();
		mrBackbufferDepth						= zenRes::zGfxTarget2D::Create(zenConst::keTexFormat_D32, vBackbufferDim ); 
		FinalColorRTConfig.mrTargetSurface		= mrMainWindowGfx.GetBackbuffer();
		FinalDepthRTConfig.mrTargetSurface		= mrBackbufferDepth;
		FinalDepthRTConfig.mbDepthEnable		= true;
		FinalDepthRTConfig.mbDepthWrite			= true;
		FinalDepthRTConfig.meDepthTest			= zenRes::zGfxRenderPass::ConfigDepthRT::keCmpTest_Less;
		mrRndPassFinal							= zenRes::zGfxRenderPass::Create("RenderBackbufferFinal", 2, FinalColorRTConfig, FinalDepthRTConfig, mrStateRaster);	
		zenMath::MatrixProjectionLH( matProjection, 60, float(vBackbufferDim.y)/float(vBackbufferDim.x), 0.01f, 100.f );
	}

}

void SampleRendererInstance::Destroy()
{
	Super::Destroy();
}


void SampleRendererInstance::Update()
{	
	Super::Update();	
	
	//---------------------------------------------------------------------
	// Render loop
	//---------------------------------------------------------------------
	mrMainWindowGfx.FrameBegin();
	UpdateBackbuffers();

	zenGfx::zContext rContextRoot				= zenGfx::zContext::Create("RenderLoop");
	zenGfx::zContext rContextRenderToTexture	= zenGfx::zContext::Create("RenderToTexture",	rContextRoot, mrRndPassTexture);
	zenGfx::zContext rContextFinal				= zenGfx::zContext::Create("Final",				rContextRoot, mrRndPassFinal);
			
	float t = static_cast<float>(zenSys::GetElapsedSec() / 3.0);	// Update our time animation

	//-----------------------------------------------------------------
	// Render cube in RenderTarget
	//-----------------------------------------------------------------
	{
		zenGfx::zCommand::ClearColor(rContextRenderToTexture, mrRenderToTextureRT1, zVec4F(0, 0, 0, 1));
		zenGfx::zCommand::ClearColor(rContextRenderToTexture, mrRenderToTextureRT2, zVec4F(0, 0, 0, 1));
		zenGfx::zCommand::ClearDepthStencil(rContextRenderToTexture, mrRenderToTextureDepth);

		zVec4F vShaderColor = zenMath::TriLerp<zVec4F>(zVec4F(1.f), zVec4F(0.15f, 0.15f, 1.0f, 1), zVec4F(1.f), zenMath::Fract(t * 2));
		matWorld[0].SetRotationY(t);							// Rotate cube around the origin
		mrCube1MeshStrip.SetValue(zHash32("World"), matWorld[0]);
		mrCube1MeshStrip.SetValue(zHash32("vColor"), vShaderColor);
		zenGfx::zCommand::DrawMesh(rContextRenderToTexture, 0, mrCube1MeshStrip);
	}

	//-----------------------------------------------------------------
	// Render cubes in main render target
	//-----------------------------------------------------------------
	zVec4F vClearColor = zenMath::TriLerp( zVec4F(0.05f,0.05f,0.05f,1), zVec4F(0.1f,0.1f,0.20f,1), zVec4F(0.05f,0.05f,0.05f,1), zenMath::Fract(t) );
	zenGfx::zCommand::ClearColor(rContextFinal, mrMainWindowGfx.GetBackbuffer(), vClearColor);
	zenGfx::zCommand::ClearDepthStencil(rContextFinal, mrBackbufferDepth);

	// Render the cube with rendertarget as texture
	mrCube2MeshStrip.SetValue( zHash32("World"),		matWorld[1] );
	mrCube2MeshStrip.SetValue( zHash32("Projection"),	matProjection );
	zenGfx::zCommand::DrawMesh(rContextFinal, 0, mrCube2MeshStrip);

	// Render the cube with point sampling
	matWorld[2].SetRotationY( t );						// Rotate cube around the origin 				
	mrCube3MeshStrip.SetValue( zHash32("World"),		matWorld[2] );
	mrCube3MeshStrip.SetValue( zHash32("Projection"),	matProjection );
	zenGfx::zCommand::DrawMesh(rContextFinal, 0, mrCube3MeshStrip);

	matWorld[3].SetRotationX( t );						// Rotate cube around the origin 				
	mrCube4Mesh.SetValue( zHash32("World"),				matWorld[3] );
	mrCube4Mesh.SetValue( zHash32("Projection"),		matProjection );
	mrCube4Mesh.SetValue( zHash32("World"),				matWorld[3] );
	mrCube4Mesh.SetValue( zHash32("Projection"),		matProjection );
	zenGfx::zCommand::DrawMesh(rContextFinal, 0, mrCube4Mesh);

	rContextRoot.Submit();

	mrMainWindowGfx.FrameEnd();
}
}
