#include <iostream>
#include <map>
#include <vector>

#define DBG 1

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
                    end_memory_ptr{nullptr}, size{0}, occupied{0}, released{0}
    {
        std::cout << "MemoryChunk default constructor: " << this << std::endl;
        std::cout << std::endl;
    };

    void *allocate_block(const size_t &items_number)
    {
#ifdef DBG
        // std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        memory_ptr = std::malloc(items_number * sizeof(T));
        if (!memory_ptr)
            return nullptr;

        end_memory_ptr = memory_ptr;
        size = items_number;
        #ifdef DBG
        std::cout  << "<=========allocate_block========>" << std::endl;
        std::cout  << "Block start address:\t " << memory_ptr << std::endl;
        // std::cout << "Allocating " << items_number * sizeof(T) << " bytes\n";
        // std::cout << "MemoryChunk end: " << memory_ptr + items_number * sizeof(T)<< std::endl;
        std::cout  << std::endl;
        #endif
        return memory_ptr;
    }

    void *rezerve_block(const size_t &n)
    {
        void *current_ptr = end_memory_ptr;
        end_memory_ptr = (char*)end_memory_ptr + n * sizeof(T);
        occupied += n;
       
        #ifdef DBG
        std::cout  << "<=========rezerve_block========>" << std::endl;
        std::cout  << "Block start address:\t " << memory_ptr << std::endl;
        std::cout  << "Block end address:\t " << end_memory_ptr << std::endl;
        // auto diff =  end_memory_ptr - memory_ptr;
        // std::cout  << "Block length: " << diff << std::endl;
        #endif
        return current_ptr;
    }

    bool free_block(void *p, const size_t &n)
    {   
        void *right_border = (void *)((char*) memory_ptr + size * sizeof(T));
        if (!((p >= memory_ptr) && (p < right_border)))
            return false;

        released += n;
        if (released == occupied)
        {
            std::free(memory_ptr);
            memory_ptr = end_memory_ptr = nullptr;
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
        std::cout << "Allocator default constructor: " << this << std::endl;
        items_per_block = N;
    }
    ~CustomAllocator()
    {
        std::cout << "Allocator destructor" << std::endl;

        // while (first_memory_chunk != nullptr){
        //     std::cout << "Delete chunk with address: " << last_memory_chunk->memory_ptr << std::endl;
        //     ptrChunk temp_chunk = last_memory_chunk->next_chank;
        //     last_memory_chunk -> free_block();
        //     delete last_memory_chunk;
        //     last_memory_chunk = temp_chunk;
        // }
    }

    pointer allocate(size_type n)
    {
#ifdef DBG
        std::cout << std::endl
                  << __PRETTY_FUNCTION__ << " " << n << " +++" << std::endl;
        std::cout << "Allocating for " << typeid(T).name();
		std::cout << " " << n * sizeof(T) << " bytes\n";
        
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
            // return reinterpret_cast<pointer>(last_memory_chunk);
        }
        if (last_memory_chunk->fit(n))
        {
            return reinterpret_cast<pointer>(last_memory_chunk->rezerve_block(n));
            // return reinterpret_cast<pointer>(last_memory_chunk);
        }

        first_memory_chunk->next_chank = allocate_new_block(block_number);
        if (!last_memory_chunk->next_chank)
        {
            throw std::bad_alloc();
        }
        last_memory_chunk = first_memory_chunk->next_chank;
        return reinterpret_cast<pointer>(last_memory_chunk->rezerve_block(n));
        // return reinterpret_cast<pointer>(last_memory_chunk);
    }

    void deallocate(pointer ptr, size_type n)
    {
#ifdef DBG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "Deallocate space. Required:\t " << n << " Address: " << ptr << std::endl;
#endif
        if (first_memory_chunk == nullptr)
        {
            std::cout << "deallocte error!" << std::endl;
            return;
        }

        ptrChunk curr_chunk = first_memory_chunk;
        // ptrChunk next_chunk = nullptr;
        ptrChunk prev_chunk = nullptr;
        while (curr_chunk != nullptr)
        {
            // next_chunk = curr_chunk->next_chank;
            if (curr_chunk->free_block(ptr, n))
                break;

            prev_chunk = curr_chunk;
            curr_chunk = curr_chunk->next_chank;
        }
        // first_memory_chunk = currChunk;

        

        if (curr_chunk->memory_ptr == nullptr){
            prev_chunk->next_chank = nullptr;
            last_memory_chunk = prev_chunk;
        }

        delete curr_chunk;
        // delete next_chunk;
        delete prev_chunk;
    }

    template <typename U, typename... Args>
    void construct(U *p, Args &&...args)
    {
#ifdef DBG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "Construct address:\t " << p << " size " << sizeof(U) << std::endl;
#endif
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U *p)
    {
#ifdef DBG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << "Destroy Required address: " << p << std::endl;
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