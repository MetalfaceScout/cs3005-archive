#ifndef _THREADEDVECTOR_H_
#define _THREADEDVECTOR_H_

#include <functional>
#include <memory>
#include <vector>
#include <mutex>
#include "NumberGrid.h"
#include <thread>
#include <stdlib.h>
#include <iostream>

template < typename T >
class ThreadedVector {
public:
  typedef typename std::vector< T >::size_type size_type;

  ThreadedVector( );
  ThreadedVector( size_type n );

  void back( T& value );
  void back( std::vector< T >& values, const size_type n );
  
  void clear( );

  bool empty( );

  const T& operator[]( const size_type n );

  void pop_back( );
  void pop_back( const size_type n );
  void pop_back( std::vector< T >& values, const size_type n );

  void push_back( const T& value );
  void push_back( const std::vector< T >& values );
  
  void resize( size_type n );
  void resize( size_type n, const T& value );

  size_type size( );
  
protected:
  std::mutex mReadLock;
  std::mutex mWriteLock;
  std::vector< T > mData;
  
private:
  
};


template < typename T >
ThreadedVector< T >::ThreadedVector( ) {
}

template < typename T >
ThreadedVector< T >::ThreadedVector( size_type n )
  : mData( n ) {
}

template < typename T >
/*
Push back a single value to the vector.
*/
void ThreadedVector< T >::back( T& value ) {
  mReadLock.lock( );

  value = mData.back( );

  mReadLock.unlock( );
}

template < typename T >
/*
Push back a vector to the threadedvector 
*/
void ThreadedVector< T >::back( std::vector< T >& values, const size_type n ) {
  mReadLock.lock( );

  for( size_type i = 0; i < n && i < mData.size( ); i++ ) {
    values.push_back( mData[ mData.size( ) - i - 1 ] );
  }
  
  mReadLock.unlock( );
  
}

template < typename T >
/*
Clear the vectors data.
*/
void ThreadedVector< T >::clear( ) {
  mWriteLock.lock( );
  mReadLock.lock( );

  mData.clear( );

  mReadLock.unlock( );
  mWriteLock.unlock( );
}

template < typename T >
/*
Check if the vector is empty.
*/
bool ThreadedVector< T >::empty( ) {
  mReadLock.lock( );

  bool value = mData.empty( );

  mReadLock.unlock( );
  return value;
}

template < typename T >
/*
Use the [] operator to grab a value from the vector.
*/
const T& ThreadedVector< T >::operator[]( const size_type n ) {
  mReadLock.lock( );

  T& value = mData[ n ];

  mReadLock.unlock( );
  
  return value;
}

template < typename T >
/**
       *  @brief  Removes last element.
       *
       *  This is a typical stack operation. It shrinks the %vector by one.
       *
       *  Note that no data is returned, and if the last element's
       *  data is needed, it should be retrieved before pop_back() is
       *  called.
       */
void ThreadedVector< T >::pop_back( ) {
  mWriteLock.lock( );
  mReadLock.lock( );

  mData.pop_back( );

  mReadLock.unlock( );
  mWriteLock.unlock( );
}
 
template < typename T >
/*
pop_back() n times, see pop_back() for details.
*/
void ThreadedVector< T >::pop_back( const size_type n ) {
  mWriteLock.lock( );
  mReadLock.lock( );
  
  for( size_type i = 0; i < n && mData.size( ) > 0; i++ ) {
    mData.pop_back( );
  }

  mReadLock.unlock( );
  mWriteLock.unlock( );
}
 
template < typename T >
/*
Pop N values from the vector, then push back value N times.
*/
void ThreadedVector< T >::pop_back( std::vector< T >& values, const size_type n ) {
  mWriteLock.lock( );
  mReadLock.lock( );
  
  for( size_type i = 0; i < n && mData.size( ) > 0; i++ ) {
    values.push_back( mData.back( ) );
    mData.pop_back( );
  }

  mReadLock.unlock( );
  mWriteLock.unlock( );
}

template < typename T >
/**
       *  @brief  Add data to the end of the %vector.
       *  @param  __x  Data to be added.
       *
       *  This is a typical stack operation.  The function creates an
       *  element at the end of the %vector and assigns the given data
       *  to it.  Due to the nature of a %vector this operation can be
       *  done in constant time if the %vector has preallocated space
       *  available.
       */
void ThreadedVector< T >::push_back( const T& value ) {
  mWriteLock.lock( );
  mReadLock.lock( );

  mData.push_back( value );

  mReadLock.unlock( );
  mWriteLock.unlock( );
}

/*
Push back a vector of values. See push_back for details.
*/
template < typename T >
void ThreadedVector< T >::push_back( const std::vector< T >& values ) {
  mWriteLock.lock( );
  mReadLock.lock( );
  
  for( size_type i = 0; i < values.size( ); i++ ) {
    mData.push_back( values[ i ] );
  }

  mReadLock.unlock( );
  mWriteLock.unlock( );
}
  
template < typename T >
/*
Makes vector size of N. Vector values are undefined.
*/
void ThreadedVector< T >::resize( size_type n ) {
  mWriteLock.lock( );
  mReadLock.lock( );

  mData.resize( n );

  mReadLock.unlock( );
  mWriteLock.unlock( );
}

template < typename T >
/*
Makes vector size of N. Vector values are "value".
*/
void ThreadedVector< T >::resize( size_type n, const T& value ) {
  mWriteLock.lock( );
  mReadLock.lock( );

  mData.resize( n, value );

  mReadLock.unlock( );
  mWriteLock.unlock( );
}

template < typename T >
/*
Return number of elements in vector.
*/
typename ThreadedVector< T >::size_type ThreadedVector< T >::size( ) {
  mReadLock.lock( );

  size_type value = mData.size( );

  mReadLock.unlock( );
  
  return value;
}


#endif /* _THREADEDVECTOR_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
