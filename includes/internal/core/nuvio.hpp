#pragma once
#include "nuvio_namespaces.h"

NUVIO_NAMESPACE_BEGIN

class NuvioApp {
    public:
        NuvioApp(int argc, char** argv);
        void run();
};

NUVIO_NAMESPACE_END