#include "stdafx.h"
#include "Server.h"

Server::Server( ) {
  properties = (APIproperty*)malloc(sizeof(APIproperty) * 3);
  properties[0] = { { L"Port",	L"Порт" }, true, true, 0 };
  properties[1] = { { L"TypeRequest",	L"ТипЗапроса" }, true, true, 0 };
  properties[2] = { { L"StrRequest",	L"СтрокаЗапроса" }, true, false, 0 };

  functions = (APIfunction*)malloc( sizeof( APIfunction ) * 2 );
  functions[0] = { { L"Start", L"Запустить" }, 0, false };
  functions[1] = { {L"Stop",	L"Остановить" }, 0, false };
  
  this->prop_count = 3;
  this->func_count = 2;
}

Server::~Server( ) {
  free( properties );
  free( functions );
}

bool Server::CallAsProc( const long lMethodNum, tVariant * paParams, const long lSizeArray ) {
  switch( lMethodNum ) {
    case 0:
      return this->start_server( );
    case 1:
      return this->stop_server( );
    default:
      break;
  }
  return false;
}

PCWSTR Server::convert_api_string( PCWSTR str, int len ) {
  PCWSTR str_new = (PCWSTR)malloc( sizeof( wchar_t ) * (len + 1));
  ZeroMemory( (void*)str_new, sizeof( wchar_t ) * ( len + 1 ) );
  memcpy( (void*)str_new, str, sizeof( wchar_t ) * len );
  return str_new;
}

bool Server::start_server() {
  int iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );  

  if( iResult != 0 ) {
    wsa_error_to_api( L"WSAStartup failed with error:", iResult );    
    return false;
  }

  ZeroMemory( &hints, sizeof( hints ) );
  hints.ai_family   = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags    = AI_PASSIVE;  
  
  tVariant *port_var = this->properties[0].value;
  if( !port_var ) {    
    m_iConnect->AddError( iResult, L"Необходимо задать порт", L" Укажите ПОРТ = строка", 0 );
    return false;
  }

  PCWSTR port = convert_api_string(TV_WSTR( port_var ), port_var->wstrLen);

  iResult = GetAddrInfo( NULL, port , &hints, &result );
  if( iResult != 0 ) {
    wsa_error_to_api(L"getaddrinfo failed with error:", iResult);    
    WSACleanup( );
    return 1;
  }
  
  
  ListenSocket = socket( result->ai_family, result->ai_socktype, result->ai_protocol );
  if( ListenSocket == INVALID_SOCKET ) {
    wsa_error_to_api(L"socket failed with error: %d %s\0", WSAGetLastError() );    
    WSACleanup( );
    return 1;
  }

  iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen );
  if( iResult == SOCKET_ERROR ) {
    wsa_error_to_api(L"socket failed with error: %d %s\0", WSAGetLastError( ) );    
    closesocket( ListenSocket );
    WSACleanup( );
    return 1;
  }

  if( listen( ListenSocket, 1 ) == SOCKET_ERROR ) {
    wsa_error_to_api(L"listen failed with error: %d %s\0", WSAGetLastError( ) );    
    closesocket( ListenSocket );
    WSACleanup( );
    return 1;
  } 

  listen_th = std::thread( &Server::listen_socket, this );

  return true;
}

bool Server::stop_server( ) {
  stop_listen = true;
  listen_th.join( );
  FreeAddrInfo( result );  
  closesocket( ListenSocket );
  shutdown( ClientSocket, SD_BOTH );
  WSACleanup( );
  return true;
}

void Server::wsa_error_to_api( const wchar_t *message, int code) {
  wchar_t *buf = (wchar_t*)LocalAlloc(LHND, 200);
  wchar_t *s = NULL;
  FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, WSAGetLastError( ),
                  MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                  (LPWSTR)&s, 0, NULL );
  wsprintf( buf, L"%s [no.: %d]\0", message, code);
  m_iConnect->AddError( code, buf, s, WSAGetLastError( ) );
  LocalFree( s );
  LocalFree( buf );
}

void Server::listen_socket( ) {
  int16_t len;
  char *buf = (char*)malloc( 100 );

  while( !stop_listen ) {
    SOCKET listen_sc = accept( ListenSocket, NULL, NULL );
    if( listen_sc == INVALID_SOCKET ) {
      wsa_error_to_api( L"accept failed with error", WSAGetLastError( ) );
      continue;
    }
    len = recv( listen_sc, buf, 10, MSG_WAITALL );
    if( len == -1 ) {
      this->wsa_error_to_api( L"Recive data error", WSAGetLastError( ) );
      return;
    }
    //std::thread lsc = std::thread( &Server::listen_client, this, listen_sc );
    //lsc.detach( );
  }  
  free( buf );
}

void Server::listen_client( SOCKET soc ) {
  /*
    
  while(!stop_listen ){
    
    
  }

  */
}
