/*
  Copyright (c) 2012 Matthew Stump

  This file is part of libcql.

  libcql is free software; you can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  libcql is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CQL_MESSAGE_RESULT_IMPL_H_
#define CQL_MESSAGE_RESULT_IMPL_H_

#include <boost/asio/buffer.hpp>

#include "libcql/cql.hpp"
#include "libcql/cql_result.hpp"
#include "libcql/internal/cql_message.hpp"
#include "libcql/internal/cql_result_metadata.hpp"

namespace cql {

    class cql_message_result_impl_t :
        boost::noncopyable,
        public cql_message_t,
        public cql_result_t
    {

    public:
        cql_message_result_impl_t(size_t size);

        cql_message_result_impl_t();

        cql_int_t
        result_type() const;

        cql::cql_opcode_enum
        opcode() const;

        cql_int_t
        size() const;

        std::string
        str() const;

        size_t
        column_count() const;

        size_t
        row_count() const;

        const std::vector<cql::cql_byte_t>&
        query_id() const;

        bool
        next();

        bool
        consume(cql::cql_error_t* err);

        bool
        prepare(cql::cql_error_t* err);

        cql_message_buffer_t
        buffer();

        bool
        exists(const std::string& column) const;

        bool
        column_class(int i,
                     std::string& output) const;

        bool
        column_class(const std::string& column,
                     std::string& output) const;

        bool
        column_type(int i,
                    cql_column_type_enum& output) const;

        bool
        column_type(const std::string& column,
                    cql_column_type_enum& output) const;

        bool
        get_index(const std::string& column,
                  int& output) const;

        bool
        is_null(int i,
                bool& output) const;

        bool
        is_null(const std::string& column,
                bool& output) const;

        bool
        get_bool(int i,
                 bool& output) const;

        bool
        get_bool(const std::string& column,
                 bool& output) const;

        bool
        get_int(int i,
                cql_int_t& output) const;

        bool
        get_int(const std::string& column,
                cql_int_t& output) const;

        bool
        get_float(int i,
                  float& output) const;

        bool
        get_float(const std::string& column,
                  float& output) const;

        bool
        get_double(int i,
                   double& output) const;

        bool
        get_double(const std::string& column,
                   double& output) const;

        bool
        get_bigint(int i,
                   cql::cql_bigint_t& output) const;

        bool
        get_bigint(const std::string& column,
                   cql::cql_bigint_t& output) const;

        bool
        get_string(int i,
                   std::string& output) const;

        bool
        get_string(const std::string& column,
                   std::string& output) const;

        bool
        get_data(int i,
                 cql::cql_byte_t** output,
                 size_t& size) const;

        bool
        get_data(const std::string& column,
                 cql::cql_byte_t** output,
                 size_t& size) const;

        // bool
        // get_list(int i,
        //          cql::cql_list_impl_t& output) const;

        // bool
        // get_list(const std::string& column,
        //          cql::cql_list_impl_t& output) const;

        // bool
        // get_set(int i,
        //         cql::cql_set_impl_t& output) const;

        // bool
        // get_set(const std::string& column,
        //         cql::cql_set_impl_t& output) const;

        // bool
        // get_map(int i,
        //         cql::cql_map_impl_t& output) const;

        // bool
        // get_map(const std::string& column,
        //         cql::cql_map_impl_t& output) const;


    private:
        cql::cql_message_buffer_t     _buffer;
        cql::cql_byte_t*              _pos;
        std::vector<cql::cql_byte_t*> _row;
        size_t                        _row_pos;
        cql_int_t                     _row_count;
        cql_int_t                     _column_count;
        std::vector<cql::cql_byte_t>  _query_id;
        cql_int_t                     _result_type;
        std::string                   _keyspace_name;
        std::string                   _table_name;
        cql::cql_result_metadata_t    _metadata;
    };

} // namespace cql

#endif // CQL_MESSAGE_RESULT_IMPL_H_
