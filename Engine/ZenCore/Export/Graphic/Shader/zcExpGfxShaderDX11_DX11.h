#pragma once
#ifndef __zCore_Exp_Gfx_GfxShader_DX11_DX11_h__
#define __zCore_Exp_Gfx_GfxShader_DX11_DX11_h__

namespace zcExp
{	
	class ExporterGfxShaderDX11_DX11 : public ExporterBase 
	{
	ZENClassDeclare(ExporterGfxShaderDX11_DX11, ExporterBase)
	public:				
		typedef zEngineRef<ExportGfxShaderDX11>	ExportResultRef; //todo use proper ref class
												ExporterGfxShaderDX11_DX11(const ExportResultRef& _rExportOut);
	protected:	
		virtual bool							ExportWork(bool _bIsTHRTask);
		virtual bool							ExportEnd();
		bool									ExportWorkCompile();
		bool									ExportWorkExtractResources();		
		ExportResultRef							mrExport;
	};
}

#endif
