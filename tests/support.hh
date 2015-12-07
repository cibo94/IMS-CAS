/**
 * @file support.hh
 * @author Miroslav Cibulka
 * @created 12/5/15
 * @copyright Copyright (c) 2015 XXX
 * @detail
 *
 */


#pragma once

#include "../src/state.hh"
#include "../src/cell.hh"
#include "../src/cellular_automata.hh"

#include <iostream>
#include <ctime>
#include <stdexcept>

#ifndef MAP_SIZE
# define MAP_SIZE 1000
#endif

#ifndef LOOP_COUNT
# define LOOP_COUNT 200
#endif

/**
 * @brief this example state recalculates each tick average from
 *        surrounding states
 */
struct ExampleState :
    public State<unsigned>
  {
    typedef State<unsigned> _BaseC;

    virtual _BaseC &operator<<(const State &another_state)
      {
        new_value += another_state.getValue();
        ++count;
        return *this;
      }

    virtual _BaseC::value_type getValue() const
      { return value; }

    virtual void setValue(_BaseC::value_type _value)
      { value = _value; }

    virtual void renew()
      { if (count != 0) value = new_value / count; }

private:
    _BaseC::value_type new_value = 0;
    _BaseC::value_type count = 0;
    _BaseC::value_type value = 0;
  };

typedef Cell <4, ExampleState> cellT;

typedef AliveCell <4, ExampleState> alive_cellT;

class VanNeumannCAutomata :
    public CellularAutomata2D<MAP_SIZE, MAP_SIZE, ExampleState, alive_cellT>
  {
public:
    typedef CellularAutomata2D<MAP_SIZE, MAP_SIZE, ExampleState, alive_cellT> _BaseT;

    /**
     * if chance is out of bounds then exception is called
     */
    VanNeumannCAutomata(float p) : _BaseT(), chance(p)
      {
        if (p < 0 || p > 1)
          throw ::std::runtime_error(
              std::string("{class VanNeumannCAutomata} parameter 'p' means ") +
              "chance <=> <0, 1>!\nbut I've got '" + ::std::to_string(p) + "'");

        // init randomizer
        ::std::srand((unsigned)::std::time(0));

        for (_BaseT::cell_type *&ptr : this->map)
          ptr->getState().setValue((unsigned)(rand() * p));

        for (size_t x = 0; x < height; ++x)
          for (size_t y = 0; y < width; ++y)
            {
              auto _cell = map[x * width + y];
              if (x < height - 1)
                _cell->setNeighbour(0, map[(x + 1) * width + y]);

              if (x > 0)
                _cell->setNeighbour(1, map[(x - 1) * width + y]);

              if (y < width - 1)
                _cell->setNeighbour(2, map[x * width + y + 1]);

              if (y > 0)
                _cell->setNeighbour(3, map[x * width + y - 1]);
            }
      }

private:
    float chance;
  };

