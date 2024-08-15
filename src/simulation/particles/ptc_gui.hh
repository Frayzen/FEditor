#pragma once

#include "simulation/particles/ptc_simulation.hh"
#include "gui/gui.hh"

class PtcGUI : public GUI {
  public:
    PtcGUI(PtcSimulation &sim) : GUI(sim) {}
    void update() override;
};
