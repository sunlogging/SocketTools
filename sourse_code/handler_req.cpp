#include "handler_req.h"
#include "settings.h"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <curl/curl.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libcurl.lib")

#include <iostream>

int WINAPI WSAGetLastError(void);

void HTTP::sendHTTP(std::string target)
{
    CURL* curl;
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, target.c_str());
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

}


void Socket::sendUDPPacket(char* destIP, int destPort){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(destPort);

    inet_pton(AF_INET, destIP, &servaddr.sin_addr);
    

    WSAGetLastError();
    char data[UDPSIZE] = {};
    int resultSend = sendto(sock, data, UDPSIZE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    std::cout << "\n" << resultSend << "\n" << WSAGetLastError() << "\n";

    closesocket(sock);
    //int sockfd;
    //struct sockaddr_in server_addr;

    ////Create the socket
    //sockfd = socket(AF_INET, SOCK_DGRAM,
    //    IPPROTO_UDP);

    ////configure settings in address struct
    //server_addr.sin_family = AF_INET;
    //server_addr.sin_port = htons(destPort);
    //
    //server_addr.sin_addr.s_addr = (ULONG)destIP; //IP address here
    //
    //
    //memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

    ////Send UDP packet
    //char buf[] = "Hello, World!";
    //int len;
    //len = strlen(buf) + 1;
    //if (len > 0)
    //{WSAGetLastError();
    //   int res =  sendto(sockfd, buf, len, 0,
    //        (struct sockaddr*)&server_addr,
    //        sizeof(server_addr));
    //    std::cout << WSAGetLastError() << " " << res;
    //}
}

void Socket::sendTCPPacket(char* destIP, int destPort) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(destPort);
    inet_pton(AF_INET, destIP, &(servaddr.sin_addr));

    connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    char data[TCPSIZE] = {};
    send(sock, data, TCPSIZE, 0);

    closesocket(sock);
}