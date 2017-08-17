#include "stdafx.h"
#include "NAPI1C.h"
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "Properties.h"
#include "Functions.h"
#include "LLV.h"

static const wchar_t g_ComponentNameType[] = L"com_1c_kkm_controller";

NAPI1C::NAPI1C() {
	m_iMemory = 0;
	m_iConnect = 0;
}


NAPI1C::~NAPI1C() {
	if (this->llv != NULL) {
		this->llv->~LLV();
	}
}

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len) {
	if (!len)
		len = ::wcslen(Source) + 1;

	if (!*Dest)
		*Dest = new WCHAR_T[len];

	WCHAR_T* tmpShort = *Dest;
	wchar_t* tmpWChar = (wchar_t*)Source;
	uint32_t res = 0;

	::memset(*Dest, 0, len * sizeof(WCHAR_T));
	for (; len; --len, ++res, ++tmpWChar, ++tmpShort) {
		*tmpShort = (WCHAR_T)*tmpWChar;
	}

	return res;
}

bool NAPI1C::Init(void* pConnection) {
	m_iConnect = (IAddInDefBase*)pConnection;	
	this->llv = new LLV;
	if (this->llv && this->llv->init()) {
		parseStatus( llv->getStatus() );
	}
	return m_iConnect != NULL;
}

long NAPI1C::GetInfo() {
	return 2000;
}

bool NAPI1C::setMemManager(void* mem) {
	m_iMemory = (IMemoryManager*)mem;
	return m_iMemory != 0;
}

void NAPI1C::Done() {
	return;
}

bool NAPI1C::RegisterExtensionAs(WCHAR_T** wsExtensionName) {
	const wchar_t *wsExtension = L"kkmExtension";
	int iActualSize = ::wcslen(wsExtension) + 1;
	WCHAR_T* dest = 0;
	
	if (m_iMemory) {
		if (m_iMemory->AllocMemory((void**)wsExtensionName, iActualSize * sizeof(WCHAR_T)))
			convToShortWchar(wsExtensionName, wsExtension, iActualSize);
		return true;
	}

	return false;
}

long NAPI1C::GetNProps() { 
	return numProp; 
}

long NAPI1C::FindProp(const WCHAR_T* wsPropName) {
	for (UCHAR i = 0; i < numProp; i++) {
		propList prop = properties[i];
		if ( (wcscmp(wsPropName, prop.Name[0]) == 0) || (wcscmp(wsPropName, prop.Name[1]) == 0) ) {
			return i;
		}
	}
	return -1;
}

const WCHAR_T* NAPI1C::GetPropName(long lPropNum, long lPropAlias) {
	if ((lPropNum >= numProp) || ( lPropAlias > 1))
		return NULL;	

	wchar_t *wsCurrentName = (wchar_t*)&properties[lPropNum].Name[lPropAlias];
	WCHAR_T *wsPropName = NULL;
	int iActualSize = 0;

	iActualSize = wcslen(wsCurrentName) + 1;

	if (m_iMemory && wsCurrentName) {
		if (m_iMemory->AllocMemory((void**)&wsPropName, iActualSize * sizeof(WCHAR_T)))
			::convToShortWchar(&wsPropName, wsCurrentName, iActualSize);
	}

	return wsPropName; 	
}

void NAPI1C::copyVariant(tVariant *var_dst, tVariant *var_src) {	
	if (var_dst == NULL) {
		return;		
	}

	memcpy(var_dst, var_src, sizeof(tVariant));

	if (var_src->strLen > 0) {
		m_iMemory->AllocMemory((void**)&var_dst->pstrVal, var_src->strLen);
		memcpy(var_dst->pstrVal, var_src->pstrVal, var_src->strLen);
	}

	if (var_src->wstrLen > 0) {
		m_iMemory->AllocMemory((void**)&var_dst->pwstrVal, var_src->wstrLen * sizeof(wchar_t));
		memcpy(var_dst->pwstrVal, var_src->pwstrVal, var_src->wstrLen * sizeof(wchar_t));
	}

}

bool NAPI1C::GetPropVal(const long lPropNum, tVariant* pvarPropVal) {	
	tVariant *value = properties[lPropNum].value;
	if (value == 0) {
		return false;
	}
	copyVariant(pvarPropVal, value);
	return true;
}

bool NAPI1C::SetPropVal(const long lPropNum, tVariant* varPropVal) {
	tVariant *value = properties[lPropNum].value;
	if (value == 0) {
		m_iMemory->AllocMemory((void**)&value, sizeof(tVariant));		
	}
	copyVariant(value, varPropVal);
	properties[lPropNum].value = value;
	return true;
}

bool NAPI1C::IsPropReadable(const long lPropNum) {	
	return properties[lPropNum].readable;	
}

bool NAPI1C::IsPropWritable(const long lPropNum) {
	return properties[lPropNum].writeable;
}

long NAPI1C::GetNMethods() {
	return numFunctions;
}

long NAPI1C::FindMethod(const WCHAR_T* wsMethodName) {
	for (UCHAR i = 0; i < numProp; i++) {
		functList funct = fList[i];
		if ((wcscmp(wsMethodName, funct.Name[0]) == 0) || (wcscmp(wsMethodName, funct.Name[1]) == 0)) {
			return i;
		}
	}
	return -1;	
}

const WCHAR_T* NAPI1C::GetMethodName(const long lMethodNum, const long lMethodAlias) {
	if ((lMethodNum > numFunctions) || (lMethodAlias > 1)) {
		return false;
	}

	wchar_t *wsCurrentName = (wchar_t*)&fList[lMethodNum].Name[lMethodAlias];
	WCHAR_T *wsPropName = NULL;
	int iActualSize = 0;

	iActualSize = wcslen(wsCurrentName) + 1;

	if (m_iMemory && wsCurrentName) {
		if (m_iMemory->AllocMemory((void**)&wsPropName, iActualSize * sizeof(WCHAR_T)))
			::convToShortWchar(&wsPropName, wsCurrentName, iActualSize);
	}

	return wsPropName;
}

long NAPI1C::GetNParams(const long lMethodNum) {

	if (lMethodNum > numFunctions) {
		return 0;
	}

	return fList[lMethodNum].params_num;
}

bool NAPI1C::GetParamDefValue(const long lMethodNum, const long lParamNum, tVariant *pvarParamDefValue) {	
	m_iMemory->AllocMemory((void**)&pvarParamDefValue, sizeof(tVariant));
	TV_VT(pvarParamDefValue) = VTYPE_EMPTY;
	return true;
}

bool NAPI1C::HasRetVal(const long lMethodNum) {
	if (lMethodNum > numFunctions) {
		return false;
	}
	return fList[lMethodNum].is_function;
}

bool NAPI1C::CallAsProc(const long lMethodNum, tVariant* paParams, const long lSizeArray) {
	bool result = true;
	switch (lMethodNum) {
	case 0:
		result = add_item(paParams, lSizeArray);
		break;
	case 1:
		result = open_check();
		break;
	case 2:
		result = add_pay(paParams, lSizeArray);
		break;
	case 3:
		result = close_check();
		break;
	case 4:
		result = z_report();
		break;
	default:
		result = false;
		break;
	}
	return result;
}

bool NAPI1C::CallAsFunc(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray) {
	bool result = true;
	switch (lMethodNum) {
	case 5:
		result = get_check_number(pvarRetValue);
		break;
	case 6:
		result = get_check_summ(pvarRetValue);
		break;
	default:
		result = false;
		break;
	}

	return result;
}

void NAPI1C::SetLocale(const WCHAR_T* loc) { _wsetlocale(LC_ALL, loc); }

tVariant inline *NAPI1C::get_or_create(const int num) {	

	if (properties[num].value == NULL) {
		void *t = malloc(sizeof(tVariant));		
		properties[num].value = (tVariant*)t;
		DATA_SET_BEGIN(properties[num].value);
	}

	return properties[num].value;
}

int NAPI1C::addError(uint32_t wcode, const wchar_t* source, const wchar_t* descriptor, long code) {
	if (m_iConnect) {
		WCHAR_T *err = 0;
		WCHAR_T *descr = 0;

		::convToShortWchar(&err, source, wcslen(source));
		::convToShortWchar(&descr, descriptor, wcslen(descriptor));

		m_iConnect->AddError(wcode, err, descr, code);
		delete[] err;
		delete[] descr;
	}
	return 0;
}

void NAPI1C::parseStatus(pkkm_status status) {
	tVariant *value = get_or_create(0);

	TV_VT(value) = VTYPE_BOOL;
	TV_BOOL(value) = status->connected;

	value = get_or_create(1);
	TV_VT(value) = VTYPE_BOOL;
	TV_BOOL(value) = status->fiscal;

	value = get_or_create(2);
	TV_VT(value) = VTYPE_PWSTR;
	TV_WSTR(value) = status->serial_number;	
	value->wstrLen = wcslen(status->serial_number);

	value = get_or_create(3);
	TV_VT(value) = VTYPE_BOOL;
	TV_BOOL(value) = status->session_open;
	
	value = get_or_create(4);
	TV_VT(value) = VTYPE_BOOL;
	TV_BOOL(value) = status->paper_present;
	
	value = get_or_create(5);
	TV_VT(value) = VTYPE_I1;
	TV_I1(value) = status->kkm_operator;

	value = get_or_create(6);
	TV_VT(value) = VTYPE_PWSTR;
	TV_WSTR(value) = status->machine_number;
	value->wstrLen = wcslen(status->machine_number);

	value = get_or_create(7);
	TV_VT(value) = VTYPE_TM;	
	value->tmVal = status->date;
	value->strLen = 0;
	value->wstrLen = 0;
	
	value = get_or_create(8);
	TV_VT(value) = VTYPE_BOOL;
	TV_I1(value) = status->cover_open;

	value = get_or_create(9);
	TV_VT(value) = VTYPE_PWSTR;
	TV_WSTR(value) = status->ver_hi;
	value->wstrLen = wcslen(status->ver_hi);
	

	value = get_or_create(10);
	TV_VT(value) = VTYPE_PWSTR;
	TV_WSTR(value) = status->ver_lo;
	value->wstrLen = wcslen(status->ver_lo);
	
	value = get_or_create(11);
	TV_VT(value) = VTYPE_PWSTR;
	TV_WSTR(value) = status->build;
	value->wstrLen = wcslen(status->build);	

}

bool NAPI1C::open_check() {
	return llv->open_check();
}

bool NAPI1C::close_check() {
	return llv->close_check();
}

bool NAPI1C::z_report() {
	return llv->report_z();
}

double inline convert_to_double(tVariant data) {
	switch ( TV_VT(&data)) {
	case VTYPE_I1:
	case VTYPE_I2:
	case VTYPE_I4:
	case VTYPE_I8:
		return data.intVal;
	break;
	case VTYPE_R4:
	case VTYPE_R8:
		return data.dblVal;
	default:
		break;
	}
	return data.i8Val;
}

bool NAPI1C::add_item(tVariant *pvarList, const long params) {
	if (params != 3) {
		return false;
	}
	tVariant tv_name = pvarList[0];
	tVariant tv_count = pvarList[1];
	tVariant tv_price = pvarList[2];	

	wchar_t *name = TV_WSTR(&tv_name);
	double count = convert_to_double(tv_count);
	double price = convert_to_double(tv_price);	
	
	if ((count <= 0.0f) || (price <= 0.0f) ) {
		this->addError(1, L"Цена или количество равны нолю!", L"Исправить надо", 1);
		return false;
	}

	if (!llv->add_item(name, count, price)) {
		return false;
	}

	return true;
}

bool NAPI1C::add_pay(tVariant *pvarList, const long params) {
	if (params != 2) {
		return false;
	}
	tVariant tv_type = pvarList[0];
	tVariant tv_sum = pvarList[1];

	int type = TV_I4(&tv_type);
	double sum = convert_to_double(tv_sum);

	return llv->add_pay(type, sum);
}

bool NAPI1C::get_check_number(tVariant* pvarRetValue) {
	int num = llv->get_check_number();
	if (num == -1) {
		return false;
	}
	TV_VT(pvarRetValue) = VTYPE_I4;
	TV_I4(pvarRetValue) = num;
	return true;
}

bool NAPI1C::get_check_summ(tVariant* pvarRetValue) {
	double sum = llv->get_check_summ();
	if (sum < 0) {
		return false;
	}
	TV_VT(pvarRetValue) = VTYPE_R8;
	TV_R8(pvarRetValue) = sum;
	return true;
}