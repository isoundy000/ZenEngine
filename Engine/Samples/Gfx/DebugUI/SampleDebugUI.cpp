#include "zenEngine.h"
#include "SampleDebugUI.h"

//Test merge

//=================================================================================================
//! @example SampleGfxRenderer.cpp
//! Renderer initialization and test
//=================================================================================================
namespace sample
{

SimpleVertex CubeVertices[] =
{
	{ zVec3F( -1.0f, 1.0f, -1.0f ),	zVec2F( 0.0f, 1.0f ) },
	{ zVec3F( 1.0f, 1.0f, -1.0f ),	zVec2F( 1.0f, 1.0f ) },
	{ zVec3F( 1.0f, 1.0f, 1.0f ),	zVec2F( 1.0f, 0.0f ) },
	{ zVec3F( -1.0f, 1.0f, 1.0f ),	zVec2F( 0.0f, 0.0f ) },

	{ zVec3F( -1.0f, -1.0f, -1.0f ),zVec2F( 0.0f, 1.0f ) },
	{ zVec3F( 1.0f, -1.0f, -1.0f ),	zVec2F( 1.0f, 1.0f ) },
	{ zVec3F( 1.0f, -1.0f, 1.0f ),	zVec2F( 1.0f, 0.0f ) },
	{ zVec3F( -1.0f, -1.0f, 1.0f ),	zVec2F( 0.0f, 0.0f ) },

	{ zVec3F( -1.0f, -1.0f, 1.0f ),	zVec2F( 0.0f, 1.0f ) },
	{ zVec3F( -1.0f, -1.0f, -1.0f ),zVec2F( 1.0f, 1.0f ) },
	{ zVec3F( -1.0f, 1.0f, -1.0f ),	zVec2F( 1.0f, 0.0f ) },
	{ zVec3F( -1.0f, 1.0f, 1.0f ),	zVec2F( 0.0f, 0.0f ) },

	{ zVec3F( 1.0f, -1.0f, 1.0f ),	zVec2F( 0.0f, 1.0f ) },
	{ zVec3F( 1.0f, -1.0f, -1.0f ),	zVec2F( 1.0f, 1.0f ) },
	{ zVec3F( 1.0f, 1.0f, -1.0f ),	zVec2F( 1.0f, 0.0f ) },
	{ zVec3F( 1.0f, 1.0f, 1.0f ),	zVec2F( 0.0f, 0.0f ) },

	{ zVec3F( -1.0f, -1.0f, -1.0f ),zVec2F( 0.0f, 1.0f ) },
	{ zVec3F( 1.0f, -1.0f, -1.0f ),	zVec2F( 1.0f, 1.0f ) },
	{ zVec3F( 1.0f, 1.0f, -1.0f ),	zVec2F( 1.0f, 0.0f ) },
	{ zVec3F( -1.0f, 1.0f, -1.0f ),	zVec2F( 0.0f, 0.0f ) },

	{ zVec3F( -1.0f, -1.0f, 1.0f ),	zVec2F( 0.0f, 1.0f ) },
	{ zVec3F( 1.0f, -1.0f, 1.0f ),	zVec2F( 1.0f, 1.0f ) },
	{ zVec3F( 1.0f, 1.0f, 1.0f ),	zVec2F( 1.0f, 0.0f ) },
	{ zVec3F( -1.0f, 1.0f, 1.0f ),	zVec2F( 0.0f, 0.0f ) },
};

const zenRes::zGfxVertex::Element CubeVerticeInfos[]={	
	zenRes::zGfxVertex::Element(zenConst::keShaderElemType_Float, 3, zenConst::keShaderSemantic_Position,	ZENMemberOffset(SimpleVertex, Pos) ),
	zenRes::zGfxVertex::Element(zenConst::keShaderElemType_Float, 2, zenConst::keShaderSemantic_UV,		ZENMemberOffset(SimpleVertex, Tex) ) 
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


bool SampleDebugUIInstance::IsDone()
{
	return false;
}

bool SampleDebugUIInstance::Init()
{
	Super::Init();
	CreateGfxWindow( zVec2U16(1280, 800), zVec2U16(0,0) );
	
	//! @todo Urgent : Finish raster state, per mesh values

	//-----------------------------------------------------------
	// Prepare some data for asset creation
	zArrayStatic<zenRes::zGfxVertex::Stream> aVerticeStreams(1);		
	aVerticeStreams[0].muStride = sizeof(SimpleVertex);
	aVerticeStreams[0].maData.Copy( (zU8*)CubeVertices, sizeof(CubeVertices) );
	aVerticeStreams[0].maElements.Copy(CubeVerticeInfos, ZENArrayCount(CubeVerticeInfos) );

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
	mrCubeVertex									= zenRes::zGfxVertex::Create(aVerticeStreams, zFlagResUse());	
	mrCubeIndex										= zenRes::zGfxIndex::Create( zArrayStatic<zU16>(CubeIndices, ZENArrayCount(CubeIndices), TRUE), zenConst::kePrimType_TriangleList );
	mrShaderVS										= zenRes::zGfxShaderVertex::Create( "Shader/Tutorial07.fx", "VS");
	mrShaderPS										= zenRes::zGfxShaderPixel::Create( "Shader/Tutorial07.fx", "PS", aShaderDefines );		
	mrShaderPS2Output								= zenRes::zGfxShaderPixel::Create( "Shader/Tutorial07.fx", "PS2Output", aShaderDefines );		
	mrTexture										= zenRes::zGfxTexture2d::Create(zenConst::keTexFormat_RGBA8, vTexSize, aTexRGBA );
	mrSampler										= zenRes::zGfxSampler::Create(zenConst::keTexFilter_Trilinear, zenConst::keTexFilter_Bilinear, zenConst::keTexWrap_Clamp, zenConst::keTexWrap_Clamp, 0);
	mrSampler2										= zenRes::zGfxSampler::Create(zenConst::keTexFilter_Point, zenConst::keTexFilter_Point, zenConst::keTexWrap_Clamp, zenConst::keTexWrap_Clamp, 0);	
	
	// Some bindings of render resource together
	zArrayStatic<zenRes::zGfxShader> aShaders		= {zenRes::zGfxShader(mrShaderVS), zenRes::zGfxShader(mrShaderPS)};
	mrShaderBind									= zenRes::zGfxShaderBinding::Create( aShaders );
	zArrayStatic<zenRes::zGfxShader> aShader2Output	= {zenRes::zGfxShader(mrShaderVS), zenRes::zGfxShader(mrShaderPS2Output)};
	mrShader2OutputBind								= zenRes::zGfxShaderBinding::Create( aShader2Output );
	mrCube3MeshStrip								= zenRes::zGfxMeshStrip::Create( mrCubeVertex, mrCubeIndex, mrShaderBind );

	
	zenRes::zGfxStateRasterizer::Config	DefaultRasterConfig;
	mrStateRaster									= zenRes::zGfxStateRasterizer::Create(DefaultRasterConfig);
	
	
	//-------------------------------------------------
	// Init some shader values
	//---------------------------------------------------------------------
	zenMath::V4 vEye	= zenMath::simdXYZW( 0.0f, 0.0f,-5.0f, 0.0f );
	zenMath::V4 vAt		= zenMath::simdXYZW( 0.0f, 0.0f, 0.0f, 0.0f );
	zenMath::V4 vUp		= zenMath::simdXYZW( 0.0f, 1.0f, 0.0f, 0.0f );
	zenMath::MatrixLookAtLH(matView, vEye, vAt, vUp );		
	matWorld.SetIdentity();
	matWorld.SetPos(zenMath::simdXYZW(3.0f, 0.0f, 0.0f, 1.0f));
	mrCube3MeshStrip.SetValue( aParamAll );
	mrCube3MeshStrip.SetValue( zHash32("View"),		matView );
	mrCube3MeshStrip.SetValue( zHash32("Projection"),matProjection );		
	mrCube3MeshStrip.SetValue( zHash32("World"),	matWorld );
	mrCube3MeshStrip.SetValue( zHash32("txColor"),	mrTexture, mrSampler2);
	mrCube3MeshStrip.SetValue( zHash32("vColor"),	zVec4F(1,1,1,1));

	return true;
}

void SampleDebugUIInstance::UpdateBackbuffers()
{
	if( !mrRndPassFinal.IsValid() || mrMainWindowGfx.PerformResize() )
	{	
		zenRes::zGfxRenderPass::ConfigColorRT	FinalColorRTConfig;
		zenRes::zGfxRenderPass::ConfigDepthRT	FinalDepthRTConfig;		
		zVec2U16 vBackbufferDim					= mrMainWindowGfx.GetBackbuffer().GetDim();
		mrBackbufferDepth						= zenRes::zGfxRenderTarget::Create(zenConst::keTexFormat_D24S8, vBackbufferDim ); 
		FinalColorRTConfig.mrTargetSurface		= mrMainWindowGfx.GetBackbuffer();
		FinalDepthRTConfig.mrTargetSurface		= mrBackbufferDepth;
		FinalDepthRTConfig.mbDepthEnable		= true;
		FinalDepthRTConfig.mbDepthWrite			= true;
		FinalDepthRTConfig.meDepthTest			= zenRes::zGfxRenderPass::ConfigDepthRT::keCmpTest_Less;
		mrRndPassFinal							= zenRes::zGfxRenderPass::Create("RenderBackbufferFinal", 2, FinalColorRTConfig, FinalDepthRTConfig, mrStateRaster);	
		zenMath::MatrixProjectionLH( matProjection, 60, float(vBackbufferDim.y)/float(vBackbufferDim.x), 0.01f, 100.f );
	}
}

void SampleDebugUIInstance::Destroy()
{
	Super::Destroy();
}

void SampleDebugUIInstance::Update()
{	
	Super::Update();
	zArrayDynamic<zenRes::zGfxDrawcall> aDrawcalls;
	aDrawcalls.Reserve(2000);

	//---------------------------------------------------------------------
	// Render loop
	//---------------------------------------------------------------------
	UpdateBackbuffers();
	mrMainWindowGfx.FrameBegin();
	
	float t = static_cast<float>(zenSys::GetElapsedSec() / 3.0);	// Update our time animation

	zVec4F vClearColor = zenMath::TriLerp( zVec4F(0.05f,0.05f,0.05f,1), zVec4F(0.1f,0.1f,0.20f,1), zVec4F(0.05f,0.05f,0.05f,1), zenMath::Fract(t) );
	aDrawcalls.Push( zenRes::zGfxDrawcall::ClearColor(mrRndPassFinal, 0, mrMainWindowGfx.GetBackbuffer(), vClearColor) );
	aDrawcalls.Push( zenRes::zGfxDrawcall::ClearDepthStencil(mrRndPassFinal, 0, mrBackbufferDepth) );

	matWorld.SetRotationY( t );						// Rotate cube around the origin 				
	mrCube3MeshStrip.SetValue( zHash32("World"),		matWorld );
	mrCube3MeshStrip.SetValue( zHash32("Projection"),	matProjection );
	mrCube3MeshStrip.Draw(mrRndPassFinal, 0, aDrawcalls);

	zenRes::zGfxDrawcall::Submit(aDrawcalls);
	mrMainWindowGfx.FrameEnd();

}
}