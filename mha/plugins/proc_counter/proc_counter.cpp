// This file is part of the open HörTech Master Hearing Aid (openMHA)
// Copyright © 2006 2009 2010 2013 2014 2015 2018 2020 2021 HörTech gGmbH
//
// openMHA is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, version 3 of the License.
//
// openMHA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License, version 3 for more details.
//
// You should have received a copy of the GNU Affero General Public License,
// version 3 along with openMHA.  If not, see <http://www.gnu.org/licenses/>.

#include "mha_plugin.hh"

class proc_counter_t : public MHAParser::int_mon_t {
public:
    proc_counter_t(algo_comm_t iac, const std::string &configured_name);
    ~proc_counter_t();
    mha_wave_t* process(mha_wave_t* s);
    mha_spec_t* process(mha_spec_t* s);
    void prepare_(mhaconfig_t&) {}
    void release_() {}
private:
    algo_comm_t ac;
};

proc_counter_t::proc_counter_t(algo_comm_t iac, const std::string &configured_name)
    : MHAParser::int_mon_t("Counter for invocations of signal processing callback"),
      ac(iac)
{
    data = 0;
    ac.insert_var_int(ac.handle, configured_name.c_str(), &data);
}

proc_counter_t::~proc_counter_t()
{
    ac.remove_ref(ac.handle, &data);
}

mha_wave_t* proc_counter_t::process(mha_wave_t* s)
{
    ++data;
    return s;
}

mha_spec_t* proc_counter_t::process(mha_spec_t* s)
{
    ++data;
    return s;
}

MHAPLUGIN_CALLBACKS(proc_counter,proc_counter_t,wave,wave)
MHAPLUGIN_PROC_CALLBACK(proc_counter,proc_counter_t,spec,spec)
MHAPLUGIN_DOCUMENTATION(proc_counter,"testing signalhandling","")

/*
 * Local Variables:
 * c-basic-offset: 4
 * compile-command: "make"
 * indent-tabs-mode: nil
 * End:
 */
