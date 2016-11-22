#include "observer.h"

class Server : public IObserver
{
public:
    Server();
    ~Server();

    void update(int);

private:
    int shmKey_;
};

