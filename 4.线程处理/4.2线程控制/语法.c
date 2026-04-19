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