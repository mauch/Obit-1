/* $Id$   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
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
/*  Define the basic components of the ObitTableRow structure       */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTablePCRowDef.h
 * ObitTablePCRow structure members for derived classes.
 */
#include "ObitTableRowDef.h"  /* Parent class definitions */
/** The center time. */
odouble  Time;
/** Source ID number */
oint  SourID;
/** Antenna number */
oint  antennaNo;
/** Array number */
oint  Array;
/** Frequency ID */
oint  FreqID;
/** CABLE_CAL */
odouble  CableCal;
/** State counts(?) */
ofloat*  State1;
/** Frequencies of the phase tones */
odouble*  PCFreq1;
/** Real part of tone phase */
odouble*  PCReal1;
/** Imaginary part of tone phase */
odouble*  PCImag1;
/** Tone rate phase */
odouble*  PCRate1;
/** State counts(?) */
ofloat*  State2;
/** Frequencies of the phase tones */
odouble*  PCFreq2;
/** Real part of tone phase */
odouble*  PCReal2;
/** Imaginary part of tone phase */
odouble*  PCImag2;
/** Tone rate phase */
odouble*  PCRate2;
/** status 0=normal, 1=modified, -1=flagged */
olong  status;