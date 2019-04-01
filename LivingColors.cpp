/*!
 *  \file    LivingColors.cpp
 *  \version 1.1
 *  \date    29-01-2009
 *  \author  George Mathijssen, george.knutsel@gmail.com
 *
 *  Copyright (c) 2008, 2009 George Mathijssen
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  \internal
 *    Created: 03-10-2008
 */

#include "LivingColors.h"
#include "Arduino.h"

LivingColors::LivingColors(unsigned char pinCS, unsigned char pinSCK, unsigned char pinMOSI,
    unsigned char pinMISO)
    : m_cc2500(pinCS, pinSCK, pinMOSI, pinMISO)
    , m_sequence(0)
    , m_lamps()
    , m_maxNumLamps(MAXLAMPS)
    , m_numLamps(0)
{
    for (int y=0; y<m_maxNumLamps; ++y) {
        for (int x=0; x<10; ++x) {
            m_lamps[y][x] = 0;
        }
    }
}

LivingColors::~LivingColors()
{
}

void LivingColors::init()
{
    // initialize the CC2500
    m_cc2500.init();

    // reset device (0x30)
    m_cc2500.reset();

    // reset device (0x30)
    m_cc2500.reset();

    // write configuration register: FSCTRL1 � Frequency Synthesizer Control
    m_cc2500.sendCommand(CC2500_REG_FSCTRL1, 0x09);

    // write configuration register: FSCTRL0 � Frequency Synthesizer Control
    m_cc2500.sendCommand(CC2500_REG_FSCTRL0, 0x00);

    // write configuration register: FREQ2 � Frequency Control Word, High Byte
    m_cc2500.sendCommand(CC2500_REG_FREQ2, 0x5D);

    // write configuration register: FREQ1 � Frequency Control Word, Middle Byte
    m_cc2500.sendCommand(CC2500_REG_FREQ1, 0x93);

    // write configuration register: FREQ0 � Frequency Control Word, Low Byte
    m_cc2500.sendCommand(CC2500_REG_FREQ0, 0xB1);

    // write configuration register: MDMCFG4 � Modem Configuration
    m_cc2500.sendCommand(CC2500_REG_MDMCFG4, 0x2D);

    // write configuration register: MDMCFG3 � Modem Configuration
    m_cc2500.sendCommand(CC2500_REG_MDMCFG3, 0x3B);

    // write configuration register: MDMCFG2 � Modem Configuration
    m_cc2500.sendCommand(CC2500_REG_MDMCFG2, 0x73);

    // write configuration register: MDMCFG1 � Modem Configuration
    m_cc2500.sendCommand(CC2500_REG_MDMCFG1, 0x22);

    // write configuration register: MDMCFG0 � Modem Configuration
    m_cc2500.sendCommand(CC2500_REG_MDMCFG0, 0xF8);

    // write configuration register: CHANNR � Channel Number
    m_cc2500.sendCommand(CC2500_REG_CHANNR, 0x03);

    // write configuration register: DEVIATN � Modem Deviation Setting
    m_cc2500.sendCommand(CC2500_REG_DEVIATN, 0x00);

    // write configuration register: FREND1 � Front End RX Configuration
    m_cc2500.sendCommand(CC2500_REG_FREND1, 0xB6);

    // write configuration register: FREND0 � Front End TX configuration
    m_cc2500.sendCommand(CC2500_REG_FREND0, 0x10);

    // write configuration register: MCSM0 � Main Radio Control State Machine Configuration
    m_cc2500.sendCommand(CC2500_REG_MCSM0, 0x18);

    // write configuration register: FOCCFG � Frequency Offset Compensation Configuration
    m_cc2500.sendCommand(CC2500_REG_FOCCFG, 0x1D);

    // write configuration register: BSCFG � Bit Synchronization Configuration
    m_cc2500.sendCommand(CC2500_REG_BSCFG, 0x1C);

    // write configuration register: AGCCTRL2 � AGC Control
    m_cc2500.sendCommand(CC2500_REG_AGCCTRL2, 0xC7);

    // write configuration register: AGCCTRL1 � AGC Control
    m_cc2500.sendCommand(CC2500_REG_AGCCTRL1, 0x00);

    // write configuration register: AGCCTRL0 � AGC Control
    m_cc2500.sendCommand(CC2500_REG_AGCCTRL0, 0xB2);

    // write configuration register: FSCAL3 � Frequency Synthesizer Calibration
    m_cc2500.sendCommand(CC2500_REG_FSCAL3, 0xEA);

    // write configuration register: FSCAL2 � Frequency Synthesizer Calibration
    m_cc2500.sendCommand(CC2500_REG_FSCAL2, 0x0A);

    // write configuration register: FSCAL1 � Frequency Synthesizer Calibration
    m_cc2500.sendCommand(CC2500_REG_FSCAL1, 0x00);

    // write configuration register: FSCAL0 � Frequency Synthesizer Calibration
    m_cc2500.sendCommand(CC2500_REG_FSCAL0, 0x11);

    // write configuration register: TEST2 � Various Test Settings
    m_cc2500.sendCommand(CC2500_REG_TEST2, 0x88);

    // write configuration register: TEST1 � Various Test Settings
    m_cc2500.sendCommand(CC2500_REG_TEST1, 0x31);

    // write configuration register: TEST0 � Various Test Settings
    m_cc2500.sendCommand(CC2500_REG_TEST0, 0x0B);

    // write configuration register: IOCFG2 � GDO2 Output Pin Configuration
    m_cc2500.sendCommand(CC2500_REG_IOCFG2, 0x06);

    // write configuration register: IOCFG0 � GDO0 Output Pin Configuration
    m_cc2500.sendCommand(CC2500_REG_IOCFG0, 0x01);

    // write configuration register: PKTCTRL1 � Packet Automation Control
    m_cc2500.sendCommand(CC2500_REG_PKTCTRL1, 0x04);

    // write configuration register: PKTCTRL0 � Packet Automation Control
    m_cc2500.sendCommand(CC2500_REG_PKTCTRL0, 0x45);

    // write configuration register: ADDR � Device Address
    m_cc2500.sendCommand(CC2500_REG_ADDR, 0x00);

    // write configuration register: PKTLEN � Packet Length
    m_cc2500.sendCommand(CC2500_REG_PKTLEN, 0xFF);

    // write configuration register: FIFOTHR � RX FIFO and TX FIFO Thresholds
    m_cc2500.sendCommand(CC2500_REG_FIFOTHR, 0x0D);

    // write power setting to PATABLE memory using single access write. See table 31 on page 47
    // of datasheet original value is 0xA9    
    m_cc2500.sendCommand(CC2500_REG_PATABLE, 0xFF);

    // SIDLE: exit RX/TX
    m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);

    // SIDLE: exit RX/TX
    m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);

    // SPWD: enter power down mode when CSn goes high
    m_cc2500.sendStrobeCommand(CC2500_CMD_SPWD);

    // SIDLE: exit RX/TX
    m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);
}

unsigned char LivingColors::getMaxNumLamps()
{
    return m_maxNumLamps;
}

unsigned char LivingColors::getNumLamps()
{
    return m_numLamps;
}

char LivingColors::addLamp(unsigned char* address)
{
    if (m_numLamps == m_maxNumLamps) {
        return -1;
    }

    // store address
    m_lamps[m_numLamps][0] = 1;

    for (int x=0; x<9; ++x) {
        m_lamps[m_numLamps][x+1] = address[x];
    }

    ++m_numLamps;

    return (m_numLamps - 1);
}

bool LivingColors::getLamp(unsigned char index, unsigned char* address)
{
    // check params
    if ((address != 0) && (index < m_numLamps) && (m_lamps[index][0] != 0)) {

        // fill address
        for (int x=0; x<9; ++x) {
            address[x] = m_lamps[index][x+1];
        }

        return true;
    }

    return false;
}

void LivingColors::learnLamps()
{
    // clear addresses
    clearLamps();

    // SIDLE: exit RX/TX
    m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);

    // read RX FIFO until empty
    unsigned char result = m_cc2500.sendCommand(0xFB, 0x00);

    for (int i=0; i<result; ++i) {
        m_cc2500.sendCommand(0xBF, 0x00);
    }

    unsigned long startTime = millis();

    // try learning addresses for 5 seconds
    while ((millis() - startTime) < 5000) {

        // SRX: enable RX
        m_cc2500.sendStrobeCommand(CC2500_CMD_SRX);

        // wait a bit
        delay(10);

        // read RXBYTES register, result should be 0x11
        result = m_cc2500.sendCommand(0xFB, 0x00);

        if (result >= 0x11) {
            // single access RX FIFO to get number of bytes to read, should be 0x0E
            result = m_cc2500.sendCommand(0xBF, 0x00);

            if (result == 0x0E) {
                unsigned char data[15];

                // read RX FIFO
                m_cc2500.sendBurstCommand(0xFF, data, result);

                // commands 0x03, 0x05 and 0x07 are send by remote
                if ((data[9] == 0x03) || (data[9] == 0x05) || (data[9] == 0x07)) {
                    checkAddress(data);
                }

                // read 2 remaining bytes
                m_cc2500.sendCommand(0xBF, 0x00);
                m_cc2500.sendCommand(0xBF, 0x00);
            } else {
                // something is not right, clear RX FIFO
                result = m_cc2500.sendCommand(0xFB, 0x00);

                for (int i=0; i<result; ++i) {
                    m_cc2500.sendCommand(0xBF, 0x00);
                }
            }
        }

        // SIDLE: exit RX/TX
        m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);

        delay(2);
    }

    // SIDLE: exit RX/TX
    m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);

    // read RXBYTES register, should be 0
    result = m_cc2500.sendCommand(0xFB, 0x00);

    for (int i=0; i<result; ++i) {
        m_cc2500.sendCommand(0xBF, 0x00);
    }
}

void LivingColors::clearLamps()
{
    // clear addresses
    for (int y=0; y<m_maxNumLamps; ++y) {
        for (int x=0; x<10; ++x) {
            m_lamps[y][x] = 0;
        }
    }

    m_numLamps = 0;
}

void LivingColors::setLampColourRGB(unsigned char index, unsigned char r, unsigned char g,
    unsigned char b)
{
    // convert rgb to hsv
    unsigned char h = 0;
    unsigned char s = 0;
    unsigned char v = 0;

    convertRGBtoHSV(r, g, b, h, s, v);

    sendCommand(index, 0x03, h, s, v);
}

void LivingColors::setLampColourHSV(unsigned char index, unsigned char h, unsigned char s,
    unsigned char v)
{
    sendCommand(index, 0x03, h, s, v);
}

void LivingColors::turnLampOnRGB(unsigned char index, unsigned char r, unsigned char g,
    unsigned char b)
{
    // convert rgb to hsv
    unsigned char h = 0;
    unsigned char s = 0;
    unsigned char v = 0;

    convertRGBtoHSV(r, g, b, h, s, v);

    sendCommand(index, 0x05, h, s, v);
}

void LivingColors::turnLampOnHSV(unsigned char index, unsigned char h, unsigned char s,
    unsigned char v)
{
    sendCommand(index, 0x05, h, s, v);
}

void LivingColors::turnLampOff(unsigned char index)
{
    sendCommand(index, 0x07, 0, 0, 0);
}

void LivingColors::checkAddress(unsigned char* address)
{
    // heuristic: it seems that a valid address ends with 0x11
    if (address[8] != 0x11) {
        return;
    }

    // check if address is known
    bool addressIsSame = true;

    for (int y=0; y<m_numLamps; ++y) {
        addressIsSame = true;

        if (m_lamps[y][0] == 0) {
            // uninitialized address, can never be the same
            addressIsSame = false;
        } else {
            // check all bytes of address
            for (int x=0; x<9; ++x) {
                if (address[x] != m_lamps[y][x+1]) {
                    addressIsSame = false;
                }
            }
        }

        // code was found, no need to store address
        if (addressIsSame) {
            return;
        }
    }

    // check for full storage
    if (m_numLamps == m_maxNumLamps) {
        // storage is full
        return;
    }

    // store address
    m_lamps[m_numLamps][0] = 1;

    for (int x=0; x<9; ++x) {
        m_lamps[m_numLamps][x+1] = address[x];
    }

    ++m_numLamps;
}

void LivingColors::sendCommand(unsigned char index, unsigned char command, unsigned char h,
    unsigned char s, unsigned char v)
{
    // index and address must be valid
    if ((index < m_numLamps) && (m_lamps[index][0] != 0)) {
        
        // wait for previous packet to be completely sent
        while ((m_cc2500.sendByte(0xF5) & 0x1F) > 1) {
        };

        // prepare burst data
        unsigned char data[15];

        // command
        data[0] = 0x0E;

        // lamp address
        for (int x=1; x<10; ++x) {
            data[x] = m_lamps[index][x];
        }

        // lamp command
        data[10] = command;

        // sequence
        data[11] = m_sequence++;

        // HSV
        data[12] = h;
        data[13] = s;
        data[14] = v;

        // SIDLE: exit RX/TX
        m_cc2500.sendStrobeCommand(CC2500_CMD_SIDLE);

        // fill TX FIFO
        m_cc2500.sendBurstCommand(0x7F, data, 15);

        // STX: enable TX
        m_cc2500.sendStrobeCommand(CC2500_CMD_STX);
    }
}
