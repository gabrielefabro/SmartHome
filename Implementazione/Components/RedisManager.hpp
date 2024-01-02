#ifndef REDIS_MANAGER_HPP
#define REDIS_MANAGER_HPP

#include <cpp_redis/cpp_redis>

class RedisManager {
public:
    RedisManager();

    void sendCommand(const std::string &command);

private:
    cpp_redis::client client;
};

#endif // REDIS_MANAGER_HPP
