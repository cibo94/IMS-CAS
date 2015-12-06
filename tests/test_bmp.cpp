/**
 * @file test_bmp.cpp
 * @author Miroslav Cibulka
 * @created 12/6/15
 * @copyright Copyright (c) 2015 XXX
 * @detail
 *
 */

#include "../src/bmp.hh"
#include <vector>
#include "support.hh"

int main()
  {
    {
      ::std::vector<unsigned> bitmap(100 * 100, 255);
      BMP ("out.bmp", 100, 100) << bitmap;
      ::std::cout << "out.bmp" << ::std::endl;
    }

    {
      VanNeumannCAutomata automata(.7f);
      ::std::vector<unsigned> bitmap(100, 100);
      for (auto &node : automata())
        {
          unsigned state = (unsigned) (
              ((unsigned long) node->getState().getValue() * 4)
              / (unsigned long) RAND_MAX);
          bitmap.push_back(state * (256 / 4));
        }
      BMP ("out2.bmp", 100, 100) << bitmap;
      ::std::cout << "out2.bmp" << ::std::endl;
    }
    return 0;
  }
