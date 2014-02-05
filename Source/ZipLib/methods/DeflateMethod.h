#pragma once
#include "ICompressionMethod.h"
#include "StoreMethod.h"
#include "../compression/deflate/deflate_encoder.h"
#include "../compression/deflate/deflate_decoder.h"

#include <memory>

class DeflateMethod :
  public ICompressionMethodMayBeStored
{
  public:
    ZIP_METHOD_CLASS_PROLOGUE(
      DeflateMethod,
      deflate_encoder, deflate_decoder,
      /* CompressionMethod */ 8,
      /* VersionNeededToExtract */ 20
    );

    enum class CompressionLevel : int
    {
      L0 = 0,
      L1 = 1,
      L2 = 2,
      L3 = 3,
      L4 = 4,
      L5 = 5,
      L6 = 6,
      L7 = 7,
      L8 = 8,
      L9 = 9,

      Stored = L0,
      Fastest = L1,
      Default = L6,
      Best = L9
    };

    size_t GetBufferCapacity() const { return _props.BufferCapacity; }
    void SetBufferCapacity(size_t bufferCapacity) { _props.BufferCapacity = bufferCapacity; }

    CompressionLevel GetCompressionLevel() const { return static_cast<CompressionLevel>(_props.CompressionLevel); }
    void SetCompressionLevel(CompressionLevel compressionLevel)
    {
      this->SetIsStored(compressionLevel == CompressionLevel::L0);
      _props.CompressionLevel = static_cast<int>(compressionLevel);
    }

  private:
    deflate_encoder_properties _props;
};
