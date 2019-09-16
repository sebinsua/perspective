/******************************************************************************
 *
 * Copyright (c) 2019, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */
#pragma once
#ifdef PSP_ENABLE_PYTHON

#include <perspective/base.h>
#include <perspective/binding.h>
#include <perspective/python/base.h>
#include <arrow/table.h>
#include <arrow/python/pyarrow.h>


namespace perspective {
namespace binding {

void arrow_test(py::object val);

} //namespace binding
} //namespace perspective

#endif
