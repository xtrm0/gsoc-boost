#ifndef BOOST_CONTAINER_CONTAINER_VECTOR_HPP
#define BOOST_CONTAINER_CONTAINER_VECTOR_HPP
//TODO: IMPLEMENT MOVE AND EQUAL OPERATORS

/*
  C++ vector implemented by Afonso Tinoco

  This is an abridged version of a standard c++11 vector

  It is based on the definitions on [1] (based on STL), except that everything has at least exception strong guarantee (unless stated otherwise in the code)

  Reverse iterators where skipped to to keep things as short as possible.
  Most const function were also skipped.
  We also decided to skip relational operators and the swap function
  Some function that would bring no new knowledge demonstration to the table were also skipped
  We decided not to add documentation comments, as everything is pretty well documented on [1].

  Because of the fact that it said in the proposal that push_back should throw if the buffer is full, we implemented a small pre_push_back, that automatically grows the vector over some constants, just like std::vector does inside push_back

  [1] http://www.cplusplus.com/reference/vector/vector/
 */


//Memory is used to include std::allocator, in theory, we can use any allocator who gives us contiguous memory blocks of the size we request
#include <memory>
//We include cstring for memcpy
#include <cstring>
//We include exception for stl exceptions
#include <exception>
//We include initializer_list due to their awesome flying cows
#include <initializer_list>

/*
  These are the constants for the amortized time push_back.
  whenever we call pre_push_back, if the vector is full, we resize it to have
  ((old_size + INC) * MULT) elements

  So for instance:
    (INC,MULT) = (0,2) would give us the STL amortized memory eficient vector
  while:
    (INC,MULT) = (1,0) would give us the time O(n^2) but with list-like memory eficiency
  and:
    (INC,MULT) = (1,1.6f) would give us a vector like the Dinkumware implementation (Visual Studio)
 */
#define VECTOR_AMORT_INC 0
#define VECTOR_AMORT_MULT 2

namespace boost {
  namespace exceptions
  {
    struct invalid_size : public std::exception
    {
      const char * what () const throw ()
        {
          return "Invalid Vector Size Parameter";
        }
    };
    struct buffer_overflow : public std::exception
    {
      const char * what () const throw ()
        {
          return "Buffer Overflow";
        }
    };
    struct out_of_bounds : public std::exception
    {
      const char * what () const throw ()
        {
          return "Out of bound memory access";
        }
    };   
  }
  /*
    We're not implementing an iterator class, because it would just be a pointer wrapper.
    But if we were, it would be something like this
    template <typename T>
    class iterator {};
  */
  template <typename T, class Alloc = std::allocator<T> >
  class vector {
  public:
    //types:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef T* iterator;
    typedef unsigned int size_type;
    typedef size_type difference_type;

    typedef unsigned char byte;


    
  /*
  ========================================
  Member functions
  ========================================
  */

    vector() {
      try {
        m_capacity = 0;
        m_size = 0;
        m_buffer = m_allocator.allocate(m_capacity);
      }  catch (const std::exception& e) {
        m_capacity = 0;
        throw e;
      }
    }

    vector(const size_type n) {
      try {
        m_capacity = n; 
        m_size = 0;
        m_buffer = m_allocator.allocate(m_capacity);
      }  catch (const std::exception& e) {
        m_capacity = 0;
        throw e;
      }
    }

    vector(std::initializer_list<T> l) {
      typename std::initializer_list<T>::iterator it;
      size_type i=0;
      m_capacity = l.size();
      m_size = l.size();
      try {
        m_buffer = m_allocator.allocate(m_capacity);
      } catch (const std::exception& e) {
        m_capacity = 0;
        m_size = 0;
        throw e;
      }
      try {
        for (i=0, it=l.begin(); i<m_size && it!=l.end(); i++, it++) {
          m_allocator.construct(m_buffer+i, *it);
        }
      } catch (const std::exception& e) {
          for (size_type j=0; j<i; j++) {
            m_allocator.destroy(m_buffer+j);
          }
        m_allocator.deallocate(m_buffer, m_capacity); 
      }
    }
    
    /*
      Destructor
     */
    ~vector() noexcept {
      for (boost::vector<int>::size_type i=0; i<m_size; i++) {
        m_allocator.destroy(m_buffer + i);
      }
      if(m_buffer!=NULL) 
        m_allocator.deallocate(m_buffer, m_capacity);
    }
  /*
  ========================================
  Iterators
  ========================================
  */
    iterator begin() noexcept{
      return m_buffer;
    }

    iterator end() noexcept{
      return m_buffer + m_size;
    }

  /*
  ========================================
  Capacity
  ========================================
  */

    size_type size() const noexcept{
      return m_size;
    }

    /*
      Resizes the container to have exactly n empty constructed elements( m_size=m_capacity=n)
      Has only weak guarantee (if (n>m_capacity and the T constructor can throw))
     */
    void resize(size_type n) {
      size_type i;
      value_type * pre_buffer;
      if (n<0) throw exceptions::invalid_size();
      if (n < m_capacity) {
        pre_buffer = m_allocator.allocate(n); 
        memcpy(pre_buffer, m_buffer, ((byte*)(m_buffer + n)) - ((byte*)m_buffer));
        for (size_type i=n; i<m_size; i++) {
          m_allocator.destroy(m_buffer + i);
        }
        m_allocator.deallocate(m_buffer, m_capacity);
        m_buffer = pre_buffer;
        m_capacity = n;
        m_size = (m_size < n ? m_size : n);
      } else if (n > m_capacity) {
        reserve(n);
        //from now on we can only hold weak guarantee:
        try {
          for (i=m_size; i<n; i++) {
            m_allocator.construct(m_buffer + i); 
          }
        } catch (const std::exception& e) {
          for (size_type j=m_size; j<i; j++) {
            m_allocator.destroy(m_buffer + j); //To mantain the weak guarantee (we assume the destroyer cannot throw (which should be a standard), and to avoid resource leak
          }
          throw e;
        }
        m_size = n;
      }
    }

    size_type capacity() const noexcept {
      return m_capacity;
    }

    bool empty() const noexcept {
      return (m_size == 0);
    }

    void shrink_to_fit() {
      resize(m_size);
    }

    void reserve(size_type n) {
      value_type * pre_buffer;
      if (n > m_capacity) {
        try {
          pre_buffer = m_allocator.allocate(n);
        } catch (const std::exception& e) {
          throw e;
        }
        memcpy(pre_buffer, m_buffer, ((byte*)(m_buffer + m_size)) - ((byte*)m_buffer));
        m_allocator.deallocate(m_buffer, m_capacity);
        m_buffer = pre_buffer;
        m_capacity = n;
      }
    }

  /*
  ========================================
  Element Access
  ========================================
  */
    reference operator[](size_type n) {      
      return at(n);
    }
    reference at(size_type n) {
      if (n<0 || n>=m_size)
        throw exceptions::out_of_bounds();
      return m_buffer[n];
    }
    reference front() {
      if (empty())
        throw exceptions::out_of_bounds();      
      return m_buffer[0];
    }
    reference back() {
      if (empty())
        throw exceptions::out_of_bounds();
      return m_buffer[m_size-1];
    }
    value_type* data() noexcept {
      return m_buffer;
    }
    
  /*
  ========================================
  Modifiers
  ========================================
  */
    void pre_push_back() {
      if(m_capacity <= m_size) {
        if ((m_size+VECTOR_AMORT_INC) * (VECTOR_AMORT_MULT) != 0)
          reserve((m_size+VECTOR_AMORT_INC) * (VECTOR_AMORT_MULT)); //Throws if reserve throws
        else
          reserve(1);
      }
    }
    
    void push_back(const T& x) {
      if(m_capacity <= m_size) {
        throw exceptions::buffer_overflow();
      }
      m_allocator.construct(m_buffer + m_size);
      m_buffer[m_size] = x;
      m_size++;
    }

    void pop_back() {
      if (empty())
        throw exceptions::out_of_bounds();
      m_allocator.destroy(m_buffer + --m_size);
    }

    void clear() {//we could rewrite part of resize in here to make this noexcept, but that would be overkill for this example
      resize(0);
    }

   
  private:
    size_type m_size;
    size_type m_capacity;
    Alloc m_allocator;
    T* m_buffer;

  };

  
};


#endif
