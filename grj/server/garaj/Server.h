#include "APIServer.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <Windows.h>
#include <thread>

#ifndef UNICODE
#define UNICODE
#endif

#pragma comment (lib, "Ws2_32.lib")

#define BUFLEN 512

class Server : public APIServer {
private:
  WSADATA wsaData;
  ADDRINFOW hints, *result;
  SOCKET ListenSocket, ClientSocket;
  std::thread listen_th;

  bool stop_listen = false;

  bool start_server( );
  bool stop_server( );
  PCWSTR convert_api_string( PCWSTR str, int len );
  void listen_socket( );
  void listen_client( SOCKET soc );
  void wsa_error_to_api( const wchar_t *format, int code );
protected:  
  virtual bool ADDIN_API CallAsProc( const long lMethodNum, tVariant * paParams, const long lSizeArray ) override;   
public:
  Server();
	~Server();
};

