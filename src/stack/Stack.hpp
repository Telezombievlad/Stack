#ifndef HEADER_GUARD_STACK_STACK_HPP_INCLUDED
#define HEADER_GUARD_STACK_STACK_HPP_INCLUDED

namespace Stack
{

	namespace _detail
	{
		template <class T>
		struct Node
		{
			public:

				// Variables:

					Node<T>* nextNode_;

					T element_;

				// Ctors && dtor:

					Node() = default;

					Node(Node<T>&& element);

					Node(T&& element);

					~Node();

				// Assignment:

					Node& operator=(const Node<T>&& node);

					Node& operator=(const T&& element);
		};
	}

	template <class T>
	class Stack
	{
		public:

			// Ctors && dtor:

				Stack();

				Stack(const Stack<T>&  stack);
				Stack(const Stack<T>&& stack);

				~Stack();

			// Assignment:

				Stack& operator=(const Stack<T>&  stack);
				Stack& operator=(const Stack<T>&& stack);

			// Functions:

				bool empty() const;

				Stack& push(T&& element); 
				
				T&& pop();

				const T& head() const;
				T& head();

		private:

			// Variables:

				_detail::Node<T>* stackHead_;
	};

}

#endif /*HEADER_GUARD_STACK_STACK_HPP_INCLUDED*/
