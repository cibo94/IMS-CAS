/**
 * @file cellular_automata.cpp
 * @author Miroslav Cibulka
 * @created 12/5/15
 * @copyright Copyright (c) 2015 XXX
 * @brief CellularAutomata2D class
 * @detail
 *
 */


#pragma once


#include <stddef.h>
#include <vector>
#include <ctime>

#include "cell.hh"


enum class AutomataFieldType : int
  {
    VonNeumann = 4
  };


/**
 * @details High-level container for cellular automata - 2d vector with special
 *          methods. After delete, pointers from this container are deallocated.
 * @tparam width is width of cellular map
 * @tparam height is height of cellular map
 * @tparam _StateType is class of state that will be used base class @see State
 * @tparam __neighbourhood_count is number of cells on which each cell relies
 */
template<
    size_t _width, size_t _height, typename _StateType,
    AutomataFieldType __neighbourhood_count = AutomataFieldType::VonNeumann>
  class CellularAutomata2D
    {
  public:
      typedef _StateType                                                           state_type;
      typedef AliveCell<static_cast<unsigned>(__neighbourhood_count), state_type>  alive_cell_type;
      typedef DeadCell <static_cast<unsigned>(__neighbourhood_count), state_type>  dead_cell_type;
      typedef Cell     <static_cast<unsigned>(__neighbourhood_count), state_type>  cell_type;

      CellularAutomata2D() : map(_width * _height, nullptr)
        {
          for (auto &_m : map) _m = new alive_cell_type();
        }

      /** @return row by index */
      ::std::vector<cell_type *> operator()(const unsigned row)
        {
          return (row >= height - 1)
                 ? ::std::vector<cell_type *>()
                 : ::std::vector<cell_type *>(
                       map.begin() + row * width,
                       map.begin() + (row + 1) * width);
        }

      /** @return cell on [row, col] position */
      constexpr cell_type *operator()(const unsigned row, const unsigned col)
        { return (row >= height || col >= width) ? nullptr : map[row * width + col]; }

      /** @return whole map as it is as vector ... */
      constexpr ::std::vector<cell_type *> operator()()
        { return map; }

      /** Notifies all cells */
      void notify()
        {
          for (auto &_m : map) if (_m != nullptr) _m->notify();
          for (auto &_m : map) if (_m != nullptr) _m->apply();
          ++time;
        }

      ~CellularAutomata2D()
        { for (auto &_m : map) delete _m; }

  protected:
      ::std::vector<cell_type *>  map;
      const int                   neighb_cnt  = static_cast<const int>(__neighbourhood_count);
      const size_t                width       = _width;
      const size_t                height      = _height;
      size_t                      time        = 0;
    };
