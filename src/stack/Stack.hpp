#ifndef HEADER_GUARD_STACK_STACK_HPP_INCLUDED
#define HEADER_GUARD_STACK_STACK_HPP_INCLUDED

template <class TypeA>
class Node
{
	friend class Stack<TypeA>;

	private:

		// Variables:

			std::unique_ptr<Node<TypeA>> nextNode_;

			TypeA element_;

		// Ctors && dtor:

			// Creates a node
			Node(TypeA&& element);

			// Move constructor
			Node(Node&& element);

			// Dtor
			~Node();

		// Assignment:

			// Move assignment operator
			Node& operator=(const Node<TypeA>&& node);
};

template <class TypeA>
class Stack
{
	public:

		// Ctors && dtor:

			// Creates an empty stack
			Stack();

			// Copy constructor
			Stack(const Stack<TypeA>& stack);

			// Destructor
			~Stack();

		// Assignment:

			// Assignment operator
			Stack& operator=(const Stack<TypeA>& stack);

		// Functions:

			// Checks, whether the stack is empty
			bool empty() const;

			// Inserts an element to stack head
			Stack& push(TypeA&& element); 

			// Provides access to the head of the stack
			const TypeA& head();

			// Returns head of the stack and deletes it from the stack
			TypeA&& pop();

	private:

		// Variables:

			std::unique_ptr<Node<TypeA>> stackHead_;
};

#endif /*HEADER_GUARD_STACK_STACK_HPP_INCLUDED*/

