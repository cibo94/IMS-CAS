/**
 * @file plot.cpp
 * @author Miroslav Cibulka
 * @created 12/7/15
 * @copyright Copyright (c) 2015 XXX
 * @brief plot class
 * @detail
 *
 */

#include <boost/test/unit_test.hpp>
#include "../src/plot.hh"
#include <ctime>


BOOST_AUTO_TEST_SUITE(base_plot)

      BOOST_AUTO_TEST_CASE(plot_testy)
        {
          GnuPlot<long, long> pl ("plot.gp");

          ::std::vector<long> header(100), data(100);

          ::std::srand((unsigned)::std::time(0));
          int i = 0;
          for (auto &h : header)
            {
              data[i] = ::std::rand() % 100;
              h = ++i;
            }

          pl.write_data(header, data);
        }

  BOOST_AUTO_TEST_SUITE_END()
