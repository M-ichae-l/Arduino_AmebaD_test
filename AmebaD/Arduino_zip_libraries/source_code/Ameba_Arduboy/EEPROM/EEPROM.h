/* 
  EEPROM.cpp - EEPROM emulation using RTL8722 flash memory

  Copyright (c) 2014 Ivan Grokhotkov. All rights reserved.
  This file is part of the esp8266 core for Arduino environment.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified by Realtek
*/

#ifndef EEPROM_h
#define EEPROM_h

//#include <stddef.h>
//#include <stdint.h>
//#include <string.h>
#include <FlashMemory.h>

// Default to using same flash memory as the FlashMemory library
#define EEPROM_MEMORY_APP_BASE FLASH_MEMORY_APP_BASE
#define EEPROM_DEFAULT_SIZE FLASH_SECTOR_SIZE

class EEPROMClass {
public:
  EEPROMClass(void);
  EEPROMClass(uint32_t base_address);

  void begin(size_t size = EEPROM_DEFAULT_SIZE);
  uint8_t read(int const address);
  void write(int const address, uint8_t const value);
  void update(int    const address, uint8_t const value);
  bool commit();
  bool end();

  uint8_t * getDataPtr();
  uint8_t const * getConstDataPtr() const;

  template<typename T> 
  T &get(int const address, T &t) {
    if (address < 0 || address + sizeof(T) > _size)
      return t;

    memcpy((uint8_t*) &t, _data + address, sizeof(T));
    return t;
  }

  template<typename T> 
  const T &put(int const address, const T &t) {
    if (address < 0 || address + sizeof(T) > _size)
      return t;
    if (memcmp(_data + address, (const uint8_t*)&t, sizeof(T)) != 0) {
      _dirty = true;
      memcpy(_data + address, (const uint8_t*)&t, sizeof(T));
    }

    return t;
  }

  size_t length() {return _size;}

  uint8_t& operator[](int const address) {return getDataPtr()[address];}
  uint8_t const & operator[](int const address) const {return getConstDataPtr()[address];}

protected:
  uint32_t _base_address;
  uint8_t* _data = nullptr;
  size_t _size = 0;
  bool _dirty = false;
  void* pFlash;
};

extern EEPROMClass EEPROM;

#endif