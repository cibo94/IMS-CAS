/**
 * @file test_automata.cpp
 * @author Miroslav Cibulka
 * @created 12/5/15
 * @copyright Copyright (c) 2015 XXX
 * @detail
 *
 */

#include <boost/test/unit_test.hpp>

#include "support.hh"

BOOST_AUTO_TEST_SUITE(automata_tests)

      BOOST_AUTO_TEST_CASE(regression)
        {
          VanNeumannCAutomata automata(.7f);

          for (auto &node : automata())
            BOOST_MESSAGE(node->getState().getValue());

          automata.notify();

          BOOST_MESSAGE("\n\n");

          for (auto &node : automata())
            BOOST_MESSAGE(node->getState().getValue());
        }

  BOOST_AUTO_TEST_SUITE_END()
