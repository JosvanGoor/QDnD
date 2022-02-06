#ifndef JB_COMMON_BYTEBUFFER_H
#define JB_COMMON_BYTEBUFFER_H

#include <cstdint>
#include <span>
#include <string_view>

namespace jb
{

    using Byte = std::uint8_t;

    class ByteBuffer
    {
        Byte *_buffer;
        std::size_t _size;
        std::size_t _start;
        std::size_t _capacity;

        public:
            // constructors
            ByteBuffer() noexcept;
            ByteBuffer(ByteBuffer&& other) noexcept;
            ByteBuffer(const ByteBuffer& other);
            explicit ByteBuffer(std::string_view data);
            explicit ByteBuffer(std::span<const Byte> data);
            ~ByteBuffer();

            // assign operators
            ByteBuffer& operator=(ByteBuffer&& move) noexcept;
            ByteBuffer& operator=(const ByteBuffer& copy);
            void swap(ByteBuffer& other) noexcept;

            // direct access
            Byte& front() noexcept;
            Byte front() const noexcept;
            Byte& back() noexcept;
            Byte back() const noexcept;
            Byte* data() noexcept;
            const Byte* data() const noexcept;

            Byte& at(size_t index);
            Byte at(size_t index) const;
            Byte& operator[](size_t index) noexcept;
            Byte operator[](size_t index) const noexcept;
            
            // capacity
            void clear() noexcept;
            bool is_empty() const noexcept;
            void resize(size_t capacity);
            void reserve(size_t capacity);
            size_t size() const noexcept;
            size_t capacity() const noexcept;

            // comparison
            bool operator==(const ByteBuffer& other) const noexcept;
            bool operator!=(const ByteBuffer& other) const noexcept;

            // search
            Byte* find(Byte byte, Byte* from = nullptr) noexcept;
            Byte* find(std::string_view str, Byte *from = nullptr) noexcept;
            Byte* find(std::span<const Byte> span, Byte *from = nullptr) noexcept;
            const Byte* find(Byte byte, const Byte* from = nullptr) const noexcept;
            const Byte* find(std::string_view str, const Byte* from = nullptr) const noexcept;
            const Byte* find(std::span<const Byte> span, const Byte* from = nullptr) const noexcept;

            // iterators
            Byte* begin() noexcept;
            Byte* end() noexcept;
            const Byte* begin() const noexcept;
            const Byte* end() const noexcept;
            std::reverse_iterator<Byte*> rbegin() noexcept;
            std::reverse_iterator<Byte*> rend() noexcept;
            std::reverse_iterator<const Byte*> rbegin() const noexcept;
            std::reverse_iterator<const Byte*> rend() const noexcept;

            // views
            std::span<Byte> span() noexcept;
            std::span<const Byte> span() const noexcept;
            std::string_view string_view() const noexcept;

            // insertion
            void insert(Byte *it, Byte byte);
            void insert(Byte *it, Byte byte, size_t count);
            void insert(Byte *it, std::string_view data);
            void insert(Byte *it, const ByteBuffer& buffer);
            void insert(Byte *it, std::span<const Byte> data);
            void insert(Byte *it, std::initializer_list<Byte> data);
            void insert(Byte *it, const Byte* bytes, size_t num_bytes);
            void insert(Byte *it, const Byte* begin, const Byte* end);
            void push_back(Byte byte);

            // manipulation
            void pop() noexcept;
            void pop(size_t num) noexcept;
            void pop_back() noexcept;
            void pop_back(size_t num) noexcept;
            void erase(Byte* it);
            void erase(Byte* from, Byte* to);
            Byte* insert_empty_space(Byte* it, size_t size);

            // file io
            static ByteBuffer from_file(const std::string& filename);
            void write_to_file(const std::string& filename, bool append = false) const;

        private:
            size_t unused_capacity() const noexcept;
            size_t unused_tail_capacity() const noexcept;
            void validate_iterator(const Byte* it) const;

            void enlarge(size_t capacity);
            size_t calculate_new_capacity(size_t requested) const noexcept;
            void rebase_toward_front() noexcept;

        public:
            using value_type = jb::Byte;
            using size_type = std::size_t;
    };

}

#endif