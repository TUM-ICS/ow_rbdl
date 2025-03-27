#ifndef OW_RBDL_URDFREADER_H
#define OW_RBDL_URDFREADER_H

#include <ow_rbdl/rbdl_config.h>

namespace ow_rbdl {

struct Model;

namespace Addons {
  OW_RBDL_DLLAPI bool URDFReadFromFile (const char* filename, Model* model, bool floating_base, bool verbose = false);
  OW_RBDL_DLLAPI bool URDFReadFromString (const char* model_xml_string, Model* model, bool floating_base, bool verbose = false);
}

}

/* _OW_RBDL_URDFREADER_H */
#endif
