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
#include "plot.hh"


#define MAP_SIZE 1000


static inline bool take_chance(double chance)
  { return ((double)::std::rand() / (double)RAND_MAX) < chance; }

enum class CellStatus : unsigned
  {
    Healthy, Infected, HeavyInfected, Dead
  };

struct CellState :
    public State<CellStatus>
  {
    typedef State<CellStatus> _BaseC;

    CellState() { }

    CellState(int T_steps, double HIV, double REPLACE, double INFECT) :
        _t(T_steps), _hiv(HIV), _replace(REPLACE), _infect(INFECT)
      {
        // Cell is infected
        if (take_chance(HIV))
          value = CellStatus::Infected;
        else
          value = CellStatus::Healthy;
      }

    virtual _BaseC &operator<<(const State &another_state)
      {
        surrounding_states.push_back(another_state.getValue());
        return *this;
      }

    virtual _BaseC::value_type getValue() const
      { return value; }

    virtual void setValue(_BaseC::value_type _value)
      { value = _value; }

    /** One tick */
    virtual void renew()
      {
        _BaseC::value_type new_value = value;

        if (newly_created && value == CellStatus::Healthy && take_chance(_infect))
          new_value = CellStatus::Infected;

        // Changes by surrounding cells
        else if (value == CellStatus::Healthy && ::std::count(
            surrounding_states.begin(), surrounding_states.end(),
            CellStatus::Infected) > 0)
          { new_value = CellStatus::Infected; }
        else if (value == CellStatus::Healthy && ::std::count(
            surrounding_states.begin(), surrounding_states.end(),
            CellStatus::HeavyInfected) > 1)
          { new_value = CellStatus::Infected; }

        // Stepps for CellStatus::Infected to become CellStatus::HeavyInfected
        else if (value == CellStatus::Infected && step_counter == _t)
          {
            new_value = CellStatus::HeavyInfected;
            step_counter = 0;
          }

        // Every tick HeavyInfected cell die
        else if (value == CellStatus::HeavyInfected)
          { new_value = CellStatus::Dead; }

        // Replace chances
        else if (value == CellStatus::Dead && take_chance(_replace))
          {
            newly_created = true;
            if (take_chance(_infect))
              new_value = CellStatus::Infected;
            else
              new_value = CellStatus::Healthy;
          }

        if (value == CellStatus::Infected)
          { step_counter++; }
        else
          { step_counter = 0; }

        surrounding_states.clear();

        value = new_value;
      }

private:
    int     _t;
    double   _hiv;
    double   _replace;
    double   _infect;
    bool    newly_created = false;

    int     step_counter = 0;

    _BaseC::value_type value;
    ::std::vector<_BaseC::value_type> surrounding_states;
  };

class HealthyCell :
    public Cell<8, CellState, CellStatus>
  {
    typedef Cell<8, CellState, CellStatus> _BaseT;

public:
    #define DEFAULT_T         4
    #define DEFAULT_HIV       0.05
    #define DEFAULT_REPLACE   0.99
    #define DEFAULT_INFECT    0.00001

    struct params
      {
        params()        { }
        int T_steps   = DEFAULT_T;
        double HIV    = DEFAULT_HIV;
        double REPLACE= DEFAULT_REPLACE;
        double INFECT = DEFAULT_INFECT;
      };

    /**
     * @param T_steps until CellStatus::Infected becomes CellStatus::HeavyInfected
     * @param HIV is chance to cell become CellStatus::Infected on initialization
     * @param REPLACE is chance to resurrect CellStatus::Dead Cell
     *                (it will become CellStatus::Healthy)
     * @param INFECT is chance that newborn cell that is CellStatus::Healthy
     *               becomes CellStatus::Infected right after creation
     */
    HealthyCell(struct params p = params())
      { _BaseT::state = CellState(p.T_steps, p.HIV, p.REPLACE, p.INFECT); }

    virtual _BaseT *die()
      {
        state.setValue(CellStatus::Dead);
        return this;
      }

    /** @return Status of this cell */
    virtual value_type getValue() const
      { return state.getValue(); }
  };


class CellAutomata :
    public CellularAutomata2D<MAP_SIZE, MAP_SIZE, CellState, HealthyCell>
  {
public:
    typedef CellularAutomata2D<MAP_SIZE, MAP_SIZE, CellState, HealthyCell> _BaseT;

    /**
     * if chance is out of bounds then exception is called
     */
    CellAutomata() : _BaseT(HealthyCell::params())
      {
        ::std::srand((unsigned)::std::time(0));
        // Filling neighbour list
        for (size_t x = 0; x < height; ++x)
          for (size_t y = 0; y < width; ++y)
            {
              auto _cell = map[x * width + y];
              if (x < height - 1)
                _cell->setNeighbour(0, map[(x + 1) * width + y]);

              if (x < height - 1 && y < width - 1)
                _cell->setNeighbour(4, map[(x + 1) * width + y + 1]);

              if (x > 0)
                _cell->setNeighbour(1, map[(x - 1) * width + y]);

              if (x > 0 && y > 0)
                _cell->setNeighbour(5, map[(x - 1) * width + y - 1]);

              if (y < width - 1)
                _cell->setNeighbour(2, map[x * width + y + 1]);

              if (y < width - 1 && x > 0)
                _cell->setNeighbour(6, map[(x - 1) * width + y + 1]);

              if (y > 0)
                _cell->setNeighbour(3, map[x * width + y - 1]);

              if (y > 0 && x < height - 1)
                _cell->setNeighbour(7, map[(x + 1) * width + y - 1]);
            }
      }

    ::std::vector<typename state_type::value_type> getValues()
      {
        ::std::vector<typename state_type::value_type> _ret;
        for (auto &_m : map)
          _ret.push_back(_m->getState().getValue());
        return _ret;
      }
  };


struct Statistics
  {
    typedef GnuPlot<long, long> plot_type;

    Statistics (::std::string fn) : filename(fn)
      { }

    Statistics &operator << (CellStatus &c)
      { ++counts[(unsigned)c]; return *this; }

    void notify()
      {
        for (int i = 0; i < 4; ++i)
          {
            _statuses[i].push_back(counts[i]);
            counts[i] = 0;
          }
        header.push_back(++disc_time);
      }

    ~Statistics()
      {
        plot_type(filename+"_healty.gp").write_data(header, _statuses[0]);
        plot_type(filename+"_infected.gp").write_data(header, _statuses[1]);
        plot_type(filename+"_heavy_infected.gp").write_data(header, _statuses[2]);
        plot_type(filename+"_dead.gp").write_data(header, _statuses[3]);
      }

private:
    long counts[4] = { 0 };
    ::std::vector<long> _statuses[4];
    ::std::vector<long> header;
    ::std::string filename;
    int disc_time = 0;
  };


int main(int /*argc*/, const char **/*argv*/)
  {
    CellAutomata _aut;
    Statistics _stats ("plot");
    for (int i = 0; i < 200; ++i)
      {
        ::std::vector<unsigned> _vals;
        for (CellStatus &_c : _aut.getValues())
          {
            switch(_c)
              {
                case CellStatus::Healthy:       _vals.push_back(0x0033CC33); break;
                case CellStatus::Infected:      _vals.push_back(0x00FFFF00); break;
                case CellStatus::HeavyInfected: _vals.push_back(0x00FF0000); break;
                case CellStatus::Dead:          _vals.push_back(0x00000000); break;
              }
            _stats << _c;
          }
        BMP(::std::string("obr") + ::std::to_string(i) + ".bmp", MAP_SIZE, MAP_SIZE)
            << _vals;
        _aut.notify();
        _stats.notify();
      }
    return 0;
  }
