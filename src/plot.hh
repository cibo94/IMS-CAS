/**
 * @file plot.cpp
 * @author Miroslav Cibulka
 * @created 12/7/15
 * @copyright Copyright (c) 2015 XXX
 * @brief plot class
 * @detail
 *
 */


#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>


template<typename header_T = long, typename data_T = long>
struct GnuPlot
  {
    GnuPlot(::std::string _fn) :
        file(_fn)
      { }

    /**
     * @brief It is assumed that y and x have same size
     */
    void write_data(::std::vector<header_T> y, ::std::vector<data_T> x)
      {
        table.reserve(y.size());
        int c = 0;
        for (auto &row : y)
          table.push_back(::std::tuple<header_T, data_T>(row, x[++c]));
      }

    ~GnuPlot()
      {
        for (auto &row : table)
          { file << ::std::get<0>(row) << "\t" << ::std::get<1>(row) << ::std::endl; }
      }

private:
    ::std::ofstream file;
    ::std::vector<::std::tuple<header_T, data_T>> table;
  };
