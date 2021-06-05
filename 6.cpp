//class MyIntArray {
//private:
//	int* data;
//	size_t length;
//public:
//    MyIntArray(int c)
//    {
//        data = new int;
//        *data = c;
//    }
//
//    ~MyIntArray()
//    {
//        delete[] data;
//    }
//
//    // Copy constructor
//    MyIntArray(const MyIntArray& c)
//        : MyIntArray{ *c.data }
//    {
//
//    }
//
//    // Move constructor
//    MyIntArray(MyIntArray&& c) noexcept
//        : data{ c.data }
//    {
//        c.data = nullptr;
//    }
//
//    // Оператор присваивания перемещением (move assignment)
//    MyIntArray& operator=(MyIntArray&& c) noexcept
//    {
//        if (this == &c)
//            return *this;
//        delete[] data;
//        data = c.data;
//        c.data = nullptr;
//        return *this;
//    }
//
//    // operator=
//    MyIntArray& operator= (const MyIntArray& c) {
//        data = c.data;
//    }
//    
//
//};