//need multi argument logger
//need list (for loop) logger
//need conditional logger

#ifndef DEBUG_LOGGER_HPP
    #define DEBUG_LOGGER_HPP
    #include<iostream>
    #ifndef dblogs
        #define LOG(a) ;
    #else
        #define LOG(a)  std::cout << (a);
    #endif
#endif

/*

would use a different macro
#define INPUT(a) std::cin >> *a;

//#define LOGBREAK "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"


*/