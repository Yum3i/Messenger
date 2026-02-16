#include<string>
class Work {
public:
    Work();
    ~Work();
    std::string reception(int work_sock);
    void send_message(int work_sock, std::string msg);

private:
    int work_sock;
};