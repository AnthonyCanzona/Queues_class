/*****************************************
 * UW User ID:  acanzona
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2022
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
		unsigned int q_size;
		unsigned int q_cap;
		unsigned int q_init_cap;
		unsigned int q_head;
		unsigned int q_tail;
		Type *Q_arr;

		// Any private member functions
		//   - helper functions for resizing your array?
		void resize_q( unsigned int );
		void first_elem( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor of the deque Class that initializes and allocates memory for array and initializes variables
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
// Your initalization list
{
	q_init_cap = n;
	q_size = 0;
	q_cap = (n >= 16) ? n : 16;
	Q_arr = new Type[q_cap];
	q_head = (q_cap/2);
	q_tail = (q_cap/2);
}

// Copy Constructor (OPTIONAL) copies data from one deque to another
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	// Enter your implementation here
	Resizable_deque new_q (deque.q_cap);
	for(unsigned int i {0}; i < deque.q_cap; i++){
		new_q.Q_arr[i] = deque.Q_arr[i];
	}
	new_q.q_head = deque.q_head;
	new_q.q_tail = deque.q_tail;
	new_q.q_size = deque.q_size;
}

// Move Constructor (OPTIONAL) moves variable data from a existing deque to a new deque
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	Resizable_deque new_q (deque.q_cap);
	deque.swap(new_q);
}

// Destructor that deletes the arrays memory
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	// Enter your implementation here
	delete[] Q_arr;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

//Returns the size of the deque
template <typename Type>
int Resizable_deque<Type>::size() const {
	// Enter your implementation here
	return q_size;
}

//Returns the capacity of the deque
template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Enter your implementation here
	return q_cap;
}

//Returns whether or not the deque is empty 
template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	return q_size <= 0 ;
}

//Returns the data at the front of the deque. Returns an error if empty
template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
	if (empty()){throw underflow();}
	return Q_arr[q_head];
}

//Returns the data at the back of the deque. Returns an error if empty
template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
	if (empty()){throw underflow();}
	return Q_arr[q_tail];
}

//Swaps all private variables of a given passed deque and the called 'this' deque
template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );

	// Enter your implementation here
	std::swap( q_size, deque.q_size );
	std::swap( q_cap, deque.q_cap );
	std::swap( q_head, deque.q_head );
	std::swap( q_tail, deque.q_tail);
	std::swap( q_init_cap, deque.q_init_cap );
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

//Pushes a given object to the front of the deque. Resizes the deque if full
template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Enter your implementation here
	if (q_size == q_cap){resize_q(2 * q_cap);}
	if (empty()){first_elem( obj );}
	else{
		q_head = (q_head == q_cap - 1) ? 0 : ++q_head;
		Q_arr[q_head] = obj;
		q_size++;
	}
}

//Pushes a given object to the back of the deque. Resizes the deque if full
template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Enter your implementation here
	if (q_size == q_cap){resize_q(2 * q_cap);}
	if (empty()){first_elem( obj );}
	else{
		q_tail = (q_tail == 0) ? q_cap - 1 : --q_tail;
		Q_arr[q_tail] = obj;
		q_size++;
	}
}

//Removes the object at the front of the deque. Returns an error if the deque is empty. Resizes the deque if only 1/4 full
template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Enter your implementation here
	if (empty()){throw underflow();}
	if (q_size <= q_cap/4){resize_q(q_cap / 2);}
	if (q_size == 1){q_size = 0;}
	else{ 
		q_head = (q_head == 0) ? q_cap - 1 : --q_head;
		q_size--;
	}
}
//Removes the object at the back of the deque. Returns an error if the deque is empty. Resizes the deque if only 1/4 full
template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Enter your implementation here
	if (empty()){throw underflow();}
	if (q_size <= q_cap/4){resize_q(q_cap / 2);}
	if (q_size == 1){q_size = 0;}
	else{
		q_tail = (q_tail == q_cap - 1) ? 0 : ++q_tail;
		q_size--;
	}
}

//Clears the deque of all data. Resets the deque
template <typename Type>
void Resizable_deque<Type>::clear() {
	// Enter your implementation here
	resize_q(q_init_cap);
	q_size = 0;
	q_cap = (q_init_cap >= 16) ? q_init_cap : 16;
	q_head = (q_cap/2);
	q_tail = (q_cap/2);

}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functions (helper functions) here

//A private function that takes an unsigned int size of a cap to resize "this" given array
template <typename Type>
void Resizable_deque<Type>::resize_q(unsigned int cap) {
	if (cap < 16){cap = 16;}
	Type *New_arr = new Type [cap];
	unsigned int indx = q_tail;
	for(unsigned int i {0}; i < q_size; i++){
		New_arr[i] = Q_arr[indx];
		indx = (indx >= q_cap - 1)? 0 : ++indx;
	}	
	q_cap = cap;
	q_tail = 0;
	q_head = q_size - 1;
	delete [] Q_arr; 
	Q_arr = New_arr;
}

//A private function that is called to input the first element into the array
template <typename Type>
void Resizable_deque<Type>::first_elem( Type const &obj ) {
	Q_arr[q_head] = obj;
	q_size++;
}

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
