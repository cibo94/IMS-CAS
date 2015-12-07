/**
 * @file test_cell.cpp
 * @author Miroslav Cibulka
 * @created 12/5/15
 * @copyright Copyright (c) 2015 XXX
 * @detail
 *
 */


#include <boost/test/unit_test.hpp>

#include "support.hh"
#include "../src/cell.hh"


BOOST_AUTO_TEST_SUITE(cell_tests)

      BOOST_AUTO_TEST_CASE(regression)
        {
          ::std::vector<cellT *> _cell_vector(10 * 10);
          for (auto &_cell : _cell_vector)
            _cell = new alive_cellT;

          for (auto &_cell : _cell_vector)
            {
              BOOST_CHECK(_cell->getValue());
              _cell = _cell->die();
              BOOST_CHECK(! _cell->getValue());
              delete _cell;
            }
        }

  BOOST_AUTO_TEST_SUITE_END()
