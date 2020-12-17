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


//https://stackoverflow.com/questions/597078/file-line-and-function-usage-in-c
/*

would use a different macro
#define INPUT(a) std::cin >> *a;

//#define LOGBREAK "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"


*/