/*=========================================================================
 *
 *  Copyright David Doria 2011 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "PointSelectionStyle2D.h"

// VTK
#include <vtkAbstractPicker.h>
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkProp.h>
#include <vtkPropPicker.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

// STL
#include <sstream>


vtkStandardNewMacro(PointSelectionStyle2D);

PointSelectionStyle2D::PointSelectionStyle2D()
{
  this->ClickedPointEvent = vtkCommand::UserEvent + 1;
}

void PointSelectionStyle2D::OnLeftButtonDown()
{
  int* clickPos = this->GetInteractor()->GetEventPosition();
  //std::cout << "Picking pixel: " << clickPos[0] << " " << clickPos[1] << std::endl;

  vtkSmartPointer<vtkPropPicker>  picker =
    vtkSmartPointer<vtkPropPicker>::New();
  picker->PickFromListOff();
  int success = picker->Pick(clickPos[0], clickPos[1], 0, this->CurrentRenderer);
  // returns non-zero if something was picked
  if(!success)
  {
    std::cerr << "Nothing was picked." << std::endl;
  }
  double picked[3];

  picker->GetPickPosition(picked);
  // std::cout << "Picked point with coordinate: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

  this->InvokeEvent(this->ClickedPointEvent, picked);

  // Forward events
  vtkInteractorStyleImage::OnLeftButtonDown();
}
