/*LICENSE_START*/ 
/* 
 *  Copyright 1995-2002 Washington University School of Medicine 
 * 
 *  http://brainmap.wustl.edu 
 * 
 *  This file is part of CARET. 
 * 
 *  CARET is free software; you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation; either version 2 of the License, or 
 *  (at your option) any later version. 
 * 
 *  CARET is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 * 
 *  You should have received a copy of the GNU General Public License 
 *  along with CARET; if not, write to the Free Software 
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 * 
 */ 


#define __NIFTITIMEUNITS_DECLARE__
#include "NiftiTimeUnits.h"
#undef __NIFTITIMEUNITS_DECLARE__

#include <cassert>

using namespace caret;

/**
 * Constructor.
 *
 * @param e
 *    An enumerated value.
 * @param name
 *    Name of enumberated value.
 */
NiftiTimeUnits::NiftiTimeUnits(
                   const Enum e,
                   const int32_t integerCode,
                   const std::string& name)
{
    this->e = e;
    this->name = name;
}

/**
 * Destructor.
 */
NiftiTimeUnits::~NiftiTimeUnits()
{
}

void
NiftiTimeUnits::initializeTimeUnits()
{
    if (initializedFlag) {
        return;
    }
    initializedFlag = true;

    enumData.push_back(NiftiTimeUnits(NIFTI_UNITS_UNKNOWN, 0,"NIFTI_UNITS_UNKNOWN"));
    enumData.push_back(NiftiTimeUnits(NIFTI_UNITS_SEC, 8,"NIFTI_UNITS_SEC"));
    enumData.push_back(NiftiTimeUnits(NIFTI_UNITS_MSEC, 16,"NIFTI_UNITS_MSEC"));
    enumData.push_back(NiftiTimeUnits(NIFTI_UNITS_USEC, 24,"NIFTI_UNITS_USEC"));
    enumData.push_back(NiftiTimeUnits(NIFTI_UNITS_HZ, 32,"NIFTI_UNITS_HZ"));
    enumData.push_back(NiftiTimeUnits(NIFTI_UNITS_PPM, 40,"NIFTI_UNITS_PPM"));
}

/**
 * Find the data for and enumerated value.
 * @param e
 *     The enumerated value.
 * @return Pointer to data for this enumerated type
 * or NULL if no data for type or if type is invalid.
 */
const NiftiTimeUnits*
NiftiTimeUnits::findData(const Enum e)
{
    initializeTimeUnits();
    int64_t num = enumData.size();
    for (int64_t i = 0; i < num; i++) {
        const NiftiTimeUnits* d = &enumData[i];
        if (d->e == e) {
            return d;
        }
    }
    assert(0);

    return NULL;
}

/**
 * Get a string representation of the enumerated type.
 * @param e 
 *     Enumerated value.
 * @param isValidOut 
 *     If not NULL, it is set indicating that a
 *     label exists for the input enum value.
 * @return 
 *     String representing enumerated value.
 */
std::string 
NiftiTimeUnits::toName(Enum e) {
    initializeTimeUnits();
    
    const NiftiTimeUnits* ntu = findData(e);
    return ntu->name;
}

/**
 * Get an enumerated value corresponding to its name.
 * @param s 
 *     Name of enumerated value.
 * @param isValidOut 
 *     If not NULL, it is set indicating that a
 *     enum value exists for the input name.
 * @return 
 *     Enumerated value.
 */
NiftiTimeUnits::Enum 
NiftiTimeUnits::fromName(const std::string& s, bool* isValidOut)
{
    initializeTimeUnits();
    
    bool validFlag = false;
    Enum e;
    
    for (std::vector<NiftiTimeUnits>::iterator iter = enumData.begin();
         iter != enumData.end();
         iter++) {
        const NiftiTimeUnits& d = *iter;
        if (d.name == s) {
            e = d.e;
            validFlag = true;
            break;
        }
    }
    
    if (isValidOut != 0) {
        *isValidOut = validFlag;
    }
    return e;
}
/**
 * Get the integer code associated with an time units.
 * @param e
 *   The enum.
 * @return 
 *   Integer code associated with time units.
 */
int32_t 
NiftiTimeUnits::toIntegerCode(Enum e)
{
    initializeTimeUnits();
    const NiftiTimeUnits* nsu = findData(e);
    return nsu->integerCode;
}

/**
 * Find enum corresponding to integer code.
 * @param integerCode
 *    The integer code.
 * @param isValidOut
 *    If not NULL, on exit it indicates valid integer code.
 * @return
 *    Enum corresponding to integer code.
 */
NiftiTimeUnits::Enum 
NiftiTimeUnits::fromIntegerCode(const int32_t integerCode, bool* isValidOut)
{
    initializeTimeUnits();
    
    bool validFlag = false;
    Enum e;
    
    for (std::vector<NiftiTimeUnits>::const_iterator iter = enumData.begin();
         iter != enumData.end();
         iter++) {
        const NiftiTimeUnits& nsu = *iter;
        if (nsu.integerCode == integerCode) {
            e = nsu.e;
            validFlag = true;
            break;
        }
    }
    
    if (isValidOut != 0) {
        *isValidOut = validFlag;
    }
    return e;
}


