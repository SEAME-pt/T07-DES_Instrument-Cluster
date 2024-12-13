#pragma once

#include <linux/can.h>      // Para struct can_frame
#include <linux/can/raw.h>  // Para CAN_RAW
#include <sys/socket.h>     // Para socket()
#include <sys/ioctl.h>      // Para ioctl() e SIOCGIFINDEX
#include <net/if.h>         // Para struct ifreq
#include <cstring>          // Para std::strncpy
#include <stdexcept>        // Para std::runtime_error
#include <unistd.h>         // Para close()
#include <iostream>         // Para std::cout e std::cerr
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class CANBus {
private:
    int socket_fd; // File descriptor para o socket CAN
public:
    CANBus();
    CANBus(const std::string& interface, int bitrate);
    ~CANBus();

    bool sendMessage(uint32_t id, const std::vector<uint8_t>& data);
    bool receiveMessage(uint32_t& id, std::vector<uint8_t>& data);
};
