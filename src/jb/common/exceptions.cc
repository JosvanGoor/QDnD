#include "exceptions.h"

namespace jb
{

    /////
    //  Exception
    /////

    Exception::Exception(const char* type)
    :   _type(type)
    { }

    
    const std::string& Exception::message() const noexcept
    {
        return _message;
    }

    
    const char* Exception::type() const noexcept
    {
        return _type;
    }


    const char* Exception::what() const noexcept
    {
        return _message.c_str();
    }

    /////
    //  Trivial Specialisations
    /////

    IllegalArgumentException::IllegalArgumentException()
    :   Exception("IllegalArgumentException")
    { }


    IOException::IOException()
    :   Exception("IOException")
    { }


    LogicException::LogicException()
    :   Exception("LogicException")
    { }


    NetException::NetException()
    :   Exception("NetException")
    { }


    ParserException::ParserException()
    :   Exception("ParserException")
    { }


    RuntimeException::RuntimeException()
    :   Exception("RuntimeException")
    { }


    UnimplementedException::UnimplementedException()
    :   Exception("UnimplementedException")
    { }

    /////
    //  IndexOutOfBoundsException
    /////

    IndexOutOfBoundsException::IndexOutOfBoundsException()
    :   Exception("IndexOutOfBoundsException")
    { }


    IndexOutOfBoundsException::IndexOutOfBoundsException(size_t idx, size_t cap)
    :   IndexOutOfBoundsException()
    {
        _message = fmt::format("Requested index {} is outside of range [0, {}).", idx, cap);
    }


    IndexOutOfBoundsException::IndexOutOfBoundsException(long idx, long min, long max)
    :   IndexOutOfBoundsException()
    {
        _message = fmt::format("Requested index {} is outside of range [{}, {}).", idx, min, max);
    }

}