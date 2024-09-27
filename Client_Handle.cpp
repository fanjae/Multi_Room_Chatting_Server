#include "Client_Handle.h"
static std::map<std::string, std::set<SOCKET>> chatRooms;

ClientEventHandler::ClientEventHandler(SOCKET clientSocket) : socket(clientSocket) {}
void ClientEventHandler::handleMessage(const std::string& message)
{

	if(message.substr(0,GET_CHATTING_ROOM.length()) == GET_CHATTING_ROOM)
	{
		Handle_Get_Chatting_Room();
	}
	else if (message.substr(0, HANDLE_CREATE_CHATTING_ROOM.length()) == HANDLE_CREATE_CHATTING_ROOM)
	{
		Handle_Create_Chatting_Room(message.substr(HANDLE_CREATE_CHATTING_ROOM.length(), message.length()));
	}
	else if (message.substr(0, HANDLE_JOIN_CHATTING_ROOM.length()) == HANDLE_JOIN_CHATTING_ROOM)
	{
		Handle_Join_Chatting_Room(message.substr(HANDLE_JOIN_CHATTING_ROOM.length(), message.length()));
	}
	else
	{


		for (SOCKET target_socket : chatRooms[this->roomName]) 
		{
			if (target_socket != socket) {
				send(socket, buffer, bytesReceived, 0);
			}
		}
	}
}
void ClientEventHandler::Handle_Get_Chatting_Room()
{
	std::string room_List = "";
	if (chatRooms.empty())
	{
		room_List += "/No_Rooms";
	}
	else
	{
		for (auto& room : chatRooms)
		{
			room_List += room.first + "\n";
		}
	}
	send(socket, room_List.c_str(), room_List.length(), 0);
}
void ClientEventHandler::Handle_Create_Chatting_Room(const std::string& message)
{

}
void ClientEventHandler::Handle_Join_Chatting_Room(const std::string& message)
{
	this->roomName = message;
	chatRooms[message].insert(socket);
}

void ConnectClient(SOCKET clientSocket)
{
	ClientEventHandler handler(clientSocket);
	char buffer[1024];
	std::string str_buffer;
	
	std::cout << "[Log] Client Connect!" << std::endl;

	while (true)
	{
		int recv_length = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (recv_length <= 0)
		{
			closesocket(clientSocket);
		}
		buffer[recv_length] = '\0';
		str_buffer = buffer;
		handler.handleMessage(str_buffer);
	}
}