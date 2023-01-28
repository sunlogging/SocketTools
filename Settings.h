#pragma once
#include <iostream>

#define THREAD_LEN 1
#define TCPSIZE 60
#define UDPSIZE 65535 


class Settings {
private:
    char* IP;
    int COUNT, PORTTCP, PORTUDP;
    //std::string HTTP, SYN, UDP, MAC;
    std::string HTTP;
public:

    void set_http(std::string http) { this->HTTP = http; }
    std::string get_http() { return this->HTTP; }


    void set_count(int count) { this->COUNT = count / THREAD_LEN; }
    int get_count() { return this->COUNT; }

    void set_port_tcp(int port) { this->PORTTCP = port; }
    int get_port_tcp() { return this->PORTTCP; }

    void set_port_udp(int port) { this->PORTUDP = port; }
    int get_port_udp() { return this->PORTUDP; }

    void set_ip(char* ip) { this->IP = ip; }
    char* get_ip() { return this->IP; }


    //void set_syn(std::string syn) { this->SYN = syn; }
    //std::string get_syn() { return this->SYN; }

    //void set_udp(std::string udp) { this->UDP = udp; }
    //std::string get_udp() { return this->HTTP; }

    //void set_mac(std::string mac) { this->MAC = mac; }
    //std::string get_mac() { return this->MAC; }
};
