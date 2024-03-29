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
void userInputCityMenu(char* outStr, char userCityInput[255]) {

		if (strcmp(userCityInput, "1") == 0) {
			sprintf(outStr, "%s", "GetTimeWithoutDateInCity1");
		}
		else if (strcmp(userCityInput, "2") == 0) { // Prague
			sprintf(outStr, "%s", "GetTimeWithoutDateInCity2");
		}
		else if (strcmp(userCityInput, "3") == 0) {// New York
			sprintf(outStr, "%s", "GetTimeWithoutDateInCity3");
		}
		else if (strcmp(userCityInput, "4") == 0) {// Berlin
			sprintf(outStr, "%s", "GetTimeWithoutDateInCity4");
		}
		else if (strcmp(userCityInput, "5") == 0) {// Universal
			sprintf(outStr, "%s", "GetTimeWithoutDateInCity5");
		}
		else{ //Illegal
			sprintf(outStr, "%s", "Illegal");
		}

}
void getResponseFromRequest(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket) {
	sendRequest(sendBuff, connSocket, server);
	getResponse(connSocket, recvBuff, true);
}
void getClientToServerDelayEstimation(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket) {
	double sum = 0;
	double prevResponse = 0;
	double response = 0;
	strcpy(sendBuff, "GetClientToServerDelayEstimation");
	for (int i = 0; i < 100; i++) {
		sendRequest(sendBuff, connSocket, server);
	}
	for (int i = 0; i < 100; i++) {
		getResponse(connSocket, recvBuff,false);
		sscanf_s(recvBuff, "%lf", &response);
		if (i != 0) {
			sum += response - prevResponse;
		}
		prevResponse = response;
	}
	double avg = sum / 99;
	cout << "Time client : client to server delay estimation in msec: " << avg << endl;
}
void measureRTT(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket) {
	double sum = 0;
	unsigned int startTime = 0;
	unsigned int endTime = 0;
	double avg = 0;
	strcpy(sendBuff, "MeasureRTT");
	for (int i = 0; i < 100; i++) {
		startTime = GetTickCount();
		sendRequest(sendBuff, connSocket, server);
		getResponse(connSocket, recvBuff,false);
		endTime = GetTickCount();
		sum += endTime-startTime;
	}
    avg = sum / 100;
	cout << "Time client : client to server RTT measured in msec: " << avg << endl;

}
void getTimeWithoutDateInCity(char(&sendBuff)[255], char(&recvBuff)[255], const sockaddr_in& server, const SOCKET& connSocket) {
	char selectedOption[255] = "GetTimeWithoutDateInCity";
	printCityMenu();
	char userCityInput[255];
	cin >> userCityInput;
	userInputCityMenu(selectedOption, userCityInput);
	while (!strcmp("Illegal", selectedOption)) {
		cout << "Illegal,please select a valid option.\n";
		cin >> userCityInput;
		userInputCityMenu(selectedOption, userCityInput);
	}
	strcpy(sendBuff, selectedOption);
	sendRequest(sendBuff, connSocket, server);
	getResponse(connSocket, recvBuff,true);
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

		if (strcmp(selectedOption, "1") == 0)		{
			strcpy(sendBuff, "GET_TIME");
			getResponseFromRequest(sendBuff,recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "2") == 0){
			strcpy(sendBuff, "GetTimeWithoutDate");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "3") == 0){
			strcpy(sendBuff, "GetTimeSinceEpoch");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "4") == 0){
			getClientToServerDelayEstimation(sendBuff, recvBuff, server, connSocket);		
		}
	    else if (strcmp(selectedOption, "5") == 0){
			measureRTT(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "6") == 0){
			strcpy(sendBuff, "GetTimeWithoutDateOrSeconds");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "7") == 0){
			strcpy(sendBuff, "GetYear");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "8") == 0){
			strcpy(sendBuff, "GetMonthAndDay");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "9") == 0){
			strcpy(sendBuff, "GetSecondsSinceBeginingOfMonth");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "10") == 0){
			strcpy(sendBuff, "GetWeekOfYear");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "11") == 0){
			strcpy(sendBuff, "GetDaylightSavings");
			getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
		}
	    else if (strcmp(selectedOption, "12") == 0){
		getTimeWithoutDateInCity(sendBuff, recvBuff, server, connSocket);
		}
		else if (strcmp(selectedOption, "13") == 0){
				strcpy(sendBuff, "MeasureTimeLap");
				getResponseFromRequest(sendBuff, recvBuff, server, connSocket);
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
	bytesSent = sendto(connSocket, sendBuff, (int)strlen(sendBuff), 0, (const sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		exit(0);
	}
		
	if((strcmp(sendBuff, "MeasureRTT")!=0)&&(strcmp(sendBuff, "GetClientToServerDelayEstimation")!=0)){
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(sendBuff) << " bytes of \"" << sendBuff << "\" message.\n";
	}
}
void getResponse(const SOCKET& connSocket, char(&recvBuff)[255], bool isResponesShouldBePrint) {
	int bytesRecv = 0;
	bytesRecv = recv(connSocket, recvBuff, 255, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		exit(0);
	}
	recvBuff[bytesRecv] = '\0';
	if (isResponesShouldBePrint) {
		cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n" << endl;
	}
}
