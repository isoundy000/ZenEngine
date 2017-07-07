#pragma once

namespace zcExp
{	

class ExporterGfxBuffer_DX12 : public ExporterBase
{
zenClassDeclare(ExporterGfxBuffer_DX12, ExporterBase)
public:				
typedef zEngineRef<ExportGfxBuffer>		ExportDataRef; //todo use proper ref class
										ExporterGfxBuffer_DX12(const ExportDataRef& _rExportData);		
							
protected:	
	virtual bool						ExportStart();	
	ExportDataRef						mrExportData;
};

}
