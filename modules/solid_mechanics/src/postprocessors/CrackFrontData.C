/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "CrackFrontData.h"
#include "MooseMesh.h"
#include "SubProblem.h"

// libMesh
#include "libmesh/boundary_info.h"

template<>
InputParameters validParams<CrackFrontData>()
{
  InputParameters params = validParams<GeneralPostprocessor>();
  params.addRequiredParam<VariableName>("variable", "The name of a variable whose value at the crack front is to be reported");
  params.addRequiredParam<UserObjectName>("crack_front_definition","The CrackFrontDefinition user object name");
  params.addParam<unsigned int>("crack_front_node_index","The index of the node on the crack front where data is to be reported");
  params.addParam<Real>("scale_factor",1, "A scale factor to be applied to the reported quantity");
  return params;
}

CrackFrontData::CrackFrontData(const std::string & name, InputParameters parameters) :
    GeneralPostprocessor(name, parameters),
    _crack_front_definition(&getUserObject<CrackFrontDefinition>("crack_front_definition")),
    _crack_front_node_index(isParamValid("crack_front_node_index") ? getParam<unsigned int>("crack_front_node_index") : 0),
    _crack_front_node(NULL),
    _mesh(_subproblem.mesh()),
    _var_name(parameters.get<VariableName>("variable")),
    _scale_factor(getParam<Real>("scale_factor"))
{
}

void
CrackFrontData::initialize()
{
  if (!(_crack_front_node_index < _crack_front_definition->getNumCrackFrontNodes()))
    mooseError("crack_front_node_index out of range in CrackFrontData");

  _crack_front_node = _crack_front_definition->getCrackFrontNodePtr(_crack_front_node_index);
}

Real
CrackFrontData::getValue()
{
  Real value = 0;

  if (_crack_front_node->processor_id() == processor_id())
    value = _subproblem.getVariable(_tid, _var_name).getNodalValue(*_crack_front_node);

  gatherSum(value);

  return _scale_factor * value;
}
