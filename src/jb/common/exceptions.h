#ifndef JB_COMMON_EXCEPTIONS_H
#define JB_COMMON_EXCEPTIONS_H

#include <exception>
#include <fmt/format.h>
#include <sstream>
#include <string>
#include <type_traits>

namespace jb
{

    class Exception : public std::exception
    {
        public:
            const char* type() const noexcept;
            const std::string& message() const noexcept;
            const char* what() const noexcept override;

        protected:
            Exception(const char* type);

            template <typename... Args>
            Exception(const char* type, fmt::format_string<Args...> str, Args&&... args);
            
            const char* _type;
            std::string _message;
    };


    template <typename... Args>
    Exception::Exception(const char* type, fmt::format_string<Args...> str, Args&&... args)
    :   Exception(type)
    {
        _message = fmt::format(str, std::forward<Args>(args)...);
    }

    
    // //
    // //  Trivial Exception Specialisations
    // //

    struct IllegalArgumentException : public Exception
    {
        IllegalArgumentException();

        template <typename... Args>
        IllegalArgumentException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("IllegalArgumentException", str, std::forward<Args>(args)...)
        { }
    };


    struct IOException : public Exception
    {
        IOException();

        template <typename... Args>
        IOException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("IOException", str, std::forward<Args>(args)...)
        { }
    };


    struct LogicException : public Exception
    {
        LogicException();

        template <typename... Args>
        LogicException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("LogicException", str, std::forward<Args>(args)...)
        { }
    };
    
    
    struct NetException : public Exception
    {
        NetException();

        template <typename... Args>
        NetException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("NetException", str, std::forward<Args>(args)...)
        { }
    };


    struct ParserException : public Exception
    {
        ParserException();

        template <typename... Args>
        ParserException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("ParserException", str, std::forward<Args>(args)...)
        { }
    };


    struct RuntimeException : public Exception
    {
        RuntimeException();

        template <typename... Args>
        RuntimeException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("RuntimeException", str, std::forward<Args>(args)...)
        { }
    };

    
    struct UnimplementedException : public Exception
    {
        UnimplementedException();

        template <typename... Args>
        UnimplementedException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("UnimplementedException", str, std::forward<Args>(args)...)
        { }
    };


    //
    //  Exception Specializations
    //

    struct IndexOutOfBoundsException : public Exception
    { 
        IndexOutOfBoundsException();
        IndexOutOfBoundsException(size_t idx, size_t cap);
        IndexOutOfBoundsException(long idx, long min, long max);

        template <typename... Args>
        IndexOutOfBoundsException(fmt::format_string<Args...> str, Args&&... args)
        :   Exception("IndexOutOfBoundsException", str, std::forward<Args>(args)...)
        { }
    };
}

#endif