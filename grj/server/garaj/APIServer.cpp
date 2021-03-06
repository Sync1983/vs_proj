#include "stdafx.h"
#include <locale.h>

#include "APIServer.h"

APIServer::APIServer() {
	m_iMemory = 0;
	m_iConnect = 0;
    return;
}

uint32_t APIServer::convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len) {
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

void APIServer::copyVariant(tVariant *var_dst, tVariant *var_src) {
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

bool ADDIN_API APIServer::Init(void * pConnection) {
	m_iConnect = (IAddInDefBase*)pConnection;	    
	return m_iConnect != NULL;
}

bool ADDIN_API APIServer::setMemManager(void * mem) {
	m_iMemory = (IMemoryManager*)mem;
	return m_iMemory != 0;
}

long ADDIN_API APIServer::GetInfo() {
	return 2000;
}

void ADDIN_API APIServer::Done() {
	return;
}

bool ADDIN_API APIServer::RegisterExtensionAs(WCHAR_T ** wsExtensionName) {
	const wchar_t *wsExtension = L"garajExtension";
	int iActualSize = ::wcslen(wsExtension) + 1;
	WCHAR_T* dest = 0;

	if (m_iMemory) {
		if (m_iMemory->AllocMemory((void**)wsExtensionName, iActualSize * sizeof(WCHAR_T)))
			convToShortWchar(wsExtensionName, wsExtension, iActualSize);
		return true;
	}

	return false;
}

long ADDIN_API APIServer::GetNProps() {
	return prop_count;
}

long ADDIN_API APIServer::FindProp(const WCHAR_T * wsPropName) {	
  for( uint8_t i = 0; i < prop_count; ++i ){
		if ((wcscmp(wsPropName, properties[i].Name[0]) == 0) || (wcscmp(wsPropName, properties[i].Name[1]) == 0)) {
			return i;
		}
	}
	return 0;
}

const WCHAR_T *ADDIN_API APIServer::GetPropName(long lPropNum, long lPropAlias) {
	if ( (lPropNum >= prop_count) || (lPropAlias > 1) ){
		return NULL;
	}	
	wchar_t *wsCurrentName = (wchar_t*)&properties[lPropNum].Name[lPropAlias];
	WCHAR_T *wsPropName = NULL;
	int iActualSize = 0;

	iActualSize = wcslen(wsCurrentName) + 1;

	if (m_iMemory && wsCurrentName) {
		if (m_iMemory->AllocMemory((void**)&wsPropName, iActualSize * sizeof(WCHAR_T)))
			convToShortWchar(&wsPropName, wsCurrentName, iActualSize);
	}

	return wsPropName;
}

bool ADDIN_API APIServer::GetPropVal(const long lPropNum, tVariant * pvarPropVal) {
	tVariant *value = properties[lPropNum].value;

	if (value == 0) {
		return false;
	}

	copyVariant(pvarPropVal, value);

	return true;
}

bool ADDIN_API APIServer::SetPropVal(const long lPropNum, tVariant * varPropVal) {
	tVariant *value = properties[lPropNum].value;

	if (value == 0) {
    properties[lPropNum].value = (tVariant*) malloc( sizeof( tVariant ) );		
	}

	copyVariant( properties[lPropNum].value, varPropVal);	
	return true;
}

bool ADDIN_API APIServer::IsPropReadable(const long lPropNum) {
	if (lPropNum >= prop_count) {
		return false;
	}
	return properties[lPropNum].readable;
}

bool ADDIN_API APIServer::IsPropWritable(const long lPropNum) {
	if (lPropNum > prop_count) {
		return false;
	}
	return properties[lPropNum].writeable;
}

long ADDIN_API APIServer::GetNMethods() {
  return func_count;
}

long ADDIN_API APIServer::FindMethod(const WCHAR_T * wsMethodName) {
  for(uint8_t i = 0; i < func_count; ++i ) {
    if( ( wcscmp( wsMethodName, functions[i].Name[0] ) == 0 ) || ( wcscmp( wsMethodName, functions[i].Name[1] ) == 0 ) ) {
      return i;
    }
  }
  return 0;
}

const WCHAR_T *ADDIN_API APIServer::GetMethodName(const long lMethodNum, const long lMethodAlias) {
  if( (lMethodNum >= func_count) || ( lMethodAlias > 1) ) {
    return NULL;
  }
  wchar_t *wsCurrentName = (wchar_t*)&functions[lMethodNum].Name[lMethodAlias];
  WCHAR_T *wsPropName = NULL;
  int iActualSize = 0;

  iActualSize = wcslen( wsCurrentName ) + 1;

  if( m_iMemory && wsCurrentName ) {
    if( m_iMemory->AllocMemory( (void**)&wsPropName, iActualSize * sizeof( WCHAR_T ) ) )
      convToShortWchar( &wsPropName, wsCurrentName, iActualSize );
  }

  return wsPropName;	
}

long ADDIN_API APIServer::GetNParams(const long lMethodNum) {
  if( lMethodNum >= func_count ) {
    return false;
  }
	return functions[lMethodNum].params_num;
}

bool ADDIN_API APIServer::GetParamDefValue(const long lMethodNum, const long lParamNum, tVariant * pvarParamDefValue) {
	return false;
}

bool ADDIN_API APIServer::HasRetVal(const long lMethodNum) {
  if( lMethodNum >= func_count ) {
    return false;
  }
  return functions[lMethodNum].is_function;
}

bool ADDIN_API APIServer::CallAsProc(const long lMethodNum, tVariant * paParams, const long lSizeArray) {
	return false;
}

bool ADDIN_API APIServer::CallAsFunc(const long lMethodNum, tVariant * pvarRetValue, tVariant * paParams, const long lSizeArray) {
	return false;
}

void ADDIN_API APIServer::SetLocale(const WCHAR_T * loc) {
  _wsetlocale( LC_ALL, loc );
}

void ADDIN_API APIServer::sendError(const int code, const wchar_t *text, const wchar_t *descr) {
	if (!m_iConnect) {
		throw;
		return;
	}
	m_iConnect->AddError(code, text, descr, code);
	return;
}
