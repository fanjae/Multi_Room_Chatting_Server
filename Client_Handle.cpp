#include "Client_Handle.h"
static std::map<std::string, std::set<SOCKET>> chatRooms;

ClientEventHandler::ClientEventHandler(SOCKET clientSocket) : socket(clientSocket) {}
bool ClientEventHandler::handleMessage(const std::string& message)
{

	if(message.substr(0,GET_CHATTING_ROOM.length()) == GET_CHATTING_ROOM)
	{
		Handle_Get_Chatting_Room();
	}
	else if (message.substr(0, EXIT_ROOM.length()) == EXIT_ROOM)
	{
		Handle_Exit_Room();
	}
	else if (message.substr(0, HANDLE_CREATE_CHATTING_ROOM.length()) == HANDLE_CREATE_CHATTING_ROOM)
	{
		Handle_Create_Chatting_Room(message.substr(HANDLE_CREATE_CHATTING_ROOM.length(), message.length()));
	}
	else if (message.substr(0, HANDLE_JOIN_CHATTING_ROOM.length()) == HANDLE_JOIN_CHATTING_ROOM)
	{
		Handle_Join_Chatting_Room(message.substr(HANDLE_JOIN_CHATTING_ROOM.length(), message.length()));
	}
	else if (message.substr(0, CLOSE_SOCKET.length()) == CLOSE_SOCKET)
	{
		std::cout << "[Log] : Client disconnected : " << message << std::endl;
		return false;
	}
	else
	{
		const char* buffer = message.c_str();
		std::cout << "[Log] : roomName : " << this->roomName << std::endl;
		for (SOCKET target_socket : chatRooms[this->roomName]) 
		{
			std::cout << "[Log] : target_socket : " << target_socket << std::endl;
			send(target_socket, buffer, sizeof(buffer), 0);
		}
	}
	return true;
}
void ClientEventHandler::Handle_Get_Chatting_Room()
{
	std::string room_List = "";
	if (chatRooms.empty())
	{
		room_List += NO_ROOM;
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
void ClientEventHandler::Handle_Exit_Room()
{
	chatRooms[roomName].erase(this->socket);
	if (chatRooms[roomName].empty()) 
	{
		chatRooms.erase(roomName);
	}
}
void ClientEventHandler::Handle_Create_Chatting_Room(const std::string& message)
{
	this->roomName = message;
	std::string send_message = "";
	if (chatRooms.find(roomName) != chatRooms.end())
	{
		send_message = EXIST_ROOM;
		send(socket, send_message.c_str(), send_message.length(), 0);
	}
	else
	{
		std::cout << "[Log] : Client Create Room : " << message << std::endl;
		chatRooms[message].insert(socket);
		send_message = roomName;
		send(socket, send_message.c_str(), send_message.length(), 0);
	}
}
void ClientEventHandler::Handle_Join_Chatting_Room(const std::string& message)
{
	this->roomName = message;
	std::string send_message = "";
	if (chatRooms.find(roomName) != chatRooms.end())
	{
		send_message = roomName;
		chatRooms[message].insert(socket);
		send(socket, send_message.c_str(), send_message.length(), 0);
	}
	else
	{
		send_message = NOT_EXIST_ROOM;
		send(socket, send_message.c_str(), send_message.length(), 0);
	}
}

void ConnectClient(SOCKET clientSocket)
{
	ClientEventHandler handler(clientSocket);
	char buffer[1024];
	std::string str_buffer;
	
	std::cout << "[Log] Client Connect! " << "clientSocket : "  << clientSocket << std::endl;

	while (true)
	{
		bool message_handle = false;
		int recv_length = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (recv_length <= 0)
		{
			break;
		}
		buffer[recv_length] = '\0';
		str_buffer = buffer;
		std::cout << "[Log] " << str_buffer << std::endl;
		message_handle = handler.handleMessage(str_buffer);
		if (!message_handle) break;
	}
	closesocket(clientSocket);
}