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


template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  class Cell
    {
  public:
      typedef _StateType state_type;

      Cell();

      /** Copies cell _c into this cell */
      void copy(Cell *_c);

      /** Notifies surroundings about his new state */
      void change();

      /** Notify cell about time change */
      void notify();

      /** @return state in which this cell is on */
      _StateType &getState();

      /** Set state to new value */
      void setState(_StateType _s);

      /**
       * @brief converts this cell to dead cell
       * @details Returns newly allocated
       */
      virtual Cell *die();

      /** @return true if cell is AliveCell or DeadCell */
      virtual bool isAlive() const = 0;

      void setNeighbour(unsigned x, Cell *ptr);

      virtual ~Cell();

  protected:
      Cell *neighbours[NEIGHBOURS_COUNT] = {nullptr};

      _StateType state;
    };

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  class AliveCell :
      public Cell<NEIGHBOURS_COUNT, _StateType>
    {
      typedef Cell<NEIGHBOURS_COUNT, _StateType> __BaseT;

  public:

      /** Healty cell is alive */
      virtual bool isAlive() const
        { return true; }

      virtual ~AliveCell()
        { }
    };


template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  class DeadCell :
      public Cell<NEIGHBOURS_COUNT, _StateType>
    {
      typedef Cell<NEIGHBOURS_COUNT, _StateType> __BaseT;

  public:
      /**
       * @brief Dead cell cannot die
       * @return it self without change
       */
      virtual __BaseT *die()
        { return this; }

      /** Dead cell is not alive */
      virtual bool isAlive() const
        { return false; }

      virtual ~DeadCell()
        { }
    };

/*  ---------------------------------  */
/*          IMPLEMENTATIONS            */
/*  ---------------------------------  */

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  Cell<NEIGHBOURS_COUNT, _StateType>::Cell()
    { }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  void Cell<NEIGHBOURS_COUNT, _StateType>::change()
    {
      for (Cell<NEIGHBOURS_COUNT, _StateType> **ite = neighbours;
           ite != neighbours + NEIGHBOURS_COUNT; ++ite)
        { if (*ite != nullptr) state << (*ite)->getState(); }
    }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  void Cell<NEIGHBOURS_COUNT, _StateType>::notify()
    { change(); state.renew(); }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
void Cell<NEIGHBOURS_COUNT, _StateType>::setNeighbour(
    unsigned x, Cell<NEIGHBOURS_COUNT, _StateType> *ptr)
  { if (x < NEIGHBOURS_COUNT) neighbours[x] = ptr; }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  _StateType &Cell<NEIGHBOURS_COUNT, _StateType>::getState()
    { return state; }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  Cell<NEIGHBOURS_COUNT, _StateType> *Cell<NEIGHBOURS_COUNT, _StateType>::die()
    {
      // Create new dead cell from this one and deallocate it
      Cell *dead = new DeadCell<NEIGHBOURS_COUNT, _StateType>;
      dead->copy(this);
      delete this; /* Cell now die in horrible pain */
      return dead;
    }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  void Cell<NEIGHBOURS_COUNT, _StateType>::setState(_StateType _s)
    { state = _s; }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  Cell<NEIGHBOURS_COUNT, _StateType>::~Cell()
    { }

template<unsigned NEIGHBOURS_COUNT, typename _StateType>
  void Cell<NEIGHBOURS_COUNT, _StateType>::copy(
      Cell<NEIGHBOURS_COUNT, _StateType> *cell)
    {
      this->state = cell->state;
      int i = 0;
      for (Cell<NEIGHBOURS_COUNT, _StateType> **beg = cell->neighbours;
           beg != cell->neighbours + NEIGHBOURS_COUNT; ++beg)
        this->neighbours[++i] = *beg;
    }
