/*
    const char *__path: 文件路径
    int __oflag: 用于指定打开文件的方式,可以是以下选项的组合:
        (1) O_RDONLY: 以只读方式打开文件 
        (2) O_WRONLY: 以只写方式打开文件 
        (3) O_RDWR: 以读写方式打开文件 
        (4) O_CREAT: 如果文件不存在,则创建一个新文件 
        (5) O_APPEND: 将所有写入操作追加到文件的末尾 
        (6) O_TRUNC: 如果文件存在并且以写入模式打开,则截断文件长度为0 
        还有其他标志,如O_EXCL（当与O_CREAT一起使用时,只有当文件不存在时才创建新文件）、O_SYNC（同步I/O）、O_NONBLOCK（非阻塞I/O）等 
    可选参数: mode -> 仅在使用了O_CREAT标志且文件尚不存在的情况下生效,用于指定新创建文件的权限位 权限位通常由三位八进制数字组成,分别代表文件所有者、同组用户和其他用户的读写执行权限
    return: (1) 成功时返回非负的文件描述符。
            (2) 失败时返回-1，并设置全局变量errno以指示错误原因。
*/
int open (const char *__path, int __oflag, ...);



/*
    int __fd:一个整数,表示要从中读取数据的文件描述符
    void *__buf:一个指向缓冲区的指针,读取的数据将被存放到这个缓冲区中
    size_t __nbytes:一个size_t类型的整数,表示要读取的最大字节数 系统调用将尝试读取最多这么多字节的数据,但实际读取的字节数可能会少于请求的数量
    return: (1) 成功时,read()返回实际读取的字节数 这个值可能小于__nbytes,如果遇到了文件结尾（EOF）或者因为网络读取等原因提前结束读取 
            (2) 失败时,read()将返回-1
*/
ssize_t read (int __fd, void *__buf, size_t __nbytes);



/*
    int __fd:一个整数,表示要写入数据的文件描述符
    void *__buf:一个指向缓冲区的指针,写入的数据需要先存放到这个缓冲区中
    size_t __n:一个size_t类型的整数,表示要写入的字节数 write()函数会尝试写入__n个字节的数据,但实际写入的字节数可能会少于请求的数量
    return: (1) 成功时,write()返回实际写入的字节数 这个值可能小于__n,如果写入操作因故提前结束,例如: 磁盘满、网络阻塞等情况 
            (2) 失败时,write()将返回-1
*/
ssize_t write (int __fd, const void *__buf, size_t __n);

/*
    int __fd:一个整数,表示要关闭的文件描述符
    return: (1) 成功关闭时 返回0
            (2) 失败时 返回-1
*/
int close (int __fd);

/** * @brief 将格式化的数据写入字符串缓冲区
 * * @param str 指向用于存储生成的 C 字符串的缓冲区指针
 * @param format 包含格式说明符的字符串（如 %d, %s 等）
 * @param ... 根据 format 字符串所需的附加参数
 * * @return int 成功时返回写入的字符总数（不包括终止符 '\0'），失败返回负值
 */ 
int sprintf(char *str, const char *format, ...);


/**
 * const char *name: 这是共享内存对象的名称，直接写一个文件名称，本身会保存在 /dev/shm 。名称必须是唯一的，以便不同进程可以定位同一个共享内存段。
 * 命名规则：必须是以正斜杠/开头，以\0结尾的字符串，中间可以包含若干字符，但不能有正斜杠
 * int oflag: 打开模式 二进制可拼接
 *      (1) O_CREAT：如果不存在则创建新的共享内存对象
 *      (2) O_EXCL：当与 O_CREAT 一起使用时，如果共享内存对象已经存在，则返回错误（避免覆盖现有对象）
 *      (3) O_RDONLY：以只读方式打开
 *      (4) O_RDWR：以读写方式打开
 *      (5) O_TRUNC 用于截断现有对象至0长度（只有在打开模式中包含 O_RDWR 时才有效）。
 * mode_t mode: 当创建新共享内存对象时使用的权限位，类似于文件的权限模式,一般0644即可
 * return: 成功执行,它将返回一个新的描述符;发生错误,返回值为 -1
*/
int shm_open(const char *name, int oflag, mode_t mode);




3.3.5消息队列
/**
 * @brief 创建或打开一个已存在的POSIX消息队列，消息队列是通过名称唯一标识的。
 *
 * @param name 消息队列的名称
 * 命名规则：必须是以正斜杠/开头，以\0结尾的字符串，中间可以包含若干字符，但不能有正斜杠
 * @param oflag 指定消息队列的控制权限，必须也只能包含以下三者之一
 * O_RDONLY 打开的消息队列只用于接收消息
 * O_WRONLY 打开的消息队列只用于发送消息
 * O_RDWR 打开的消息队列可以用于收发消息
 * 可以与以下选项中的0至多个或操作之后作为oflag
 * O_CLOEXEC 设置close-on-exec标记，这个标记表示执行exec时关闭文件描述符
 * O_CREAT 当文件描述符不存在时创建它，如果指定了这一标记，需要额外提供mode和attr参数
 * O_EXCL 创建一个当前进程独占的消息队列，要同时指定O_CREAT，要求创建的消息队列不存在，否则将会失败，并提示错误EEXIST
 * O_NONBLOCK 以非阻塞模式打开消息队列，如果设置了这个选项，在默认情况下收发消息发生阻塞时，会转而失败，并提示错误EAGAIN
 * @param mode 每个消息队列在mqueue文件系统对应一个文件，mode是用来指定消息队列对应文件的权限的
 * @param attr 属性信息，如果为NULL，则队列以默认属性创建

* @return mqd_t 成功则返回消息队列描述符，失败则返回(mqd_t)-1，同时设置errno以指明错误原因
*/
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);


/**
 * @brief 当oflag没有包含O_CREAT时方可调用
 *
 * @param name 同上
 * @param oflag 同上
 * @return mqd_t 同上
 */
mqd_t mq_open(const char *name, int oflag);


/**
 * @brief 消息队列的属性信息
 * mq_flags 标记，对于mq_open，忽略它，因为这个标记是通过前者的调用传递的
 * mq_maxmgs 队列可以容纳的消息的最大数量
 * mq_msgsize 单条消息的最大允许大小，以字节为单位
 * mq_curmsgs 当前队列中的消息数量，对于mq_open，忽略它
 */
struct mq_attr {
    long mq_flags;
    long mq_maxmsg;
    long mq_msgsize;
    long mq_curmsgs;
};



/**
 * @brief 将msg_ptr指向的消息追加到消息队列描述符mqdes指向的消息队列的尾部。如果消息队列已满，默认情况下，调用阻塞直至有充足的空间允许新的消息入队，或者达到abs_timeout指定的等待时间节点，或者调用被信号处理函数打断。需要注意的是，正如上文提到的，如果在mq_open时指定了O_NONBLOCK标记，则转而失败，并返回错误EAGAIN。
 * 
 * @param mqdes 消息队列描述符
 * @param msg_ptr 指向消息的指针
 * @param msg_len msg_ptr指向的消息长度，不能超过队列的mq_msgsize属性指定的队列最大容量，长度为0的消息是被允许的
 * @param msg_prio 一个非负整数，指定了消息的优先级，消息队列中的数据是按照优先级降序排列的，如果新旧消息的优先级相同，则新的消息排在后面。
 * @param abs_timeout 指向struct timespec类型的对象，指定了阻塞等待的最晚时间。如果消息队列已满，且abs_timeout指定的时间节点已过期，则调用立即返回。
 * @return int 成功返回0，失败返回-1，同时设置errno以指明错误原因。
 */
int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio, const struct timespec *abs_timeout);



/**
 * @brief 从消息队列中取走最早入队且权限最高的消息，将其放入msg_ptr指向的缓存中。如果消息队列为空，默认情况下调用阻塞，此时的行为与mq_timedsend同理。
 * 
 * @param mqdes 消息队列描述符
 * @param msg_ptr 接收消息的缓存
 * @param msg_len msg_ptr指向的缓存区的大小，必须大于等于mq_msgsize属性指定的队列单条消息最大字节数
 * @param msg_prio 如果不为NULL，则用于接收接收到的消息的优先级 
 * @param abs_timeout 阻塞时等待的最晚时间节点，同mq_timedsend
 * @return ssize_t 成功则返回接收到的消息的字节数，失败返回-1，并设置errno指明错误原因
 */
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio, const struct timespec *abs_timeout);

/**
 * @brief 时间结构体，提供了纳秒级的UNIX时间戳
 * tv_sec 秒
 * tv_nsec 纳秒
 */
struct timespec {
time_t tv_sec;        /* seconds */
long tv_nsec;       /* nanoseconds */
};


/**
 * @brief 获取以struct timespec形式表示的clockid指定的时钟
 * 
 * @param clockid 特定时钟的标识符，常用的是CLOCK_REALTIME，表示当前真实时间的时钟
 * @param tp 用于接收时间信息的缓存
 * @return int 成功返回0，失败返回-1，同时设置errno以指明错误原因
 */
int clock_gettime(clockid_t clockid, struct timespec *tp);
