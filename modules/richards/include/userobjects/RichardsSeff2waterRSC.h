/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

#ifndef RICHARDSSEFF2WATERRSC_H
#define RICHARDSSEFF2WATERRSC_H

#include "RichardsSeff.h"
#include "RichardsSeffRSC.h"

class RichardsSeff2waterRSC;


template<>
InputParameters validParams<RichardsSeff2waterRSC>();

/**
 * Rogers-Stallybrass-Clements version of effective saturation of water phase
 * as a function of (Pwater, Pgas), and its derivs wrt to those pressures.
 * Note that the water pressure appears first in the tuple (Pwater, Pgas).
 * valid for residual saturations = 0, and viscosityOil = 2*viscosityWater.  (the "2" is important here!).
 * C Rogers, MP Stallybrass and DL Clements "On two phase filtration under gravity and with boundary infiltration: application of a Backlund transformation" Nonlinear Analysis Theory Methods and Applications 7 (1983) 785--799.
 */
class RichardsSeff2waterRSC : public RichardsSeff
{
public:
  RichardsSeff2waterRSC(const std::string & name, InputParameters parameters);

  /**
   * water effective saturation
   * @param p porepressures.  Here (*p[0])[qp] is the water pressure at quadpoint qp, and (*p[1])[qp] is the gas porepressure
   * @param qp the quadpoint to evaluate effective saturation at
   */
  Real seff(std::vector<VariableValue *> p, unsigned int qp) const;

  /**
   * derivative of effective saturation as a function of porepressure
   * @param p porepressure in the element.  Note that (*p[0])[qp] is the porepressure at quadpoint qp
   * @param qp the quad point to evaluate effective saturation at
   * @param result the derivtives will be placed in this array
   */
  void dseff(std::vector<VariableValue *> p, unsigned int qp, std::vector<Real> & result) const;

  /**
   * second derivative of effective saturation as a function of porepressure
   * @param p porepressure in the element.  Note that (*p[0])[qp] is the porepressure at quadpoint qp
   * @param qp the quad point to evaluate effective saturation at
   * @param result the derivtives will be placed in this array
   */
  void d2seff(std::vector<VariableValue *> p, unsigned int qp, std::vector<std::vector<Real> > & result) const;

protected:

  /// oil viscosity
  Real _oil_viscosity;

  /// RSC scale ratio
  Real _scale_ratio;

  /// RSC shift
  Real _shift;

  /// RSC scale
  Real _scale;

};

#endif // RICHARDSSEFF2WATERRSC_H
