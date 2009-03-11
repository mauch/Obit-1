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
/*  Define the basic components of the ObitTableIDI_ARRAY_GEOMETRY  structure          */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTableIDI_ARRAY_GEOMETRYDef.h
 * ObitTableIDI_ARRAY_GEOMETRY structure members for derived classes.
 */
#include "ObitTableDef.h"  /* Parent class definitions */
/** Table format revision number */
oint  tabrev;
/** Number of Stokes parameters */
oint  no_stkd;
/** First Stokes parameter */
oint  stk_1;
/** Number of frequency bands (IF) */
oint  no_band;
/** Number of frequency channels */
oint  no_chan;
/** Reference frequency (Hz) */
odouble  ref_freq;
/** Channel bandwidth (Hz) */
odouble  chan_bw;
/** Reference frequency bin */
oint  ref_pixl;
/** Observation project code */
gchar  obscode[MAXKEYCHARTABLEIDI_ARRAY_GEOMETRY];
/** Array name */
gchar  ArrName[MAXKEYCHARTABLEIDI_ARRAY_GEOMETRY];
/** Reference date as "YYYY-MM-DD" */
gchar  RefDate[MAXKEYCHARTABLEIDI_ARRAY_GEOMETRY];
/** Coordinate system */
gchar  frame[MAXKEYCHARTABLEIDI_ARRAY_GEOMETRY];
/** Number of orbital parameters */
oint  numOrb;
/** Obs. Reference Frequency for subarray(Hz) */
odouble  Freq;
/** Time system, 'IAT' or 'UTC' */
gchar  TimeSys[MAXKEYCHARTABLEIDI_ARRAY_GEOMETRY];
/** GST at time=0 (degrees) on the reference date */
odouble  GSTiat0;
/** Earth rotation rate (deg/IAT day) */
odouble  DegDay;
/** UT1-UTC  (time sec.) */
ofloat  ut1Utc;
/** data time-UTC  (time sec.) */
ofloat  iatUtc;
/** Polar position X (meters) on ref. date */
ofloat  PolarX;
/** Polar position Y (meters) on ref. date */
ofloat  PolarY;
/** Array center X coord. (meters, earth center) */
odouble  ArrayX;
/** Array center Y coord. (meters, earth center) */
odouble  ArrayY;
/** Array center Z coord. (meters, earth center) */
odouble  ArrayZ;
/** Column offset for Station number, used as an index in other tables, uv data in table record */
olong  noStaOff;
/** Physical column number for Station number, used as an index in other tables, uv data in table record */
olong  noStaCol;
/** Column offset for Mount type, 0=altaz, 1=equatorial, 2=orbiting, 3=dipole in table record */
olong  mntStaOff;
/** Physical column number for Mount type, 0=altaz, 1=equatorial, 2=orbiting, 3=dipole in table record */
olong  mntStaCol;
/** Column offset for Station name in table record */
olong  AntNameOff;
/** Physical column number for Station name in table record */
olong  AntNameCol;
/** Column offset for X,Y,Z offset from array center in table record */
olong  StaXYZOff;
/** Physical column number for X,Y,Z offset from array center in table record */
olong  StaXYZCol;
/** Column offset for look this up in table record */
olong  derXYZOff;
/** Physical column number for look this up in table record */
olong  derXYZCol;
/** Column offset for Orbital parameters. in table record */
olong  OrbParmOff;
/** Physical column number for Orbital parameters. in table record */
olong  OrbParmCol;
/** Column offset for Axis offset (in 3D???) in table record */
olong  staXofOff;
/** Physical column number for Axis offset (in 3D???) in table record */
olong  staXofCol;