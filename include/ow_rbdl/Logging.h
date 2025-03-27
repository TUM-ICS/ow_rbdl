/*
 * RBDL - Rigid Body Dynamics Library
 * Copyright (c) 2011-2018 Martin Felis <martin@fysx.org>
 *
 * Licensed under the zlib license. See LICENSE for more details.
 */

#ifndef OW_RBDL_LOGGING_H
#define OW_RBDL_LOGGING_H

#include <sstream>
#include <ow_rbdl/rbdl_config.h>

namespace ow_rbdl{

class LoggingGuard;

/** \def OW_RBDL_ENABLE_LOGGING
 *
 * Enables/Disables logging
 *
 * \warning Logging has a huge impact on performance.
 */
#ifndef OW_RBDL_ENABLE_LOGGING
#define LOG if (false) LogOutput 
#define SUPPRESS_LOGGING ;
#else
#define LOG LogOutput
#define SUPPRESS_LOGGING LoggingGuard _nolog
#endif

extern OW_RBDL_DLLAPI std::ostringstream LogOutput;
OW_RBDL_DLLAPI void ClearLogOutput ();

/** \brief Helper object to ignore any logs that happen during its lifetime
 *
 * If an instance of this class exists all logging gets suppressed. This
 * allows to disable logging for a certain scope or a single function call,
 * e.g.
 *
 * \code
 * {
 *   // logging will be active
 *   do_some_stuff();
 *  
 *   // now create a new scope in which a LoggingGuard instance exists
 *   {
 *     LoggingGuard ignore_logging;
 *    
 *     // as a _Nologging instance exists, all logging will be discarded
 *     do_some_crazy_stuff();
 *   }
 *
 *   // logging will be active again
 *   do_some_more_stuff();
 * }
 * \endcode
 *
 */
class OW_RBDL_DLLAPI LoggingGuard {
  public:
    LoggingGuard() {
      log_backup.str("");
      log_backup << LogOutput.str();
    }
    ~LoggingGuard() {
      LogOutput.str("");
      LogOutput << log_backup.str();
    }

  private:
    std::ostringstream log_backup;
};
}
/* OW_RBDL_LOGGING_H */
#endif
