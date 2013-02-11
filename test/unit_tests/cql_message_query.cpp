#include "gtest/gtest.h"
#include "libcql/cql.hpp"
#include "libcql/cql_error.hpp"
#include "libcql/internal/cql_defines.hpp"
#include "libcql/internal/cql_message_query_impl.hpp"

char TEST_MESSAGE_QUERY[] = {
    0x00, 0x00, 0x00, 0x0b, 0x75, 0x73, 0x65, 0x20,
    0x73, 0x79, 0x73, 0x74, 0x65, 0x6d, 0x3b, 0x00,
    0x05 };

TEST(cql_message_query_cpp, opcode)
{
	cql::cql_message_query_impl_t m;
	EXPECT_EQ(cql::CQL_OPCODE_QUERY, m.opcode());
}

TEST(cql_message_query_cpp, serialization_to_byte)
{
	cql::cql_message_query_impl_t m("use system;", cql::CQL_CONSISTENCY_ALL);
    cql::cql_error_t err;
    m.prepare(&err);
    EXPECT_EQ(sizeof(TEST_MESSAGE_QUERY), m.size());
    EXPECT_TRUE(memcmp(TEST_MESSAGE_QUERY, &(*m.buffer())[0], sizeof(TEST_MESSAGE_QUERY)) == 0);
}

TEST(cql_message_query_cpp, serialization_from_byte)
{
	cql::cql_message_query_impl_t m;
    m.buffer()->assign(TEST_MESSAGE_QUERY, TEST_MESSAGE_QUERY + sizeof(TEST_MESSAGE_QUERY));
    cql::cql_error_t err;
    m.consume(&err);

	EXPECT_EQ("use system;", m.query());
	EXPECT_EQ(cql::CQL_CONSISTENCY_ALL, m.consistency());
}
