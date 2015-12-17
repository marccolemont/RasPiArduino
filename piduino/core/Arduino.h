#ifndef Arduino_h
#define Arduino_h

#include "bcm2835_registers.h"
#include <math.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef void * PTHREAD;

#define PWM_DEVIDER 	16
#define PWM_RANGE   	0xFF
#define PWM_MODE    	1

void yield(void);

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define ALT0 0x04
#define ALT1 0x05
#define ALT2 0x06
#define ALT3 0x07
#define ALT4 0x03
#define ALT5 0x02
#define INPUT_PULLUP 0x10
#define INPUT_PULLDOWN 	0x20

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 3
#define FALLING 1
#define RISING 2

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

#define interrupts()
#define noInterrupts()
#define cli()
#define seu()

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
#define _NOP() do {} while (0)
#endif

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef uint8_t boolean;
typedef uint8_t byte;

#define micros() (STCV)
#define millis() (STCV / 1000)
#define delay(m) nap(m * 1000)
#define delayMicroseconds(m) (m>450)?nap(m):halt(m)

int init(void);
void uninit(void);

int create_thread(void *(*fn)(void *));
int start_thread(void *(*fn)(void *), void * arg);
void lock_thread(int index);
void unlock_thread(int index);
int elevate_prio(const int prio);

void nap(uint32_t);

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);//47.5ns direct register write takes 23ns
int digitalRead(uint8_t);//110ns direct register read takes 74ns
int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, uint8_t);//500ns direct register write takes 23ns rest is pin mode and channel enable

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

typedef void (*voidFuncPtr)(void);

void isr_check(void);
void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);

void setup(void);
void loop(void);

#define analogInPinToBit(P) (P)

#define digitalPinToPort(P) (((P)<32)?0:1)
#define portOutputRegister(P) (((P)<32)?&GPSET0:&GPSET1)
#define digitalPinToBitMask(P) (P)
#define digitalPinToTimer(P) ((P==12||P==18)?0:(P==13||P==19)?1:-1)

#define NOT_A_PIN 0
#define NOT_A_PORT 0

#define NOT_AN_INTERRUPT -1

void uart_check_fifos();

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"
#include "SPI.h"
#include "Wire.h"
#include "console.h"
#include "LinuxConsole.h"

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

// WMath prototypes
long map(long, long, long, long, long);
#endif

#include "binary.h"
#include "pins_arduino.h"

#endif