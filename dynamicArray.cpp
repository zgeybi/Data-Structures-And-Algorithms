#include <iostream>
#include <string>

template<typename T>
class Vector
{
private:
    T *arr;
    size_t size;
    size_t capacity;

public:
    Vector()
    {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }

    ~Vector()
    {
        delete[] arr;
    }

    void Push(T val)
    {
        if (size == capacity) {
            T* new_array = new T[capacity * 2];
            for (size_t i = 0; i < size; i++) {
                new_array[i] = arr[i];
            }
            delete[] arr;
            arr = new_array;
            capacity *= 2;
        }
        arr[size++] = val;

        std::cout << "ok" << '\n';
        return;
    }

    void Pop()
    {
        if(size == 0)
        {
            std::cout << "error" << '\n';
            return;
        }
        size--;
        std::cout << arr[size] << '\n';
        if(size == (capacity/2) && size > 0)
        {
            capacity /= 2;
            T *new_array = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                new_array[i] = arr[i];
            }
            delete[] arr;
            arr = new_array;
        }

        return;
    }

    void ElementAtIndex(size_t index)
    {
        if(index >= size || index < 0)
        {
            std::cout << "error" << '\n';
            return;
        }
        std::cout << arr[index] << '\n';
        return;
    }

    void Resize(size_t new_capacity)
    {
        T* new_array = new T[new_capacity];
        capacity = new_capacity;

        if(new_capacity < size)
        {
            for(int i = 0; i < new_capacity; i++)
            {
                new_array[i] = arr[i];
            }  
            delete[] arr;
            arr = new_array;
            std::cout << "ok" << '\n';
            return;
        }
        else if(new_capacity >= size)
        {
            for (int i = 0; i < size; i++)
            {
                new_array[i] = arr[i];
            }
            delete[] arr;
            arr = new_array;
            std::cout << "ok" << '\n';
            return;
        }

        
    }

    void PrintSize()
    {
        std::cout << size << '\n';
        return;
    }

    void PrintCapacity()
    {
        std::cout << capacity << '\n';
        return;
    }

    void Clear()
    {
        size = 0;
        capacity = 1;
        T *cleared_array = new T[capacity];
        delete[] arr;
        arr = cleared_array;
        std::cout << "ok" << '\n';
    }


};

int main()
{
    Vector<int> vector;
    std::string input;
    int val = 0;
    while (1)
    {
        std::cin >> input;
        if(input == "push")
        {
            std::cin >> val;
            vector.Push(val);
            
            continue;
        }
        else if(input == "pop")
        {
            vector.Pop();
            continue;
        }
        else if(input == "at")
        {
            std::cin >> val;
            vector.ElementAtIndex(val);
            continue;
        }
        else if(input == "size")
        {
            vector.PrintSize();
            continue;
        }
        else if(input == "resize")
        {
            
            std::cin >> val;
            vector.Resize(val);
            continue;
        }
        else if(input == "capacity")
        {
            vector.PrintCapacity();
            continue;
        }
        else if(input == "clear")
        {
            vector.Clear();
            continue;
        }

        else if(input == "exit")
        {
            std::cout << "bye";
            return 0;
        }
        /*else {
            continue;
        }*/
        
    }

    return 0;
}