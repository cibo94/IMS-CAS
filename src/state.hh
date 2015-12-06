/**
 * @file state.hh
 * @author Miroslav Cibulka
 * @created 12/4/15
 * @copyright Copyright (c) 2015 XXX
 * @brief State class
 * @detail
 *
 */


#pragma once


/** Interface for states */
template<typename _ValueType>
  struct State
    {
      typedef _ValueType value_type;

      /** Change value via another state */
      virtual State &operator<<(const State &another_state) = 0;

      /** @return value of state */
      virtual _ValueType getValue() const = 0;

      /** Set value */
      virtual void setValue(value_type _value) = 0;

      /** Recalculate value from '+=' new_value
       *    For instance calculate average
       */
      virtual void renew() = 0;
    };
