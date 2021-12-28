/*-*-c++-*-*/
/*
 * Copyright 2021 John Sallay
 *
 * SPDX-License-Identifier: LGPL-3.0
 *
 */
#include <gtest/gtest.h>
#include <complex>

#include <pmtf/base.hpp>
#include <pmtf/vector.hpp>
#include <pmtf/scalar.hpp>
#include <pmtf/map.hpp>
#include <pmtf/wrap.hpp>

using namespace pmtf;

TEST(PmtMap, EmptyMap) {
    map empty;
    empty["abc"] = scalar(4);
}

TEST(PmtMap, PmtMapTests)
{
    std::complex<float> val1(1.2, -3.4);
    std::vector<int32_t> val2{ 44, 34563, -255729, 4402 };

    // Create the PMT map
    std::map<std::string, pmt> input_map({
        { "key1", val1 },
        { "key2", val2 },
    });
    map map_pmt(input_map);

    // Lookup values in the PMT map and compare with what was put in there
    auto vv1 = map_pmt["key1"];
    std::cout << vv1 << std::endl;
    EXPECT_EQ(get_scalar<std::complex<float>>(vv1), val1);

    auto vv2 = map_pmt["key2"];
    EXPECT_EQ(vv2 == val2, true);
    std::cout << map_pmt << std::endl;
}

TEST(PmtMap, MapSerialize)
{
    std::complex<float> val1(1.2, -3.4);
    std::vector<int32_t> val2{ 44, 34563, -255729, 4402 };

    // Create the PMT map
    std::map<std::string, pmt> input_map({
        { "key1", val1 },
        { "key2", val2 },
    });
    map map_pmt(input_map);
    std::stringbuf sb;
    map_pmt.get_pmt_buffer().serialize(sb);
    auto y = pmt::deserialize(sb);
    std::cout << map_pmt << std::endl;
    std::cout << map_pmt.size() << " " << map_pmt.size2() << std::endl;
    std::cout << y << std::endl;
    std::cout << "Before Test\n";
    EXPECT_EQ(map_pmt, y);

}


