#include <iostream>
#include <winsock2.h>
#include <thread>
int main(int argc, char* argv[])
{
	char message[] = "Message";
	WSADATA wsaData;
	SOCKET serverSocket;
	SOCKADDR_IN serverAddr;

	if (argc != 2)
	{
		std::cerr << "Usage : " << argv[0] << "  <port>";
		return 1;
	}


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup() Error" << std::endl;
		return 1;
	}

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cerr << "Socket() Error" << std::endl;
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(atoi(argv[1]));

	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		std::cerr << "bind() Error" << std::endl;
		return 1;
	}

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "listen() Error" << std::endl;
		return 1;
	}

	SOCKET clientSocket;
	SOCKADDR_IN clientAddr;
	int clientAddrsize = sizeof(clientAddr);

	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrsize);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "accept() Error" << std::endl;
	}
	send(clientSocket, message, strlen(message), 0);
}