#include <iostream> //the c++ console.write funcs
#include <WinSock2.h> //the windows equivalent of sys.socket.h, the linux library i used earlier to enable socket programming; so we can create the UDP datagram.
#include <WS2tcpip.h> //gives us the tools to work with the sockets.
#include "protocol.h"

#pragma comment(lib, "ws2_32.lib") 
int main()
{
	WSADATA wsaData; // Structure to hold information about the Windows Sockets implementation, necessary for initializing the socket library. creates a bucket in the RAM
	WSAStartup(MAKEWORD(2, 2), &wsaData); // Initializes the Winsock library, specifying the version (2.2) and passing a pointer to the WSADATA structure to receive details about the implementation.

	SOCKET receiverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in receiverAddr; // Structure to hold the address information for the receiver socket, including IP address and port number.
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(5005);
	receiverAddr.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces, allowing the receiver to accept packets from any source.

	bind(receiverSocket, (sockaddr*)&receiverAddr, sizeof(receiverAddr)); // Binds the receiver socket to the specified address and port, enabling it to receive incoming UDP packets sent to that port.
	std::cout << "Receiver is listening on port 5005..." << std::endl;

	RadarPacket packet;
	sockaddr_in senderAddr;

	int senderAddrLen = sizeof(senderAddr);

	while (true) {
		int result = recvfrom(receiverSocket, (char*)&packet, sizeof(packet), 0, (sockaddr*)&senderAddr, &senderAddrLen); // Waits for incoming UDP packets and receives them into the packet structure, while also capturing the sender's address information.

		if (result > 0) {
			std::cout << "Target Locked [ID: " << packet.packet_id
				<< "] Signal: " << packet.value << std::endl;
		}
	}
	//remember to clean up, c# doesnt have this problem because of the garbage collector, so i have a slight feeling im going to forget this quite a bit.
	closesocket(receiverSocket);
	WSACleanup();
	return 0;
}