#include <iostream>
#include <map>
#include <vector>

#define USE_PRETTY 1

/**
 * @brief  The custom MemoryChunk for allocator.
 *
 * @tparam  *memory_ptr
 * @tparam  *end_memory_ptr
 * @tparam  size
 * @tparam  occupied
 * @tparam  released
 * @tparam  *next_chank
 *
 * @headerfile memory
 */
template <typename T>
struct MemoryChunk
{
    void *memory_ptr = nullptr;
    void *end_memory_ptr = nullptr;

    std::size_t size = 0;
    std::size_t occupied = 0;
    std::size_t released = 0;

    MemoryChunk<T> *next_chank = nullptr;

    MemoryChunk() : memory_ptr{nullptr},
                    end_memory_ptr{nullptr}, size{0}, occupied{0}, released{0} {
                        std::cout << "MemoryChunk default constructor."<< sizeof(T) << std::endl;
                    };

    void *allocate_block(const size_t &items_number)
    {
#ifdef USE_PRETTY
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        memory_ptr = std::malloc(items_number * sizeof(T));
        std::cout << memory_ptr << std::endl;
        if (!memory_ptr)
            return nullptr;

        end_memory_ptr = memory_ptr;
        size = items_number;

        return memory_ptr;
    }

    void *rezerve_block(const size_t &n)
    {
        end_memory_ptr = (static_cast<char *>(end_memory_ptr) + n + sizeof(T));
        occupied += n;
        return end_memory_ptr;
    }

    bool free_block(void *p, const size_t &n)
    {
        void *right_border = ((char *)memory_ptr) + size * sizeof(T);
        if ((p >= memory_ptr) && (p < right_border))
            return false;

        released += n;
        if (released == occupied)
        {
            std::free(memory_ptr);
            memory_ptr = nullptr;
        }
        return true;
    }

    bool fit(const size_t &n)
    {
        return ((size - occupied) >= n);
    }
};

/**
 * @brief  The custom allocator.
 *
 * @tparam  _Tp  Type of allocated object e.g.: std::pair<const int, int>
 * @tparam  _N  size
 *
 * @headerfile memory
 */
template <typename T, size_t N = 5>
struct CustomAllocator
{
    using value_type = T;
    using size_type = size_t;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using ptrChunk = MemoryChunk<T> *;

    template <typename U>
    struct rebind
    {
        using other = CustomAllocator<U>;
    };

    CustomAllocator()
    {
        std::cout << "Allocator default constructor. Allocate at least: " << N << " Item size: " << sizeof(T) << std::endl;
        items_per_block = N;
    }
    ~CustomAllocator()
    {
        std::cout << "Allocator destructor" << std::endl;
    }

    pointer allocate(size_type n)
    {
#ifdef USE_PRETTY
        std::cout << std::endl
                  << __PRETTY_FUNCTION__ << " " << n << " +++" << std::endl;
#endif
        size_t block_number = (n < items_per_block) ? items_per_block : n;
        if (!first_memory_chunk)
        {
            first_memory_chunk = allocate_new_block(block_number);
            if (!first_memory_chunk)
            {
                throw std::bad_alloc();
            }

            last_memory_chunk = first_memory_chunk;
            return reinterpret_cast<pointer>(last_memory_chunk->rezerve_block(n));
        }
        if (last_memory_chunk->fit(n))
        {
            return reinterpret_cast<pointer>(last_memory_chunk->rezerve_block(n));
        }

        last_memory_chunk->next_chank = allocate_new_block(block_number);
        if (!last_memory_chunk->next_chank)
        {
            throw std::bad_alloc();
        }
        last_memory_chunk = last_memory_chunk->next_chank;
        return reinterpret_cast<pointer>(last_memory_chunk);
    }

    void deallocate(pointer ptr, size_type n)
    {
#ifdef USE_PRETTY
        std::cout << __PRETTY_FUNCTION__ << n << " " << ptr << " ---" << std::endl
                  << std::endl;
#endif
        if (first_memory_chunk == nullptr)
        {
            std::cout << "deallocte error!" << std::endl;
            return;
        }

        ptrChunk tempChunk = nullptr;
        while (first_memory_chunk != nullptr)
        {
            tempChunk = first_memory_chunk->next_chank;
            if (first_memory_chunk->free_block(ptr, n))
                break;
            first_memory_chunk = tempChunk;
        }
        delete tempChunk;
    }

    template <typename U, typename... Args>
    void construct(U *p, Args &&...args)
    {
#ifdef USE_PRETTY
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new (p) U(std::forward<Args>(args)...);
        std::cout << p << std::endl;
    }

    template <typename U>
    void destroy(U *p)
    {
#ifdef USE_PRETTY
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~U();
    }

private:
    std::size_t items_per_block;

    ptrChunk first_memory_chunk = nullptr;
    ptrChunk last_memory_chunk = nullptr;

    ptrChunk allocate_new_block(const size_t &items_number)
    {
        ptrChunk current_chunk = reinterpret_cast<ptrChunk>(new MemoryChunk<T>);
        current_chunk->allocate_block(items_number);
        if (!current_chunk)
        {
            delete current_chunk;
            return nullptr;
        }
        return current_chunk;
    }
};