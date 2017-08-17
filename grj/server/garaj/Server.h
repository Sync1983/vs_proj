#include "APIServer.h"
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#define BUFLEN 512

class Server : public APIServer {
private:
  WSADATA wsaData;
  ADDRINFOW hints, *result;

  bool start_server( );
  bool stop_server( );
    
protected:  
  enum Props {
    typePort = 0,
    typeRequest,
    strRequest,
    lastProps
  };

  tProps properties = {
    { typePort,{ { L"Port",	L"Порт" }, true, true, 0 } },
    { typeRequest,{ { L"TypeRequest",	L"ТипЗапроса" }, true, true, 0 } },
    { strRequest,{ { L"StrRequest",	L"СтрокаЗапроса" }, true, false, 0 } }
  };

  bool ADDIN_API CallAsProc( const long lMethodNum, tVariant * paParams, const long lSizeArray );
public:
  Server();
	~Server();
};

