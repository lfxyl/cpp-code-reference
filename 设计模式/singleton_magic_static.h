// 来源；https://www.cnblogs.com/sunchaothu/p/10389842.html
#include <iostream>

class Singleton
{
public:
    ~Singleton(){
        std::cout<<"destructor called!"<<std::endl;
    }
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
    static Singleton& get_instance(){
        static Singleton instance;
        return instance;

    }
private:
    Singleton(){
        std::cout<<"constructor called!"<<std::endl;
    }
};

// 这种实现叫做 Meyers' Singleton，是著名的写出《Effective C++》系列书籍的作者 Meyers 提出的。
// 所用到的特性是在C++11标准中的Magic Static特性：
// If control enters the declaration concurrently while the variable is being initialized, 
// the concurrent execution shall wait for completion of the initialization.
// 当变量在初始化的时候，并发同时进入声明语句，并发线程将会阻塞等待初始化结束。
// 这样保证了并发线程在获取静态局部变量的时候一定是初始化过的，所以具有线程安全性。

// C++静态变量的生存期是从声明到程序结束，因此这也是一种懒汉式。





