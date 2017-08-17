#pragma once
#include "LLV.h"
#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"


class NAPI1C : public IComponentBase {
private:
	IAddInDefBase      *m_iConnect;
	IMemoryManager     *m_iMemory;
	LLV				   *llv;
	void copyVariant(tVariant *var_dst, tVariant *var_src);
	void parseStatus(pkkm_status status);
	tVariant inline *get_or_create(const int num);
	bool add_item(tVariant *pvarList, const long params);
	bool add_pay(tVariant *pvarList, const long params);
	bool open_check();
	bool close_check();	
	bool z_report();
	bool get_check_number(tVariant* pvarRetValue);
	bool get_check_summ(tVariant* pvarRetValue);
public:
	int addError(uint32_t wcode, const wchar_t* source, const wchar_t* descriptor, long code);

	NAPI1C();
	~NAPI1C();
	virtual bool ADDIN_API Init(void*);
	virtual long ADDIN_API GetInfo();
	virtual bool ADDIN_API setMemManager(void* mem);	
	virtual void ADDIN_API Done();
	// ILanguageExtenderBase
	virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T**);
	virtual long ADDIN_API GetNProps();
	virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
	virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
	virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
	virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
	virtual bool ADDIN_API IsPropReadable(const long lPropNum);
	virtual bool ADDIN_API IsPropWritable(const long lPropNum);
	virtual long ADDIN_API GetNMethods();
	virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
	virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum,
		const long lMethodAlias);
	virtual long ADDIN_API GetNParams(const long lMethodNum);
	virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum,
		tVariant *pvarParamDefValue);
	virtual bool ADDIN_API HasRetVal(const long lMethodNum);
	virtual bool ADDIN_API CallAsProc(const long lMethodNum,
		tVariant* paParams, const long lSizeArray);
	virtual bool ADDIN_API CallAsFunc(const long lMethodNum,
		tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
	// LocaleBase
	virtual void ADDIN_API SetLocale(const WCHAR_T* loc);
};

