#pragma once
#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <mutex>

extern "C" {
    class KaiSocket
    {
    public:
        KaiSocket() {};
        KaiSocket(unsigned short servport);
        KaiSocket(const char* srvip, unsigned short servport);
        virtual ~KaiSocket();
        int start();
        int connect();
        int send(const char* data, int len);
        int broadcast(const char* data, int len);
        int broker(char* data, int len);
        int recv(char* buff, int len);
        bool running();
        static void wait(unsigned int tms);
        void setCallback(void(*func)(void*));
        void addCallback(void(*func)(void*));
        // call after connect()
        // 3 - pubilsher; 4 - subscriber
        inline void setTopic(std::string topic, int tag = 3) {
            memcpy(current.flag.mqid, topic.c_str(), 32);
            current.flag.etag = tag;
        };
    private:
        struct Header {
            char resv;
            int etag;
            volatile unsigned long long ssid; //ssid = port | socket | ip
            char mqid[32]; // topic
            int size;
        };
        struct Network {
            int socket;
            std::string IP;
            unsigned short PORT;
            volatile bool run_ = false;
            Header flag;
        } current;
        bool server = false;
        bool thdref = false;
        volatile unsigned int g_threadNo_ = 0;
        std::vector<Network> networks;
        std::vector<void(*)(void*)> callbacks;
        void handleNotify(int socket);
        void runCallback(KaiSocket* sock, void(*func)(void*));
        unsigned long long setSsid(Network network, int socket);
        bool verifySsid(Network network, unsigned long long ssid);
    public:
        struct Message {
            Header head;
            struct Payload {
                char result[8];
                char body[256];
            } data;
        };
        int produceClient(std::string body, ...);
        int consumeClient();
    private:
        int produce(Message& msg);
        int consume(Message& msg);
        std::deque<Message*> *msgque = new std::deque<Message*>();
    };
}
