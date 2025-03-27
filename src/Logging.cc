/*
 * RBDL - Rigid Body Dynamics Library
 * Copyright (c) 2011-2018 Martin Felis <martin@fysx.org>
 *
 * Licensed under the zlib license. See LICENSE for more details.
 */

#include "ow_rbdl/Logging.h"

OW_RBDL_DLLAPI std::ostringstream LogOutput;

OW_RBDL_DLLAPI void ClearLogOutput() {
  LogOutput.str("");
}
