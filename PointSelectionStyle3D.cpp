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

#include "PointSelectionStyle3D.h"

// VTK
#include <vtkAbstractPicker.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkFollower.h>
#include <vtkGlyph3D.h>
#include <vtkLabeledDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkPointPicker.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTextProperty.h>
#include <vtkVectorText.h>

// STL
#include <sstream>
#include <stdexcept>

vtkStandardNewMacro(PointSelectionStyle3D);

PointSelectionStyle3D::PointSelectionStyle3D()
{

}

void PointSelectionStyle3D::Initialize()
{
  // This function must be called after calling selectionStyle->SetCurrentRenderer(renderer);
  if(!this->CurrentRenderer)
  {
    throw std::runtime_error("Initialize: CurrentRenderer is NULL!");
  }
}

void PointSelectionStyle3D::OnLeftButtonDown()
{
  //std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
  int success = vtkPointPicker::SafeDownCast(this->Interactor->GetPicker())->Pick(this->Interactor->GetEventPosition()[0],
  //vtkPointPicker::SafeDownCast(this->Interactor->GetPicker())->Pick(this->Interactor->GetEventPosition()[0],
          this->Interactor->GetEventPosition()[1],
          0,  // always zero.
          this->CurrentRenderer);
  if(!success)
    {
    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    return;
    }

  vtkPointPicker* pointPicker = vtkPointPicker::SafeDownCast(this->Interactor->GetPicker());
  if(!pointPicker)
    {
    throw std::runtime_error("pointPicker is invalid!");
    }

//   if(pointPicker->GetDataSet() != this->Data)
//     {
//     std::cerr << "pointPicker->GetDataSet(): " << pointPicker->GetDataSet() << " this->Data: " << this->Data << std::endl;
//     throw std::runtime_error("Did not pick from the correct data set!");
//     }
  /*
  vtkIdType pointId = vtkPointPicker::SafeDownCast(this->Interactor->GetPicker())->GetPointId();
  double p[3];
  this->Data->GetPoint(pointId, p);

  //std::cout << "Picked point: " << pointId << std::endl;
  //std::cout << "Point: " << pointId << " should have coordinate: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
  */
  double picked[3] = {0,0,0};

  pointPicker->GetPickPosition(picked);
  //std::cout << "Picked point with coordinate: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

  if(this->Interactor->GetShiftKey())
    {
    this->CurrentRenderer->GetActiveCamera()->SetFocalPoint(picked);
    }

  // Forward events
  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();

}

void PointSelectionStyle3D::SetCurrentRenderer(vtkRenderer* renderer)
{
  vtkInteractorStyle::SetCurrentRenderer(renderer);
}
