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


void displayMenuOptions()
{
	cout << "Please select an option (to exit press 0)" << endl;
	cout << "1.  " << "Get time" << endl;
	cout << "2.  " << "Get time Without date" << endl;
	cout << "3.  " << "Get time since epoch" << endl;
	cout << "4.  " << "Get client to server delay estimation" << endl;
	cout << "5.  " << "Mesure RTT" << endl;
	cout << "6.  " << "Get time withouth date or seconds" << endl;
	cout << "7.  " << "Get year" << endl;
	cout << "8.  " << "Get month and day" << endl;
	cout << "9.  " << "Get seconds since beginning of the month" << endl;
	cout << "10. " << "Get week of year" << endl;
	cout << "11. " << "Get day light savings" << endl;
	cout << "12. " << "Get time without date in city" << endl;
	cout << "13. " << "Measure time lap" << endl;
}


void main()
{


	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}



	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);


	int bytesSent = 0;
	int bytesRecv = 0;
	int selectesOptionNumber = 0;
	char recvBuff[255];
	char selectedOption[255];
	char sendBuff[255]="";

	displayMenuOptions();
	cin >> selectedOption;
	while (strcmp(selectedOption, "0") != 0){
		if (strcmp(selectedOption, "1") == 0)
		{
			strcpy(sendBuff, "GET_TIME");
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0';
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		}
		if (strcmp(selectedOption, "2") == 0)
		{
			strcpy(sendBuff, "GetTimeWithoutDate");
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0';
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		}
		if (strcmp(selectedOption, "3") == 0)
		{
			strcpy(sendBuff, "GetTimeSinceEpoch");
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0';
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		}
		if (strcmp(selectedOption, "4") == 0)
		{
			double sum = 0;
			double prevResponse = 0;
			double response = 0;
			strcpy(sendBuff, "GetClientToServerDelayEstimation");
			for (int i = 0; i < 100; i++) {
				bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			}
			for (int i = 0; i < 100; i++) {
				bytesRecv = recv(connSocket, recvBuff, 255, 0);
				if (SOCKET_ERROR == bytesRecv)
				{
					cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				recvBuff[bytesRecv] = '\0';
				if (i != 0) {
					sum += (stoi(recvBuff)) - prevResponse;
				}
				prevResponse = stoi(recvBuff);
			}
			double avg = sum / 100;
			cout <<"Time client : client to server delay estimation in msec: "<< avg << endl;
		}
		if (strcmp(selectedOption, "5") == 0)
		{
			double sum = 0;
			double prevResponse = 0;
			double response = 0;
			unsigned int startTime = 0;
			unsigned int endTime = 0;
			strcpy(sendBuff, "MeasureRTT");
			for (int i = 0; i < 100; i++) {
				startTime=GetTickCount();
				bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
				if (SOCKET_ERROR == bytesSent)
				{
					cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
				bytesRecv = recv(connSocket, recvBuff, 255, 0);
				endTime = GetTickCount();
				if (SOCKET_ERROR == bytesRecv)
				{
					cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
					closesocket(connSocket);
					WSACleanup();
					return;
				}
				recvBuff[bytesRecv] = '\0';
				if (i != 0) {
					sum += (stoi(recvBuff)) - prevResponse;
				}
				prevResponse = stoi(recvBuff);
			}
			double avg = sum / 100;
			cout << "Time client : client to server RTT measured in msec: " << avg << endl;
			cout << "\nRTT Estimation in msec: " << avg << endl;
		}
		if (strcmp(selectedOption, "6") == 0)
		{
			strcpy(sendBuff, "GetTimeWithoutDateOrSeconds");
			bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
			if (SOCKET_ERROR == bytesSent)
			{
				cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}
			cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

			bytesRecv = recv(connSocket, recvBuff, 255, 0);
			if (SOCKET_ERROR == bytesRecv)
			{
				cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
				closesocket(connSocket);
				WSACleanup();
				return;
			}

			recvBuff[bytesRecv] = '\0';
			cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
		}

		displayMenuOptions();
		cin >> selectedOption;

	}






















	/*bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

	bytesRecv = recv(connSocket, recvBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; 
	cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";*/

	
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}