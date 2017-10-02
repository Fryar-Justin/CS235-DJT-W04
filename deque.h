/***********************************************************************
 * Header:
 *    DEQUE
 * Summary:
 *    This will contain the deque class that is similar to the deque
 *    class, except it is FIFO/LILO
 * Author
 *    Devin Cenatiempo, Justin Fryar, Tyler Austin
 ************************************************************************/

#ifndef deque_h
#define deque_h
#include <new>
#include <iostream>
namespace custom
{
   /************************************************
    * deque
    * A class that holds stuff and is accessible
    * at either end
    ***********************************************/
   template <class T>
   class deque {
      private:
      T * data;         // dynamically allocated array of T
      int iFront;       // changed when push-front() or pop_front called
      int iBack;        // changed when push-front() or pop()_back called
      int numCapacity;  // how many items the deque can hold
      int iFrontNormalized() const ;
      int iBackNormalized() const ;
      public:
      // constructors and destructors
      deque() {this->iFront = 0; this->iBack = -1; this->numCapacity = 0; this->data = NULL;}
      deque(int capacity) throw (const char *);
      deque(const deque & rhs) throw (const char *);
      ~deque();
      // standard container interfaces
      int  size()     const { return iBack - iFront + 1;  }
      bool empty()    const { return size() == 0; }
      void clear()          { iFront = 0; iBack = -1;  }
      deque & operator = (const deque & rhs) throw (const char *);
      // deque specific methods
      void push_front(T data) throw (const char *);
      void push_back(T data) throw (const char *);
      void pop_front();
      void pop_back();
      T & front()     throw (const char *);
      T front() const throw (const char *);
      T & back()      throw (const char *);
      T back() const  throw (const char *);
   };
   
   /**********************************************
    * deque : NON-DEFAULT CONSTRUCTOR
    * Preallocate the deque to capacity
    **********************************************/
   template <class T>
   deque <T> :: deque(int capacity)
   throw (const char *)
   {
      this->iFront = 0;
      this->iBack = -1;
      this->numCapacity = capacity;
      // do nothing if there is nothing to do.
      if (numCapacity <= 0)
      {
         this->data = NULL;
         return;
      }
      // attempt to allocate
      try
      { data = new T[capacity]; }
      catch (std::bad_alloc)
      { throw "ERROR: Unable to allocate buffer"; }
   }
   
   /*******************************************
    * deque :: COPY CONSTRUCTOR
    *******************************************/
   template <class T>
   deque <T> :: deque(const deque <T> & rhs)
   throw (const char *)
   {
      // do nothing if there is nothing to do
      if (rhs.size() == 0)
      {
         iFront = 0;
         iBack = -1;
         numCapacity = 0;
         data = NULL;
         return;
      }
      // attempt to allocate
      try
      { data = new T[rhs.numCapacity]; }
      catch (std::bad_alloc)
      { throw "ERROR: Unable to allocate buffer"; }
      // copy over the capacity
      iFront = 0;
      iBack = rhs.size() - 1;
      numCapacity = iBack + 1;
      
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[ (rhs.iFrontNormalized() + i) % rhs.numCapacity ];
   }
   
   /*******************************************
    * deque :: DECONSTRUCTOR
    *******************************************/
   template <class T>
   deque <T> :: ~deque()
   {
      delete [] data;
   }
   /*******************************************
    * deque :: Assignment
    *******************************************/
   template <class T>
   deque <T> & deque <T> :: operator = (const deque <T> & rhs)
   throw (const char *)
   {
      iFront = 0;
      iBack = rhs.size() - 1;
      
      if (size() > numCapacity)
      {
         // attempt to allocate memory
         try
         { data = new T[rhs.size()]; }
         catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate buffer"; }
         numCapacity = iBack +1 ;
      }
      for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[ (rhs.iFrontNormalized() + i) % rhs.numCapacity ];
      return *this;
   }
   
   /*****************************************************
    * deque :: IFRONTNORMALIZED
    * Returns a normalized value of iFront.
    * void --> int
    *****************************************************/
   template <class T>
   int deque <T> :: iFrontNormalized() const
   {
      if (iFront >= 0)
      return iFront % numCapacity;
      else
      return iFront + numCapacity + (-iFront/(numCapacity+1)) * numCapacity;
   }
   
   /*****************************************************
    * deque :: IBACKNORMALIZED
    * Returns a normalized value of iBack.
    * void --> int
    *****************************************************/
   template <class T>
   int deque <T> :: iBackNormalized() const
   {
      if (iBack >= 0)
      return iBack % numCapacity;
      else
      return iBack + numCapacity + (-iBack/(numCapacity+1)) * numCapacity;
   }
   /*****************************************************
    * deque :: PUSH_BACK
    * Adds an element to the deque.
    * If the deque is full,
    * then the capacity will be doubled.
    * void --> void
    *****************************************************/
   template <class T>
   void deque <T> :: push_back(T data)
   throw(const char *)
   {
      //---Create New deque:---
      //Checks whether the deque is empty
      if (numCapacity <= 0)
      {
         numCapacity = 1;
         try
         { this->data = new T[1]; }
         catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate a new buffer for deque"; }
      }
      else if (numCapacity == size())
      {
         numCapacity *= 2;
         // attempt to allocate memory
         try
         {
            T * tempData = new T[numCapacity];
            // copy data to a new, larger array
            for (int i = iFrontNormalized(); i < (iFrontNormalized()+size()); i++)
            {
               if (i< numCapacity/2)
               tempData[i % numCapacity] = this->data[i];
               else tempData[i % numCapacity] = this->data[(i-numCapacity/2)%(numCapacity/2)];
            }
            
            // save data to correct location
            delete [] this->data;
            this->data = tempData;
         }
         catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate a new buffer for deque"; }
      }
      
      //---Add Element to deque:---
      //attempt to allocate memory
      iBack++;
      this->data[iBackNormalized()] = data;
      
      //std::cerr << "elements: " << size() << "/" << numCapacity << std::endl;
      //std::cerr << "push: " << numPush << ", pop: " << numPop << std::endl;
      //std::cerr << "iHead: " << this->data[iHead()] << " at index " << iHead() << std::endl;
      //std::cerr << " iTail: " << this->data[iTail()] << " at index " << iTail() << std::endl;
   }
   
   /*****************************************************
    * deque :: PUSH_FRONT
    * Adds an element to the deque.
    * If the deque is full,
    * then the capacity will be doubled.
    * void --> void
    *****************************************************/
   template <class T>
   void deque <T> :: push_front(T data)
   throw(const char *)
   {
      //---Create New deque:---
      //Checks whether the deque is empty
      if (numCapacity <= 0)
      {
         numCapacity = 1;
         try
         { this->data = new T[1]; }
         catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate a new buffer for deque"; }
      }
      else if (numCapacity == size())
      {
         numCapacity *= 2;
         // attempt to allocate memory
         try
         {
            T * tempData = new T[numCapacity];
            // copy data to a new, larger array
            for (int i = iFrontNormalized(); i < (iFrontNormalized()+size()); i++)
            {
               if (i< numCapacity/2)
               tempData[i % numCapacity] = this->data[i];
               else tempData[i % numCapacity] = this->data[(i-numCapacity/2)%(numCapacity/2)];
            }
            
            // save data to correct location
            delete [] this->data;
            this->data = tempData;
         }
         catch (std::bad_alloc)
         { throw "ERROR: Unable to allocate a new buffer for deque"; }
      }
      
      //---Add Element to deque:---
      //attempt to allocate memory
      iFront--;
      this->data[iFrontNormalized()] = data;
      
      //std::cerr << "elements: " << size() << "/" << numCapacity << std::endl;
      //std::cerr << "push: " << numPush << ", pop: " << numPop << std::endl;
      //std::cerr << "iHead: " << this->data[iHead()] << " at index " << iHead() << std::endl;
      //std::cerr << " iTail: " << this->data[iTail()] << " at index " << iTail() << std::endl;
   }
   
   /*****************************************************
    * deque :: POP_BACK
    * Removes an element from the end of the deque,
    * serving to reduce the size by one.
    * void --> void
    *****************************************************/
   template <class T>
   void deque <T> :: pop_back()
   {
      // if the deque is empty, there is nothing to do.
      if(size() == 0 || numCapacity <= 0)
      return;
      else
      iBack--;
   }
   
   /*****************************************************
    * deque :: POP_FRONT
    * Removes an element from the end of the deque,
    * serving to reduce the size by one.
    * void --> void
    *****************************************************/
   template <class T>
   void deque <T> :: pop_front()
   {
      // if the deque is empty, there is nothing to do.
      if(size() == 0 || numCapacity <= 0)
      return;
      else
      iFront++;
   }
   
   /*****************************************************
    * deque :: BACK
    * Returns the element currently
    * at the end of the deque.
    * A non-constant method which returns by-reference.
    * void --> Object Reference
    *****************************************************/
   template <class T>
   T & deque <T> :: back()
   throw (const char *)
   {
      // if the deque is empty, throw an error.
      if(size() == 0 || numCapacity <= 0)
      throw "ERROR: unable to access data from an empty deque";
      return data[ iBackNormalized() ];
   }
   
   /*****************************************************
    * deque :: BACK - CONST
    * Returns the element currently
    * at the end of the deque.
    * A constant method which returns const by-reference.
    * void --> Object
    *****************************************************/
   template <class T>
   T deque <T> :: back() const
   throw (const char *)
   {
      // if the deque is empty, throw an error.
      if(size() == 0 || numCapacity <= 0)
      throw "ERROR: unable to access data from an empty deque";
      return data[ iBackNormalized() ];
   }
   
   /*****************************************************
    * deque :: FRONT
    * Returns the element at front of deque
    * A non-constant method which returns by-reference.
    * void --> Object Reference
    *****************************************************/
   template <class T>
   T & deque <T> :: front()
   throw (const char *)
   {
      // if the deque is empty, throw an error.
      if(size() == 0 || numCapacity <= 0)
      throw "ERROR: unable to access data from an empty deque";
      return data[ iFrontNormalized() ];
   }
   
   /*****************************************************
    * deque :: FRONT - CONST
    * Returns the element at front of deque
    * A constant method which returns const by-reference.
    * void --> Object
    *****************************************************/
   template <class T>
   T deque <T> :: front() const
   throw (const char *)
   {
      // if the deque is empty, throw an error.
      if(size() == 0 || numCapacity <= 0)
      throw "ERROR: unable to access data from an empty deque";
      return data[ iFrontNormalized() ];
   }
   
}; // end custom namespace
#endif /* deque_h */
