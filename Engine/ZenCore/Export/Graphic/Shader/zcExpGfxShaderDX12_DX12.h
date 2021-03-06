#pragma once

namespace zcExp
{	
	class ExporterGfxShaderDX12_DX12 : public ExporterBase 
	{
	zenClassDeclare(ExporterGfxShaderDX12_DX12, ExporterBase)
	public:				
		typedef zEngineRef<ExportGfxShaderDX12>				ExportResultRef; //todo 3 use proper ref class
															ExporterGfxShaderDX12_DX12(const ExportResultRef& _rExportOut);
	protected:	
		virtual bool										ExportWork(bool _bIsTHRTask);
		virtual bool										ExportEnd();
		bool												ExportWorkCompile();
		bool												ExportWorkExtractResources();
		
		ExportResultRef										mrExport;
		zArrayStatic< zStringHash32 >						maCBufferName;
		zArrayStatic< zArrayStatic<zHash32> >				maCBufferParamName;
		zArrayStatic< zArrayStatic<GfxCBufferParamInfo> >	maCBufferParamInfo;
		zArrayStatic< zArrayStatic<zU8> >					maCBufferDefaultValues;
	};
}
