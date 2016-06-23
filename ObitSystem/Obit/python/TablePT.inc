/* $Id:  $   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2016                                              */
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
#include "Obit.h"
#include "ObitData.h"
#include "ObitTablePT.h"
%}
 
%inline %{
 
extern ObitTable* TablePT (ObitData *inData, long *tabVer,
 	                   int access,
 	                   char *tabName,
                           int numTerm,
                           ObitErr *err)
 {
   ObitIOAccess laccess;
   /* Cast structural keywords to correct type */
   oint lnumTerm = (oint)numTerm;
   olong ltabVer = (olong)*tabVer;
   ObitTable *outTable=NULL;
   laccess = OBIT_IO_ReadOnly;
   if (access==2) laccess = OBIT_IO_WriteOnly;
   else if (access==3) laccess = OBIT_IO_ReadWrite;
   outTable = (ObitTable*)newObitTablePTValue ((gchar*)tabName, inData, (olong*)&ltabVer,
   			   laccess, 
                           lnumTerm,
                           err);
   *tabVer = (long)ltabVer;
   return outTable;
   }
 
extern PyObject* TablePTGetHeadKeys (ObitTable *inTab) {
  PyObject *outDict=PyDict_New();
  ObitTablePT *lTab = (ObitTablePT*)inTab;
  PyDict_SetItemString(outDict, "numTerm",  PyInt_FromLong((long)lTab->numTerm));
  PyDict_SetItemString(outDict, "revision",  PyInt_FromLong((long)lTab->revision));
  PyDict_SetItemString(outDict, "RefDate", PyString_InternFromString(lTab->RefDate));

  return outDict;
} 

extern void TablePTSetHeadKeys (ObitTable *inTab, PyObject *inDict) {
  ObitTablePT *lTab = (ObitTablePT*)inTab;
  char *tstr;
  int lstr=MAXKEYCHARTABLEPT;

  lTab->revision = (oint)PyInt_AsLong(PyDict_GetItemString(inDict, "revision"));
  tstr = PyString_AsString(PyDict_GetItemString(inDict, "RefDate"));
  strncpy (lTab->RefDate, tstr, lstr); lTab->RefDate[lstr-1]=0;

  if ((lTab->myDesc->access==OBIT_IO_ReadWrite) || (lTab->myDesc->access==OBIT_IO_WriteOnly)) 
    lTab->myStatus = OBIT_Modified;
} 

%}