#include "RedisManager.hpp"

RedisManager::RedisManager() {
    client.connect("127.0.0.1", 6379, [](const std::string &host, std::size_t port, cpp_redis::client::connect_state status) {
        if (status == cpp_redis::client::connect_state::dropped) {
            std::cerr << "Lost connection to Redis at " << host << ":" << port << std::endl;
        }
    });
}

void RedisManager::sendCommand(const std::string &command) {
    client.sync_commit({command}, [](cpp_redis::reply &reply) {
        // Puoi gestire la risposta qui, se necessario
    });
}
