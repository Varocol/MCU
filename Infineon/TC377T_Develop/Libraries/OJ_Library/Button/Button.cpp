/**
 * @file OneButton.cpp
 *
 * @brief Library for detecting button clicks, doubleclicks and long press
 * pattern on a single button.
 *
 * @author Matthias Hertel, https://www.mathertel.de
 * @Copyright Copyright (c) by Matthias Hertel, https://www.mathertel.de.
 *
 * This work is licensed under a BSD style license. See
 * http://www.mathertel.de/License.aspx
 *
 * More information on: https://www.mathertel.de/Arduino/OneButtonLibrary.aspx
 *
 * Changelog: see OneButton.h
 */

#include "Button.h"
// ----- Initialization and Default Values -----

/**
 * @brief Construct a new OneButton object but not (yet) initialize the IO pin.
 */
Button::Button() // @suppress("Class members should be properly initialized")
{
  // further initialization has moved to OneButton.h
}

/**
 * Initialize the OneButton library.
 * @param pin The pin to be used for input from a momentary button.
 * @param activeLow Set to true when the input level is LOW when the button is pressed, Default is true.
 * @param pullupActive Activate the internal pullup when available. Default is true.
 */
Button::Button(PIN_enum pin, const bool activeLow, const bool pullupActive)
{
  // OneButton();

  if (activeLow) {
    // the button connects the input pin to GND when pressed.
    _buttonPressed = LOW;

  } else {
    // the button connects the input pin to VCC when pressed.
    _buttonPressed = HIGH;
  } // if

  if (pullupActive) {
    // use the given pin as input and activate internal PULLUP resistor.
    GPIO::Set_Param(pin, GPI, 1, PULLUP);
  } else {
    // use the given pin as input
    GPIO::Set_Param(pin, GPI, 1, NO_PULL);
  } // if
} // OneButton

/**
    * Set the Param of OneButton library.
    * @param pin The pin to be used for input from a momentary button.
    * @param activeLow Set to true when the input level is LOW when the button is pressed, Default is true.
    * @param pullupActive Activate the internal pullup when available. Default is true.
    */
void Button::Set_Param(PIN_enum pin, const bool activeLow, const bool pullupActive)
{
    if (activeLow) {
       // the button connects the input pin to GND when pressed.
       _buttonPressed = LOW;

     } else {
       // the button connects the input pin to VCC when pressed.
       _buttonPressed = HIGH;
     } // if

     if (pullupActive) {
       // use the given pin as input and activate internal PULLUP resistor.
       GPIO::Set_Param(pin, GPI, 1, PULLUP);
     } else {
       // use the given pin as input
       GPIO::Set_Param(pin, GPI, 1, NO_PULL);
     } // if
}

/**
   * Initialize the hardware of Button
   */
void Button::Init()
{
    GPIO::Init();
}

// explicitly set the number of millisec that have to pass by before a click is assumed stable.
void Button::setDebounceTicks(const int ticks)
{
  _debounceTicks = ticks;
} // setDebounceTicks


// explicitly set the number of millisec that have to pass by before a click is detected.
void Button::setClickTicks(const int ticks)
{
  _clickTicks = ticks;
} // setClickTicks


// explicitly set the number of millisec that have to pass by before a long button press is detected.
void Button::setPressTicks(const int ticks)
{
  _pressTicks = ticks;
} // setPressTicks


// save function for click event
void Button::attachClick(callbackFunction newFunction)
{
  _clickFunc = newFunction;
} // attachClick


// save function for parameterized click event
void Button::attachClick(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramClickFunc = newFunction;
  _clickFuncParam = parameter;
} // attachClick


// save function for doubleClick event
void Button::attachDoubleClick(callbackFunction newFunction)
{
  _doubleClickFunc = newFunction;
  _maxClicks = max(_maxClicks, 2);
} // attachDoubleClick


// save function for parameterized doubleClick event
void Button::attachDoubleClick(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramDoubleClickFunc = newFunction;
  _doubleClickFuncParam = parameter;
  _maxClicks = max(_maxClicks, 2);
} // attachDoubleClick


// save function for multiClick event
void Button::attachMultiClick(callbackFunction newFunction)
{
  _multiClickFunc = newFunction;
  _maxClicks = max(_maxClicks, 100);
} // attachMultiClick


// save function for parameterized MultiClick event
void Button::attachMultiClick(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramMultiClickFunc = newFunction;
  _multiClickFuncParam = parameter;
  _maxClicks = max(_maxClicks, 100);
} // attachMultiClick


// save function for longPressStart event
void Button::attachLongPressStart(callbackFunction newFunction)
{
  _longPressStartFunc = newFunction;
} // attachLongPressStart


// save function for parameterized longPressStart event
void Button::attachLongPressStart(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramLongPressStartFunc = newFunction;
  _longPressStartFuncParam = parameter;
} // attachLongPressStart


// save function for longPressStop event
void Button::attachLongPressStop(callbackFunction newFunction)
{
  _longPressStopFunc = newFunction;
} // attachLongPressStop


// save function for parameterized longPressStop event
void Button::attachLongPressStop(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramLongPressStopFunc = newFunction;
  _longPressStopFuncParam = parameter;
} // attachLongPressStop


// save function for during longPress event
void Button::attachDuringLongPress(callbackFunction newFunction)
{
  _duringLongPressFunc = newFunction;
} // attachDuringLongPress


// save function for parameterized during longPress event
void Button::attachDuringLongPress(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramDuringLongPressFunc = newFunction;
  _duringLongPressFuncParam = parameter;
} // attachDuringLongPress


void Button::reset(void)
{
  _state = Button::OCS_INIT;
  _lastState = Button::OCS_INIT;
  _nClicks = 0;
  _startTime = 0;
}


// ShaggyDog ---- return number of clicks in any case: single or multiple clicks
int Button::getNumberClicks(void)
{
  return _nClicks;
}


/**
 * @brief Check input of the configured pin and then advance the finite state
 * machine (FSM).
 */
void Button::tick(void)
{
    tick(Pin_Get() == _buttonPressed);
}


/**
 *  @brief Advance to a new state and save the last one to come back in cas of bouncing detection.
 */
void Button::_newState(stateMachine_t nextState)
{
  _lastState = _state;
  _state = nextState;
} // _newState()


/**
 * @brief Run the finite state machine (FSM) using the given level.
 */
void Button::tick(bool activeLevel)
{
  unsigned long now = platform_getval_ms(); // current (relative) time in msecs.
  unsigned long waitTime = (now - _startTime);


  // Implementation of the state machine
  switch (_state) {
  case Button::OCS_INIT:
    // waiting for level to become active.
    if (activeLevel) {
      _newState(Button::OCS_DOWN);
      _startTime = now; // remember starting time
      _nClicks = 0;
    } // if
    break;

  case Button::OCS_DOWN:
    // waiting for level to become inactive.

    if ((!activeLevel) && (waitTime < _debounceTicks)) {
      // button was released to quickly so I assume some bouncing.
      _newState(_lastState);

    } else if (!activeLevel) {
      _newState(Button::OCS_UP);
      _startTime = now; // remember starting time

    } else if ((activeLevel) && (waitTime > _pressTicks)) {
      if (_longPressStartFunc) _longPressStartFunc();
      if (_paramLongPressStartFunc) _paramLongPressStartFunc(_longPressStartFuncParam);
      _newState(Button::OCS_PRESS);
    } // if
    break;

  case Button::OCS_UP:
    // level is inactive

    if ((activeLevel) && (waitTime < _debounceTicks)) {
      // button was pressed to quickly so I assume some bouncing.
      _newState(_lastState); // go back

    } else if (waitTime >= _debounceTicks) {
      // count as a short button down
      _nClicks++;
      _newState(Button::OCS_COUNT);
    } // if
    break;

  case Button::OCS_COUNT:
    // dobounce time is over, count clicks

    if (activeLevel) {
      // button is down again
      _newState(Button::OCS_DOWN);
      _startTime = now; // remember starting time
    } else if ((waitTime > _clickTicks) || (_nClicks == _maxClicks)) {
      // now we know how many clicks have been made.

      if (_nClicks == 1) {
        // this was 1 click only.
        if (_clickFunc) _clickFunc();
        if (_paramClickFunc) _paramClickFunc(_clickFuncParam);

      } else if (_nClicks == 2) {
        // this was a 2 click sequence.
        if (_doubleClickFunc) _doubleClickFunc();
        if (_paramDoubleClickFunc) _paramDoubleClickFunc(_doubleClickFuncParam);

      } else {
        // this was a multi click sequence.
        if (_multiClickFunc) _multiClickFunc();
        if (_paramMultiClickFunc) _paramMultiClickFunc(_doubleClickFuncParam);
      } // if

      reset();
    } // if
    break;

  case Button::OCS_PRESS:
    // waiting for menu pin being release after long press.

    if (!activeLevel) {
      _newState(Button::OCS_PRESSEND);
      _startTime = now;

    } else {
      // still the button is pressed
      if (_duringLongPressFunc) _duringLongPressFunc();
      if (_paramDuringLongPressFunc) _paramDuringLongPressFunc(_duringLongPressFuncParam);
    } // if
    break;

  case Button::OCS_PRESSEND:
    // button was released.

    if ((activeLevel) && (waitTime < _debounceTicks)) {
      // button was released to quickly so I assume some bouncing.
      _newState(_lastState); // go back

    } else if (waitTime >= _debounceTicks) {
      if (_longPressStopFunc) _longPressStopFunc();
      if (_paramLongPressStopFunc) _paramLongPressStopFunc(_longPressStopFuncParam);
      reset();
    }
    break;

  default:
    // nothing to do.
    break;
  } // if

} // OneButton.tick()


// end.
