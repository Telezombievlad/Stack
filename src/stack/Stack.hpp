#ifndef HEADER_GUARD_STACK_STACK_HPP_INCLUDED
#define HEADER_GUARD_STACK_STACK_HPP_INCLUDED

#include <utility>

namespace Stack
{
	namespace _detail
	{
		template <class T>
		struct Node
		{
			public:
				Node<T>* nextNode;
				T element;

				//
				// Basics
					Node(Node<T>* next, T&& data) :
						nextNode(next),
						element(data)
					{}

					Node(const Node<T>& that) :
						nextNode(new Node<T>(*that.nextNode)),
						element(that.element)
					{}

					Node(Node<T>&& that) :
						nextNode(that.nextNode),
						element(std::move(that.element)) // Instead of the copy constructor invoke the move constructor
					{
						that.releaseResources();
					}

					Node(T&& data) :
						nextNode(nullptr),
						element(data)
					{}

					~Node()
					{
						if (nextNode != nullptr)
							delete nextNode;
					}

				//
				// operator=
					Node& operator=(const Node<T>& that)
					{
						nextNode = new Node<T>(*that.nextNode);
						element = that.element;

						return *this;
					}

					Node& operator=(Node<T>&& that)
					{
						nextNode = that.nextNode;
						element = std::move(that.element);
						that.releaseResources();

						return *this;
					}

					Node& operator=(T&& data)
					{
						element = data;

						return *this;
					}

			private:
				void releaseResources()
				{
					nextNode = nullptr;
				}
		};
	}

	template <class T>
	class Stack
	{
		public:
			// Ctors && dtor:
				Stack() :
					stackHead_ (nullptr)
				{}

				Stack(const Stack<T>& stack);
				Stack(const Stack<T>&& stack);
				~Stack();
			// Assignment:
				Stack& operator=(const Stack<T>& stack);
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
