#include "UDPTimeClient.h"

void displayMenuOptions()
{
	cout << "==================Menu================== " << endl;
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
    cout << "========================================== " << endl;
	cout << "Please select an option (to exit press 0)" << endl;
}
void printCityMenu()
{
	cout << "Please choose a city:" << endl;
	cout << "1. Doha" << endl;
	cout << "2. Prague" << endl;
	cout << "3. New York" << endl;
	cout << "4. Berlin" << endl;
	cout << "5. UTC" << endl;
}
void userInputCityMenu(char* outStr, int userCityInput) {
	switch (userCityInput)
	{
	case 1:
		sprintf(outStr, "%s", "GetTimeWithoutDateInCity1");	
		break;
	case 2: // Prague
	    sprintf(outStr, "%s", "GetTimeWithoutDateInCity2");
		break;
	case 3: // New York
		sprintf(outStr, "%s", "GetTimeWithoutDateInCity3");
		break;
	case 4: // Berlin
		sprintf(outStr, "%s", "GetTimeWithoutDateInCity4");
			break;
	case 5: // Universal
		sprintf(outStr, "%s", "GetTimeWithoutDateInCity5");
		break;
	default://Illegal
		sprintf(outStr, "%s", "Illegal");
		break;
	}

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
			sendRequest(sendBuff,connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "2") == 0)
		{
			strcpy(sendBuff, "GetTimeWithoutDate");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "3") == 0)
		{
			strcpy(sendBuff, "GetTimeSinceEpoch");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "4") == 0)
		{
			double sum = 0;
			double prevResponse = 0;
			double response = 0;
			strcpy(sendBuff, "GetClientToServerDelayEstimation");
			for (int i = 0; i < 100; i++) {
				sendRequest(sendBuff, connSocket, server);
			}
			for (int i = 0; i < 100; i++) {
				getResponse(connSocket, recvBuff);
				
				if (i != 0) {
					sum += (stoi(recvBuff)) - prevResponse;
				}
				prevResponse = stoi(recvBuff);
			}
			double avg = sum / 99;
			cout << "Time client : client to server delay estimation in msec: " << avg << endl;
		}
	else if (strcmp(selectedOption, "5") == 0)
		{
			double sum = 0;
			double prevResponse = 0;
			double response = 0;
			unsigned int startTime = 0;
			unsigned int endTime = 0;
			strcpy(sendBuff, "MeasureRTT");
			for (int i = 0; i < 100; i++) {
				    startTime=GetTickCount();
					sendRequest(sendBuff, connSocket, server);
					getResponse(connSocket, recvBuff);
					endTime = GetTickCount();
				if (i != 0) {
					sum += (stoi(recvBuff)) - prevResponse;
				}
				prevResponse = stoi(recvBuff);
			}
			double avg = sum / 100;
			cout << "Time client : client to server RTT measured in msec: " << avg << endl;
			cout << "\nRTT Estimation in msec: " << avg << endl;
		}
	else if (strcmp(selectedOption, "6") == 0)
		{
			strcpy(sendBuff, "GetTimeWithoutDateOrSeconds");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "7") == 0)
		{
			strcpy(sendBuff, "GetYear");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "8") == 0)
		{
			strcpy(sendBuff, "GetMonthAndDay");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "9") == 0)
		{
			strcpy(sendBuff, "GetSecondsSinceBeginingOfMonth");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "10") == 0)
		{
			strcpy(sendBuff, "GetWeekOfYear");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "11") == 0)
		{
			strcpy(sendBuff, "GetDaylightSavings");
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
	else if (strcmp(selectedOption, "12") == 0)
		{
			char selectedOption[255] = "GetTimeWithoutDateInCity";
			printCityMenu();
			int userCityInput;
			cin >> userCityInput;
			userInputCityMenu(selectedOption, userCityInput);
			while (!strcmp("Illegal", selectedOption)) {
				cout << "Illegal,please select a valid option.\n";
				cin >> userCityInput;
				userInputCityMenu(selectedOption, userCityInput);
			}
			strcpy(sendBuff, selectedOption);
			sendRequest(sendBuff, connSocket, server);
			getResponse(connSocket, recvBuff);
		}
		else if (strcmp(selectedOption, "13") == 0)
		{
				strcpy(sendBuff, "MeasureTimeLap");
				sendRequest(sendBuff, connSocket, server);
				getResponse(connSocket, recvBuff);
		}
		else {
			cout << "Select an valid option.\n";
		}
		displayMenuOptions();
		cin >> selectedOption;
	}
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}

void sendRequest(char(&sendBuff)[255],const SOCKET& connSocket, const sockaddr_in& server) {
	int bytesSent = 0;
	//char sendBuff[255] = "";
	bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		//return;
		exit(0);
	}
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";

}
void getResponse(const SOCKET& connSocket, char(&recvBuff)[255] ) {
	int bytesRecv = 0;
	bytesRecv = recv(connSocket, recvBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
	//	return;
		exit(0);
	}
	recvBuff[bytesRecv] = '\0';
	cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n" << endl;

}
