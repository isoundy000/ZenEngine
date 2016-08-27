#pragma once
#ifndef __zCore_Gfx_Renderer_Context_h__
#define __zCore_Gfx_Renderer_Context_h__

namespace zcGfx
{

class DrawContext : public zRefCounted
{
zenClassDeclare(DrawContext, zRefCounted)
zListLink mlnkChild;
typedef zList<DrawContext, &DrawContext::mlnkChild, false> TypeListChild;		

public:
	
	ZENInline const zcRes::GfxRenderPassRef&	GetRenderpass();
	ZENInline void								AddCommand( const zEngineRef<zcGfx::Command>& _rCommand );
	void										Submit();
	void										Clear();

protected:
												DrawContext(const zStringHash32& _zContextName, DrawContext* _pParent, const zcRes::GfxRenderPassRef& _rRenderpass);
	virtual										~DrawContext();
	void										SubmitInternal();
	zStringHash32								mzName;					//!< Name of the context (used for draw events)
	bool										mbSubmitted;
	bool										mbRootContext;			//!< True if there's no parent for this context
	TypeListChild								mlstChilds;				//!< List of childs DrawingContext	
	zcRes::GfxRenderPassRef						mrRenderpass;			//!< Associated renderpass to draw this context
	zArrayDynamic<zEngineRef<zcGfx::Command>>	marDrawcalls;			//!< List of drawcalls for this DrawingContext
	static zMap<zU16>::Key32					sdDrawcallCount[2];		//!< Drawcall count of previous/current frame, of all DrawingContext
	friend class zenGfx::zContext;
};

}

#include "zcGfxContext.inl"

#endif