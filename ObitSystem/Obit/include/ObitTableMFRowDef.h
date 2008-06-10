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
 * \file ObitTableMFRowDef.h
 * ObitTableMFRow structure members for derived classes.
 */
#include "ObitTableRowDef.h"  /* Parent class definitions */
/** Plane number */
gfloat  plane;
/** Peak Ipol */
gfloat  Peak;
/** Integrated Ipol flux */
gfloat  IFlux;
/** X offset of center */
gfloat  DeltaX;
/** Y offset of center */
gfloat  DeltaY;
/** Fitted major axis size */
gfloat  MajorAx;
/** Fitted minor axis size */
gfloat  MinorAx;
/** Fitted PA */
gfloat  PosAngle;
/** Integrated Q flux density */
gfloat  QFlux;
/** Integrated U flux density */
gfloat  UFlux;
/** Integrated Y flux density */
gfloat  VFlux;
/** rror in Peak Ipol */
gfloat  errPeak;
/** rror in Integrated Ipol flux */
gfloat  errIFlux;
/** Error in X offset of center */
gfloat  errDeltaX;
/** Error in Y offset of center */
gfloat  errDeltaY;
/** Error in Fitted major axis size */
gfloat  errMajorAx;
/** Error in Fitted minor axis size */
gfloat  errMinorAx;
/** Error in Fitted PA */
gfloat  errPosAngle;
/** Error in Integrated Q flux density */
gfloat  errQFlux;
/** Error in Integrated U flux density */
gfloat  errUFlux;
/** Error in Integrated Y flux density */
gfloat  errVFlux;
/** Model type 1 = Gaussian */
gfloat  TypeMod;
/** Deconvolved best major axis */
gfloat  D0Major;
/** Deconvolved best minor axis */
gfloat  D0Minor;
/** Deconvolved best PA */
gfloat  D0PosAngle;
/** Deconvolved least major axis */
gfloat  DmMajor;
/** econvolved least minor axis */
gfloat  DmMinor;
/** Deconvolved least PA */
gfloat  DmPosAngle;
/** Deconvolved most major axis */
gfloat  DpMajor;
/** Deconvolved most minor axis */
gfloat  DpMinor;
/** Deconvolved most PA */
gfloat  DpPosAngle;
/** RMS of Ipol residual */
gfloat  ResRMS;
/** Peak in Ipol residual */
gfloat  ResPeak;
/** Integrated Ipol in residual */
gfloat  ResFlux;
/** Center x position in pixels */
gfloat  PixelCenterX;
/** Center y position in pixels */
gfloat  PixelCenterY;
/** Fitted major axis in pixels */
gfloat  PixelMajorAxis;
/** Fitted minor axis in pixels */
gfloat  PixelMinorAxis;
/** Fitted PA(?) */
gfloat  PixelPosAngle;
/** status 0=normal, 1=modified, -1=flagged */
olong  status;
