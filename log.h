typedef enum  
{ 
    LOG_LEVEL_OFF=0,
    LOG_LEVEL_ERROR, 
    LOG_LEVEL_WARNING, 
    LOG_LEVEL_INFO, 
    LOG_LEVEL_ALL
}LOG_LEVEL; 

    // printf("\nFILE:%s LINE:%d,FUNC:%s  ", __FILE__, __LINE__ ,__func__); 
#define log(level,...) \
do { \
     if(level<=LEVEL) \
     { \
    printf("\tLevel %d \t", level); \
    printf(__VA_ARGS__); \
     } \
} while (0) 

#define LOGA(...) \
do { \
    log(LOG_LEVEL_ALL,__VA_ARGS__); \
} while (0) 

#define LOGI(...) \
do { \
    log(LOG_LEVEL_INFO,__VA_ARGS__); \
} while (0) 

#define LOGW(...) \
do { \
    log(LOG_LEVEL_WARNING,__VA_ARGS__); \
} while (0) 

#define LOGE(...) \
do { \
    log(LOG_LEVEL_ERROR,__VA_ARGS__); \
} while (0) 