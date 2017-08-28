#ifdef GARAJ_EXPORTS
#define GARAJ_API __declspec(dllexport)
#else
#define GARAJ_API __declspec(dllimport)
#endif

#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"
#include <map>

class APIServer;

struct APIproperty {
  const wchar_t Name[2][50];
  bool readable;
  bool writeable;
  tVariant *value;
  inline APIproperty operator =( const APIproperty &in ) {
    memcpy( (void*)Name[0], in.Name[0], 50 );
    memcpy( (void*)Name[1], in.Name[1], 50 );    
    readable = in.readable;
    writeable = in.writeable;
    value = in.value;
    return in;
  }
} ;

struct APIfunction{
  wchar_t Name[2][50];
  int		params_num;
  bool	is_function;  
};

class APIServer : public IComponentBase {
protected:
	IMemoryManager *m_iMemory;
	IAddInDefBase *m_iConnect;   
	void copyVariant(tVariant *var_dst, tVariant *var_src);

  APIproperty *properties;
  APIfunction *functions;
  uint8_t prop_count = 0;
  uint8_t func_count = 0;
public:
	APIServer(void);
  uint32_t convToShortWchar( WCHAR_T** Dest, const wchar_t* Source, uint32_t len );
  virtual bool ADDIN_API Init(void * disp) override;
  virtual bool ADDIN_API setMemManager(void * mem) override;
  virtual long ADDIN_API GetInfo() override;
  virtual void ADDIN_API Done() override;
  virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T ** wsExtensionName) override;
  virtual long ADDIN_API GetNProps() override;
  virtual long ADDIN_API FindProp(const WCHAR_T * wsPropName) override;
  virtual const WCHAR_T *ADDIN_API GetPropName(long lPropNum, long lPropAlias) override;
  virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant * pvarPropVal) override;
  virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant * varPropVal) override;
  virtual bool ADDIN_API IsPropReadable(const long lPropNum) override;
  virtual bool ADDIN_API IsPropWritable(const long lPropNum) override;
	virtual long ADDIN_API GetNMethods() override;
	virtual long ADDIN_API FindMethod(const WCHAR_T * wsMethodName) override;
	virtual const WCHAR_T *ADDIN_API GetMethodName(const long lMethodNum, const long lMethodAlias) override;
	virtual long ADDIN_API GetNParams(const long lMethodNum) override;
	virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum, tVariant * pvarParamDefValue) override;
	virtual bool ADDIN_API HasRetVal(const long lMethodNum) override;
	virtual bool ADDIN_API CallAsProc(const long lMethodNum, tVariant * paParams, const long lSizeArray) override;
	virtual bool ADDIN_API CallAsFunc(const long lMethodNum, tVariant * pvarRetValue, tVariant * paParams, const long lSizeArray) override;
	virtual void ADDIN_API SetLocale(const WCHAR_T * loc) override;
	virtual void ADDIN_API sendError(const int code, const wchar_t *text, const wchar_t *descr);
};