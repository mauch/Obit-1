/* $Id$  */  
/*--------------------------------------------------------------------*/
/* Swig module description celestial geometry utilities               */
/*                                                                    */
/*;  Copyright (C) 2007-2019                                          */
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

%{
#include "ObitSkyGeom.h"
#include "ObitPBUtil.h"
%}



%inline %{

/** Public: Determine shift between two positions */
void SkyGeomShiftXY (double ra, double dec, float rotate,
			double shiftRA, double shiftDec,
			float* outFlt1, float* outFlt2) {
  ObitSkyGeomShiftXY ((odouble)ra, (odouble)dec, (ofloat)rotate,
		     (odouble)shiftRA, (odouble)shiftDec,
		      outFlt1, outFlt2);
}

/** Public: Determine result of a shift to a position */
void SkyGeomXYShift (double ra, double dec, 
			float xShift, float yShift, float rotate,
			double* outDbl1, double* outDbl2) {
  ObitSkyGeomXYShift ((odouble)ra, (odouble)dec, 
		     (ofloat)xShift, (ofloat)yShift, (ofloat)rotate,
                      outDbl1, outDbl2);
}

/** Public: Determine coefficients of a 3D SIN projection shift, return list of floats */
extern PyObject* SkyGeomShiftSIN (double ra, double dec, float rotate, double xra, double xdec) {
  ofloat dxyzc[3];
  PyObject *outList, *o;
  ObitSkyGeomShiftSIN ((odouble)ra, (odouble)dec, (ofloat)rotate, (odouble)xra, (odouble)xdec, 
		     dxyzc);
  outList = PyList_New(3);
  o = PyFloat_FromDouble((double)dxyzc[0]);
  PyList_SetItem(outList, 0, o);
  o = PyFloat_FromDouble((double)dxyzc[1]);
  PyList_SetItem(outList, 1, o);
  o = PyFloat_FromDouble((double)dxyzc[2]);
  PyList_SetItem(outList, 2, o);
  return outList;
}

/** Public: Determine coefficients of a 3D NCP projection shift, return list of floats */
extern PyObject* SkyGeomShiftNCP (double ra, double dec, float rotate, double xra, double xdec) {
  ofloat dxyzc[3];
  PyObject *outList, *o;
  ObitSkyGeomShiftNCP ((odouble)ra, (odouble)dec, (ofloat)rotate, (odouble)xra, (odouble)xdec, 
		     dxyzc);
  outList = PyList_New(3);
  o = PyFloat_FromDouble((double)dxyzc[0]);
  PyList_SetItem(outList, 0, o);
  o = PyFloat_FromDouble((double)dxyzc[1]);
  PyList_SetItem(outList, 1, o);
  o = PyFloat_FromDouble((double)dxyzc[2]);
  PyList_SetItem(outList, 2, o);
  return outList;
}

/** Public: Returns astronomical coordinates given direction cosines, projection */
void 
SkyGeomNewPos (char *type, double ra0, double dec0, double l, double m, 
		   double* outDbl1, double* outDbl2, long* outLong1) {
  olong ierr;
  ObitSkyGeomProj Proj = OBIT_SkyGeom_SIN;
  /* Projection type */
  if (!strncmp (type, "-TAN", 4)) Proj = OBIT_SkyGeom_TAN;
  if (!strncmp (type, "-ARC", 4)) Proj = OBIT_SkyGeom_ARC;
  if (!strncmp (type, "-NCP", 4)) Proj = OBIT_SkyGeom_NCP;
  if (!strncmp (type, "-GLS", 4)) Proj = OBIT_SkyGeom_GLS;
  if (!strncmp (type, "-MER", 4)) Proj = OBIT_SkyGeom_MER;
  if (!strncmp (type, "-AIT", 4)) Proj = OBIT_SkyGeom_AIT;
  if (!strncmp (type, "-STG", 4)) Proj = OBIT_SkyGeom_STG;
  ObitSkyGeomNewPos (Proj, (odouble)ra0, (odouble)dec0, (odouble)l, (odouble)m, 
		     outDbl1, outDbl2, &ierr);
  *outLong1 = (long)ierr;
}

/** Public: accurate position for pixel coordinates */
long 
SkyGeomWorldPos(float xpix, float ypix, double xref, double yref, 
		    float xrefpix, float yrefpix, float xinc, float yinc, 
		    float rot, char *type, double *outDbl1, double *outDbl2) {
  return (long)ObitSkyGeomWorldPos((ofloat)xpix, (ofloat)ypix, (odouble)xref, (odouble)yref, 
		    (ofloat)xrefpix, (ofloat)yrefpix, (ofloat)xinc, (ofloat)yinc, 
		    (ofloat)rot, (gchar*)type, outDbl1, outDbl2);
}

/** Public: Position for pixel coordinates from IRAF style CD matrix */
long 
SkyGeomCDpos(float xpix, float ypix, double xref, double yref,
		 float xrefpix, float yrefpix, float xinc, float yinc, float rot,
		 float cd1[2], float cd2[2], char *type, double *outDbl1, double *outDbl2) {
  ofloat lcd1[2], lcd2[2];
  lcd1[0] = cd1[0];
  lcd1[1] = cd1[1];
  lcd2[0] = cd2[0];
  lcd2[1] = cd2[1];
  return (long)ObitSkyGeomCDpos((ofloat)xpix, (ofloat)ypix, (odouble)xref, (odouble)yref,
		 (ofloat)xrefpix, (ofloat)yrefpix, (ofloat)xinc, (ofloat)yinc, (ofloat)rot,
		 lcd1, lcd2, (gchar*)type, outDbl1, outDbl2);
}

/** Public: Pixel coordinates for an RA and Dec*/
long 
SkyGeomXYpix(double xpos, double ypos, double xref, double yref, 
		 float xrefpix, float yrefpix, float xinc, float yinc, 
		 float rot, char *type, float *outFlt1, float *outFlt2){
  return (long)ObitSkyGeomXYpix((odouble)xpos, (odouble)ypos, (odouble)xref, (odouble)yref, 
		 (ofloat)xrefpix, (ofloat)yrefpix, (ofloat)xinc, (ofloat)yinc, 
		 (ofloat)rot, (gchar*)type, outFlt1, outFlt2);
}

/** Public:pixel coordinates for an RA and Dec from IRAF  style CD matrix. */
long 
SkyGeomCDpix(double xpos, double ypos, double xref, double yref, 
		 float xrefpix, float yrefpix, float xinc, float yinc, float rot,
		 float icd1[2], float icd2[2], char *type, 
	 	 float *outFlt1, float *outFlt2) {
  ofloat licd1[2], licd2[2];
  licd1[0] = icd1[0];
  licd1[1] = icd1[1];
  licd2[0] = icd2[0];
  licd2[1] = icd2[1];
  return (long)ObitSkyGeomCDpix((odouble)xpos, (odouble)ypos, (odouble)xref, (odouble)yref, 
		 (ofloat)xrefpix, (ofloat)yrefpix, (ofloat)xinc, (ofloat)yinc, (ofloat)rot,
		 licd1, licd2, (gchar*)type, outFlt1, outFlt2);
}

/** Public: Position for pixel coordinates from  offsets from the reference position.*/
long 
SkyGeomWorldPosLM(double dx, double dy, double xref, double yref, 
		      float xinc, float yinc, float rot, char *type, 
		      double *outDbl1, double *outDbl2) {
  return (long)ObitSkyGeomWorldPosLM((odouble)dx, (odouble)dy, (odouble)xref, (odouble)yref, 
		      (ofloat)xinc, (ofloat)yinc, (ofloat)rot, (gchar*)type, 
		      outDbl1, outDbl2);
}

/** Public: Coordinate offsets for an RA and Dec   */
long
SkyGeomXYPixLM(double xpos, double ypos, double xref, double yref, 
		   float xinc, float yinc, float rot, char *type, 
		   double *outDbl1, double *outDbl2) {
  return (long)ObitSkyGeomXYPixLM((odouble)xpos, (odouble)ypos, (odouble)xref, (odouble)yref, 
		   (ofloat)xinc, (ofloat)yinc, (ofloat)rot, (gchar*)type, 
		    outDbl1, outDbl2);
}

/** Public: Precess B1950 to J2000 coordinates  */
void 
SkyGeomBtoJ (double *outDbl1, double *outDbl2) {
  ObitSkyGeomBtoJ (outDbl1, outDbl2);
}

/** Public: Precess J2000 to B1950 coordinates */
void 
SkyGeomJtoB (double *outDbl1, double *outDbl2) {
  ObitSkyGeomJtoB (outDbl1, outDbl2);
}

/** Public: Convert Equatorial (B1950) to Galactic coordinates  */
void SkyGeomEq2Gal (double *outDbl1, double *outDbl2) {
  ObitSkyGeomEq2Gal (outDbl1, outDbl2);
}

/** Public: Convert Galactic to Equatorial (B1950)  */
void SkyGeomGal2Eq (double *outDbl1, double *outDbl2) {
  ObitSkyGeomGal2Eq (outDbl1, outDbl2);
}

/** Public: Convert Equatorial to Ecliptic coordinates */
void SkyGeomEq2Ec (double *outDbl1, double *outDbl2, float epoch){
  ObitSkyGeomEq2Ec (outDbl1, outDbl2, (ofloat)epoch);
}

/** Public: Convert Ecliptic to Equatorial */
void SkyGeomEc2Eq (double *outDbl1, double *outDbl2, float epoch) {
  ObitSkyGeomEc2Eq (outDbl1, outDbl2, (ofloat)epoch);
}

/** Public: Projection to Zernike plane */
void SkyGeomRADec2Zern (double ra, double dec, float xshift, float yshift, 
			    float* outFlt1, float* outFlt2, long *outLong1) {
			    olong ierr;
  ObitSkyGeomRADec2Zern ((odouble)ra, (odouble)dec, (ofloat)xshift, (ofloat)yshift, 
			    outFlt1, outFlt2, &ierr);
  *outLong1 = (long)ierr;
}

/** Public: Compute VLA beam shape from a fitted polynomial */
float PBUtilPoly (double Angle, double Freq, float pbmin) {
  ofloat out;
  out = ObitPBUtilPoly ((odouble)Angle, (odouble)Freq, (ofloat)pbmin);
  return (float)out;
}

/** Public: Compute kat-7 beam shape from a fitted polynomial */
float PBUtilKAT7 (double Angle, double Freq, float pbmin) {
  ofloat out;
  out = ObitPBUtilKAT7 ((odouble)Angle, (odouble)Freq, (ofloat)pbmin);
  return (float)out;
}

/** Public:  Compute Antenna beam assuming uniform illumination of an antenna */
float PBUtilJinc (double Angle, double Freq, float antSize, float pbmin) {
  ofloat out;
  out = ObitPBUtilJinc ((odouble)Angle, (odouble)Freq, (ofloat)antSize, (ofloat)pbmin);
  return (float)out;
}

/** Public:  Calculates the relative gain at a reference frequency */
float PBUtilRelPB (double Angle, long nfreq, double *Freq, float antSize, 
                   float pbmin, double refFreq) {
  ofloat out;
  out = (float)ObitPBUtilRelPB ((odouble)Angle, (olong)nfreq, (odouble*)Freq, 
        (ofloat)antSize, (ofloat)pbmin, (odouble)refFreq);
  return (float)out;
}

%}
