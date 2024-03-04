#pragma once

#define LOG(str) \
    std::cout << __FILE__ << ":" << __LINE__ << " " << \
    __DATE__ << " " << __TIME__ << " : " << str << std::endl;