#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

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
      // implement this
        if (count > 0){ 
            m_first = new Type[count];
            m_last = m_first + count;
        }
        else{  
            m_first = m_last = nullptr;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        // implement this
        if (last - first > 0){ 
            m_first = new Type[last - first];
            m_last = m_first + (last - first);
            std::copy(first,last,this->m_first);
        }
        else{ 
            m_first = m_last = nullptr;
        }
    }

    vector(std::initializer_list<Type> init)
    {
      // implement this
        if (init.size() > 0){ 
            m_first = new Type[init.size()];
            m_last = m_first + init.size();
            std::copy(init.begin(), init.end(), this->m_first);
        }
        else{
            m_first = m_last = nullptr;
        }
    }

    vector(const vector& other)
    {
      // implement this
        if (other.size() > 0){
            this->m_first = new Type[other.size()];
            this->m_last  = this->m_first + other.size();
            std::copy(other.m_first, other.m_last, this->m_first);
        }
        else{ 
            m_first = m_last = nullptr;
        }
    }

    vector(vector&& other) : m_last(nullptr), m_first(nullptr)
    {
      // implement this
        std::swap(m_first,other.m_first);
        std::swap(m_last,other.m_last);
    }

    ~vector()
    {
      // implement this
        if (m_first){ 
            delete [] m_first;
            m_first = m_last = nullptr;
        }
    }
    
    //assignment operators
    vector& operator=(const vector& other)
    {
      // implement this
        if (m_first != nullptr)
            delete [] m_first;
            
        if (other.size() > 0){
            this->m_first = new Type[other.size()];
            this->m_last  = this->m_first + other.size();
            std::copy(other.m_first, other.m_last, this->m_first);
        }
        else{ 
            m_first = m_last = nullptr;
        }
        
        return *this;
    }

    vector& operator=(vector&& other)
    {
      // implement this
        if (m_first != nullptr)
            delete [] m_first;
            
        m_first = m_last = nullptr;
        std::swap(m_first, other.m_first);
        std::swap(m_last,  other.m_last);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
        if (m_first!=nullptr)
            delete [] m_first;
            
        this->m_first = new Type[last-first];
        this->m_last  = m_first + (last - first);
        std::copy(first, last, this->m_first);
    }
    
    //resize methods
    void resize(size_t count)
    {
      // implement this
        if (count > size()){
            iterator newArr = new Type[count];
            std::copy(this->m_first, this->m_last, newArr);
            delete [] this->m_first;
            this->m_first = nullptr;
            std::swap(m_first, newArr);
            m_last = m_first + count;
        }
            
        if (count < size()){
           iterator newArr = new Type[count];
            m_last = m_first+count;
            std::copy(this->m_first, this->m_last, newArr);
            delete [] this->m_first;
            this->m_first = nullptr;
            std::swap(m_first, newArr);
            m_last = m_first + count;
        }
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      // implement this
        iterator position = iterator(pos);
        std::rotate(position, position + 1, m_last);
        --m_last;
        return position;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      // implement this
        iterator posFirst = iterator(first);
        iterator posLast = iterator(last);
        std::rotate(posFirst, posLast, m_last);
        m_last = m_last - (last - first);
        return (posFirst);
    }


    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        iterator Pos = iterator(pos);
        size_t sz = size();
        size_t count = std::distance(m_first, Pos);
        Pos = m_first + count;
        iterator new_arr = new Type[size() + 1];
        iterator Pos1 = new_arr;
        Pos1 = Pos1 + count;
        if (Pos != m_first)
           std::copy(m_first, Pos, new_arr);
        *Pos1 = value;
        std::copy(Pos, m_last, Pos1 + 1);
        delete [] this->m_first;
        this->m_first = nullptr;
        std::swap(m_first, new_arr);
        m_last = m_first + sz + 1;
        return m_first + count;     
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      // implement this
        size_t sz = size();
        iterator Pos   = iterator(pos);
        iterator First = iterator(first);
        iterator Last  = iterator(last);
        size_t count1  = std::distance(First, Last);
        size_t count2  = std::distance(m_first, Pos);
            
        Pos = m_first + count2;
        iterator new_arr = new Type[size() + count1];
        iterator Pos1 = new_arr;
        Pos1 = Pos1 + count2;
        if (Pos != m_first)
            std::copy(m_first, Pos, new_arr);
        std::copy(First, Last, Pos1);
        std::copy(Pos, m_last, Pos1 + count1);
        delete [] this->m_first;
        this->m_first = nullptr;
        std::swap(m_first, new_arr);
        m_last = m_first + sz + count1;
        return m_first + count2;   
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      // implement this
        resize(size() + 1);
        *(m_last - 1) = value;
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