#ifndef BOOST_CONTAINER_CONTAINER_DEVECTOR_HPP
#define BOOST_CONTAINER_CONTAINER_DEVECTOR_HPP


/*
  C++ devector implemented by Afonso Tinoco

  This is an abridged version of a standard c++11 vector, with some modifications.
  It is based on the definitions on [1] (based on STL), but has the following advantages:
     + Everything has at least exception strong guarantee
     + Everything has at least as good as STL time complexity
     + Push_front and pop_front have amortized constant time complexity (on the number of elements)
     + The value_type constructors are only called on push operations (to keep everything independent of the constructors complexity)
     + [The value_type destructors are only called on pop operations]

  Reverse iterators were skipped to to keep things as short as possible.
  Most const function were also skipped.
  Some functions that would bring no new knowledge demonstration to the table were also skipped
  We decided not to add documentation comments, as everything is pretty well documented on [1].

  [1] http://www.cplusplus.com/reference/vector/vector/
 */


/*
  In order to mantain the O(1) push_front and push_back, we decided to use the same algorithm as for theexponentialy growing vector, except that the assigned element are mantained in the middle of the vector:
  The vector grows as follows (X = valid element, I = last inserted element, _=allocated empty space):
     [_] : push_back(T)
     [I] : push_back(T)
     [_XI]
     [IXX]
     [IIXX__]
     [___IIXX_____]
  This guarantees O(N) memory and O(1) front or back insertion. But we migth have up to 3 times more memory than needed.

  Another strategy to reduce the ammount of memory to be at least as good as push_back only vectors, would be to use a ring buffer. But then we couldn't guarantee the continuos memory property required for the c++11 vector::data array access
  
 */

//Memory is used to include std::allocator, in theory, we can use any allocator who gives us contiguous memory blocks of the size we request
#include <memory>
//We include cstring for memcpy
#include <cstring>
//We include limits for max_size
#include <limits>

/*
  These are the constants for the amortized time push_back.
  whenever we call push_back, if the vector is full, we resize it to have
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
  /*
    We're not implementing iterator yet, but if we were, it would be something like this
    template <typename T>
    class iterator {};
  */
  template <typename T, class Alloc = std::allocator<T> >
  class devector {
  public:
    //types:
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef value_type& reference;
    typedef const reference const_reference;
    typedef T* iterator;
    typedef const iterator const_iterator;
    typedef unsigned int size_type;
    typedef size_type difference_type;

    typedef unsigned char byte;
  /*
  ========================================
  Member functions
  ========================================
  */
    devector() {
      try {
        m_capacity = 1;
        m_front = 0;
        m_size = 0;
        m_buffer = m_allocator.allocate(m_capacity);
      }  catch (const std::exception& e) {
        m_capacity = 0;
        throw e;
      }
    }


    /*
      Destructor
     */
    ~devector() noexcept {
      for (size_type i=0; i<m_size; i++) {
        m_allocator.destroy(m_buffer + m_front + i);
      }
      m_allocator.deallocate(m_buffer, m_capacity);
    }

  /*
  ========================================
  Iterators
  ========================================
  */
    iterator begin() noexcept{
      return m_buffer + m_front;
    }

    iterator end() noexcept{
      return m_buffer + m_front + m_size;
    }

    const_iterator cbegin() noexcept{
      return begin();
    }

    const_iterator cend() noexcept{
      return end();
    } 


  /*
  ========================================
  Capacity
  ========================================
  */

    size_type size() const noexcept{
      return m_size;
    }

    size_type max_size() const noexcept {
      return std::numeric_limits<size_type>::max();
    }

    /*
      This function is ugly and should be remade
     */
    void resize(size_type n) {
      size_type i;
      size_type new_front;
      value_type * pre_buffer;
      if (n<1) n=1; //we do not throw here, because it makes much more sense to just resize to the minimum size (1);
      if (n < m_capacity) {
        //then we have strong guarantee
        if (n>m_size) 
          new_front = (n - m_size)/2;
        else
          new_front = 0;
        pre_buffer = m_allocator.allocate(n); 
        memcpy(pre_buffer + new_front, m_buffer + m_first, ((byte*)(m_buffer + m_first + n)) - ((byte*)(m_buffer+m_first)));
        m_allocator.deallocate(m_buffer, m_capacity);
        m_buffer = pre_buffer;
        m_capacity = n;
        m_fromt = new_front;
        m_size = (m_size < n ? m_size : n);
      } else if (n > m_capacity-m_front) {
        reserve(1.5*n);
        //from here on it's weak guarantee
        try {
          for (i=m_size; i<n; i++) {
            m_allocator.construct(m_buffer + m_front + i); 
          }
        } catch (const std::exception& e) {
          for (size_type j=m_size; j<i; j++) {
            m_allocator.destroy(m_buffer + m_front + j); //To mantain weak guarantee
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
      resize(m_size >= 1 ? m_size : 1);
    }

    /*
      Strong guarantee met
    */
    void reserve(size_type n) {
      priv_reserve_mid(n);
    }

  /*
  ========================================
  Element Access
  ========================================
  */
    reference operator[](size_type n) {
      return m_buffer[m_front + n]; //We complain with c++11 stl standard, leaving undefined behavior in case of n not beeing a valid index
    }
    
    const_reference operator[](size_type n) const {
      return m_buffer[m_front + n];
    }

    reference front() {
      return m_buffer[m_front];
    }

    reference back() {
      return m_buffer[m_front + m_size - 1];
    }
    
    value_type* data() {
      return m_buffer + m_front;
    }

    

    
  /*
  ========================================
  Modifiers
  ========================================
  */
    void push_back(const T& x) {
      if(m_capacity <= m_size + m_front) {
        reserve((m_capacity+VECTOR_AMORT_INC) * (VECTOR_AMORT_MULT)); //Throws if reserve throws
      }
      m_allocator.construct(m_buffer + m_front + m_size);
      m_buffer[m_front + m_size] = x;
      m_size++;
    }

    void push_front(const T& x) {
      if(m_front == 0) {
        reserve((m_capacity+VECTOR_AMORT_INC) * (VECTOR_AMORT_MULT)); //Throws if reserve throws
      }
      m_allocator.construct(m_buffer + m_front - 1);
      m_buffer[m_front-1] = x;
      m_size++; m_front--;
    }

    void clear() {
      resize(0);
    }
    

   
  private:
    size_type m_front; //position of the first element on the m_buffer
    size_type m_size;  //number of elements in the vector
    size_type m_capacity; //number of allocated elements, it's always >=1
    Alloc m_allocator; //allocator class
    T* m_buffer; //array of elements


    /*
      Reserves space to have at least n free elements, if reallocation happens, m_first = m_first + increase_in_capacity.
     */
    void priv_reserve_front(size_type n);
    /*
      Reserves to have at least n free elements, if reallocation happens, first is left unchanged.
     */
    void priv_reserve_back(size_type n);

    /*
      Reserves space for at least n elements and sets first so that the free size on the begining is at most 1 less than the free space at the end
     */
    void priv_reserve_mid(size_type n) {
      value_type * pre_buffer;
      size_type new_front;
      if (n > m_capacity) {
        if(n-m_size == 1) n+=1;
        try {
          pre_buffer = m_allocator.allocate(n);
        } catch (const std::exception& e) {
          throw e;
        }        
        new_front = (n - m_size)/2;        
        memcpy(pre_buffer + new_front, m_buffer + m_front, ((byte*)(m_buffer + m_front + m_size)) - ((byte*)(m_buffer + m_front))) ;
        m_allocator.deallocate(m_buffer, m_capacity);
        m_buffer = pre_buffer;
        m_front = new_front;
        m_capacity = n;
      }
    }
  };
};


#endif
