/* $Id$  */
/*--------------------------------------------------------------------*/
/*;  Copyright (C) 2006-2008                                          */
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

#include "ObitTableCCUtil.h"
#include "ObitSkyModelVMIon.h"
#include "ObitSkyGeom.h"
#include "ObitUVUtil.h"
#include "ObitPBUtil.h"
#include "ObitMem.h"
#include "ObitZernike.h"

/*----------------Obit: Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitSkyModelVMIon.c
 * ObitSkyModelVMIon class function definitions.
 *
 * This class is derived from the #ObitSkyModelVM class.
 *
 * This class represents sky models incorporating ionospheric phase models and 
 * their Fourier transforms.
 */

/** name of the class defined in this file */
static gchar *myClassName = "ObitSkyModelVMIon";

/** Function to obtain parent ClassInfo - Obit */
static ObitGetClassFP ObitParentGetClass = ObitSkyModelVMGetClass;

/**
 * ClassInfo structure ObitSkyModelVMIonClassInfo.
 * This structure is used by class objects to access class functions.
 */
static ObitSkyModelVMIonClassInfo myClassInfo = {FALSE};

/*---------------Private function prototypes----------------*/

/** Private: Initialize newly instantiated object. */
void  ObitSkyModelVMIonInit  (gpointer in);

/** Private: Deallocate members. */
void  ObitSkyModelVMIonClear (gpointer in);

/** Private: Set Class function pointers. */
static void ObitSkyModelVMIonClassInfoDefFn (gpointer inClass);

/** Private: Get Inputs. */
void  ObitSkyModelVMIonGetInput (ObitSkyModel* inn, ObitErr *err);

/*----------------------Public functions---------------------------*/
/**
 * Constructor.
 * Initializes class if needed on first call.
 * \param name An optional name for the object.
 * \return the new object.
 */
ObitSkyModelVMIon* newObitSkyModelVMIon (gchar* name)
{
  ObitSkyModelVMIon* out;

  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitSkyModelVMIonClassInit();

  /* allocate/init structure */
  out = g_malloc0(sizeof(ObitSkyModelVMIon));

  /* initialize values */
  if (name!=NULL) out->name = g_strdup(name);
  else out->name = g_strdup("Noname");

  /* set ClassInfo */
  out->ClassInfo = (gpointer)&myClassInfo;

  /* initialize other stuff */
  ObitSkyModelVMIonInit((gpointer)out);

 return out;
} /* end newObitSkyModelVMIon */

/**
 * Returns ClassInfo pointer for the class.
 * \return pointer to the class structure.
 */
gconstpointer ObitSkyModelVMIonGetClass (void)
{
  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitSkyModelVMIonClassInit();

  return (gconstpointer)&myClassInfo;
} /* end ObitSkyModelVMIonGetClass */

/**
 * Make a deep copy of an ObitSkyModelVMIon.
 * \param in  The object to copy
 * \param out An existing object pointer for output or NULL if none exists.
 * \param err Obit error stack object.
 * \return pointer to the new object.
 */
ObitSkyModelVMIon* ObitSkyModelVMIonCopy  (ObitSkyModelVMIon *in, 
					   ObitSkyModelVMIon *out, ObitErr *err)
{
  const ObitClassInfo *ParentClass;
  /*gchar *routine = "ObitSkyModelVMCopy";*/

  /* Copy any base class members */
  ParentClass = myClassInfo.ParentClass;
  g_assert ((ParentClass!=NULL) && (ParentClass->ObitCopy!=NULL) && 
	    /* Don't call yourself */
	    (ParentClass!=(const ObitClassInfo*)&myClassInfo));
  out = ParentClass->ObitCopy (in, out, err);


  return out;
} /* end ObitSkyModelVMIonCopy */

/**
 * Creates an ObitSkyModelVMIon 
 * \param name  An optional name for the object.
 * \param mosaic ObitImageMosaic giving one or more images/CC tables
 * \return the new object.
 */
ObitSkyModelVMIon* ObitSkyModelVMIonCreate (gchar* name, ObitImageMosaic* mosaic)
{
  ObitSkyModelVMIon* out;
  olong number, i;

  /* Create basic structure */
  out = newObitSkyModelVMIon (name);

  /* Modify for input mosaic */
  out->mosaic = ObitImageMosaicRef(mosaic);
  if ((out->mosaic) && (out->mosaic->numberImages>0)) {
    number = out->mosaic->numberImages;
    out->CCver = ObitMemRealloc (out->CCver, sizeof(olong)*number);
    for (i=0; i<number; i++) out->CCver[i] = 0;
    out->startComp = ObitMemRealloc (out->startComp, sizeof(olong)*number);
    out->endComp = ObitMemRealloc (out->endComp, sizeof(olong)*number);
    for (i=0; i<number; i++) out->startComp[i] = 1;
    for (i=0; i<number; i++) out->endComp[i] = 0;
  }

  return out;
} /* end ObitSkyModelVMIonCreate */

/**
 * Initializes Sky Model
 * Keeps coordinate conversions to convert position offsets to the 
 * projection used to calculate phases.
 * \li fieldIndex index in field based tables for a given field (0-rel)
 * \li uRotTab  Table of rotation matrices for components 6 needed per row (field)
 *              Only fields with actual components are included
 * \li ZernX    Table of Zernike X gradient terms per field
 * \li ZernY    Table of Zernike Y gradient terms per field
 * \li do3D     if true need 3D rotation 
 * \li ccrot, ssrot = cosine, sine of rotation difference between uv, image
 * \param inn  SkyModel to initialize
 * \param uvdata  uv data being modeled.
 * \param err Obit error stack object.
 */
void ObitSkyModelVMIonInitMod (ObitSkyModel* inn, ObitUV *uvdata, ObitErr *err)
{
  ObitSkyModelVMIon *in = (ObitSkyModelVMIon*)inn;
  olong field, ndim, naxis[2], ver, i, count;
  olong ierr, ncoef=5;
  ObitImageDesc *imDesc=NULL;
  ObitUVDesc *uvDesc=NULL;
  ofloat maprot, uvrot, *rotTable, *XTable, *YTable;
  ofloat umat[3][3], pmat[3][3], shift[2], ZernXY[2];
  ObitInfoType type;
  gint32 dim[MAXINFOELEMDIM];
  odouble raPnt, decPnt;
  gchar *routine = "ObitSkyModelVMIonInitMod";

  /* Call parent initializer */
  ObitSkyModelVMInitMod(inn, uvdata, err);
  if (err->error) Obit_traceback_msg (err, routine, in->name);

  /* Uv descriptor */
  uvDesc = uvdata->myDesc;
  imDesc = in->mosaic->images[0]->myDesc; /* Image descriptor */
  /* different rotation in image and uv */
  maprot = ObitImageDescRotate(imDesc);
  uvrot  = ObitUVDescRotate(uvDesc);
  in->ssrot = sin (DG2RAD * (uvrot - maprot));
  in->ccrot = cos (DG2RAD * (uvrot - maprot));

  /* index array for fields */
  if (in->fieldIndex) g_free(in->fieldIndex); in->fieldIndex = NULL;
  in->fieldIndex = g_malloc0(in->mosaic->numberImages*sizeof(olong));

  /* Is a point model being used? */
  if ((in->pointFlux!=0.0) && (in->mosaic->numberImages <= 1)) {
    /* Use point model */
    count = 1;
    in->fieldIndex[0] = 0;
    in->startComp[0] = 1;
    in->endComp[0]   = 1;
  } else { /* Use CC tables */
    
    /* Count fields with components to model */
    count = 0;
    for (field = 0; field<in->mosaic->numberImages; field++) {
      in->fieldIndex[field] = -1;
      /* Anything to do in this field? */
      if ((in->endComp[field]>0) && 
	  (in->endComp[field]>=in->startComp[field])) {
	in->fieldIndex[field] = count;
	count++;  /* Count fields with actual components */
	/* Diagnostic message */
	if (in->prtLv>2) {
	  Obit_log_error(err, OBIT_InfoErr, 
			 "%s: field %d process components %d - %d factor %g minFlux %g",
			 routine, field+1, in->startComp[field],  
			 in->endComp[field], in->factor, in->minFlux);
	  ObitErrLog(err); 
	}
      }
    }
  }

  /* Create arrays with one row per field with components to process,
   rows are indexed by fieldIndex */
  ndim = 2;
  /* Create array for storing rotations */
  naxis[0] = 6; naxis[1] = count;
  in->uRotTab = ObitFArrayCreate("Rotation table", ndim, naxis);

  /* Loop over fields */
  count = 0;
  for (field = 0; field<in->mosaic->numberImages; field++) {
    /* Anything to do in this field? */
    if ((in->endComp[field]>0) && 
	(in->endComp[field]>=in->startComp[field])) {
      count++;  /* Count fields with actual components */
      
      imDesc = in->mosaic->images[field]->myDesc; /* Image descriptor */

      /* rotation matrices */
      if (in->pointFlux==0.0) /* use image */
	in->do3Dmul = ObitUVDescShift3DMatrix (uvDesc, imDesc, umat, pmat);
      else { /* use point model */
	shift[0] = -in->pointXOff;
	shift[1] = -in->pointYOff;
	in->do3Dmul = ObitUVDescShift3DPos (uvDesc, shift, 0.0, umat, pmat);
      }
      /* save */
      naxis[0] = 0; naxis[1] = count-1; 
      rotTable = ObitFArrayIndex(in->uRotTab, naxis);
      rotTable[0] = umat[0][0];
      rotTable[1] = umat[1][0];
      rotTable[2] = umat[0][1];
      rotTable[3] = umat[1][1];
      rotTable[4] = umat[0][2];
      rotTable[5] = umat[1][2];
    } /* end if got data */
  } /* end loop over fields */

  /* Open NI table */
  in->NITable  = ObitTableNIUnref(in->NITable);
  in->NIRow    = ObitTableNIRowUnref(in->NIRow);

  /* Create NI table Object */
  ver = 1;
  ObitInfoListGetTest(in->info, "ionVer", &type, dim, &ver);
  in->NITable = newObitTableNIValue ("IonCal NI table", (ObitData*)uvdata, &ver, 
				     OBIT_IO_ReadOnly, ncoef, err);
  if (err->error) Obit_traceback_msg (err, routine, in->name);
       Obit_return_if_fail((in->NITable!=NULL), err,
			  "%s: NI Table not found on %s", routine, uvdata->name);

  /* Open */
  ObitTableNIOpen(in->NITable, OBIT_IO_ReadOnly, err);
  if (err->error) Obit_traceback_msg (err, routine, in->name);
  in->NIRow = newObitTableNIRow(in->NITable);
  in->ncoef = in->NITable->numCoef;
  if (in->priorCoef)  g_free(in->priorCoef);  in->priorCoef  = NULL;
  in->priorCoef  = g_malloc0(in->ncoef*sizeof(ofloat));
  if (in->followCoef) g_free(in->followCoef); in->followCoef = NULL;
  in->followCoef = g_malloc0(in->ncoef*sizeof(ofloat));

  /* Create arrays for Zernike gradient terms */
  ndim = 2;
  naxis[0] = in->ncoef; naxis[1] = count;
  in->ZernX = ObitFArrayUnref(in->ZernX);
  in->ZernX = ObitFArrayCreate("ZerngrdX", ndim, naxis);
  in->ZernY = ObitFArrayUnref(in->ZernY);
  in->ZernY = ObitFArrayCreate("ZerngrdX", ndim, naxis);

  /* Loop over fields Saving Zernike gradient terms */
  count = 0;
  for (field = 0; field<in->mosaic->numberImages; field++) {
    /* Anything to do in this field? */
    if ((in->endComp[field]>0) && 
	(in->endComp[field]>=in->startComp[field])) {
      count++;  /* Count fields with actual components */
      /* save */
      naxis[0] = 0; naxis[1] = count-1; 
      XTable = ObitFArrayIndex(in->ZernX, naxis);
      YTable = ObitFArrayIndex(in->ZernY, naxis);
      
      imDesc = in->mosaic->images[field]->myDesc; /* Image descriptor */
      /* pointing position */
      ObitImageDescGetPoint (imDesc, &raPnt, &decPnt);
      
      /* Shift to field center, image or point model */
      if (in->pointFlux!=0.0) { /* Point */
	shift[0] = -in->pointXOff;
	shift[1] = -in->pointYOff;
      } else {
	/* From image header*/
	ObitSkyGeomShiftXY (raPnt, decPnt, imDesc->crota[imDesc->jlocd], 
			    imDesc->crval[imDesc->jlocr], imDesc->crval[imDesc->jlocd], 
			    &shift[0], &shift[1]);
      }
      
      /* Offset on Zernike plane */
      ObitSkyGeomRADec2Zern (raPnt, decPnt, shift[0], shift[1],
			     &ZernXY[0], &ZernXY[1], &ierr);
      Obit_return_if_fail((ierr==0), err,
			  "%s: Error projecting onto Zernike Unit circle", routine);
      for (i=0; i<in->ncoef; i++) {
	XTable[i] = ObitZernikeGradX(i+2, ZernXY[0], ZernXY[1]);
	YTable[i] = ObitZernikeGradY(i+2, ZernXY[0], ZernXY[1]);
      } 
    } /* end if got data */
  } /* end loop over fields */

} /* end ObitSkyModelVMIonInitMod */

/**
 * Any shutdown operations needed for a model
 * \param inn  SkyModel to shutdown
 * \param uvdata  uv data being modeled.
 * \param err Obit error stack object.
 */
void ObitSkyModelVMIonShutDownMod (ObitSkyModel* inn, ObitUV *uvdata, 
				   ObitErr *err)
{
  ObitSkyModelVMIon *in = (ObitSkyModelVMIon*)inn;

  if (err->error) return; /* existing error */

  gchar *routine = "ObitSkyModelVMIonShutDownMod";
  /* Call parent shutdown */
  ObitSkyModelVMShutDownMod(inn, uvdata, err);

  /* Free arrays */
  in->uRotTab  = ObitFArrayUnref(in->uRotTab);
  in->ZernX    = ObitFArrayUnref(in->ZernX);
  in->ZernY    = ObitFArrayUnref(in->ZernY);
  if (in->fieldIndex) g_free(in->fieldIndex); in->fieldIndex = NULL;

  /* Close NI table */
  ObitTableNIClose(in->NITable, err);
  in->NITable  = ObitTableNIUnref(in->NITable);
  in->NIRow    = ObitTableNIRowUnref(in->NIRow);
  if (in->priorCoef)  g_free(in->priorCoef);  in->priorCoef  = NULL;
  if (in->followCoef) g_free(in->followCoef); in->followCoef = NULL;
  if (err->error) Obit_traceback_msg (err, routine, in->name);

} /* end ObitSkyModelVMIonShutDownMod */

/**
 * Initializes an ObitSkyModel for a pass through data in time order.
 * Resets current times
 * \param inn  SkyModel to initialize
 * \param err Obit error stack object.
 */
void ObitSkyModelVMIonInitModel (ObitSkyModel* inn, ObitErr *err)
{
  ObitSkyModelVMIon *in = (ObitSkyModelVMIon*)inn;
  olong i;
  gchar *routine = "ObitSkyModelVMIonInitModel";

  /*  Reset time of current model */
  in->endVMModelTime = -1.0e20;
  in->curVMModelTime = -1.0e20;

  /* Read, swallow first two Ion table entries */
  in->lastNIRow = 0;
  ObitTableNIReadRow (in->NITable, ++in->lastNIRow, in->NIRow, err);
  if (err->error) Obit_traceback_msg (err, routine, in->name);
  in->priorTime   = in->NIRow->Time;
  in->priorWeight = in->NIRow->weight;
  for (i=0; i<in->ncoef; i++) in->priorCoef[i] = in->NIRow->coef[i];
  if (in->NITable->myDesc->nrow>1) {
    ObitTableNIReadRow (in->NITable, ++in->lastNIRow, in->NIRow, err);
    if (err->error) Obit_traceback_msg (err, routine, in->name);
    in->followTime   = in->NIRow->Time;
    in->followWeight = in->NIRow->weight;
    for (i=0; i<in->ncoef; i++) in->followCoef[i] = in->NIRow->coef[i];
  } else { /* only one entry */
    in->priorTime   = in->NIRow->Time;
    in->priorWeight = 0.0;
    for (i=0; i<in->ncoef; i++) in->followCoef[i] = in->priorCoef[i];
  }
} /* end ObitSkyModelVMIonInitModel */

/**
 * Update VM model with time or spatial modifications to model
 * Update model in VMComps member from comps member and
 * Ionospheric calibration table.
 * \param inn      SkyModelVM 
 * \param time    current time (d)
 * \param suba    0-rel subarray number (not used here)
 * \param err Obit error stack object.
 */
void ObitSkyModelVMIonUpdateModel (ObitSkyModelVM *inn, 
				   ofloat time, olong suba,
				   ObitUV *uvdata, ObitErr *err)
{
  ObitSkyModelVMIon *in = (ObitSkyModelVMIon*)inn;
  olong i, field, itmp, icomp, ncomp, lcomp, naxis[2];
  ofloat dra, ddec, draP, draF, ddecP, ddecF, wtP, wtF;
  ofloat konst, xyz[3]={0.0,0.0,0.0}, xp[2];
  ofloat *rotTable, *XTable, *YTable, *inData, *outData;
  gchar *routine = "ObitSkyModelVMIonUpdateModel";

  /* Data in ccomps are per row:
     field number, DeltaX, DeltaY, amp, -2*pi*x, -2*pi*y, -2*pi*z */

  /* Update coefficient tables */
  while ((time>in->followTime) && (in->lastNIRow<in->NITable->myDesc->nrow)) {
    /* Shuffle */
    in->priorTime   = in->followTime;
    in->priorWeight = in->followWeight;
    for (i=0; i<in->ncoef; i++) in->priorCoef[i] = in->followCoef[i];
    
    /* Read next */
    ObitTableNIReadRow (in->NITable, ++in->lastNIRow, in->NIRow, err);
    if (err->error) Obit_traceback_msg (err, routine, in->name);
    in->followTime   = in->NIRow->Time;
    in->followWeight = in->NIRow->weight;
    for (i=0; i<in->ncoef; i++) in->followCoef[i] = in->NIRow->coef[i];
  } /* end updating coef. */

  /*  Reset time of current model */
  in->curVMModelTime = time;
  in->endVMModelTime = in->curVMModelTime + in->updateInterval;

  /* geometric constant */
  konst = DG2RAD * 2.0 * G_PI;

  /* Loop through data in in->VMComps adding corruptions to in->comps */
  lcomp = in->VMComps->naxis[0];
  ncomp = in->numComp;
  naxis[0] = 0; naxis[1] = 0;
  inData  = ObitFArrayIndex(in->comps, naxis);
  outData = ObitFArrayIndex(in->VMComps, naxis);
  field = -1;
  for (icomp=0; icomp<ncomp; icomp++) {

    /* If new field the calculate offset */
    itmp = inData[0] + 0.5;
    if ((field!=itmp) && (itmp>=0)) {
      /* Calculate, interpolate current position offset */
      /* Get pointing position for offsets */
      field = itmp;
      naxis[0] = 0; naxis[1] = in->fieldIndex[field]; 
      /* Barf and die if invalid */
      Obit_return_if_fail((naxis[1]>=0), err,
			  "%s: Internal tables corrupted or invalid", routine);
      rotTable = ObitFArrayIndex(in->uRotTab, naxis);
      XTable   = ObitFArrayIndex(in->ZernX, naxis);
      YTable   = ObitFArrayIndex(in->ZernY, naxis);
      
      draP  = 0.0;
      ddecP = 0.0;
      if (in->priorWeight>0.0) {
	for (i=0; i<in->ncoef; i++) {
	  draP  += in->priorCoef[i]*XTable[i];
	  ddecP += in->priorCoef[i]*YTable[i];
	} 
      }
      
      draF  = 0.0;
      ddecF = 0.0;
      if (in->followWeight>0.0) {
	for (i=0; i<in->ncoef; i++) {
	  draF  += in->followCoef[i]*XTable[i];
	  ddecF += in->followCoef[i]*YTable[i];
	} 
      }

      /* Interpolate - before first? or following bad*/
      if ((time<in->priorTime) || (in->followWeight<=0.0)) {
	dra  = draP;
	ddec = ddecP;
      } else if ((time>in->followTime) || (in->followWeight<=0.0)){ 
	/* after last or preceeding bad */
	dra  = draF;
	ddec = ddecF;
      } else {  /* in between and both OK, interpolate */
	wtF = (time - in->priorTime) / (in->followTime-in->priorTime+1.0e-10);
	wtP = 1.0 - wtF;
	dra  = wtP*draP  + wtF*draF;
	ddec = wtP*ddecP + wtF*ddecF;
      }

      /* Position offset term */
      xp[0] = -dra  * konst;
      xp[1] = -ddec * konst;
      if (in->do3Dmul) {
	xyz[0] = xp[0]*rotTable[0] + xp[1]*rotTable[1];
	xyz[1] = xp[0]*rotTable[2] + xp[1]*rotTable[3];
	xyz[2] = xp[0]*rotTable[4] + xp[1]*rotTable[5];
	/* PRJMUL (2, XP, UMAT, XYZ); */
      } else {  /* no 3D */
	xyz[0] = in->ccrot * xp[0] + in->ssrot * xp[1];
	xyz[1] = in->ccrot * xp[1] - in->ssrot * xp[0];
	xyz[2] = 0.0;
      }
    } /* end calculate new field offset */

    /* DEBUG
    xyz[0] = xyz[1] = xyz[2] = 0.0; */

    /* Update - copy to outData */
    if (inData[0]>=0.0) {
      outData[0] = inData[3];  /* Amplitude */
      outData[1] = inData[4] + xyz[0]; /* X phase term */
      outData[2] = inData[5] + xyz[1]; /* Y phase term */
      outData[3] = inData[6] + xyz[2]; /* Z phase term */
      for (i=7; i<lcomp; i++) outData[4+i] = inData[7+i]; /* other terms */
    } else {
      outData[0] = 0.0;
      outData[1] = 0.0;
      outData[2] = 0.0;
      outData[3] = 0.0;
    }
    inData  += lcomp;
    outData += lcomp;
  } /* end loop over component table */

} /* end ObitSkyModelVMIonUpdateModel */

/**
 * Initialize global ClassInfo Structure.
 */
void ObitSkyModelVMIonClassInit (void)
{
  if (myClassInfo.initialized) return;  /* only once */
  
  /* Set name and parent for this class */
  myClassInfo.ClassName   = g_strdup(myClassName);
  myClassInfo.ParentClass = ObitParentGetClass();

  /* Set function pointers */
  ObitSkyModelVMIonClassInfoDefFn ((gpointer)&myClassInfo);
 
  myClassInfo.initialized = TRUE; /* Now initialized */
 
} /* end ObitSkyModelVMIonClassInit */

/**
 * Initialize global ClassInfo Function pointers.
 */
static void ObitSkyModelVMIonClassInfoDefFn (gpointer inClass)
{
  ObitSkyModelVMIonClassInfo *theClass = (ObitSkyModelVMIonClassInfo*)inClass;
  ObitClassInfo *ParentClass = (ObitClassInfo*)myClassInfo.ParentClass;

  if (theClass->initialized) return;  /* only once */

  /* Check type of inClass */
  g_assert (ObitInfoIsA(inClass, (ObitClassInfo*)&myClassInfo));

  /* Initialize (recursively) parent class first */
  if ((ParentClass!=NULL) && 
      (ParentClass->ObitClassInfoDefFn!=NULL))
    ParentClass->ObitClassInfoDefFn(theClass);

  /* function pointers defined or overloaded this class */
  theClass->ObitClassInit = (ObitClassInitFP)ObitSkyModelVMIonClassInit;
  theClass->ObitClassInfoDefFn = (ObitClassInfoDefFnFP)ObitSkyModelVMIonClassInfoDefFn;
  theClass->ObitGetClass  = (ObitGetClassFP)ObitSkyModelVMIonGetClass;
  theClass->newObit       = (newObitFP)newObitSkyModelVMIon;
  theClass->ObitCopy      = (ObitCopyFP)ObitSkyModelVMIonCopy;
  theClass->ObitClear     = (ObitClearFP)ObitSkyModelVMIonClear;
  theClass->ObitInit      = (ObitInitFP)ObitSkyModelVMIonInit;
  theClass->ObitSkyModelCreate       = (ObitSkyModelCreateFP)ObitSkyModelVMIonCreate;
  theClass->ObitSkyModelInitMod      = (ObitSkyModelInitModFP)ObitSkyModelVMIonInitMod;
  theClass->ObitSkyModelShutDownMod  = (ObitSkyModelShutDownModFP)ObitSkyModelVMIonShutDownMod;
  theClass->ObitSkyModelInitModel    = (ObitSkyModelInitModelFP)ObitSkyModelVMIonInitModel;
  theClass->ObitSkyModelGetInput     = (ObitSkyModelGetInputFP)ObitSkyModelVMIonGetInput;
  theClass->ObitSkyModelVMUpdateModel=
    (ObitSkyModelVMUpdateModelFP)ObitSkyModelVMIonUpdateModel;

} /* end ObitSkyModelVMIonClassDefFn */


/*---------------Private functions--------------------------*/

/**
 * Creates empty member objects, initialize reference count.
 * Parent classes portions are (recursively) initialized first
 * \param inn Pointer to the object to initialize.
 */
void ObitSkyModelVMIonInit  (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitSkyModelVMIon *in = inn;

  /* error checks */
  g_assert (in != NULL);

  /* recursively initialize parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  if ((ParentClass!=NULL) && ( ParentClass->ObitInit!=NULL)) 
    ParentClass->ObitInit (inn);

  /* set members in this class */
  in->uRotTab    = NULL;
  in->ZernX      = NULL; 
  in->ZernY      = NULL; 
  in->NITable    = NULL;
  in->NIRow      = NULL;
  in->priorCoef  = NULL;
  in->followCoef = NULL;
  in->fieldIndex = NULL;
} /* end ObitSkyModelVMIonInit */


/**
 * Deallocates member objects.
 * Does (recursive) deallocation of parent class members.
 * For some reason this wasn't build into the GType class.
 * \param  inn Pointer to the object to deallocate.
 *           Actually it should be an ObitSkyModelVMIon* cast to an Obit*.
 */
void ObitSkyModelVMIonClear (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitSkyModelVMIon *in = inn;

  /* error checks */
  g_assert (ObitIsA(in, &myClassInfo));

  /* delete this class members */
  in->uRotTab  = ObitFArrayUnref(in->uRotTab);
  in->ZernX    = ObitFArrayUnref(in->ZernX);
  in->ZernY    = ObitFArrayUnref(in->ZernY);
  in->NITable  = ObitTableNIUnref(in->NITable);
  in->NIRow    = ObitTableNIRowUnref(in->NIRow);
  if (in->priorCoef)  g_free(in->priorCoef);
  if (in->followCoef) g_free(in->followCoef);
  if (in->fieldIndex) g_free(in->fieldIndex);

  /* unlink parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  /* delete parent class members */
  if ((ParentClass!=NULL) && ( ParentClass->ObitClear!=NULL)) 
    ParentClass->ObitClear (inn);
  
} /* end ObitSkyModelVMIonClear */

/**
 * Get input parameters from info member
 * \param in Pointer to the ObitSkyModelVMIon .
 * \param err Obit error stack object.
 */
void  ObitSkyModelVMIonGetInput (ObitSkyModel* inn, ObitErr *err)
{
  ObitSkyModelVMIon *in = (ObitSkyModelVMIon*)inn;
  ObitInfoType type;
  /* gint32 i, dim[MAXINFOELEMDIM];
     ofloat rtemp[10];
     olong itemp, *iptr, num;
     gchar tempStr[5];*/
  union ObitInfoListEquiv InfoReal; 
  gchar *routine = "ObitSkyModelVMIonGetInput";

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return;
  g_assert (ObitSkyModelVMIonIsA(in));
  if (!ObitInfoListIsA(in->info)) return;
  InfoReal.itg = 0;type = OBIT_oint;

  /* Call base class version */
  ObitSkyModelVMGetInput (inn, err);
  if (err->error) Obit_traceback_msg (err, routine, in->name);

} /* end ObitSkyModelVMIonGetInput */

