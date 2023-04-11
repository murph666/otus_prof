#pragma once

#include <iostream>

// Базовый узел - элемент
// template <class T>


template <typename T, class Allocator = std::allocator<T>>
class OneWayList
{
private:
    struct Node
        {
            Node() : next{nullptr} {}
            explicit Node(const T &value) : data{value}, next{nullptr} {}

            T data;     // данные
            Node *next; // следующий элемент
        };

    Node *begin_node;           // указатель на начало списка
    Node *end_node;             // указатель на конец списка
    unsigned int total_number;  // количество элементов в списке

public:
    using node_alloc = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    node_alloc allocator;
    // typename std::allocator_traits<Allocator>::template rebind_alloc<Node<T>> allocator;

    struct Iterator
    {
        Iterator() : iter_node{nullptr} {}
        explicit Iterator(Node *new_iter_ptr) : iter_node{new_iter_ptr} {}

        Node *operator++()
        {
            iter_node = iter_node->next;
            return iter_node;
        }
        T &operator*()
        {
            return iter_node->data;
        }

        bool operator==(const Iterator &another)
        {
            return (iter_node == another.iter_node);
        }

        bool operator!=(const Iterator &another)
        {
            return !(iter_node == another.iter_node);
        }

    private:
        Node *iter_node;
    };

    OneWayList() : begin_node{nullptr}, end_node{nullptr}, total_number{0}
    {
        std::cout << "OneWayList Container default constructor" << std::endl;
    }

    ~OneWayList()
    {
        Node* current_node_ptr = begin_node;
		Node* next_to_delete_node_ptr = nullptr;

		while (current_node_ptr != nullptr) {
			next_to_delete_node_ptr = current_node_ptr->next;
			allocator.deallocate(current_node_ptr, 1);
			current_node_ptr = next_to_delete_node_ptr;
		}

		begin_node = end_node = nullptr;
		total_number = 0;

    }

    int size() { return total_number; }

    // void destroyNode(Node *node)
    // {
    //     allocator.destroy(node);
    //     allocator.deallocate(node, 1);
    // }

    void push_back(const T &value)
    {
        // Создаем новую ноду
        Node *new_value = allocator.allocate(1);
        allocator.construct(new_value, value);
        // new_value->next = nullptr;
        // Если пустой -> новая нода будет начальной
        if (total_number == 0)
        {
            begin_node = end_node = new_value;
        }
        // // Если нет, то новая нода становится последней
        else
        {
            end_node->next = new_value;
            end_node = new_value;
        }
            total_number++;
    }

    Node *move(const unsigned int position)
    {
        if (total_number > 0)
        {
            Node *temp_node = begin_node;
            for (unsigned int i = 0; i < position; i++)
            {
                temp_node = temp_node->next;
            }
            return temp_node;
        }
        return nullptr;
    }

    void erase(const unsigned int position)
    {
        if (position != 0)
        {
            Node *del_node = move(position);
            Node *prev_del_node = move(position - 1);

            prev_del_node->next = del_node->next;
            delete del_node;
        }
        else
        {
            Node *del_node = begin_node;
            begin_node = del_node->next;
            delete del_node;
        }
        total_number--;
    }

    void insert(const unsigned int position, const T &value)
    {
        if (position == total_number)
        {
            push_back(value);
        }
        else if (position == 0)
        {
            Node *new_node = new Node;
            new_node->data = value;
            new_node->next = begin_node;
            begin_node = new_node;
            total_number++;
        }

        else
        {
            Node *new_node = new Node;
            Node *insert_node = move(position - 1);

            new_node->data = value;
            new_node->next = insert_node->next;

            insert_node->next = new_node;
            total_number++;
        }
    }

    T &operator[](const unsigned int place)
    {
        Node *temp_node = move(place);
        return temp_node->data;
    }

    Iterator begin() const
    {
        return Iterator(begin_node);
    }

    Iterator last_valid() const
    {
        if (end_node != nullptr)
        {
            return Iterator(end_node);
        }
        else
        {
            return Iterator(nullptr);
        }
    }

    Iterator end() const
    {
        if (end_node != nullptr)
        {
            return Iterator(end_node->next);
        }
        else
        {
            return Iterator(nullptr);
        }
    }
};

template <typename T, class Allocator>
std::ostream &operator<<(std::ostream &os, const OneWayList<T, Allocator> &container)
{
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        os << *iter;
        if (iter != container.last_valid())
        {
            os << ", ";
        }
        else
        {
            os << std::endl;
        }
    }
    return os;
}
