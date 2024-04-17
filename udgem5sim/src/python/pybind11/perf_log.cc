#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "perf_log/logger.hh"

namespace py = pybind11;

namespace gem5
{

void
pybind_init_perf_log(py::module_ &m_native)
{
    py::module_ m = m_native.def_submodule("perf_log");

    m
        .def("openBasimPerflog", &PerfLog::openBasimPerflog)
        // .def("openPerfLog", &PerfLog::openPerfLog)
        .def("openTsvPerfLog", &PerfLog::openTsvPerfLog)
        // .def("writePerfLog", &PerfLog::writePerfLog)
        // .def("writePerfLogUpdown", &PerfLog::writePerfLogUpdown)
        // .def("writePerfLogUpdownV2", &PerfLog::writePerfLogUpdownV2)
        .def("writeTsvPerfLogUpdownEvent", &PerfLog::writeTsvPerfLogUpdownEvent)
        // .def("closePerfLog", &PerfLog::closePerfLog)
        .def("closeTsvPerfLog", &PerfLog::closeTsvPerfLog)
        ;
}

} // namespace gem5
