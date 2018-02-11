#include "System.h"

#include <algorithm>

namespace Core {

  System::System() {
    Module::AddGlobalObserver(this);
  }

  System::~System() {
    Module::RemoveGlobalObserver(this);
  }

  void System::Initialise(Module* const module) {
    // Initialise all inactive modules, most required first.
    const auto& requirements = m_moduleConfig[module].requirements;
    for (auto& req : requirements) {
      if (m_moduleConfig[req].state == State::INACTIVE) {
        Initialise(req);
      }
    }
    module->NotifyObservers(&Module::Observer::onInitialise, module);
    module->Initialise();
  }

  void System::Startup() {
    // Push modules into a vector for sorting.
    std::vector<Module*> modules;
    modules.reserve(m_moduleConfig.size());
    for (auto& config : m_moduleConfig) {
      modules.push_back(config.first);
    }

    // Sort modules in priority order.
    std::sort(modules.begin(), modules.end(), [&](Module* const l, Module* const r) {
      return m_moduleConfig[l].priority < m_moduleConfig[r].priority;
    });

    // Startup each module.
    for (auto& module : modules) {
      module->NotifyObservers(&Module::Observer::onStartup, module);
      module->Startup();
    }

    // TODO: Establish threads for each module after startup.
  }

  void System::Update() {
    // TODO: Check condition of each module and the associated threads.
    for (auto& config : m_moduleConfig) {
      if (config.second.state == State::ACTIVE) {
        auto module = config.first;
        module->NotifyObservers(&Module::Observer::onUpdate, module);
        module->Update();
      }
    }
  }

  void System::Quit() {
    for (auto& config : m_moduleConfig) {
      if (config.second.state < State::QUITTING) {
        Quit(config.first);
      }
    }
  }

  void System::Shutdown() {
    for (auto& config : m_moduleConfig) {
      auto module = config.first;
      // Esnure that the module has quit safely before shutting down.
      if (config.second.state < State::QUITTING) {
        Quit(module);
      }
      module->NotifyObservers(&Module::Observer::onShutdown, module);
      module->Shutdown();
      config.second.state = State::INACTIVE;
    }
  }

  void System::Quit(Module* const module) {
    // Quit all active modules, most dependent first.
    const auto& dependents = m_moduleConfig[module].dependents;
    for (auto& dep : dependents) {
      if (m_moduleConfig[dep].state < State::QUITTING) {
        Quit(dep);
      }
    }
    // TODO: Stop the thread associated with the module.
    module->NotifyObservers(&Module::Observer::onQuit, module);
    module->Quit();
  }

  void System::onInitialise(Module* const module) {
    m_moduleConfig[module].state = State::INITIALISING;
  }

  void System::onStartup(Module* const module) {
    m_moduleConfig[module].state = State::STARTING_UP;
  }

  void System::onUpdate(Module* const module) {
    m_moduleConfig[module].state = State::ACTIVE;
  }

  void System::onQuit(Module* const module) {
    m_moduleConfig[module].state = State::QUITTING;
  }

  void System::onShutdown(Module* const module) {
    m_moduleConfig[module].state = State::SHUTTING_DOWN;
  }

  void System::ConfigureModule(Module* const module, const DTU::String& name) {
    m_moduleConfig[module].name = name;
  }

  void System::ConfigurePriortiy(const DTU::String& name, const int8_t priority) {
    for (auto& config : m_moduleConfig) {
      if (config.second.name == name) {
        config.second.priority = priority;
      }
    }
  }

  void System::ConfigureRequirement(Module* const dependent, Module* const requirement) {
    m_moduleConfig[dependent].requirements.insert(requirement);
    m_moduleConfig[requirement].dependents.insert(dependent);
  }

}