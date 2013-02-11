#include <sstream>
#include <boost/foreach.hpp>

#include "libcql/cql_vector_stream.hpp"
#include "libcql/cql_serialization.hpp"
#include "libcql/internal/cql_defines.hpp"

#include "libcql/internal/cql_message_error_impl.hpp"

cql::cql_message_error_impl_t::cql_message_error_impl_t() :
    _buffer(new std::vector<cql::cql_byte_t>()),
    _code(0),
    _message()
{}

cql::cql_message_error_impl_t::cql_message_error_impl_t(size_t size) :
    _buffer(new std::vector<cql::cql_byte_t>(size)),
    _code(0),
    _message()
{}

cql::cql_message_error_impl_t::cql_message_error_impl_t(cql::cql_int_t code,
                                                        const std::string& message) :
    _buffer(new std::vector<cql::cql_byte_t>(0)),
    _code(code),
    _message(message)
{}

const std::string&
cql::cql_message_error_impl_t::message() const
{
    return _message;
}

void
cql::cql_message_error_impl_t::message(const std::string& m)
{
    _message = m;
}

cql::cql_int_t
cql::cql_message_error_impl_t::code() const
{
    return _code;
}

void
cql::cql_message_error_impl_t::code(cql::cql_int_t c)
{
    _code = c;
}

cql::cql_opcode_enum
cql::cql_message_error_impl_t::opcode() const
{
    return CQL_OPCODE_ERROR;
}

cql::cql_int_t
cql::cql_message_error_impl_t::size() const
{
    return _buffer->size();
}

std::string
cql::cql_message_error_impl_t::str() const
{
    return _message;
}

bool
cql::cql_message_error_impl_t::consume(cql::cql_error_t* err)
{
    cql::vector_stream_t buffer(*_buffer);
    std::istream input(&buffer);

    cql::decode_int(input, _code);
    cql::decode_string(input, _message);
    return true;
}

bool
cql::cql_message_error_impl_t::prepare(cql::cql_error_t* err)
{
    _buffer->resize(sizeof(_code) + sizeof(cql::cql_short_t) + _message.size());

    cql::vector_stream_t buffer(*_buffer);
    std::ostream output(&buffer);

    cql::encode_int(output, _code);
    cql::encode_string(output, _message);
    return true;
}

cql::cql_message_buffer_t
cql::cql_message_error_impl_t::buffer()
{
    return _buffer;
}
