/******************************************************************************
 *
 * Copyright (c) 2019, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */

#include <perspective/arrow.h>

#include <arrow/api.h>
#include <arrow/io/memory.h>
#include <arrow/ipc/reader.h>

using namespace perspective;
using namespace ::arrow;

namespace perspective {
namespace arrow {

std::vector<std::shared_ptr<RecordBatch>>
parse_arrow(uintptr_t ptr, uint32_t length) {
    std::vector<std::shared_ptr<RecordBatch>> out_batches;

    io::BufferReader buffer_reader(reinterpret_cast<const std::uint8_t*>(ptr), length);
    std::shared_ptr<ipc::RecordBatchFileReader> batch_reader;
    auto status = ipc::RecordBatchFileReader::Open(&buffer_reader, &batch_reader);

    if (!status.ok()) {
        PSP_COMPLAIN_AND_ABORT(status.message());
    } else {                
        auto num_batches = batch_reader->num_record_batches();
        for (int i = 0; i < num_batches; ++i) {
            std::cout << "Reading batch " << (i + 1) << std::endl;
            std::shared_ptr<RecordBatch> chunk;
            auto status = batch_reader->ReadRecordBatch(i, &chunk);
            if (!status.ok()) {
                std::cout << "Error reading Arrow: " << status.message() << std::endl;
            }
            out_batches.push_back(chunk);
        }
        std::cout << out_batches[0]->num_rows() << " x " << out_batches[0]->num_columns() << std::endl;
        
        std::shared_ptr<Schema> schema = out_batches[0]->schema();
        std::vector<std::shared_ptr<Field>> fields = schema->fields();
    }
    return out_batches;
}

}
}