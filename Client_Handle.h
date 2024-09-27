#pragma once
#include <iostream>
#include <string>
#include <winsock2.h>
#include <map>
#include <set>

const std::string GET_CHATTING_ROOM = "/Get_Chatting_Room";
const std::string HANDLE_CREATE_CHATTING_ROOM = "/Create_Chatting_Room ";
const std::string HANDLE_JOIN_CHATTING_ROOM = "/Join_Chatting_Room ";

void ConnectClient(SOCKET clientSocket);

class ClientEventHandler
{
private:
	SOCKET socket;
	
	void Handle_Get_Chatting_Room(const std::string& message);
	void Handle_Create_Chatting_Room(const std::string& message);
	void Handle_Join_Chatting_Room(const std::string& message);
public:
	ClientEventHandler(SOCKET clientSocket);
	void handleMessage(const std::string& message);
};


