/*
 * Copyright 2010,
 * François Bleibel, 
 * Olivier Stasse,
 * Florent Lamiraux
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

#ifndef __SOT_FACTORY_HH__
#define __SOT_FACTORY_HH__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#include <dynamic-graph/factory.h>

#define SOT_FACTORY_FEATURE_PLUGIN(sotFeatureType,className) \
  DYNAMICGRAPH_FACTORY_ENTITY_PLUGIN(sotFeatureType,className)
/* -------------------------------------------------------------------------- */
/* --- TASK REGISTERER ------------------------------------------------------ */
/* -------------------------------------------------------------------------- */

#define SOT_FACTORY_TASK_PLUGIN(sotTaskType,className) \
  DYNAMICGRAPH_FACTORY_ENTITY_PLUGIN(sotTaskType,className)

#endif /* #ifndef __SOT_FACTORY_HH__ */




