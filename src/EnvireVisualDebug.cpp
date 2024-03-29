/*
 *  Copyright 2013, DFKI GmbH Robotics Innovation Center
 *
 *  This file is part of the MARS simulation framework.
 *
 *  MARS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  MARS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with MARS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \file EnvireVisualDebug.cpp
 * \author Raul (Raul.Dominguez@dfki.de)
 * \author Anna Born (anna.born@dfki.de)
 * \brief Debug
 *
 * Version 0.1
 */

#include "EnvireVisualDebug.hpp"

#include <mars/plugins/envire_managers/EnvireStorageManager.hpp>

using namespace mars::plugins::envire_visual_debug;
using namespace mars::plugins::envire_managers;

using namespace mars::utils;
using namespace mars::interfaces;

EnvireVisualDebug::EnvireVisualDebug(lib_manager::LibManager *theManager)
  : MarsPluginTemplateGUI(theManager, "EnvireVisualDebug"),
  timeSinceLastUiUpdate(0) {
    graphWindow = new envire::viz::EnvireVisualizerWindow();
}

void EnvireVisualDebug::init() {
  timeSinceLastUiUpdate = 0;
  gui->addGenericMenuAction("../EnvireVisualDebug/showEnvireGraph", 1, this);
}

void EnvireVisualDebug::reset() {}

EnvireVisualDebug::~EnvireVisualDebug() {}

void EnvireVisualDebug::update(sReal time_ms)
{
    if(graphWindow->isVisible())
    {
        timeSinceLastUiUpdate += time_ms;
        if(timeSinceLastUiUpdate > 33) //=> 30 fps
        {
            timeSinceLastUiUpdate = 0;
            graphWindow->redraw();
        }
    }
}

void EnvireVisualDebug::menuAction (int action, bool checked)
{

      graphWindow->displayGraph(control->storage->getGraph(), "center");
      graphWindow->show();
}

DESTROY_LIB(mars::plugins::envire_visual_debug::EnvireVisualDebug);
CREATE_LIB(mars::plugins::envire_visual_debug::EnvireVisualDebug);
