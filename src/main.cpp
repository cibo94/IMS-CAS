/**
 * @file main.cpp
 * @author Miroslav Cibulka
 * @created 12/4/15
 * @copyright Copyright (c) 2015 XXX
 * @detail
 *
 */

#include <stdexcept>

#include "state.hh"
#include "cell.hh"
#include "cellular_automata.hh"
#include "bmp.hh"


#define VAN_NEUMANN_SIZE 100


struct CellState : public State<unsigned>
  {
    typedef State<unsigned> _BaseC;

    virtual _BaseC &operator<<(const State &another_state)
      {
        new_value += another_state.getValue();
        return *this;
      }

    virtual _BaseC::value_type getValue() const
      { return value; }

    virtual void setValue(_BaseC::value_type _value)
      { value = _value; }

    /** There are 0 1 2 3 states only so 3 is last one */
    virtual void renew()
      { value = new_value > 3 ? 3 : new_value; new_value = 0; }

private:
    _BaseC::value_type new_value = 0;
    _BaseC::value_type value = 0;
  };

class CellAutomata :
    public CellularAutomata2D<VAN_NEUMANN_SIZE, VAN_NEUMANN_SIZE, CellState>
  {
public:
    typedef CellularAutomata2D<VAN_NEUMANN_SIZE, VAN_NEUMANN_SIZE, CellState> _BaseT;

    /**
     * if chance is out of bounds then exception is called
     */
    CellAutomata(float p) : _BaseT(), chance(p)
      {
        if (p < 0 || p > 1)
          throw ::std::runtime_error(
              std::string("{class VanNeumannCAutomata} parameter 'p' means ") +
              "chance <=> <0, 1>!\nbut I've got '" + ::std::to_string(p) + "'");

        // init randomizer
        ::std::srand((unsigned)::std::time(0));

        for (_BaseT::cell_type *&ptr : this->map)
          ptr->getState().setValue((unsigned)(rand() * p) / (RAND_MAX / 256));

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

    ::std::vector<typename state_type::value_type> getValues()
      {
        ::std::vector<typename state_type::value_type> _ret;
        for (auto &_m : map)
          _ret.push_back(_m->getState().getValue() * (256 / 4));
        return _ret;
      }

private:
    float chance;
  };


int main(int /*argc*/, const char **/*argv*/)
  {
    CellAutomata _aut(.7f);
    for (int i = 0; i < 10; ++i)
      {
        for (int j = 0; j < 5; ++j)
          ::std::cout << _aut.getValues()[j] << ::std::endl;
        BMP(::std::string("obr") + ::std::to_string(i) + ".bmp", 100, 100) << _aut.getValues();
        _aut.notify();
        ::std::cout << ::std::endl;
      }
    return 0;
  }
