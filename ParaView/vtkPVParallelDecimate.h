/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPVParallelDecimate.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 1998-1999 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.

All rights reserved. No part of this software may be reproduced, distributed,
or modified, in any form or by any means, without permission in writing from
Kitware Inc.

IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF,
EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON AN
"AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

=========================================================================*/
// .NAME vtkPVParallelDecimate - collects simplified data to process 0. 
// .SECTION Description
// This filter is used internally and is not intended to be connected
// the UI.

#ifndef __vtkPVParallelDecimate_h
#define __vtkPVParallelDecimate_h

#include "vtkPVPolyDataToPolyDataFilter.h"

class vtkKWApplication;
class vtkParallelDecimate;


class VTK_EXPORT vtkPVParallelDecimate : public vtkPVPolyDataToPolyDataFilter
{
public:
  static vtkPVParallelDecimate* New();
  vtkTypeMacro(vtkPVParallelDecimate, vtkPVPolyDataToPolyDataFilter);

  // Description:
  // You have to clone this object before you create its UI.
  void CreateProperties();

  // Description:
  // This method sets the controller in the VTK filter.
  void SetApplication(vtkKWApplication *app);
  
protected:
  vtkPVParallelDecimate();
  ~vtkPVParallelDecimate() {};
  vtkPVParallelDecimate(const vtkPVParallelDecimate&) {};
  void operator=(const vtkPVParallelDecimate&) {};
  
  // Description:
  // This is used internally to cast the source to a vtkParallelDecimate
  vtkParallelDecimate *GetParallelDecimate();
};

#endif
