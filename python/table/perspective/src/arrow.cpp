/******************************************************************************
 *
 * Copyright (c) 2019, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */
#ifdef PSP_ENABLE_PYTHON

#include <perspective/base.h>
#include <perspective/binding.h>
#include <perspective/python/base.h>
#include <perspective/python/arrow.h>
#include <arrow/api.h>
#include <arrow/python/pyarrow.h>


namespace perspective {
namespace binding {

void arrow_test(py::object val) {
    std::cout << "here" << std::endl;
    // std::shared_ptr<::arrow::Table> *table;
    // auto out = ::arrow::py::unwrap_table(val.ptr(), table);
    std::cout << ::arrow::py::is_table(val.ptr()) << std::endl;
    std::cout << "here2" << std::endl;
}

} //namespace binding
} //namespace perspective

#endif