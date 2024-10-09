#include "eogll/version.h"

const char* eogllGetVersionString() {
    return "EOGLL " HEDLEY_STRINGIFY(EOGLL_VERSION_MAJOR) "." HEDLEY_STRINGIFY(EOGLL_VERSION_MINOR) "." HEDLEY_STRINGIFY(EOGLL_VERSION_PATCH);
}