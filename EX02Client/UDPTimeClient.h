#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <iostream>
#include <string>
#define TIME_PORT	27015

void sendRequest(char(&sendBuff)[255], const SOCKET& connSocket, const sockaddr_in& server);
void getResponse(const SOCKET& connSocket, char(&recvBuff)[255], bool isResponesShouldBePrint);
void getResponseFromRequest(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket);
void getClientToServerDelayEstimation(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket);
void measureRTT(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket);
void getTimeWithoutDateInCity(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket);