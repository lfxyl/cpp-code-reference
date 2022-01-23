// 来源：   https://www.jianshu.com/p/77c2988be336
template <typename T>
class UniquePtr
{
public:
    explicit UniquePtr(T *ptr = nullptr): mPtr(ptr) {}

    ~UniquePtr()
    {
        if (mPtr)
            delete mPtr;
    }

    UniquePtr(UniquePtr &&p) noexcept;
    UniquePtr &operator=(UniquePtr &&p) noexcept;

    UniquePtr(const UniquePtr &p) = delete;
    UniquePtr &operator=(const UniquePtr &p) = delete;

    T *operator*() const noexcept { return mPtr; }
    T &operator->() const noexcept { return *mPtr; }
    explicit operator bool() const noexcept { return mPtr; }

    void reset(T *q = nullptr) noexcept
    {
        if (q != mPtr)
        {
            if (mPtr)
                delete mPtr;
            mPtr = q;
        }
    }

    T *release() noexcept
    {
        T *res = mPtr;
        mPtr = nullptr;
        return res;
    }
    T *get() const noexcept { return mPtr; }
    void swap(UniquePtr &p) noexcept
    {
        using std::swap;
        swap(mPtr, p.mPtr);
    }

private:
    T *mPtr;
};

template <typename T>
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&p) noexcept
{
    swap(*this, p);
    return *this;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr &&p) noexcept : mPtr(p.mPtr)
{
    p.mPtr == NULL;
}