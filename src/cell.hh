/**
 * @file cell.hh
 * @author Miroslav Cibulka
 * @created 12/4/15
 * @copyright Copyright (c) 2015 XXX
 * @brief Cell class
 * @detail
 *
 */

#pragma once

#include <algorithm>


#include "state.hh"


template<
    unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType = bool>
  class Cell
    {
  public:
      typedef _ValueType value_type;

      typedef _StateType state_type;

      Cell();

      /** Copies cell _c into this cell */
      void copy(Cell *_c);

      /** Notify cell about time change */
      void notify();

      /** Apply changes */
      void apply();

      /** @return state in which this cell is on */
      _StateType &getState();

      /** Set state to new value */
      void setState(_StateType _s);

      /**
       * @brief converts this cell to dead cell
       * @details Returns newly allocated
       */
      virtual Cell *die() = 0;

      /** @return true if cell is AliveCell or DeadCell */
      virtual value_type getValue() const = 0;

      void setNeighbour(unsigned x, Cell *ptr);

      virtual ~Cell();

  protected:
      Cell *neighbours[NEIGHBOURS_COUNT] = { nullptr };

      _StateType state;
    };

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType = bool>
  class DeadCell :
      public Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>
    {
      typedef Cell<NEIGHBOURS_COUNT, _StateType, _ValueType> __BaseT;

  public:
      /**
       * @brief Dead cell cannot die
       * @return it self without change
       */
      virtual __BaseT *die()
        { return this; }

      /** Dead cell is not alive */
      virtual _ValueType getValue() const
        { return _ValueType(); }

      virtual ~DeadCell()
        { }
    };

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType = bool>
  class AliveCell :
      public Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>
    {
      typedef Cell<NEIGHBOURS_COUNT, _StateType, _ValueType> __BaseT;

  public:

      /** Healty cell is alive */
      virtual _ValueType getValue() const
        { return true; }

      virtual __BaseT *die()
        {
          // Create new dead cell from this one and deallocate it
          __BaseT *dead = new DeadCell<NEIGHBOURS_COUNT, _StateType, _ValueType>;
          dead->copy(this);
          delete this; /* Cell now die in horrible pain */
          return dead;
        }

      virtual ~AliveCell()
        { }
    };

/*  ---------------------------------  */
/*          IMPLEMENTATIONS            */
/*  ---------------------------------  */

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::Cell()
    { }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  void Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::notify()
    {
      for (Cell<NEIGHBOURS_COUNT, _StateType, _ValueType> **ite = neighbours;
           ite != neighbours + NEIGHBOURS_COUNT; ++ite)
        { if (*ite != nullptr) state << (*ite)->getState(); }
    }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  void Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::apply()
    { state.renew(); }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
void Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::setNeighbour(
    unsigned x, Cell<NEIGHBOURS_COUNT, _StateType, _ValueType> *ptr)
  { if (x < NEIGHBOURS_COUNT) neighbours[x] = ptr; }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  _StateType &Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::getState()
    { return state; }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  void Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::setState(_StateType _s)
    { state = _s; }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::~Cell()
    { }

template<unsigned NEIGHBOURS_COUNT, typename _StateType, typename _ValueType>
  void Cell<NEIGHBOURS_COUNT, _StateType, _ValueType>::copy(
      Cell<NEIGHBOURS_COUNT, _StateType, _ValueType> *cell)
    {
      this->state = cell->state;
      int i = 0;
      for (Cell<NEIGHBOURS_COUNT, _StateType, _ValueType> **beg = cell->neighbours;
           beg != cell->neighbours + NEIGHBOURS_COUNT; ++beg)
        this->neighbours[++i] = *beg;
    }
