/* $Id$   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2013                                              */
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
/*;         Internet email: bcotton@nrao.edu.                         */
/*;         Postal address: William Cotton                            */
/*;                         National Radio Astronomy Observatory      */
/*;                         520 Edgemont Road                         */
/*;                         Charlottesville, VA 22903-2475 USA        */
/*--------------------------------------------------------------------*/
#ifndef OBITTABLEIDI_UV_DATA_H 
#define OBITTABLEIDI_UV_DATA_H 

#include "Obit.h"
#include "ObitErr.h"
#include "ObitTable.h"
#include "ObitData.h"

/*-------- Obit: Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitTableIDI_UV_DATA.h
 * ObitTableIDI_UV_DATA class definition.
 *
 * This class is derived from the #ObitTable class.
 *
 * This class contains tabular data and allows access.
 * This table is part of the IDI uv data format.
 * An IDI\_UV\_DATA table radio interferometer observational data.
 *
 * This class contains tabular data and allows access.
 * "IDI_UV_DATA" table
 * An ObitTableIDI_UV_DATA is the front end to a persistent disk resident structure.
 * Only FITS (as Tables) are supported.
 *
 * \section TableDataStorage Table data storage
 * In memory tables are stored in a fashion similar to how they are 
 * stored on disk - in large blocks in memory rather than structures.
 * Due to the word alignment requirements of some machines, they are 
 * stored by order of the decreasing element size: 
 * double, float long, int, short, char rather than the logical order.
 * The details of the storage in the buffer are kept in the 
 * #ObitTableIDI_UV_DATADesc.
 *
 * In addition to the normal tabular data, a table will have a "_status"
 * column to indicate the status of each row.
 *
 * \section ObitTableIDI_UV_DATASpecification Specifying desired data transfer parameters
 * The desired data transfers are specified in the member ObitInfoList.
 * In the following an ObitInfoList entry is defined by 
 * the name in double quotes, the data type code as an #ObitInfoType enum 
 * and the dimensions of the array (? => depends on application).
 *
 * The following apply to both types of files:
 * \li "nRowPIO", OBIT_int, Max. Number of visibilities per 
 *     "Read" or "Write" operation.  Default = 1.
 *
 * \subsection TableFITS FITS files
 * This implementation uses cfitsio which allows using, in addition to 
 * regular FITS images, gzip compressed files, pipes, shared memory 
 * and a number of other input forms.
 * The convenience Macro #ObitTableIDI_UV_DATASetFITS simplifies specifying the 
 * desired data.
 * Binary tables are used for storing visibility data in FITS.
 * For accessing FITS files the following entries in the ObitInfoList 
 * are used:
 * \li "FileName" OBIT_string (?,1,1) FITS file name.
 * \li "TabName"  OBIT_string (?,1,1) Table name (e.g. "AIPS CC").
 * \li "Ver"      OBIT_int    (1,1,1) Table version number
 *
 *
 * \section ObitTableIDI_UV_DATAaccess Creators and Destructors
 * An ObitTableIDI_UV_DATA can be created using newObitTableIDI_UV_DATAValue which attaches the 
 * table to an ObitData for the object.  
 * If the output ObitTableIDI_UV_DATA has previously been specified, including file information,
 * then ObitTableIDI_UV_DATACopy will copy the disk resident as well as the memory 
 * resident information.
 *
 * A copy of a pointer to an ObitTableIDI_UV_DATA should always be made using the
 * ObitTableIDI_UV_DATARef function which updates the reference count in the object.
 * Then whenever freeing an ObitTableIDI_UV_DATA or changing a pointer, the function
 * ObitTableIDI_UV_DATAUnref will decrement the reference count and destroy the object
 * when the reference count hits 0.
 *
 * \section ObitTableIDI_UV_DATAUsage I/O
 * Visibility data is available after an input object is "Opened"
 * and "Read".
 * I/O optionally uses a buffer attached to the ObitTableIDI_UV_DATA or some external
 * location.
 * To Write an ObitTableIDI_UV_DATA, create it, open it, and write.
 * The object should be closed to ensure all data is flushed to disk.
 * Deletion of an ObitTableIDI_UV_DATA after its final unreferencing will automatically
 * close it.
 */

/*--------------Class definitions-------------------------------------*/

/** Number of characters for Table keyword */
 #define MAXKEYCHARTABLEIDI_UV_DATA 24

/** ObitTableIDI_UV_DATA Class structure. */
typedef struct {
#include "ObitTableIDI_UV_DATADef.h"   /* this class definition */
} ObitTableIDI_UV_DATA;

/** ObitTableIDI_UV_DATARow Class structure. */
typedef struct {
#include "ObitTableIDI_UV_DATARowDef.h"   /* this class row definition */
} ObitTableIDI_UV_DATARow;

/*----------------- Macroes ---------------------------*/
/** 
 * Macro to unreference (and possibly destroy) an ObitTableIDI_UV_DATA
 * returns an ObitTableIDI_UV_DATA*.
 * in = object to unreference
 */
#define ObitTableIDI_UV_DATAUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableIDI_UV_DATA.
 * returns an ObitTableIDI_UV_DATA*.
 * in = object to reference
 */
#define ObitTableIDI_UV_DATARef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableIDI_UV_DATAIsA(in) ObitIsA (in, ObitTableIDI_UV_DATAGetClass())

/** 
 * Macro to unreference (and possibly destroy) an ObitTableIDI_UV_DATARow
 * returns an ObitTableIDI_UV_DATARow*.
 * in = object to unreference
 */
#define ObitTableIDI_UV_DATARowUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableIDI_UV_DATARow.
 * returns an ObitTableIDI_UV_DATARow*.
 * in = object to reference
 */
#define ObitTableIDI_UV_DATARowRef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableIDI_UV_DATARowIsA(in) ObitIsA (in, ObitTableIDI_UV_DATARowGetClass())

/*---------------Public functions---------------------------*/
/*----------------Table Row Functions ----------------------*/
/** Public: Row Class initializer. */
void ObitTableIDI_UV_DATARowClassInit (void);

/** Public: Constructor. */
ObitTableIDI_UV_DATARow* newObitTableIDI_UV_DATARow (ObitTableIDI_UV_DATA *table);

/** Public: ClassInfo pointer */
gconstpointer ObitTableIDI_UV_DATARowGetClass (void);

/*------------------Table Functions ------------------------*/
/** Public: Class initializer. */
void ObitTableIDI_UV_DATAClassInit (void);

/** Public: Constructor. */
ObitTableIDI_UV_DATA* newObitTableIDI_UV_DATA (gchar* name);

/** Public: Constructor from values. */
ObitTableIDI_UV_DATA* 
newObitTableIDI_UV_DATAValue (gchar* name, ObitData *file, olong *ver,
  		     ObitIOAccess access,
                     oint no_band, oint maxis1, oint maxis2, oint maxis3, oint maxis4, oint maxis5,
		     ObitErr *err);

/** Public: Class initializer. */
void ObitTableIDI_UV_DATAClassInit (void);

/** Public: ClassInfo pointer */
gconstpointer ObitTableIDI_UV_DATAGetClass (void);

/** Public: Copy (deep) constructor. */
ObitTableIDI_UV_DATA* ObitTableIDI_UV_DATACopy  (ObitTableIDI_UV_DATA *in, ObitTableIDI_UV_DATA *out, 
			   ObitErr *err);

/** Public: Copy (shallow) constructor. */
ObitTableIDI_UV_DATA* ObitTableIDI_UV_DATAClone (ObitTableIDI_UV_DATA *in, ObitTableIDI_UV_DATA *out);

/** Public: Convert an ObitTable to an ObitTableIDI_UV_DATA */
ObitTableIDI_UV_DATA* ObitTableIDI_UV_DATAConvert  (ObitTable *in);

/** Public: Create ObitIO structures and open file */
ObitIOCode ObitTableIDI_UV_DATAOpen (ObitTableIDI_UV_DATA *in, ObitIOAccess access, 
			  ObitErr *err);

/** Public: Read a table row */
ObitIOCode 
ObitTableIDI_UV_DATAReadRow  (ObitTableIDI_UV_DATA *in, olong iIDI_UV_DATARow, ObitTableIDI_UV_DATARow *row,
		     ObitErr *err);

/** Public: Init a table row for write */
void 
ObitTableIDI_UV_DATASetRow  (ObitTableIDI_UV_DATA *in, ObitTableIDI_UV_DATARow *row,
		     ObitErr *err);

/** Public: Write a table row */
ObitIOCode 
ObitTableIDI_UV_DATAWriteRow  (ObitTableIDI_UV_DATA *in, olong iIDI_UV_DATARow, ObitTableIDI_UV_DATARow *row,
		     ObitErr *err);

/** Public: Close file and become inactive */
ObitIOCode ObitTableIDI_UV_DATAClose (ObitTableIDI_UV_DATA *in, ObitErr *err);

/*----------- ClassInfo Structure -----------------------------------*/
/**
 * ClassInfo Structure.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableIDI_UV_DATAClassDef.h"
} ObitTableIDI_UV_DATAClassInfo; 

/**
 * ClassInfo Structure For TableIDI_UV_DATARow.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableIDI_UV_DATARowClassDef.h"
} ObitTableIDI_UV_DATARowClassInfo; 
#endif /* OBITTABLEIDI_UV_DATA_H */ 
