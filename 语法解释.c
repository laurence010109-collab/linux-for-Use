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



/*
    void *__s: 一个指向目标内存区域(缓冲区)的指针, 表示你要清空或修改的那块内存的起始物理地址。在你的代码中, 它就是 read_buf 的首地址。
    
    int __c: 一个整数, 表示你要往内存里填充的具体数值。
             🚨 极客铁律: 虽然它的类型是 int (4字节), 但在底层操作时, 操作系统会无情地把它强转为 unsigned char (单字节 8-bit), 然后像盖章一样**逐个字节**地盖到内存上。在你的代码中, 你传了 0, 就是把每一位都清零。
             
    size_t __n: 一个 size_t 类型的整数, 表示你要填充的"总字节数" (Byte)。
             🚨 致命陷阱: 它是物理字节大小, 绝不是数组的元素个数！在你的代码中, 用 sizeof(read_buf) 获取整个数组占用的物理内存大小, 这是最标准、最防越界的满分写法。
             
    return: 永远成功！它会返回指向目标缓冲区起始位置的指针 (其实就是原封不动地把 __s 返回给你)。
            在实际工业级代码中, 就像你写的那样, 我们几乎从不去接收它的返回值, 而是直接利用它“原地覆盖物理内存”的副作用。
*/
void *memset (void *__s, int __c, size_t __n);



/**
 * 创建一个新线程
 * 
 * pthread_t *thread: 指向线程标识符的指针,线程创建成功时,用于存储新创建线程的线程标识符
 * const pthread_attr_t *attr: pthead_attr_t结构体,这个参数可以用来设置线程的属性,如优先级、栈大小等。如果不需要定制线程属性,可以传入 NULL,此时线程将采用默认属性。 
 * void *(*start_routine)(void *): 一个指向函数的指针,它定义了新线程开始执行时的入口点。这个函数必须接受一个 void * 类型的参数,并返回 void * 类型的结果
 * void *arg: start_routine 函数的参数,可以是一个指向任意类型数据的指针
 * return: int 线程创建结果
 *             成功 0
 *             失败 非0
 */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine)(void *), void *arg);



/**
 * 等待指定线程结束，获取目标线程的返回值，并在目标线程结束后回收它的资源
 * 
 * pthread_t thread: 指定线程ID
 * void **retval: 这是一个可选参数，用于接收线程结束后传递的返
回值。如果非空，pthread_join 会在成功时将线程的 exit status 
复制到 *retval 所指向的内存位置。如果线程没有显式地通过
pthread_exit 提供返回值，则该参数将被设为 NULL 或忽略
 * return: int 成功 0
 *              失败 1
 */
int pthread_join(pthread_t thread, void **retval);


char dest_buf[10]; // 你自己提前在栈区开辟了 10 个字节的空间
strcpy(dest_buf, "红玫瑰"); // 把 "红玫瑰" 复制到 dest_buf 里

char* redans = strdup("红玫瑰独自去了纽约.\n");// 创建一个字符串并返回一个指向它的指针，需要注意的是，strdup内部会调用malloc来分配内存，因此使用完毕后需要调用free来释放内存以防止内存泄漏。



#include <pthread.h>

/**
 * 结束关闭调用该方法的线程，并返回一个内存指针用于存放结果
 * void *retval: 要返回给其它线程的数据
 */
void pthread_exit(void *retval);


#include <pthread.h>

/**
 * 等待指定线程结束，获取目标线程的返回值，并在目标线程结束后回收它的资源
 * 
 * pthread_t thread: 指定线程ID
 * void **retval: 这是一个可选参数，用于接收线程结束后传递的返回值。
如果非空，pthread_join 会在成功时将线程的 exit status 复制到 *retval 所指向的内存位置。
如果线程没有显式地通过 pthread_exit 提供返回值，则该参数将被设为 NULL 或忽略
 * return: int 成功 0
 *              失败 1
 */
int pthread_join(pthread_t thread, void **retval);



/**
 * @brief 向目标线程发送取消请求。目标线程是否和何时响应取决于它的取消状态和类型
 *  取消状态（Cancelability State）：可以是enabled（默认）或disabled。如果取消状态为禁用，则取消请求会被挂起，直至线程启用取消功能。如果取消状态为启用，则线程的取消类型决定它何时取消。
 *  取消类型（Cancelability Type）：可以是asynchronous（异步）或deferred（被推迟，默认值）。
 *      asynchronous：意味着线程可能在任何时候被取消（通常立即被取消，但系统并不保证这一点）
 *      deferred：被推迟意味着取消请求会被挂起，直至被取消的线程执行取消点（cancellation point）函数时才会真正执行线程的取消操作。
 *      取消点函数：是在POSIX线程库中专门设计用于检查和处理取消请求的函数。当被取消的线程执行这些函数时，如果线程的取消状态是enabled且类型是deferred，则它会立即响应取消请求并终止执行。man 7 pthreads可以看到取消点函数列表。
 * 
 * @param thread 目标线程，即被取消的线程
 * @return int 成功返回0，失败返回非零的错误码
 *      需要注意的是，取消操作和pthread_cancel函数的调用是异步的，这个函数的返回值只能告诉调用者取消请求是否成功发送。当线程被成功取消后，通过pthread_join和线程关联将会获得PTHREAD_CANCELED作为返回信息，这是判断取消是否完成的唯一方式
 */
int pthread_cancel(pthread_t thread);



/**
 * @brief 为rwlock指向的读写锁分配所有需要的资源，并将锁初始化为未锁定状态。读写锁的属性由attr参数指定，如果attr为NULL，则使用默认属性。当锁的属性为默认时，可以通过宏PTHREAD_RWLOCK_INITIALIZER初始化，即
 * pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER; 效果和调用当前方法并为attr传入NULL是一样的
 * 
 * @param rwlock 读写锁
 * @param attr 读写锁的属性
 * @return int 成功则返回0，否则返回错误码
 */
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);


/**
 * @brief 用所有属性的默认值初始化attr指向的属性对象
 * 
 * @param attr 读写锁属性对象指针
 * @return int 成功返回0，失败返回错误码
 */
int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);



/**
 * @brief 将attr指向的属性对象中的"锁类型"属性设置为pref规定的值
 * 
 * @param attr 读写锁属性对象指针
 * @param pref 希望设置的锁类型，可以被设置为以下三种取值的其中一种
 * PTHREAD_RWLOCK_PREFER_READER_NP: 默认值，读线程拥有更高优先级。当存在阻塞的写线程时，读线程仍然可以获得读写锁。只要不断有新的读线程，写线程将一直保持"饥饿"。
 * PTHREAD_RWLOCK_PREFER_WRITER_NP: 写线程拥有更高优先级。这一选项被glibc忽略。
 * PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP: 写线程拥有更高优先级，在当前系统环境下，它是有效的，将锁类型设置为该值以避免写饥饿。
 * @return int 成功返回0，失败返回非零的错误码
 */
int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *attr, int pref);