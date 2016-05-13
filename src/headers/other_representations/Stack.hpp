#ifndef HEADER_GUARD_NODE_REPRESENTATION_STACK_HPP_INCLUDED
#define HEADER_GUARD_NODE_REPRESENTATION_STACK_HPP_INCLUDED

#include <utility>
#include <exception>
#include <initializer_list>
#include <iterator>

#include <string>

namespace MyStackNodeRepresentation
{
	namespace _detail
	{
		template <class T>
		struct Node
		{
		public:
			// Variables:
				Node<T>* nextNode;
				T element;

			// Ctors && dtor:
				Node(Node<T>* next, const T& data) :
					nextNode(next),
					element(data)
				{}	

				Node(Node<T>* next, T&& data) :
					nextNode(next),
					element(std::move(data))
				{}

				Node(const Node<T>& that) :
					nextNode((that.nextNode != nullptr)? new Node<T>(*that.nextNode) : nullptr),
					element(that.element)
				{}

				Node(Node<T>&& that) :
					nextNode(that.nextNode),
					element(std::move(that.element)) // Instead of the copy constructor invoke the move constructor
				{
					that.releaseResources();
				}

				~Node()
				{
					if (nextNode != nullptr)
						delete nextNode;
				}

			// Operator=:
				Node& operator=(const Node<T>& that)
				{
					if (this == &that) return *this;

					if (nextNode != nullptr) delete nextNode;

					nextNode = new Node<T>(*that.nextNode);
					element = that.element;

					return *this;
				}

				Node& operator=(Node<T>&& that)
				{
					if (this == &that) return *this;

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

			// Additional:
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

			Stack(const Stack<T>& that) :
				stackHead_ (nullptr)
			{
				if (that.stackHead_ == nullptr) stackHead_ = nullptr;
				else stackHead_ = new _detail::Node<T>(*that.stackHead_);
			}

			Stack(Stack<T>&& that) : 
				stackHead_ (that.stackHead_)
			{
				that.releaseResources();
			}

			Stack(std::initializer_list<T> initList) :
				stackHead_ (nullptr)
			{
				for (auto i = initList.begin(); i != initList.end(); ++i)
				{
					push(*i);
				}
			}

			~Stack()
			{
				if (stackHead_ != nullptr) delete stackHead_;

				stackHead_ = nullptr;
			}

		// Operator =:
			Stack& operator=(const Stack<T>& that)
			{
				if (&that == this) return *this;

				if (stackHead_ != nullptr) delete stackHead_; 
				
				if (that.stackHead_ == nullptr) stackHead_ = nullptr;
				else stackHead_ = new _detail::Node<T>(*that.stackHead_);

				return *this;
			}

			Stack& operator=(Stack<T>&& that)
			{
				if (&that == this) return *this;

				if (stackHead_ != nullptr) delete stackHead_;
				
				stackHead_ = that.stackHead_;
				that.releaseResources();

				return *this;
			}

			Stack& operator=(std::initializer_list<T> initList)
			{
				if (stackHead_ != nullptr) delete stackHead_;
				stackHead_ = nullptr;

				for (auto i = initList.begin(); i != initList.end(); ++i)
				{
					push(*i);
				}

				return *this;
			}

		// Getters && setters:
			const T& head() const
			{
				if (stackHead_ == nullptr)
				{
					throw std::out_of_range("const T& Stack::head(): Stack is empty");
				}

				return stackHead_->element;
			}

			Stack& setHead(const T& newHead)
			{
				if (stackHead_ == nullptr)
				{
					throw std::out_of_range("T& Stack::head(): Stack is empty");
				}

				stackHead_->element = newHead;

				return *this;
			}

			Stack& setHead(T&& newHead)
			{
				if (stackHead_ == nullptr)
				{
					throw std::out_of_range("T& Stack::head(): Stack is empty");
				}

				stackHead_->element = std::move(newHead);

				return *this;
			}

			bool empty() const noexcept
			{
				return stackHead_ == nullptr;
			}

		// Push/pop:
			Stack& push(const T& element)
			{
				stackHead_ = new _detail::Node<T>(stackHead_, element);

				return *this;
			}

			Stack& push(T&& element)
			{
				stackHead_ = new _detail::Node<T>(stackHead_, element);

				return *this;
			}

			T&& pop()
			{
				if (stackHead_ == nullptr)
				{
					throw std::out_of_range("T&& Stack::pop(): Stack is empty");
				}

				T toReturn = std::move(stackHead_->element);

				_detail::Node<T>* toDelete = stackHead_;

				stackHead_ = stackHead_->nextNode;

				toDelete->releaseResources();
				delete toDelete;

				return std::move(toReturn);
			}

	private:
		// Variables:
			_detail::Node<T>* stackHead_;

		// Functions:
			void releaseResources() noexcept
			{
				stackHead_ = nullptr;
			}
	}; 
}

#endif /*HEADER_GUARD_NODE_REPRESENTATION_STACK_HPP_INCLUDED*/
