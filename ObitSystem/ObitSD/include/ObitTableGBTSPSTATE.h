/* $Id$  */
/* DO NOT EDIT - file generated by ObitSDTables.pl                    */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2008                                              */
/*;  Associated Universities, Inc. Washington DC, USA.                */
/*;                                                                   */
/*;  This program is free software; you can redistribute it and/or    */
/*;  modify it under the terms of the GNU General Public License as   */
/*;  published by the Free Software Foundation; either version 2 of   */
/*;  the License, or (at your option) any later version.              */
/*;                                                                   */
/*;  This program is distributed in the hope that it will be useful,  */
/*;  but WITHOUT ANY WARRANTY; without even the implied warranty of   */
/*;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    */
/*;  GNU General Public License for more details.                     */
/*;                                                                   */
/*;  You should have received a copy of the GNU General Public        */
/*;  License along with this program; if not, write to the Free       */
/*;  Software Foundation, Inc., 675 Massachusetts Ave, Cambridge,     */
/*;  MA 02139, USA.                                                   */
/*;                                                                   */
/*;Correspondence about this software should be addressed as follows: */
/*;         Internet email: bcotton@nrao.edu.                        */
/*;         Postal address: William Cotton                            */
/*;                         National Radio Astronomy Observatory      */
/*;                         520 Edgemont Road                         */
/*;                         Charlottesville, VA 22903-2475 USA        */
/*--------------------------------------------------------------------*/
#ifndef ObitTableGBTSPSTATE_H 
#define ObitTableGBTSPSTATE_H 

#include "Obit.h"
#include "ObitErr.h"
#include "ObitTable.h"
#include "ObitData.h"

/*-------- Obit: Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitTableGBTSPSTATE.h
 * ObitTableGBTSPSTATE class definition.
 *
 * Table in GBT archive/SpectralProcessor file.
 * This class contains tabular data and allows access.
 * This class is derived from the ObitTable class. 
 *
 * This class contains tabular data and allows access.
 * ObitTableGBTSPSTATE" 
 * An ObitTableGBTSPSTATE is the front end to a persistent disk resident structure.
 * This class is derived from the ObitTable class.
 *
 * \section TableDataStorage Table data storage
 * In memory tables are stored in a fashion similar to how they are 
 * stored on disk - in large blocks in memory rather than structures.
 * Due to the word alignment requirements of some machines, they are 
 * stored by order of the decreasing element size: 
 * double, float long, int, short, char rather than the logical order.
 * The details of the storage in the buffer are kept in the 
 * #ObitTableGBTSPSTATEDesc.
 *
 * In addition to the normal tabular data, a table will have a "_status"
 * column to indicate the status of each row.
 * The status value is read from and written to (some modification) AIPS 
 * tables but are not written to externally generated FITS tables which
 * don't have these colummns.  It will be written to Obit generated tables
 * which will have these columns.
 * Status values:
 * \li status = 0 => normal
 * \li status = 1 => row has been modified (or created) and needs to be
 *                   written.
 * \li status = -1 => row has been marked invalid.
 *
 * \section ObitTableGBTSPSTATESpecification Specifying desired data transfer parameters
 * The desired data transfers are specified in the member ObitInfoList.
 * There are separate sets of parameters used to specify the FITS 
 * data files.
 * In the following an ObitInfoList entry is defined by 
 * the name in double quotes, the data type code as an #ObitInfoType enum 
 * and the dimensions of the array (? => depends on application).
 * To specify whether the underlying data files are FITS
 * \li "FileType" OBIT_int (1,1,1) OBIT_IO_FITS 
 * which are values of an #ObitIOType enum defined in ObitIO.h.
 *
 * The following apply to both types of files:
 * \li "nRowPIO", OBIT_int, Max. Number of visibilities per 
 *     "Read" or "Write" operation.  Default = 1.
 *
 * \subsection TableFITS FITS files
 * This implementation uses cfitsio which allows using, in addition to 
 * regular FITS images, gzip compressed files, pipes, shared memory 
 * and a number of other input forms.
 * The convenience Macro #ObitTableGBTSPSTATESetFITS simplifies specifying the 
 * desired data.
 * Binary tables are used for storing visibility data in FITS.
 * For accessing FITS files the following entries in the ObitInfoList 
 * are used:
 * \li "FileName" OBIT_string (?,1,1) FITS file name.
 * \li "TabName"  OBIT_string (?,1,1) Table name (e.g. "AIPS CC").
 * \li "Ver"      OBIT_int    (1,1,1) Table version number
 *
 *
 * \section ObitTableGBTSPSTATEaccess Creators and Destructors
 * An ObitTableGBTSPSTATE can be created using newObitTableGBTSPSTATEValue which attaches the 
 * table to an ObitData for the object.  
 * If the output ObitTableGBTSPSTATE has previously been specified, including file information,
 * then ObitTableGBTSPSTATECopy will copy the disk resident as well as the memory 
 * resident information.
 *
 * A copy of a pointer to an ObitTableGBTSPSTATE should always be made using the
 * ObitTableGBTSPSTATERef function which updates the reference count in the object.
 * Then whenever freeing an ObitTableGBTSPSTATE or changing a pointer, the function
 * ObitTableGBTSPSTATEUnref will decrement the reference count and destroy the object
 * when the reference count hits 0.
 *
 * \section ObitTableGBTSPSTATEUsage I/O
 * Visibility data is available after an input object is "Opened"
 * and "Read".
 * I/O optionally uses a buffer attached to the ObitTableGBTSPSTATE or some external
 * location.
 * To Write an ObitTableGBTSPSTATE, create it, open it, and write.
 * The object should be closed to ensure all data is flushed to disk.
 * Deletion of an ObitTableGBTSPSTATE after its final unreferencing will automatically
 * close it.
 */

/*--------------Class definitions-------------------------------------*/

/** Number of characters for Table keyword */
 #define MAXKEYCHARTABLESTATE 24

/** ObitTableGBTSPSTATE Class structure. */
typedef struct {
#include "ObitTableGBTSPSTATEDef.h"   /* this class definition */
} ObitTableGBTSPSTATE;

/** ObitTableGBTSPSTATERow Class structure. */
typedef struct {
#include "ObitTableGBTSPSTATERowDef.h"   /* this class row definition */
} ObitTableGBTSPSTATERow;

/*----------------- Macroes ---------------------------*/
/** 
 * Macro to unreference (and possibly destroy) an ObitTableGBTSPSTATE
 * returns an ObitTableGBTSPSTATE*.
 * in = object to unreference
 */
#define ObitTableGBTSPSTATEUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableGBTSPSTATE.
 * returns an ObitTableGBTSPSTATE*.
 * in = object to reference
 */
#define ObitTableGBTSPSTATERef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableGBTSPSTATEIsA(in) ObitIsA (in, ObitTableGBTSPSTATEGetClass())

/** 
 * Macro to unreference (and possibly destroy) an ObitTableGBTSPSTATERow
 * returns an ObitTableGBTSPSTATERow*.
 * in = object to unreference
 */
#define ObitTableGBTSPSTATERowUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableGBTSPSTATERow.
 * returns an ObitTableGBTSPSTATERow*.
 * in = object to reference
 */
#define ObitTableGBTSPSTATERowRef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableGBTSPSTATERowIsA(in) ObitIsA (in, ObitTableGBTSPSTATERowGetClass())

/*---------------Public functions---------------------------*/
/*----------------Table Row Functions ----------------------*/
/** Public: Row Class initializer. */
void ObitTableGBTSPSTATERowClassInit (void);

/** Public: Constructor. */
ObitTableGBTSPSTATERow* newObitTableGBTSPSTATERow (ObitTableGBTSPSTATE *table);

/** Public: ClassInfo pointer */
gconstpointer ObitTableGBTSPSTATERowGetClass (void);

/*------------------Table Functions ------------------------*/
/** Public: Class initializer. */
void ObitTableGBTSPSTATEClassInit (void);

/** Public: Constructor. */
ObitTableGBTSPSTATE* newObitTableGBTSPSTATE (gchar* name);

/** Public: Constructor from values. */
ObitTableGBTSPSTATE* 
newObitTableGBTSPSTATEValue (gchar* name, ObitData *file, olong *ver,
  		     ObitIOAccess access,
                    
		     ObitErr *err);

/** Public: ClassInfo pointer */
gconstpointer ObitTableGBTSPSTATEGetClass (void);

/** Public: Copy (deep) constructor. */
ObitTableGBTSPSTATE* ObitTableGBTSPSTATECopy  (ObitTableGBTSPSTATE *in, ObitTableGBTSPSTATE *out, 
			   ObitErr *err);

/** Public: Copy (shallow) constructor. */
ObitTableGBTSPSTATE* ObitTableGBTSPSTATEClone (ObitTableGBTSPSTATE *in, ObitTableGBTSPSTATE *out);

/** Public: Convert an ObitTable to an ObitTableGBTSPSTATE */
ObitTableGBTSPSTATE* ObitTableGBTSPSTATEConvert  (ObitTable *in);

/** Public: Create ObitIO structures and open file */
ObitIOCode ObitTableGBTSPSTATEOpen (ObitTableGBTSPSTATE *in, ObitIOAccess access, 
			  ObitErr *err);

/** Public: Read a table row */
ObitIOCode 
ObitTableGBTSPSTATEReadRow  (ObitTableGBTSPSTATE *in, olong iSTATERow, ObitTableGBTSPSTATERow *row,
		     ObitErr *err);

/** Public: Init a table row for write */
void 
ObitTableGBTSPSTATESetRow  (ObitTableGBTSPSTATE *in, ObitTableGBTSPSTATERow *row,
		     ObitErr *err);

/** Public: Write a table row */
ObitIOCode 
ObitTableGBTSPSTATEWriteRow  (ObitTableGBTSPSTATE *in, olong iSTATERow, ObitTableGBTSPSTATERow *row,
		     ObitErr *err);

/** Public: Close file and become inactive */
ObitIOCode ObitTableGBTSPSTATEClose (ObitTableGBTSPSTATE *in, ObitErr *err);

/*----------- ClassInfo Structure -----------------------------------*/
/**
 * ClassInfo Structure.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableGBTSPSTATEClassDef.h"
} ObitTableGBTSPSTATEClassInfo; 

/**
 * ClassInfo Structure For TableObitTableGBTSPSTATERow.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableGBTSPSTATERowClassDef.h"
} ObitTableGBTSPSTATERowClassInfo; 
#endif /* ObitTableGBTSPSTATE_H */ 
