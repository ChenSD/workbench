#ifndef __GIFTIARRAYINDEXINGORDER_H__
#define __GIFTIARRAYINDEXINGORDER_H__

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


#include "GiftiException.h"

#include <stdint.h>
#include <vector>
#include <string>

namespace caret {

/**
 * Type for GIFTI Data Array ArrayIndexingOrder Attribute.
 */
class GiftiArrayIndexingOrder {

public:
    /**  Type for GIFTI Data Array ArrayIndexingOrder Attribute.
 */
    enum Enum {
        /** Column-Major Order (Fortran/Matlab)  */
        COLUMN_MAJOR_ORDER,
        /** Row-Major Order (C/C++/Java)  */
        ROW_MAJOR_ORDER
    };
    
    ~GiftiArrayIndexingOrder();

    static std::string toName(Enum e);
    
    static Enum fromName(const std::string& s, bool* isValidOut);
    
    static std::string toGiftiName(Enum e);
    
    static Enum fromGiftiName(const std::string& s, bool* isValidOut);
    

private:
    GiftiArrayIndexingOrder(const Enum e, 
                            const std::string& name,
                            const std::string& giftiName);

    static const GiftiArrayIndexingOrder* findData(const Enum e);
    
    static std::vector<GiftiArrayIndexingOrder> enumData;

    static void initialize();

    static bool initializedFlag;

    Enum e;

    std::string name;

    std::string giftiName;
};

#ifdef __GIFTIARRAYINDEXINGORDER_DECLARE__
std::vector<GiftiArrayIndexingOrder> GiftiArrayIndexingOrder::enumData;
bool GiftiArrayIndexingOrder::initializedFlag = false;
#endif // __GIFTIARRAYINDEXINGORDER_DECLARE__

} // namespace

#endif // __GIFTIARRAYINDEXINGORDER_H__
