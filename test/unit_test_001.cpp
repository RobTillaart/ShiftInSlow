//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-11
// PURPOSE: unit tests for the FastShiftIn library
//          https://github.com/RobTillaart/shiftInSlow
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "ShiftInSlow.h"


// PATCH FOR DUE & ZERO FOR UNIT TEST - https://github.com/Arduino-CI/arduino_ci/issues/252
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
// - due         #  ARDUINO_ARCH_SAM    does not support shiftIn apparently
// - zero        #  ARDUINO_ARCH_SAMD   
#endif


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  ShiftInSlow SIS(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTINSLOW_LIB_VERSION);
  assertEqual(0, SIS.lastRead());
  assertEqual(LSBFIRST, SIS.getBitOrder());
  
  SIS.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, SIS.getBitOrder());
}


unittest(test_constructor_LSB)
{
  ShiftInSlow SIS(12, 13, LSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTINSLOW_LIB_VERSION);
  assertEqual(0, SIS.lastRead());
  assertEqual(LSBFIRST, SIS.getBitOrder());
  
  SIS.setBitOrder(MSBFIRST);
  assertEqual(MSBFIRST, SIS.getBitOrder());
}


unittest(test_constructor_MSB)
{
  ShiftInSlow SIS(12, 13, MSBFIRST);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTINSLOW_LIB_VERSION);
  assertEqual(0, SIS.lastRead());
  assertEqual(MSBFIRST, SIS.getBitOrder());
  
  SIS.setBitOrder(LSBFIRST);
  assertEqual(LSBFIRST, SIS.getBitOrder());
}


unittest(test_setDelay)
{
  ShiftInSlow SIS(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTINSLOW_LIB_VERSION);
  for (uint16_t d = 0; d < 1000; d += 100)
  {
    SIS.setDelay(d);
    assertEqual(d, SIS.getDelay());
  }
}


unittest(test_read)
{
  ShiftInSlow SIS(12, 13);

  fprintf(stderr, "VERSION:\t%s\n", SHIFTINSLOW_LIB_VERSION);

// apparently needed... To be investigated someday ...
#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)

  assertEqual(0, SIS.read());
  assertEqual(0, SIS.readLSBFIRST());
  assertEqual(0, SIS.readMSBFIRST());

#else  // AVR

  assertEqual(255, SIS.read());
  assertEqual(255, SIS.readLSBFIRST());
  assertEqual(255, SIS.readMSBFIRST());
  
#endif
}


unittest_main()

// --------
