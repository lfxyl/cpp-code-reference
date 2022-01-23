//模板类作为友元时要先有声明
template <typename T> class SharedPtr;
   
//辅助类
template <typename T> class RefPtr
{
private:
    friend class SharedPtr<T>;      //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类
    RefPtr(T *ptr) :p(ptr), count(1) { }	//构造函数的参数为基础对象的指针
    ~RefPtr() { delete p; }
    	
    int count;   	// 引用计数
    T *p;        	// 基础对象指针                                              
};

//智能指针类
template <typename T> class SharedPtr
{
public:
    SharedPtr(T *ptr) :rp(new RefPtr<T>(ptr)) { };      //构造函数
    SharedPtr(const SharedPtr<T> &sp) :rp(sp.rp) { ++rp->count; };  //拷贝构造函数
    SharedPtr& operator=(const SharedPtr<T>& rhs)       //重载赋值操作符
    {
        ++rhs.rp->count;        //首先将右操作数引用计数加1，
        if (--rp->count == 0)   //然后将引用计数减1，可以应对自赋值
            delete rp;
        rp = rhs.rp;
        return *this;
    }
    T & operator *()        //重载*操作符  
    {
        return *(rp->p);
    }
    T* operator ->()       //重载->操作符  
    {
        return rp->p;
    }
    ~SharedPtr()            //析构函数
    {
        if (--rp->count == 0)    //当引用计数减为0时，删除辅助类对象指针，从而删除基础对象
            delete rp;
        else
        {
	        cout << "还有" << rp->count << "个指针指向基础对象" << endl;
	    }
    }
private:
    RefPtr<T> *rp;  //辅助类对象指针
};