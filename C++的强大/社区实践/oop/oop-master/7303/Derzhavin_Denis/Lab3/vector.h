#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
using namespace std;
namespace stepik
{
template <typename Type>
class vector
{
public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0)
    {
        m_first = new value_type[count];
        m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        int count = distance(first, last);
        m_first = new value_type[count];
        m_last = m_first + count;
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init): vector(init.begin(), init.end()) {}

    vector(const vector& other): vector(other.begin(), other.end()) {}

    vector(vector&& other)
    {
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
    }

//assignment operators
    vector& operator=(const vector& other)
    {
        if (other.size()) {
            delete[] m_first;
            m_first = new value_type[other.size()];
            m_last = m_first + other.size();
            std::copy(other.begin(), other.end(), m_first);
        }
        return *this;
    }

    vector& operator=(vector&& other)
    {
        if(this != &other){
            delete[] m_first;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;
        }
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        ~vector();
        if(first != last) {
            difference_type count=last-first;
            m_first = new Type[count];
            m_last = m_first + count;
            std::copy(first,last, m_first);
        } else {
            m_first = m_last = nullptr;
        }
    }
    // resize methods
    void resize(size_t count)
    {
        if (!count) {
            delete [] m_first;
            m_first = m_last = nullptr;
            return;
        }
        if (count == size())
            return;

        Type* buffer = new Type[count];

        if (count > size())
            std::copy(m_first, m_last, buffer);
        else
            std::copy(m_first, m_first + count, buffer);

        delete[] m_first;
        m_first = buffer;
        m_last = m_first + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        difference_type diff = pos - m_first;
        std::rotate(m_first + diff, m_first + diff + 1, m_last);
        resize(m_last - m_first - 1);
        return m_first + diff;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        difference_type diff = first - m_first;
        difference_type erase_zone = last - first;
        std::rotate(m_first + diff, m_first + diff + erase_zone, m_last);
        resize(m_last - m_first - erase_zone);
        return m_first + diff;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t len = size()+1;
        iterator new_m_first = new value_type[len];
        size_t first_part = pos-m_first;
        std::copy(m_first, m_first+first_part, new_m_first);
        new_m_first[first_part] = value;
        std::copy(m_first+first_part, m_last, new_m_first+first_part);
        delete [] m_first;
        m_first = new_m_first;
        m_last = m_first+len;
        return m_first+first_part;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t len = size()+(last-first);
        iterator new_m_first = new value_type[len];
        size_t first_part = pos-m_first;
        std::copy(m_first, m_first+first_part, new_m_first);
        std::copy(first, last, new_m_first+first_part);
        std::copy(m_first+first_part, m_last, new_m_first+first_part+(last-first));
        delete[] m_first;
        m_first = new_m_first;
        m_last = m_first+len;
        return m_first+first_part;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        resize(size()+1);
        *(m_last-1) = value;
    }

    ~vector()
    {
        delete [] m_first;
    }

    //at methods
    reference at(size_t pos)
    {
        return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
        return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
        return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
        return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
        return m_first;
    }

    const_iterator begin() const
    {
        return m_first;
    }

    //*end methods
    iterator end()
    {
        return m_last;
    }

    const_iterator end() const
    {
        return m_last;
    }

    //size method
    size_t size() const
    {
        return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
        return m_first == m_last;
    }

private:
    reference checkIndexAndGet(size_t pos) const
    {
        if (pos >= size())
        {
            throw std::out_of_range("out of range");
        }

        return m_first[pos];
    }
    //your private functions

private:
    iterator m_first;
    iterator m_last;
};
}// namespace stepik
