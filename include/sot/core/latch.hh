/*
 * Copyright 2017-, Rohan Budhiraja, Joseph Mirabel, CNRS
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

#ifndef __SOT_LATCH_H__
#define __SOT_LATCH_H__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* SOT */
#include <dynamic-graph/command-bind.h>
#include <sot/core/pool.hh>
#include <dynamic-graph/entity.h>
#include <dynamic-graph/all-signals.h>

/* STD */
#include <string>

namespace dynamicgraph { 
  namespace sot {
    
    /* --------------------------------------------------------------------- */
    /* --- CLASS ----------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    using dynamicgraph::Entity;
    using dynamicgraph::command::makeCommandVoid0;
    using dynamicgraph::command::docCommandVoid0;

    class Latch : public Entity
    {
     
    public: /* --- SIGNAL --- */
      DYNAMIC_GRAPH_ENTITY_DECL();
      Signal<bool,int> outSOUT;
      Signal<bool,int> turnOnSOUT;
      Signal<bool,int> turnOffSOUT;
      
    protected:
      bool signalOutput;
      void turnOn(){ signalOutput = true; }
      bool& turnOnLatch(bool& res, int){ res = signalOutput = true; return res; }

      void turnOff(){ signalOutput = false; }
      bool& turnOffLatch(bool& res, int){ res = signalOutput = false; return res; }

      bool& latchOutput(bool& res, int){ res = signalOutput; return res; }

    public:
      Latch( const std::string& name )
	: Entity(name)
	,outSOUT("Latch("+name+")::output(bool)::out")
	,turnOnSOUT ("Latch("+name+")::output(bool)::turnOnSout")
	,turnOffSOUT("Latch("+name+")::output(bool)::turnOffSout")
      {
        outSOUT.setFunction(boost::bind(&Latch::latchOutput,this,_1,_2));
        turnOnSOUT .setFunction(boost::bind(&Latch::turnOnLatch ,this,_1,_2));
        turnOffSOUT.setFunction(boost::bind(&Latch::turnOffLatch,this,_1,_2));
        signalOutput = false;
        signalRegistration (outSOUT << turnOnSOUT << turnOffSOUT);
        addCommand ("turnOn",
                    makeCommandVoid0 (*this, &Latch::turnOn,
                                      docCommandVoid0 ("Turn on the latch")));
        addCommand ("turnOff",
                    makeCommandVoid0 (*this, &Latch::turnOff,
                                      docCommandVoid0 ("Turn off the latch")));
      }
      
        virtual ~Latch( void ) {};

};
} /* namespace sot */
} /* namespace dynamicgraph */



#endif // #ifndef __SOT_LATCH_H__
