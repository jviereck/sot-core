// Copyright (c) 2018, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of sot-core.
// sot-core is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// sot-core is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// sot-core. If not, see <http://www.gnu.org/licenses/>.

#ifndef __SOT_SWITCH_H__
# define __SOT_SWITCH_H__

#include <dynamic-graph/entity.h>
#include <dynamic-graph/signal.h>
#include <dynamic-graph/signal-ptr.h>
#include <dynamic-graph/signal-time-dependent.h>
#include <dynamic-graph/pool.h>
#include <dynamic-graph/command-bind.h>
#include <dynamic-graph/command-getter.h>

#include <sot/core/config.hh>
#include <sot/core/variadic-op.hh>

namespace dynamicgraph {
  namespace sot {
    /// Switch
    template <typename Value, typename Time = int>
    class SOT_CORE_DLLAPI Switch : public VariadicAbstract<Value,Value,Time>
    {
      DYNAMIC_GRAPH_ENTITY_DECL();

      typedef VariadicAbstract<Value,Value,Time> Base;

      Switch (const std::string& name) :
        Base (name,CLASS_NAME),
        selectionSIN(NULL,"Switch("+name+")::input(int)::selection"),
        boolSelectionSIN(NULL,"Switch("+name+")::input(bool)::boolSelection")
      {
        this->signalRegistration (selectionSIN << boolSelectionSIN);
        this->SOUT.setFunction (boost::bind(&Switch::signal,this,_1,_2));
        this->SOUT.addDependency (selectionSIN);
        this->SOUT.addDependency (boolSelectionSIN);

        using command::makeCommandVoid1;
        std::string docstring =
          "\n"
          "    Set number of input signals\n";
        this->addCommand ("setSignalNumber", makeCommandVoid1
            (*(Base*)this, &Base::setSignalNumber, docstring));

        docstring =
          "\n"
          "    Get number of input signals\n";
        this->addCommand ("getSignalNumber",
            new command::Getter<Base, int> (*this, &Base::getSignalNumber, docstring));
      }

      ~Switch () {}

      /// Header documentation of the python class
      virtual std::string getDocString () const
      {
        return
          "Dynamically select a given signal based on a input information.\n";
      }

      private:
      Value& signal (Value& ret, const Time& time)
      {
        int sel;
        if (selectionSIN.isPlugged()) {
          sel = selectionSIN (time);
        } else {
          const bool& b = boolSelectionSIN(time);
          sel = b ? 1 : 0;
        }
        if (sel < 0 || sel >= int(this->signalsIN.size()))
          throw std::runtime_error ("Signal selection is out of range.");

        ret = this->signalsIN[sel]->access (time);
        return ret;
      }

      SignalPtr <int, Time> selectionSIN;
      SignalPtr <bool, Time> boolSelectionSIN;
    };
  } // namespace sot
} // namespace dynamicgraph
#endif // __SOT_SWITCH_H__
