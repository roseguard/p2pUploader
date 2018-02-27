<<<<<<< HEAD
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT "51034"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout << "No file selected " << endl;

        cout << "Need argument (path to the uploading file)";
        cout << endl;
        cout << "If you run it from desktop drag and drop file for uploading on the icon of this programm in system (not here, this one you may close)";
        cout << endl;
        cout << "If you running programm from console - put path to the uploading file as argument";
        int temp;
        std::cin >> temp;
        return 0;
    }

    cout << endl << "Server started on port : " << DEFAULT_PORT;
    cout << endl << "Now you can use your address and port to download " << argv[1] << " from network";
    cout << endl << "Example for localhost(only for your computer) 127.0.0.1:51034";
    cout << endl << "Example for some example local network(only for computer in your local network) 192.168.0.201:51034";
    cout << endl << "Last one was only example address. If you want to send file in internet find out your public address. If you do not know how, you may try to find out on 2ip.ru";

    cout << endl << "(c) roseguardd@gmail.com";


    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("Can't init network: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);

    while(true)
    {
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);

        // No longer need server socket
        //

        std::cout << argv[1] << std::endl;
        HANDLE hFile = CreateFile(argv[1],
                GENERIC_READ,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL);


        int dwSize = GetFileSize(hFile, NULL) ;
        std::cout << "size : " << dwSize << std::endl;
        char sizebuff[100];
        itoa(dwSize, sizebuff, 10);
        std::cout << "sized : " << sizebuff;

        char headerMess[1024] = "HTTP/1.0 200 Ok\r\nContent-Length: ";
        strcat(headerMess, sizebuff);
        strcat(headerMess, "\r\n");
        char fileName[50];
        char fileType[10];
        _splitpath(argv[1], NULL, NULL, fileName, fileType);
        strcat(fileName, fileType);
        strcat(headerMess, "Content-Disposition: attachment; filename=");
        strcat(headerMess, fileName);
        strcat(headerMess, "\r\n");
        strcat(headerMess, "Content-Type: application/xml\r\n");
        strcat(headerMess, "Connection: Keep-Alive\r\n");
        strcat(headerMess, "\r\n");

        int messize = 0;
        while(headerMess[messize])
            messize++;
        DWORD tempShit;
        send(ClientSocket, headerMess, messize, 0);

        for(int i = 0; i < dwSize; i+=1024)
        {
            char buffer[1024];
            auto tempBool = ReadFile(hFile, &buffer, 1024, &tempShit, NULL);
            if(!tempBool)
                cout << "SHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIT" << endl << endl << endl;
            send(ClientSocket, buffer, 1024, 0);
            if(i%1024000 == 0)
            {
                cout << "Sended : " << i << "/" << sizebuff << endl;
            }
            if (iSendResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                break;
            }
        }

        // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
        }
        CloseHandle(hFile);

        // cleanup
        closesocket(ClientSocket);
    }
    closesocket(ListenSocket);
    return 0;
}
=======
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT "51034"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout << "No file selected " << endl;

        cout << "Need argument (path to the uploading file)";
        cout << endl;
        cout << "If you run it from desktop drag and drop file for uploading on the icon of this programm in system (not here, this one you may close)";
        cout << endl;
        cout << "If you running programm from console - put path to the uploading file as argument";
        int temp;
        std::cin >> temp;
        return 0;
    }

    cout << endl << "Server started on port : " << DEFAULT_PORT;
    cout << endl << "Now you can use your address and port to download " << argv[1] << " from network";
    cout << endl << "Example for localhost(only for your computer) 127.0.0.1:51034";
    cout << endl << "Example for some example local network(only for computer in your local network) 192.168.0.201:51034";
    cout << endl << "Last one was only example address. If you want to send file in internet find out your public address. If you do not know how, you may try to find out on 2ip.ru";

    cout << endl << "(c) roseguardd@gmail.com";


    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("Can't init network: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);

    while(true)
    {
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);

        // No longer need server socket
        //

        std::cout << argv[1] << std::endl;
        HANDLE hFile = CreateFile(argv[1],
                GENERIC_READ,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL);


        int dwSize = GetFileSize(hFile, NULL) ;
        std::cout << "size : " << dwSize << std::endl;
        char sizebuff[100];
        itoa(dwSize, sizebuff, 10);
        std::cout << "sized : " << sizebuff;

        char headerMess[1024] = "HTTP/1.0 200 Ok\r\nContent-Length: ";
        strcat(headerMess, sizebuff);
        strcat(headerMess, "\r\n");
        char fileName[50];
        char fileType[10];
        _splitpath(argv[1], NULL, NULL, fileName, fileType);
        strcat(fileName, fileType);
        strcat(headerMess, "Content-Disposition: attachment; filename=");
        strcat(headerMess, fileName);
        strcat(headerMess, "\r\n");
        strcat(headerMess, "Content-Type: application/xml\r\n");
        strcat(headerMess, "Connection: Keep-Alive\r\n");
        strcat(headerMess, "\r\n");

        int messize = 0;
        while(headerMess[messize])
            messize++;
        DWORD tempShit;
        send(ClientSocket, headerMess, messize, 0);

        for(int i = 0; i < dwSize; i+=1024)
        {
            char buffer[1024];
            auto tempBool = ReadFile(hFile, &buffer, 1024, &tempShit, NULL);
            if(!tempBool)
                cout << "SHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIT" << endl << endl << endl;
            send(ClientSocket, buffer, 1024, 0);
            if(i%1024000 == 0)
            {
                cout << "Sended : " << i << "/" << sizebuff << endl;
            }
            if (iSendResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                break;
            }
        }

        // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
        }
        CloseHandle(hFile);

        // cleanup
        closesocket(ClientSocket);
    }
    closesocket(ListenSocket);
    return 0;
}
>>>>>>> d6a68fc62a36db09d520549d288f01e13205569d
