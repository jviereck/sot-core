/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 * This file is part of sot-core.
 * sot-core is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * sot-core is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.  You should
 * have received a copy of the GNU Lesser General Public License along
 * with sot-core.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SOT_FEATURE_JOINTLIMITS_HH__
#define __SOT_FEATURE_JOINTLIMITS_HH__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* SOT */
#include <sot-core/feature-abstract.h>
#include <sot-core/exception-task.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32)
#  if defined (feature_joint_limits_EXPORTS)
#    define SOTFEATUREJOINTLIMITS_EXPORT __declspec(dllexport)
#  else
#    define SOTFEATUREJOINTLIMITS_EXPORT __declspec(dllimport)
#  endif
#else
#  define SOTFEATUREJOINTLIMITS_EXPORT
#endif

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

namespace dynamicgraph { namespace sot {
namespace dg = dynamicgraph;

/*!
  \class FeatureJointLimits
  \brief Class that defines gradient vector for jl avoidance.
*/
class SOTFEATUREJOINTLIMITS_EXPORT FeatureJointLimits
: public FeatureAbstract
{

 public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

 protected:

  double threshold;
  const static double THRESHOLD_DEFAULT; // = .9;

/*   unsigned int freeFloatingIndex,freeFloatingSize; */
/*   static const unsigned int FREE_FLOATING_INDEX = 0; */
/*   static const unsigned int FREE_FLOATING_SIZE = 5; */

  /* --- SIGNALS ------------------------------------------------------------ */
 public:

  dg::SignalPtr< ml::Vector,int > jointSIN;
  dg::SignalPtr< ml::Vector,int > upperJlSIN;
  dg::SignalPtr< ml::Vector,int > lowerJlSIN;
  dg::SignalTimeDependent< ml::Vector,int > widthJlSINTERN;

  using FeatureAbstract::selectionSIN;

  using FeatureAbstract::jacobianSOUT;
  using FeatureAbstract::errorSOUT;
  using FeatureAbstract::activationSOUT;

 public:
  FeatureJointLimits( const std::string& name );
  virtual ~FeatureJointLimits( void ) {}

  virtual unsigned int& getDimension( unsigned int & dim, int time );

  virtual ml::Vector& computeError( ml::Vector& res,int time );
  virtual ml::Matrix& computeJacobian( ml::Matrix& res,int time );
  virtual ml::Vector& computeActivation( ml::Vector& res,int time );
  ml::Vector& computeWidthJl( ml::Vector& res,const int& time );

  /** Static Feature selection. */
  inline static Flags selectActuated( void );

  virtual void display( std::ostream& os ) const;
  void commandLine( const std::string& cmdLine,
		    std::istringstream& cmdArgs,
		    std::ostream& os );


} ;

} /* namespace sot */} /* namespace dynamicgraph */

#endif // #ifndef __SOT_FEATURE_JOINTLIMITS_HH__

/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
