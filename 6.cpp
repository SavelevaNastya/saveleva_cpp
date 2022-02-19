#include <utility>

class MyIntArray {
private:
	int* data;
	size_t length;
public:
    MyIntArray(int c, size_t l)
    {
        data = new int;
        *data = c;
        length = l;

    }

    ~MyIntArray()
    {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    // Copy constructor
    MyIntArray(const MyIntArray& c)
    {
        length = c.length;
        data = new int[length];
        for (int i = 0; i <= length; i++) {
            data[i] = c.data[i];
        }
        

    }

    // Move constructor
    MyIntArray(MyIntArray&& c) noexcept
    {
        length = c.length;
        data = c.data;
        c.data = nullptr;
    }

    // Оператор присваивания перемещением (move assignment)
    MyIntArray& operator=(MyIntArray&& c) noexcept
    {
        if (this == &c)
            return *this;

        delete[] data;
        data = c.data;
        length = c.length;
        c.data = nullptr;
        return *this;
    }

    // operator=
    MyIntArray& operator= (const MyIntArray& c) 
    {
        if (this == &c)
            return *this;
        delete[] data;
        length = c.length;
        data = new int[length];

        for (int i = 0; i <= length; i++) {
            data[i] = c.data[i];
        }

        return *this;
    }
};