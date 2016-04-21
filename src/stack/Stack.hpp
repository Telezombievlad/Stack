#ifndef HEADER_GUARD_STACK_STACK_HPP_INCLUDED
#define HEADER_GUARD_STACK_STACK_HPP_INCLUDED

#include <utility>
#include <exception>

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
				// Operator=
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
			//
			// Basics
				Stack() :
					stackHead_ (nullptr)
				{}

				Stack(const Stack<T>& stack) :
					stackHead_ (nullptr)
				{
					if (&stack == this) return;
					if (stack.empty())  return;

					stackHead_ = new _detail::Node<T>(*stack.stackHead_);

					for (_detail::Node<T>* thatPtr = stack.stackHead_->nextNode,
										    ourPtr = stackHead_; 
						thatPtr != nullptr; 
						thatPtr = thatPtr->nextNode,
						 ourPtr =  ourPtr->nextNode)
					{
						ourPtr->nextNode = new _detail::Node<T>(*thatPtr); 
					}
				}

				Stack(const Stack<T>&& stack) : 
					stackHead_ (nullptr)
				{
					if (stack.empty()) return;

					std::swap(stackHead_, stack.stackHead_);
				}

				~Stack()
				{
					if (!empty()) delete stackHead_;
				}

			//
			// Operator =
				Stack& operator=(const Stack<T>& stack)
				{
					if (&stack == this) return *this;
					if (stack.empty())  return *this;

					stackHead_ = new _detail::Node<T>(*stack.stackHead_);

					for (_detail::Node<T>* thatPtr = stack.stackHead_->nextNode,
										    ourPtr = stackHead_; 
						thatPtr != nullptr; 
						thatPtr = thatPtr->nextNode,
						 ourPtr =  ourPtr->nextNode)
					{
						ourPtr->nextNode = new _detail::Node<T>(*thatPtr); 
					}

					return *this;
				}

				Stack& operator=(const Stack<T>&& stack)
				{
					if (stack.empty()) return;

					if (!empty()) delete stackHead_;

					stackHead_ = nullptr;
					std::swap(stackHead_, stack.stackHead_);

					return *this;
				}

			//
			// Getters && setters

				const T& head() const
				{
					if (empty())
					{
						throw std::out_of_range("const T& Stack::head(): Stack is empty");
					}

					return stackHead_->element;
				}

				Stack& setHead(const T& newHead)
				{
					if (empty())
					{
						throw std::out_of_range("T& Stack::head(): Stack is empty");
					}

					stackHead_->element = newHead;

					return *this;
				}

				Stack& setHead(T&& newHead)
				{
					if (empty())
					{
						throw std::out_of_range("T& Stack::head(): Stack is empty");
					}

					stackHead_->element = std::move(newHead);

					return *this;
				}

			//
			// Other functions
				bool empty() const
				{
					return stackHead_ == nullptr;
				}

				Stack& push(const T& element)
				{
					stackHead_ = new _detail::Node<T>(stackHead_, element);

					return *this;
				}

				Stack& push(T&& element)
				{
					stackHead_ = new _detail::Node<T>(stackHead_, std::move(element));

					return *this;
				}

				T&& pop()
				{
					if (empty())
					{
						throw std::out_of_range("T&& Stack::pop(): Stack is empty");
					}

					T&& toReturn = std::move(stackHead_->element);

					_detail::Node<T>* toDelete = stackHead_;
					stackHead_ = stackHead_->nextNode;

					delete toDelete;

					return std::move(toReturn);
				}

		private:
			// Variables:
				_detail::Node<T>* stackHead_;
	};
}

#endif /*HEADER_GUARD_STACK_STACK_HPP_INCLUDED*/
