// Break.hh
//
// Copyright (C) 2001 - 2012 Rob Caelers & Raymond Penners
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef BREAK_HH
#define BREAK_HH

#include "config/Config.hh"

#include "IBreak.hh"
#include "Timer.hh"

using namespace workrave;
using namespace workrave::config;

// Forward declarion of external interface.
namespace workrave {
  class IApp;
  class IBreak;
}

class BreakControl;
class ICoreInternal;

class Break :
  public IBreak,
  public IConfiguratorListener
{
public:
  Break();
  virtual ~Break();

  void init(BreakId id, ICoreInternal *core, IApp *app);

  static std::string expand(const std::string &str, BreakId id);
  static std::string get_name(BreakId id);

  std::string expand(const std::string &str);
  std::string get_name() const;
  BreakId get_id() const;

  Timer *get_timer() const;
  BreakControl *get_break_control();

  // IBreak
  virtual bool is_enabled() const;
  virtual bool is_running() const;
  virtual time_t get_elapsed_time() const;
  virtual time_t get_elapsed_idle_time() const;
  virtual time_t get_auto_reset() const;
  virtual bool is_auto_reset_enabled() const;
  virtual time_t get_limit() const;
  virtual bool is_limit_enabled() const;
  virtual bool is_taking() const;

  void set_usage_mode(UsageMode mode);

  bool get_timer_activity_sensitive() const;

  void override(BreakId id);

private:
  void config_changed_notify(const std::string &key);

private:
  void init_defaults();

  void init_timer();
  void load_timer_config();

  void init_break_control();
  void load_break_control_config();

  bool starts_with(const std::string &key, std::string prefix, std::string &timer_name);

private:
  //! Core
  ICoreInternal *core;
  
  //! ID of the break.
  BreakId break_id;

  //! Name of the break (used in configuration)
  std::string break_name;

  //! Break config prefix
  std::string break_prefix;

  //! The Configurator
  IConfigurator::Ptr config;

  //!
  IApp *application;

  //! Interface pointer to the timer.
  Timer *timer;

  //! Interface pointer to the break controller.
  BreakControl *break_control;

  //! Break enabled?
  bool enabled;

  //!
  UsageMode usage_mode;
};

#endif // TIMERDATA_HH
