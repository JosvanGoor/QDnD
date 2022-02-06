#include "bytebuffer.h"

#include <algorithm>
#include <fstream>

#include "exceptions.h"

namespace jb
{

    /////
    //  Constructors
    /////

    ByteBuffer::ByteBuffer() noexcept
    :   _buffer(nullptr),
        _size(0),
        _start(0),
        _capacity(0)
    { }


    ByteBuffer::ByteBuffer(ByteBuffer&& other) noexcept
    :   _buffer(other._buffer),
        _size(other._size),
        _start(other._start),
        _capacity(other._capacity)
    {
        other._buffer = nullptr;
        other._size = 0;
        other._start = 0;
        other._capacity = 0;
    }


    ByteBuffer::ByteBuffer(const ByteBuffer& other)
    :   ByteBuffer(static_cast<std::span<const Byte>>(other))
    { }


    ByteBuffer::ByteBuffer(std::string_view data)
    :   ByteBuffer(std::span<const Byte>(reinterpret_cast<const Byte*>(data.begin()), data.size()))
    { }


    ByteBuffer::ByteBuffer(std::span<const Byte> data)
    :   _buffer(new Byte[data.size()]),
        _size(data.size()),
        _start(0),
        _capacity(data.size())
    { 
        std::copy(data.begin(), data.end(), _buffer);
    }


    ByteBuffer::~ByteBuffer()
    {
        delete[] _buffer;
    }


    /////
    //  Assign Operators
    /////

    ByteBuffer& ByteBuffer::operator=(ByteBuffer&& other) noexcept
    {
        swap(other);
        return *this;
    }


    ByteBuffer& ByteBuffer::operator=(const ByteBuffer& other)
    {
        ByteBuffer copy{other};
        swap(copy);
        return *this;
    }


    void ByteBuffer::swap(ByteBuffer& other) noexcept
    {
        std::swap(_buffer, other._buffer);
        std::swap(_size, other._size);
        std::swap(_start, other._start);
        std::swap(_capacity, other._capacity);
    }


    /////
    //  Direct Access
    /////

    Byte& ByteBuffer::front() noexcept
    {
        return *begin();
    }


    Byte ByteBuffer::front() const noexcept
    {
        return *begin();
    }


    Byte& ByteBuffer::back() noexcept
    {
        return *(end() - 1);
    }


    Byte ByteBuffer::back() const noexcept
    {
        return *(end() - 1);
    }


    Byte* ByteBuffer::data() noexcept
    {
        return begin();
    }


    const Byte* ByteBuffer::data() const noexcept
    {
        return begin();
    }


    Byte& ByteBuffer::at(size_t index)
    {
        if (index > _size)
            throw IndexOutOfBoundsException{index, _size};
        return begin()[index];
    }


    Byte ByteBuffer::at(size_t index) const
    {
        if (index > _size)
            throw IndexOutOfBoundsException{index, _size};
        return begin()[index];
    }


    Byte& ByteBuffer::operator[](size_t index) noexcept
    {
        return begin()[index];
    }


    Byte ByteBuffer::operator[](size_t index) const noexcept
    {
        return begin()[index];
    }


    /////
    //  Capacity
    /////

    void ByteBuffer::clear() noexcept
    {
        _size = 0;
        _start = 0;
    }


    bool ByteBuffer::is_empty() const noexcept
    {
        return _size == 0;
    }


    void ByteBuffer::resize(size_t capacity)
    {
        if (_capacity >= capacity)
            return;

        reserve(capacity);
        _size = capacity;
    }


    void ByteBuffer::reserve(size_t capacity)
    {
        if (_size + unused_tail_capacity() >= capacity)
            return;
        else if (_size + unused_capacity() >= capacity)
            rebase_toward_front();
        else
            enlarge(capacity);
    }


    size_t ByteBuffer::size() const noexcept
    {
        return _size;
    }


    size_t ByteBuffer::capacity() const noexcept
    {
        return _capacity;
    }


    /////
    //  Comparison
    /////

    bool ByteBuffer::operator==(const ByteBuffer& other) const noexcept
    {
        if (_size != other.size())
            return false;

        return std::equal(begin(), end(), other.begin());
    }


    bool ByteBuffer::operator!=(const ByteBuffer& other) const noexcept
    {
        return !(*this == other);
    }


    /////
    //  Search
    /////

    Byte* ByteBuffer::find(Byte byte, Byte* from) noexcept
    {
        from = from ? from : begin();
        validate_iterator(from);
        return std::find(from, end(), byte);
    }


    Byte* ByteBuffer::find(std::string_view str, Byte *from) noexcept
    {
        return find(std::span<const Byte>(reinterpret_cast<const Byte*>(str.data()), str.size()), from);
    }

    
    Byte* ByteBuffer::find(std::span<const Byte> span, Byte *from) noexcept
    {
        from = from ? from : begin();
        validate_iterator(from);
        return std::search(from, end(), span.begin(), span.end());
    }


    const Byte* ByteBuffer::find(Byte byte, const Byte* from) const noexcept
    {
        from = from ? from : begin();
        validate_iterator(from);
        return std::find(from, end(), byte);
    }
    

    const Byte* ByteBuffer::find(std::string_view str, const Byte* from) const noexcept
    {
        return find(std::span<const Byte>(reinterpret_cast<const Byte*>(str.data()), str.size()), from);
    }


    const Byte* ByteBuffer::find(std::span<const Byte> span, const Byte* from) const noexcept
    {
        from = from ? from : begin();
        validate_iterator(from);
        return std::search(from, end(), span.begin(), span.end());
    }


    /////
    //  Iterators
    /////

    Byte* ByteBuffer::begin() noexcept
    {
        return (_buffer + _start);
    }


    Byte* ByteBuffer::end() noexcept
    {
        return (begin() + _size);
    }


    const Byte* ByteBuffer::begin() const noexcept
    {
        return (_buffer + _start);
    }


    const Byte* ByteBuffer::end() const noexcept
    {
        return (begin() + _size);
    }


    std::reverse_iterator<Byte*> ByteBuffer::rbegin() noexcept
    {
        return std::reverse_iterator<Byte*>(end());
    }


    std::reverse_iterator<Byte*> ByteBuffer::rend() noexcept
    {
        return std::reverse_iterator<Byte*>(begin());
    }


    std::reverse_iterator<const Byte*> ByteBuffer::rbegin() const noexcept
    {
        return std::reverse_iterator<const Byte*>(end());
    }


    std::reverse_iterator<const Byte*> ByteBuffer::rend() const noexcept
    {
        return std::reverse_iterator<const Byte*>(begin());
    }


    /////
    //  Views
    /////

    std::span<Byte> ByteBuffer::span() noexcept
    {
        return std::span<Byte>(begin(), _size);
    }


    std::span<const Byte> ByteBuffer::span() const noexcept
    {
        return std::span<const Byte>(begin(), _size);
    }


    std::string_view ByteBuffer::string_view() const noexcept
    {
        return std::string_view{reinterpret_cast<const char*>(begin()), _size};
    }

    
    /////
    //  Insertion
    /////

    void ByteBuffer::insert(Byte *it, Byte byte)
    {
        Byte *out = insert_empty_space(it, 1);
        *out = byte;
    }

    
    void ByteBuffer::insert(Byte *it, Byte byte, size_t count)
    {
        Byte *out = insert_empty_space(it, count);
        for (size_t idx = 0; idx < count; ++idx)
            out[idx] = byte;
    }

    
    void ByteBuffer::insert(Byte *it, std::string_view data)
    {
        insert(it, reinterpret_cast<const Byte*>(data.begin()), reinterpret_cast<const Byte*>(data.end()));
    }


    void ByteBuffer::insert(Byte *it, ByteBuffer const &buffer)
    {
        insert(it, buffer.begin(), buffer.end());
    }


    void ByteBuffer::insert(Byte *it, std::span<const Byte> data)
    {
        insert(it, data.data(), data.data() + data.size());
    }


    void ByteBuffer::insert(Byte *it, std::initializer_list<Byte> data)
    {
        insert(it, data.begin(), data.end());
    }


    void ByteBuffer::insert(Byte *it, const Byte* data, size_t num_bytes)
    {
        insert(it, data, data + num_bytes);
    }


    void ByteBuffer::insert(Byte *it, Byte const *begin, Byte const *end)
    {
        Byte *out = insert_empty_space(it, std::distance(begin, end));
        std::copy(begin, end, out);
    }


    void ByteBuffer::push_back(Byte byte)
    {
        if (unused_tail_capacity() == 0)
            enlarge(0);
        *end() = byte;
        ++_size;
    }

    
    /////
    //  Manipulation
    /////

    void ByteBuffer::pop() noexcept
    {
        if (_size == 0)
            return;
        ++_start;
        --_size;
    }


    void ByteBuffer::pop(size_t num) noexcept
    {
        if (num >= _size)
            clear();
        else
        {
            _start += num;
            _size -= num;
        }
    }


    void ByteBuffer::pop_back() noexcept
    {
        if (_size == 0)
            return;
        --_size;
    }


    void ByteBuffer::pop_back(size_t num) noexcept
    {
        if (_size <= num)
            clear();
        _size -= num;
    }


    void ByteBuffer::erase(Byte *it)
    {
        validate_iterator(it);
        if (it == end())
            throw IllegalArgumentException{"Can't erase end iterator."};

        if (it == begin())
            ++_start;
        else if (it != (end() -1))
            std::copy(it + 1, end(), it);
        --_size;
    }


    void ByteBuffer::erase(Byte* first, Byte* last)
    {
        validate_iterator(first);
        validate_iterator(last);

        if (first >= last)
            throw IllegalArgumentException("Iterator to first should be before iterator to last.");

        if (first == begin())
            _start += std::distance(first, last);
        else if (last != end())
            std::copy(last, end(), first);
        _size -= std::distance(first, last);
    }


    Byte* ByteBuffer::insert_empty_space(Byte *it, size_t space)
    {
        validate_iterator(it);

        // We need to reallocate
        if (_capacity < (_size + space))
        {
            size_t new_capacity = calculate_new_capacity(_size + space);
            Byte* new_buffer = new Byte[new_capacity];

            Byte *space_start = new_buffer + (it - begin());
            std::copy(begin(), it, new_buffer);
            std::copy(it, end(), space_start + space);

            delete[] _buffer;
            _start = 0;
            _capacity = new_capacity;
            _size = new_capacity;
            _buffer = new_buffer;

            return space_start;
        }
        
        // we can fit it in the tail
        if (unused_tail_capacity() >= space)
        {
            Byte *old_end = end();
            _size += space;
            std::copy_backward(it, old_end, end());
            return it;
        }

        // we can fit it in the head
        if (_start >= space)
        {
            std::copy(begin(), it, begin() - space);
            _start -= space;
            _size += space;
            return (it - space);
        }

        // we need to move both the head and the tail
        size_t head_size = _start;
        size_t front_block_size = it - begin();

        std::copy(begin(), it, _buffer);
        std::copy_backward(it, end(), end() + (space - head_size));

        _size += space;
        _start = 0;

        return _buffer + front_block_size;
    }

    /////
    //  File IO
    /////

    ByteBuffer ByteBuffer::from_file(const std::string& filename)
    {
        std::ifstream in{filename, std::ios::binary};
        if (!in.good())
            throw IOException{"Failed to open input file '{}'.", filename};

        ByteBuffer rval;

        in.seekg(0, std::ios::end);
        rval.resize(in.tellg());
        in.seekg(0, std::ios::beg);

        in.read(reinterpret_cast<char*>(rval.data()), rval.size());
        return rval;
    }


    void ByteBuffer::write_to_file(const std::string& filename, bool append) const
    {
        std::ofstream out{filename, append ? (std::ios::binary | std::ios::app) : (std::ios::binary)};
        if (!out.good())
            throw IOException{"Failed to open output file '{}'.", filename};

        out.write(reinterpret_cast<const char*>(begin()), _size);
    }


    /////
    //  Private
    /////

    size_t ByteBuffer::unused_capacity() const noexcept
    {
        return _capacity - _size;
    }


    size_t ByteBuffer::unused_tail_capacity() const noexcept
    {
        return _capacity - (_start + _size);
    }


    void ByteBuffer::validate_iterator(const Byte* it) const
    {
        if (!(it >= begin() && it <= end()))
            throw IllegalArgumentException("Invalid iterator: not in range [begin(), end()].");
    }


    void ByteBuffer::enlarge(size_t capacity)
    {
        size_t new_capacity = calculate_new_capacity(capacity);

        Byte* new_buffer = new Byte[new_capacity];
        std::copy(begin(), end(), new_buffer);

        for (size_t idx = _size; idx != new_capacity; ++idx)
            new_buffer[idx] = 0;

        delete[] _buffer;
        _start = 0;
        _capacity = new_capacity;
        _buffer = new_buffer;
    }


    size_t ByteBuffer::calculate_new_capacity(size_t requested) const noexcept
    {
        size_t new_capacity = _capacity == 0 ? 8 : _capacity * 2;
        return std::max(requested, new_capacity);
    }


    void ByteBuffer::rebase_toward_front() noexcept
    {
        if (_start == 0)
            return;
        
        std::copy(begin(), end(), _buffer);
        _start = 0;
    }

}