#include <string>
#include <iostream>
#include <AccCtrl.h>
#include <thread>

#include "Sendler.h"
#include "Settings.h"


void send_http(std::string nameprocess, Settings settings)
{
    HTTP http;
    for (int i = 0; i < settings.get_count(); i++) {
        http.sendHTTP(settings.get_http());
    }
}

void send_tcp(std::string nameprocess, Settings settings)
{
    Socket socket;
    for (int i = 0; i < settings.get_count(); i++) {
        socket.sendTCPPacket(settings.get_ip(), settings.get_port_tcp());
    }
}

void send_udp(std::string nameprocess, Settings settings)
{
    Socket socket;
    for (int i = 0; i < settings.get_count(); i++) {
        socket.sendUDPPacket(settings.get_ip(), settings.get_port_udp());
    }
}

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

int main(int argc, char* argv[]) {

    Settings settings;
    if (argc == 1) { return 0; }
    for (int index = 1; index < argc; index++) {
        std::string command(argv[index]);

        if (command == "-http") {
            std::string http(argv[index + 1]);
            settings.set_http(http);
            index++;
        }
        else if (command == "-ip") {
            settings.set_ip(argv[index + 1]);
            index++;
        }
        else if (command == "-tcp") {
            int port = std::stoi(argv[index + 1]);
            settings.set_port_tcp(port);
            index++;
        }
        else if (command == "-udp") {
            int port = std::stoi(argv[index + 1]);
            settings.set_port_udp(port);
            index++;
        }
        else if (command == "-count") {
            settings.set_count(std::stoi(argv[index + 1]));
            index++;
        }
        else if (command == "-script_dll") {

            typedef void(__cdecl* FN_CALL)(int, char* []);
            FN_CALL Func;

            HINSTANCE dll = LoadLibrary(convertCharArrayToLPCWSTR(argv[index + 1])); //searth dll file
            if (dll == NULL) { std::cout << "Lib " << argv[index + 1] << " not found!\n"; return -1; }

            Func = (FN_CALL)GetProcAddress(dll, argv[index + 2]); // start dll searth funcs
            if (!Func) { std::cout << "Function " << argv[index + 2] << " not found!\n"; return -1; }

            Func(argc, argv); // searth and start func

            FreeLibrary(dll);
            return 0;
        }
        else if (command == "-noweb") {
            ;
        }

    }
    if (settings.get_http().c_str()) {
        std::thread http(send_http, "http", settings);
        http.join();
    }

    if (settings.get_ip()) {
        if (settings.get_port_tcp()) {

            std::thread tcp(send_tcp, "udp", settings);
            tcp.join();
        }
        if (settings.get_port_udp()) {
            std::thread udp(send_udp, "tcp", settings);
            udp.join();
        }

    }

    return 0;
}