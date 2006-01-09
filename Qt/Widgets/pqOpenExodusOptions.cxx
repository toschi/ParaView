

#include "pqOpenExodusOptions.h"
#include <QCheckBox>

#include "pqSMAdaptor.h"

#include <vtkSMSourceProxy.h>
#include <vtkSMStringVectorProperty.h>
#include <vtkSMArraySelectionDomain.h>


pqOpenExodusOptions::pqOpenExodusOptions(vtkSMSourceProxy* exodusReader, QWidget* p)
  : QDialog(p), ExodusReader(exodusReader)
{
  this->setupUi(this);

  if(!this->ExodusReader)
    return;

  this->ExodusReader->UpdateVTKObjects();
  this->ExodusReader->UpdatePipelineInformation();

  pqSMAdaptor* PropertyAdaptor = pqSMAdaptor::instance();
  
  int i;
  
  // get and populate block ids
  QList<QVariant> blocks = PropertyAdaptor->getProperty(this->ExodusReader->GetProperty("BlockArrayStatus")).toList();
  for(i=0; i<blocks.size(); i++)
    {
    QList<QVariant> block = blocks[i].toList();
    QCheckBox* cb = new QCheckBox(this->BlocksGroup);
    cb->setText(block[0].toString());
    cb->setChecked(block[1].toBool());
    this->BlocksGroup->layout()->addWidget(cb);
    }

  // get and populate cell arrays
  QList<QVariant> cellArrays = PropertyAdaptor->getProperty(this->ExodusReader->GetProperty("CellArrayStatus")).toList();
  for(i=0; i<cellArrays.size(); i++)
    {
    QList<QVariant> cellArray = cellArrays[i].toList();
    QCheckBox* cb = new QCheckBox(this->ElementVariablesGroup);
    cb->setText(cellArray[0].toString());
    cb->setChecked(cellArray[1].toBool());
    this->ElementVariablesGroup->layout()->addWidget(cb);
    }

  // get and populate point arrays
  QList<QVariant> pointArrays = PropertyAdaptor->getProperty(this->ExodusReader->GetProperty("PointArrayStatus")).toList();
  for(i=0; i<pointArrays.size(); i++)
    {
    QList<QVariant> pointArray = pointArrays[i].toList();
    QCheckBox* cb = new QCheckBox(this->NodeVariablesGroup);
    cb->setText(pointArray[0].toString());
    cb->setChecked(pointArray[1].toBool());
    this->NodeVariablesGroup->layout()->addWidget(cb);
    }
  
  // get and populate side sets
  QList<QVariant> sideSetArrays = PropertyAdaptor->getProperty(this->ExodusReader->GetProperty("SideSetArrayStatus")).toList();
  for(i=0; i<sideSetArrays.size(); i++)
    {
    QList<QVariant> sideSetArray = sideSetArrays[i].toList();
    QCheckBox* cb = new QCheckBox(this->SideSetGroup);
    cb->setText(sideSetArray[0].toString());
    cb->setChecked(sideSetArray[1].toBool());
    this->SideSetGroup->layout()->addWidget(cb);
    }
  
  // get and populate node sets
  QList<QVariant> nodeSetArrays = PropertyAdaptor->getProperty(this->ExodusReader->GetProperty("NodeSetArrayStatus")).toList();
  for(i=0; i<nodeSetArrays.size(); i++)
    {
    QList<QVariant> nodeSetArray = nodeSetArrays[i].toList();
    QCheckBox* cb = new QCheckBox(this->NodeSetGroup);
    cb->setText(nodeSetArray[0].toString());
    cb->setChecked(nodeSetArray[1].toBool());
    this->NodeSetGroup->layout()->addWidget(cb);
    }
}

pqOpenExodusOptions::~pqOpenExodusOptions()
{
}

void pqOpenExodusOptions::accept()
{
  int i;
  pqSMAdaptor* PropertyAdaptor = pqSMAdaptor::instance();

  // set blocks
  vtkSMProperty* property = this->ExodusReader->GetProperty("BlockArrayStatus");
  QList<QVariant> blocks = PropertyAdaptor->getProperty(property).toList();
  for(i=0; i<blocks.size(); i++)
    {
    QLayout* l = this->BlocksGroup->layout();
    QCheckBox* cb = qobject_cast<QCheckBox*>(l->itemAt(l->count() - blocks.size() + i)->widget());
    PropertyAdaptor->setProperty(property, i, cb->isChecked());
    this->ExodusReader->UpdateVTKObjects();  // TODO: get rid of this call
    }

  // set element arrays
  property = this->ExodusReader->GetProperty("CellArrayStatus");
  QList<QVariant> cellArrays = PropertyAdaptor->getProperty(property).toList();
  for(i=0; i<cellArrays.size(); i++)
    {
    QLayout* l = this->ElementVariablesGroup->layout();
    QCheckBox* cb = qobject_cast<QCheckBox*>(l->itemAt(l->count() - cellArrays.size() + i)->widget());
    PropertyAdaptor->setProperty(property, i, cb->isChecked());
    this->ExodusReader->UpdateVTKObjects();  // TODO: get rid of this call
    }
  
  // set point arrays
  property = this->ExodusReader->GetProperty("PointArrayStatus");
  QList<QVariant> pointArrays = PropertyAdaptor->getProperty(property).toList();
  for(i=0; i<pointArrays.size(); i++)
    {
    QLayout* l = this->NodeVariablesGroup->layout();
    QCheckBox* cb = qobject_cast<QCheckBox*>(l->itemAt(l->count() - pointArrays.size() + i)->widget());
    PropertyAdaptor->setProperty(property, i, cb->isChecked());
    this->ExodusReader->UpdateVTKObjects();  // TODO: get rid of this call
    }
  
  // set sideset arrays
  property = this->ExodusReader->GetProperty("SideSetArrayStatus");
  QList<QVariant> sideSetArrays = PropertyAdaptor->getProperty(property).toList();
  for(i=0; i<sideSetArrays.size(); i++)
    {
    QLayout* l = this->SideSetGroup->layout();
    QCheckBox* cb = qobject_cast<QCheckBox*>(l->itemAt(l->count() - sideSetArrays.size() + i)->widget());
    PropertyAdaptor->setProperty(property, i, cb->isChecked());
    this->ExodusReader->UpdateVTKObjects();  // TODO: get rid of this call
    }
  
  // set nodeset arrays
  property = this->ExodusReader->GetProperty("NodeSetArrayStatus");
  QList<QVariant> nodeSetArrays = PropertyAdaptor->getProperty(property).toList();
  for(i=0; i<nodeSetArrays.size(); i++)
    {
    QLayout* l = this->NodeSetGroup->layout();
    QCheckBox* cb = qobject_cast<QCheckBox*>(l->itemAt(l->count() - nodeSetArrays.size() + i)->widget());
    PropertyAdaptor->setProperty(property, i, cb->isChecked());
    this->ExodusReader->UpdateVTKObjects();  // TODO: get rid of this call
    }

  QDialog::accept();
}

