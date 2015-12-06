/**
 * @file test_state.cpp
 * @author Miroslav Cibulka
 * @created 12/5/15
 * @copyright Copyright (c) 2015 XXX
 * @brief test_state class
 * @detail
 *
 */

#include <boost/test/unit_test.hpp>

#include "support.hh"


BOOST_AUTO_TEST_SUITE(state_tests)

      BOOST_AUTO_TEST_CASE(regression)
        {
          ExampleState state = ExampleState();
          ExampleState _surroundings = ExampleState();

          _surroundings.setValue(5);
          state << _surroundings;

          _surroundings.setValue(4);
          state << _surroundings;

          _surroundings.setValue(3);
          state << _surroundings;

          BOOST_CHECK(state.getValue() == 0);
          state.renew();
          BOOST_CHECK(state.getValue() == 4);

          // (5 + 4 + 3) / 3 = 4
        }

  BOOST_AUTO_TEST_SUITE_END()
