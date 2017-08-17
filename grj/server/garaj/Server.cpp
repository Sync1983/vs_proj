#include "stdafx.h"
#include "Server.h"
#include "functions.h"

Server::Server( ) {
  
}

Server::~Server( ) { }

bool ADDIN_API Server::CallAsProc( const long lMethodNum, tVariant * paParams, const long lSizeArray ) {
  switch( (Functs) lMethodNum ) {
    case start:
      return start_server( );
    break;
    case stop:
      return stop_server( );
    break;
    default:
      break;
  }
  return false;
}


bool Server::start_server( ) {
  int iResult = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
  wchar_t buf[100];

  if( iResult != 0 ) {
    wsprintf(buf, L"WSAStartup failed with error: %d\0", iResult );
    m_iConnect->AddError( iResult, buf, L"", 0 );
    return false;
  }

  ZeroMemory( &hints, sizeof( hints ) );
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags    = AI_PASSIVE;
  
  tVariant *port_var = this->properties[typePort].value;
  if( !port_var ) {    
    m_iConnect->AddError( iResult, L"Необходимо задать порт", L" Укажите ПОРТ = строка", 0 );
    return false;
  }

  wchar_t *port = TV_WSTR( port_var );

  iResult = GetAddrInfo( NULL, port , &hints, &result );
  if( iResult != 0 ) {    
    wsprintf( buf, L"getaddrinfo failed with error: %d\0", iResult );
    m_iConnect->AddError( iResult, buf, L"", 0 );
    WSACleanup( );
    return 1;
  }
  
  /*
  ListenSocket = socket( result->ai_family, result->ai_socktype, result->ai_protocol );
  if( ListenSocket == INVALID_SOCKET ) {
    printf( "socket failed with error: %ld\n", WSAGetLastError( ) );
    freeaddrinfo( result );
    WSACleanup( );
    return 1;
  }

  // Setup the TCP listening socket
  iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen );
  if( iResult == SOCKET_ERROR ) {
    printf( "bind failed with error: %d\n", WSAGetLastError( ) );
    freeaddrinfo( result );
    closesocket( ListenSocket );
    WSACleanup( );
    return 1;
  }*/

  if( result != NULL ) {
    FreeAddrInfo( result );
  }

  return true;
}

bool Server::stop_server( ) {
  WSACleanup( );
  return false;
}
