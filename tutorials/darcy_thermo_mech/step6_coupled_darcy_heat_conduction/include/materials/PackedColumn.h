#ifndef PACKEDCOLUMN_H_
#define PACKEDCOLUMN_H_

#include "Material.h"

// A helper class from MOOSE that linear interpolates x,y data
#include "LinearInterpolation.h"

class PackedColumn;

template<>
InputParameters validParams<PackedColumn>();

/**
 * Material objects inherit from Material and override computeQpProperties.
 *
 * Their job is to declare properties for use by other objects in the
 * calculation such as Kernels and BoundaryConditions.
 */
class PackedColumn : public Material
{
public:
  PackedColumn(const std::string & name, InputParameters parameters);

protected:
  /**
   * Necessary override.  This is where the values of the properties
   * are computed.
   */
  virtual void computeQpProperties();

  /// The radius of the balls in the column
  const Real & _ball_radius;

  /// Based on the paper this will
  LinearInterpolation _permeability_interpolation;

  /// The permeability (K)
  MaterialProperty<Real> & _permeability;

  /// The porosity (eps)
  MaterialProperty<Real> & _porosity;

  /// The viscosity of the fluid (mu)
  MaterialProperty<Real> & _viscosity;

  /// The bulk thermal conductivity
  MaterialProperty<Real> & _thermal_conductivity;

  /// The bulk specific heat
  MaterialProperty<Real> & _specific_heat;

  /// The bulk density
  MaterialProperty<Real> & _density;
};

#endif //PACKEDCOLUMN_H
