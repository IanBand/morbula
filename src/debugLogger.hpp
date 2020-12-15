#ifndef DEBUG_LOGGER_HPP
    #define DEBUG_LOGGER_HPP
    #ifndef dblogs
        #define LOG(a) ;
    #else
        #define LOG(a)  std::cout << (a) << std::endl;
    #endif
#endif