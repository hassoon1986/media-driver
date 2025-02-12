/*
* Copyright (c) 2020, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
//!
//! \file     mhw_vdbox_vdenc_impl.h
//! \brief    MHW VDBOX VDENC interface common base
//! \details
//!

#ifndef __MHW_VDBOX_VDENC_IMPL_H__
#define __MHW_VDBOX_VDENC_IMPL_H__

#include "mhw_vdbox_vdenc_itf.h"
#include "mhw_impl.h"

#ifdef IGFX_VDENC_INTERFACE_EXT_SUPPORT
#include "mhw_vdbox_vdenc_impl_ext.h"
#endif

namespace mhw
{
namespace vdbox
{
namespace vdenc
{
inline SurfaceFormat MosFormatToVdencSurfaceRawFormat(MOS_FORMAT format)
{
    switch (format)
    {
    case Format_A8R8G8B8:
    case Format_X8R8G8B8:
    case Format_A8B8G8R8:
        return SurfaceFormat::rgba4444;
    case Format_NV12:
    case Format_NV11:
    case Format_P208:
    case Format_IMC1:
    case Format_IMC2:
    case Format_IMC3:
    case Format_IMC4:
        return SurfaceFormat::planar4208;
    case Format_400P:
    case Format_P8:
        return SurfaceFormat::y8Unorm;
    case Format_UYVY:
        return SurfaceFormat::yCrCbSwapY422;
    case Format_YVYU:
        return SurfaceFormat::yCrCbSwapUv422;
    case Format_VYUY:
        return SurfaceFormat::yCrCbSwapUvy422;
    case Format_444P:
    case Format_AYUV:
        return SurfaceFormat::yuv444;
    case Format_YUY2:
    case Format_YUYV:
        return SurfaceFormat::yuv422;
    case Format_P010:
        return SurfaceFormat::p010;
    case Format_R10G10B10A2:
    case Format_B10G10R10A2:
        return SurfaceFormat::r10g10b10a2;
        // Only Y210 supported now, allocated as Y216 format by 3D driver
    case Format_Y210:
    case Format_Y216:
        return SurfaceFormat::y216;
    case Format_Y410:
        return SurfaceFormat::y410;
    case Format_NV21:
        return SurfaceFormat::nv21;
    default:
        return SurfaceFormat::planar4208;
    }
}

inline SurfaceFormat MosFormatToVdencSurfaceReconFormat(MOS_FORMAT format)
{
    switch (format)
    {
    case Format_A8R8G8B8:
    case Format_X8R8G8B8:
    case Format_A8B8G8R8:
        return SurfaceFormat::rgba4444;
    case Format_NV12:
    case Format_IMC1:
    case Format_IMC2:
    case Format_IMC3:
    case Format_IMC4:
        return SurfaceFormat::planar4208;
    case Format_400P:
    case Format_P8:
        return SurfaceFormat::y8Unorm;
    case Format_UYVY:
        return SurfaceFormat::yCrCbSwapY422;
    case Format_YVYU:
        return SurfaceFormat::yCrCbSwapUv422;
    case Format_VYUY:
        return SurfaceFormat::yCrCbSwapUvy422;
    case Format_444P:
    case Format_AYUV:
        return SurfaceFormat::ayuvVariant;
    case Format_YUY2:
    case Format_YUYV:
        return SurfaceFormat::yuyvVariant;
    case Format_P010:
        return SurfaceFormat::p010Variant;
    case Format_R10G10B10A2:
        return SurfaceFormat::r10g10b10a2;
    case Format_Y216:
        return SurfaceFormat::y216Variant;
    case Format_Y410:
        return SurfaceFormat::y416Variant;
    case Format_NV21:
        return SurfaceFormat::nv21;
    default:
        return SurfaceFormat::planar4208;
    }
}

class Impl : public Itf, public mhw::Impl
{
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_CONTROL_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_PIPE_MODE_SELECT);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_SRC_SURFACE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_REF_SURFACE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_DS_REF_SURFACE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_PIPE_BUF_ADDR_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_WEIGHTSOFFSETS_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_HEVC_VP9_TILE_SLICE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_WALKER_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VD_PIPELINE_FLUSH);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_CMD1);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_CMD2);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_CMD3);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_CMD4);
    _MHW_CMD_ALL_DEF_FOR_IMPL(VDENC_CMD5);

public:
    MOS_STATUS EnableVdencRowstoreCacheIfSupported(uint32_t address) override
    {
        MHW_FUNCTION_ENTER;

        if (this->m_vdencRowStoreCache.supported)
        {
            this->m_vdencRowStoreCache.enabled   = true;
            this->m_vdencRowStoreCache.dwAddress = address;
        }

        return MOS_STATUS_SUCCESS;
    }

    MOS_STATUS EnableVdencRowIpdlstoreCacheIfSupported(uint32_t address) override
    {
        MHW_FUNCTION_ENTER;

        if (this->m_vdencIpdlRowstoreCache.supported)
        {
            this->m_vdencIpdlRowstoreCache.enabled   = true;
            this->m_vdencIpdlRowstoreCache.dwAddress = address;
        }

        return MOS_STATUS_SUCCESS;
    }

    MOS_STATUS SetCacheabilitySettings(MHW_MEMORY_OBJECT_CONTROL_PARAMS settings[MOS_CODEC_RESOURCE_USAGE_END_CODEC]) override
    {
        MHW_FUNCTION_ENTER;

        MHW_CHK_NULL_RETURN(settings);

        size_t size = MOS_CODEC_RESOURCE_USAGE_END_CODEC * sizeof(MHW_MEMORY_OBJECT_CONTROL_PARAMS);

        return MOS_SecureMemcpy(m_cacheabilitySettings, size, settings, size);
    }

protected:
    using base_t = Itf;

    Impl(PMOS_INTERFACE osItf) : mhw::Impl(osItf)
    {
        MHW_FUNCTION_ENTER;

        InitRowstoreUserFeatureSettings();
    }

    virtual MOS_STATUS InitRowstoreUserFeatureSettings()
    {
        MHW_FUNCTION_ENTER;

        MOS_USER_FEATURE_VALUE_DATA userFeatureData;
        MEDIA_FEATURE_TABLE *       skuTable = this->m_osItf->pfnGetSkuTable(this->m_osItf);

        MHW_MI_CHK_NULL(skuTable);

        MOS_ZeroMemory(&userFeatureData, sizeof(userFeatureData));
        if (this->m_osItf->bSimIsActive)
        {
            // Disable RowStore Cache on simulation by default
            userFeatureData.u32Data = 1;
        }
        else
        {
            userFeatureData.u32Data = 0;
        }

        userFeatureData.i32DataFlag = MOS_USER_FEATURE_VALUE_DATA_FLAG_CUSTOM_DEFAULT_VALUE_TYPE;
#if (_DEBUG || _RELEASE_INTERNAL)
        MOS_UserFeature_ReadValue_ID(
            nullptr,
            __MEDIA_USER_FEATURE_VALUE_ROWSTORE_CACHE_DISABLE_ID,
            &userFeatureData,
            m_osItf->pOsContext);
#endif  // _DEBUG || _RELEASE_INTERNAL
        bool rowstoreCachingSupported = userFeatureData.i32Data ? false : true;

        if (!rowstoreCachingSupported)
        {
            return MOS_STATUS_SUCCESS;
        }

        MOS_ZeroMemory(&userFeatureData, sizeof(userFeatureData));
#if (_DEBUG || _RELEASE_INTERNAL)
        MOS_UserFeature_ReadValue_ID(
            nullptr,
            __MEDIA_USER_FEATURE_VALUE_VDENCROWSTORECACHE_DISABLE_ID,
            &userFeatureData,
            m_osItf->pOsContext);
#endif  // _DEBUG || _RELEASE_INTERNAL
        this->m_vdencRowStoreCache.supported = userFeatureData.i32Data ? false : true;

        MOS_ZeroMemory(&userFeatureData, sizeof(userFeatureData));
#if (_DEBUG || _RELEASE_INTERNAL)
        MOS_UserFeature_ReadValue_ID(
            nullptr,
            __MEDIA_USER_FEATURE_VALUE_INTRAROWSTORECACHE_DISABLE_ID,
            &userFeatureData,
            m_osItf->pOsContext);
#endif  // _DEBUG || _RELEASE_INTERNAL
        this->m_vdencIpdlRowstoreCache.supported = userFeatureData.i32Data ? false : true;

        return MOS_STATUS_SUCCESS;
    }

protected:
    vdbox::RowStoreCache             m_vdencRowStoreCache                                       = {};
    vdbox::RowStoreCache             m_vdencIpdlRowstoreCache                                   = {};
    MHW_MEMORY_OBJECT_CONTROL_PARAMS m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_END_CODEC] = {};
};

template <typename cmd_t>
class ImplGeneric : public Impl
{
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_CONTROL_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_PIPE_MODE_SELECT);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_SRC_SURFACE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_REF_SURFACE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_DS_REF_SURFACE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_PIPE_BUF_ADDR_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_WEIGHTSOFFSETS_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_HEVC_VP9_TILE_SLICE_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_WALKER_STATE);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VD_PIPELINE_FLUSH);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_CMD1);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_CMD2);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_CMD3);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_CMD4);
    _MHW_CMD_ALL_DEF_FOR_IMPL_GENERIC(VDENC_CMD5);

protected:
    using base_t = Impl;

    ImplGeneric(PMOS_INTERFACE osItf) : base_t(osItf){};

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_CONTROL_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_CONTROL_STATE);

#define DO_FIELDS() \
    DO_FIELD(DW1, VdencInitialization, params->vdencInitialization)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_PIPE_MODE_SELECT)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_PIPE_MODE_SELECT);

#define DO_FIELDS()                                                                            \
    DO_FIELD(DW1, StandardSelect, params->standardSelect);                                     \
    DO_FIELD(DW1, ScalabilityMode, params->scalabilityMode);                                   \
    DO_FIELD(DW1, FrameStatisticsStreamOutEnable, params->frameStatisticsStreamOut);           \
    DO_FIELD(DW1, VdencPakObjCmdStreamOutEnable, params->pakObjCmdStreamOut);                  \
    DO_FIELD(DW1, TlbPrefetchEnable, params->tlbPrefetch);                                     \
    DO_FIELD(DW1, PakThresholdCheckEnable, params->dynamicSlice);                              \
    DO_FIELD(DW1, VdencStreamInEnable, params->streamIn);                                      \
    DO_FIELD(DW1, BitDepth, params->bitDepthMinus8);                                           \
    DO_FIELD(DW1, PakChromaSubSamplingType, params->chromaType);                               \
    DO_FIELD(DW1, OutputRangeControlAfterColorSpaceConversion, params->outputRangeControlCsc); \
    DO_FIELD(DW1, TileReplayEnable, params->tileBasedReplayMode);                              \
    DO_FIELD(DW1, IsRandomAccess, params->randomAccess);                                       \
    DO_FIELD(DW1, RgbEncodingEnable, params->rgbEncodingMode);                                 \
    DO_FIELD(DW1, StreamingBufferConfig, params->streamingBufferConfig);                       \
                                                                                               \
    DO_FIELD(DW2, HmeRegionPreFetchenable, params->hmeRegionPrefetch);                         \
    DO_FIELD(DW2, Topprefetchenablemode, params->topPrefetchEnableMode);                       \
    DO_FIELD(DW2, LeftpreFetchatwraparound, params->leftPrefetchAtWrapAround);                 \
    DO_FIELD(DW2, Verticalshift32Minus1, params->verticalShift32Minus1);                       \
    DO_FIELD(DW2, Hzshift32Minus1, params->hzShift32Minus1);                                   \
    DO_FIELD(DW2, NumVerticalReqMinus1, params->numVerticalReqMinus1);                         \
    DO_FIELD(DW2, Numhzreqminus1, params->numHzReqMinus1);                                     \
    DO_FIELD(DW2, PreFetchOffsetForReferenceIn16PixelIncrement, params->prefetchOffset);       \
                                                                                               \
    DO_FIELD(DW5, CaptureMode, params->captureMode);                                           \
    DO_FIELD(DW5, ParallelCaptureAndEncodeSessionId, params->wirelessSessionId);               \
    DO_FIELD(DW5, TailPointerReadFrequency, params->tailPointerReadFrequency);                 \
    DO_FIELD(DW5, QuantizationPrecisionOptimization, params->quantizationPrecision);           \
    DO_FIELD(DW5, LatencyToleratePreFetchEnable, params->latencyTolerate);                     \
    __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_PIPE_MODE_SELECT_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_SRC_SURFACE_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_SRC_SURFACE_STATE);

#define DO_FIELDS()                                                                                                 \
    DO_FIELD(Dwords25.DW0, Width, params->width - 1);                                                               \
    DO_FIELD(Dwords25.DW0, Height, params->height - 1);                                                             \
    DO_FIELD(Dwords25.DW0, ColorSpaceSelection, params->colorSpaceSelection);                                       \
    DO_FIELD(Dwords25.DW0, CrVCbUPixelOffsetVDirection, params->vDirection);                                        \
    DO_FIELD(Dwords25.DW0, SurfaceFormatByteSwizzle, params->displayFormatSwizzle);                                 \
                                                                                                                    \
    DO_FIELD(Dwords25.DW1, TileMode, GetHwTileType(params->tileType, params->tileModeGmm, params->gmmTileEn));      \
    DO_FIELD(Dwords25.DW1, SurfaceFormat, static_cast<uint32_t>(MosFormatToVdencSurfaceRawFormat(params->format))); \
    DO_FIELD(Dwords25.DW1, SurfacePitch, params->pitch - 1);                                                        \
                                                                                                                    \
    DO_FIELD(Dwords25.DW2, YOffsetForUCb, params->uOffset);                                                         \
    DO_FIELD(Dwords25.DW3, YOffsetForVCr, params->vOffset)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_REF_SURFACE_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_REF_SURFACE_STATE);

#define DO_FIELDS()                                                                                                   \
    DO_FIELD(Dwords25.DW0, Width, params->width - 1);                                                                 \
    DO_FIELD(Dwords25.DW0, Height, params->height - 1);                                                               \
    DO_FIELD(Dwords25.DW0, CrVCbUPixelOffsetVDirection, params->vDirection);                                          \
                                                                                                                      \
    DO_FIELD(Dwords25.DW1, TileMode, GetHwTileType(params->tileType, params->tileModeGmm, params->gmmTileEn));        \
    DO_FIELD(Dwords25.DW1, SurfacePitch, params->pitch - 1);                                                          \
    DO_FIELD(Dwords25.DW1, SurfaceFormat, static_cast<uint32_t>(MosFormatToVdencSurfaceReconFormat(params->format))); \
                                                                                                                      \
    DO_FIELD(Dwords25.DW2, YOffsetForUCb, params->uOffset);                                                           \
    DO_FIELD(Dwords25.DW3, YOffsetForVCr, params->vOffset)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_DS_REF_SURFACE_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_DS_REF_SURFACE_STATE);

        const bool stage2 = params->widthStage2 && params->heightStage2 && params->pitchStage2;

#define DO_FIELDS()                                                                                                                           \
    DO_FIELD(Dwords25.DW0, Width, params->widthStage1 - 1);                                                                                   \
    DO_FIELD(Dwords25.DW0, Height, params->heightStage1 - 1);                                                                                 \
    DO_FIELD(Dwords25.DW0, CrVCbUPixelOffsetVDirection, params->vDirectionStage1);                                                            \
                                                                                                                                              \
    DO_FIELD(Dwords25.DW1, TileMode, GetHwTileType(params->tileTypeStage1, params->tileModeGmmStage1, params->gmmTileEnStage1));              \
    DO_FIELD(Dwords25.DW1, SurfaceFormat, cmd_t::VDENC_Surface_State_Fields_CMD::SURFACE_FORMAT_PLANAR_420_8);                                \
    DO_FIELD(Dwords25.DW1, SurfacePitch, params->pitchStage1 - 1);                                                                            \
                                                                                                                                              \
    DO_FIELD(Dwords25.DW2, YOffsetForUCb, params->uOffsetStage1);                                                                             \
                                                                                                                                              \
    DO_FIELD(Dwords25.DW3, YOffsetForVCr, params->vOffsetStage1);                                                                             \
                                                                                                                                              \
    DO_FIELD(Dwords69.DW0, Width, stage2 ? params->widthStage2 - 1 : 0);                                                                      \
    DO_FIELD(Dwords69.DW0, Height, stage2 ? params->heightStage2 - 1 : 0);                                                                    \
    DO_FIELD(Dwords69.DW0, CrVCbUPixelOffsetVDirection, stage2 ? params->vDirectionStage2 : 0);                                               \
                                                                                                                                              \
    DO_FIELD(Dwords69.DW1, TileMode, stage2 ? GetHwTileType(params->tileTypeStage2, params->tileModeGmmStage2, params->gmmTileEnStage2) : 0); \
    DO_FIELD(Dwords69.DW1, SurfaceFormat, stage2 ? cmd_t::VDENC_Surface_State_Fields_CMD::SURFACE_FORMAT_PLANAR_420_8 : 0);                   \
    DO_FIELD(Dwords69.DW1, SurfacePitch, stage2 ? params->pitchStage2 - 1 : 0);                                                               \
                                                                                                                                              \
    DO_FIELD(Dwords69.DW2, YOffsetForUCb, stage2 ? params->uOffsetStage2 : 0);                                                                \
                                                                                                                                              \
    DO_FIELD(Dwords69.DW3, YOffsetForVCr, stage2 ? params->vOffsetStage2 : 0)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_PIPE_BUF_ADDR_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_PIPE_BUF_ADDR_STATE);

        MHW_RESOURCE_PARAMS resourceParams;

        if (params->surfaceRaw)
        {
            cmd->OriginalUncompressedPicture.PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(params->mmcStateRaw);
            cmd->OriginalUncompressedPicture.PictureFields.DW0.CompressionType         = MmcRcEnabled(params->mmcStateRaw);
            cmd->OriginalUncompressedPicture.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_ORIGINAL_UNCOMPRESSED_PICTURE_ENCODE].Value;
            cmd->OriginalUncompressedPicture.PictureFields.DW0.CompressionFormat = params->compressionFormatRaw;

            resourceParams                 = {};
            resourceParams.presResource    = &params->surfaceRaw->OsResource;
            resourceParams.dwOffset        = params->surfaceRaw->dwOffset;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->OriginalUncompressedPicture.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(OriginalUncompressedPicture.LowerAddress);
            resourceParams.bIsWritable     = false;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (this->m_vdencRowStoreCache.enabled)
        {
            cmd->RowStoreScratchBuffer.BufferPictureFields.DW0.CacheSelect = cmd_t::VDENC_Surface_Control_Bits_CMD::CACHE_SELECT_UNNAMED1;
            cmd->RowStoreScratchBuffer.LowerAddress.DW0.Value              = this->m_vdencRowStoreCache.dwAddress << 6;
        }
        else if (!Mos_ResourceIsNull(params->intraRowStoreScratchBuffer))
        {
            cmd->RowStoreScratchBuffer.BufferPictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_VDENC_ROW_STORE_BUFFER_CODEC].Value;

            resourceParams.presResource    = params->intraRowStoreScratchBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->RowStoreScratchBuffer.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(RowStoreScratchBuffer.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->streamOutBuffer))
        {
            cmd->VdencStatisticsStreamout.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_STREAMOUT_DATA_CODEC].Value;

            resourceParams.presResource    = params->streamOutBuffer;
            resourceParams.dwOffset        = params->streamOutOffset;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->VdencStatisticsStreamout.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(VdencStatisticsStreamout.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->streamInBuffer))
        {
            cmd->StreaminDataPicture.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_VDENC_STREAMIN_CODEC].Value;

            resourceParams.presResource    = params->streamInBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->StreaminDataPicture.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(StreaminDataPicture.LowerAddress);
            resourceParams.bIsWritable     = false;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        typename cmd_t::VDENC_Reference_Picture_CMD *fwdRefs[] =
            {&cmd->FwdRef0, &cmd->FwdRef1, &cmd->FwdRef2, &cmd->BwdRef0};
        uint32_t fwdRefsDwLoaction[] =
            {_MHW_CMD_DW_LOCATION(FwdRef0), _MHW_CMD_DW_LOCATION(FwdRef1), _MHW_CMD_DW_LOCATION(FwdRef2)};

        typename cmd_t::VDENC_Down_Scaled_Reference_Picture_CMD *fwdRefsDsStage1[] =
            {&cmd->DsFwdRef0, &cmd->DsFwdRef1};
        uint32_t fwdRefsDsStage1DwLoaction[] =
            {_MHW_CMD_DW_LOCATION(DsFwdRef0), _MHW_CMD_DW_LOCATION(DsFwdRef1)};

        typename cmd_t::VDENC_Down_Scaled_Reference_Picture_CMD *fwdRefsDsStage2[] =
            {&cmd->DsFwdRef04X, &cmd->DsFwdRef14X, &cmd->Additional4xDsFwdRef};
        uint32_t fwdRefsDsStage2DwLoaction[] =
            {_MHW_CMD_DW_LOCATION(DsFwdRef04X), _MHW_CMD_DW_LOCATION(DsFwdRef14X), _MHW_CMD_DW_LOCATION(Additional4xDsFwdRef)};

        uint8_t refIdx;
        for (refIdx = 0; refIdx < params->numActiveRefL0; refIdx++)
        {
            if (!Mos_ResourceIsNull(params->refs[refIdx]) && refIdx < sizeof(fwdRefs) / sizeof(fwdRefs[0]))
            {
                MOS_SURFACE details = {};
                details.Format      = Format_Invalid;
                MHW_CHK_STATUS_RETURN(this->m_osItf->pfnGetResourceInfo(this->m_osItf, params->refs[refIdx], &details));

                resourceParams.presResource    = params->refs[refIdx];
                resourceParams.dwOffset        = details.RenderOffset.YUV.Y.BaseOffset;
                resourceParams.dwLocationInCmd = fwdRefsDwLoaction[refIdx];
                resourceParams.bIsWritable     = false;
                resourceParams.pdwCmd          = (uint32_t *)&fwdRefs[refIdx]->LowerAddress;
                resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                auto mmcMode = (params->mmcStatePostDeblock != MOS_MEMCOMP_DISABLED) ? params->mmcStatePostDeblock : params->mmcStatePreDeblock;

                fwdRefs[refIdx]->PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                fwdRefs[refIdx]->PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                fwdRefs[refIdx]->PictureFields.DW0.MemoryObjectControlState =
                    this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;
                fwdRefs[refIdx]->PictureFields.DW0.CompressionFormat = params->compressionFormatRecon;

                MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                    this->m_osItf,
                    this->m_currentCmdBuf,
                    &resourceParams));
            }

            if (!Mos_ResourceIsNull(params->refsDsStage1[refIdx]) && refIdx < sizeof(fwdRefsDsStage1) / sizeof(fwdRefsDsStage1[0]))
            {
                MOS_SURFACE details = {};
                details.Format      = Format_Invalid;
                MHW_CHK_STATUS_RETURN(this->m_osItf->pfnGetResourceInfo(this->m_osItf, params->refsDsStage1[refIdx], &details));

                resourceParams.presResource    = params->refsDsStage1[refIdx];
                resourceParams.dwOffset        = details.RenderOffset.YUV.Y.BaseOffset;
                resourceParams.dwLocationInCmd = fwdRefsDsStage1DwLoaction[refIdx];
                resourceParams.bIsWritable     = false;
                resourceParams.pdwCmd          = (uint32_t *)&(fwdRefsDsStage1[refIdx]->LowerAddress);
                resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                auto mmcMode = params->mmcStateDsStage1;

                fwdRefsDsStage1[refIdx]->PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                fwdRefsDsStage1[refIdx]->PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                fwdRefsDsStage1[refIdx]->PictureFields.DW0.MemoryObjectControlState =
                    this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

                MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                    this->m_osItf,
                    this->m_currentCmdBuf,
                    &resourceParams));
            }

            if (!Mos_ResourceIsNull(params->refsDsStage2[refIdx]) && refIdx < sizeof(fwdRefsDsStage2) / sizeof(fwdRefsDsStage2[0]))
            {
                MOS_SURFACE details = {};
                details.Format      = Format_Invalid;
                MHW_CHK_STATUS_RETURN(this->m_osItf->pfnGetResourceInfo(this->m_osItf, params->refsDsStage2[refIdx], &details));

                resourceParams.presResource    = params->refsDsStage2[refIdx];
                resourceParams.dwOffset        = details.RenderOffset.YUV.Y.BaseOffset;
                resourceParams.dwLocationInCmd = fwdRefsDsStage2DwLoaction[refIdx];
                resourceParams.bIsWritable     = false;
                resourceParams.pdwCmd          = (uint32_t *)&(fwdRefsDsStage2[refIdx]->LowerAddress);
                resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                auto mmcMode = params->mmcStateDsStage2;

                fwdRefsDsStage2[refIdx]->PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                fwdRefsDsStage2[refIdx]->PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                fwdRefsDsStage2[refIdx]->PictureFields.DW0.MemoryObjectControlState =
                    this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

                MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                    this->m_osItf,
                    this->m_currentCmdBuf,
                    &resourceParams));

                if (params->numActiveRefL0 == 2 && params->numActiveRefL1 == 1 && refIdx == 1)
                {
                    resourceParams.dwLocationInCmd = fwdRefsDsStage2DwLoaction[refIdx + 1];
                    resourceParams.pdwCmd          = (uint32_t *)&(fwdRefsDsStage2[refIdx + 1]->LowerAddress);
                    resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                    fwdRefsDsStage2[refIdx + 1]->PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                    fwdRefsDsStage2[refIdx + 1]->PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                    fwdRefsDsStage2[refIdx + 1]->PictureFields.DW0.MemoryObjectControlState =
                        this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

                    MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                        this->m_osItf,
                        this->m_currentCmdBuf,
                        &resourceParams));
                }
            }
        }

        if (!params->lowDelayB && params->numActiveRefL1)
        {
            if (!Mos_ResourceIsNull(params->refs[refIdx]))
            {
                MOS_SURFACE details = {};
                details.Format      = Format_Invalid;
                MHW_CHK_STATUS_RETURN(this->m_osItf->pfnGetResourceInfo(this->m_osItf, params->refs[refIdx], &details));

                resourceParams.presResource    = params->refs[refIdx];
                resourceParams.dwOffset        = details.RenderOffset.YUV.Y.BaseOffset;
                resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(BwdRef0);
                resourceParams.bIsWritable     = false;
                resourceParams.pdwCmd          = (uint32_t *)&(cmd->BwdRef0.LowerAddress);
                resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                auto mmcMode = (params->mmcStatePostDeblock != MOS_MEMCOMP_DISABLED) ? params->mmcStatePostDeblock : params->mmcStatePreDeblock;

                cmd->BwdRef0.PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                cmd->BwdRef0.PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                cmd->BwdRef0.PictureFields.DW0.MemoryObjectControlState =
                    this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;
                cmd->BwdRef0.PictureFields.DW0.CompressionFormat = params->compressionFormatRecon;

                MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                    this->m_osItf,
                    this->m_currentCmdBuf,
                    &resourceParams));
            }

            if (!Mos_ResourceIsNull(params->refsDsStage1[refIdx]))
            {
                MOS_SURFACE details = {};
                details.Format      = Format_Invalid;
                MHW_CHK_STATUS_RETURN(this->m_osItf->pfnGetResourceInfo(this->m_osItf, params->refsDsStage1[refIdx], &details));

                resourceParams.presResource    = params->refsDsStage1[refIdx];
                resourceParams.dwOffset        = details.RenderOffset.YUV.Y.BaseOffset;
                resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(DsBwdRef0);
                resourceParams.bIsWritable     = false;
                resourceParams.pdwCmd          = (uint32_t *)&(cmd->DsBwdRef0.LowerAddress);
                resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                auto mmcMode = params->mmcStateDsStage1;

                cmd->DsBwdRef0.PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                cmd->DsBwdRef0.PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                cmd->DsBwdRef0.PictureFields.DW0.MemoryObjectControlState =
                    this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

                MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                    this->m_osItf,
                    this->m_currentCmdBuf,
                    &resourceParams));
            }

            if (!Mos_ResourceIsNull(params->refsDsStage2[refIdx]))
            {
                MOS_SURFACE details = {};
                details.Format      = Format_Invalid;
                MHW_CHK_STATUS_RETURN(this->m_osItf->pfnGetResourceInfo(this->m_osItf, params->refsDsStage2[refIdx], &details));

                resourceParams.presResource    = params->refsDsStage2[refIdx];
                resourceParams.dwOffset        = details.RenderOffset.YUV.Y.BaseOffset;
                resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(DsBwdRef04X);
                resourceParams.bIsWritable     = false;
                resourceParams.pdwCmd          = (uint32_t *)&(cmd->DsBwdRef04X.LowerAddress);
                resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

                auto mmcMode = params->mmcStateDsStage2;

                cmd->DsBwdRef04X.PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
                cmd->DsBwdRef04X.PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
                cmd->DsBwdRef04X.PictureFields.DW0.MemoryObjectControlState =
                    this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

                MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                    this->m_osItf,
                    this->m_currentCmdBuf,
                    &resourceParams));
            }
        }

        if (!Mos_ResourceIsNull(params->colocatedMvReadBuffer))
        {
            resourceParams.presResource    = params->colocatedMvReadBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->ColocatedMv.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(ColocatedMv.LowerAddress);
            resourceParams.bIsWritable     = false;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            cmd->ColocatedMv.PictureFields.DW0.MemoryCompressionEnable = 0;
            cmd->ColocatedMv.PictureFields.DW0.CompressionType         = 0;
            cmd->ColocatedMv.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->colMvTempBuffer[0]))
        {
            resourceParams.presResource    = params->colMvTempBuffer[0];
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->ColocatedMv.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(ColocatedMv.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            cmd->ColocatedMv.PictureFields.DW0.MemoryCompressionEnable = 0;
            cmd->ColocatedMv.PictureFields.DW0.CompressionType         = 0;
            cmd->ColocatedMv.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (params->surfaceDsStage1)
        {
            resourceParams.presResource    = &params->surfaceDsStage1->OsResource;
            resourceParams.dwOffset        = params->surfaceDsStage1->dwOffset;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->ScaledReferenceSurfaceStage1.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(ScaledReferenceSurfaceStage1.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            auto mmcMode = params->mmcStateDsStage1;

            cmd->ScaledReferenceSurfaceStage1.PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
            cmd->ScaledReferenceSurfaceStage1.PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
            cmd->ScaledReferenceSurfaceStage1.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (params->surfaceDsStage2)
        {
            resourceParams.presResource    = &params->surfaceDsStage2->OsResource;
            resourceParams.dwOffset        = params->surfaceDsStage2->dwOffset;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->ScaledReferenceSurfaceStage2.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(ScaledReferenceSurfaceStage2.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            auto mmcMode = params->mmcStateDsStage2;

            cmd->ScaledReferenceSurfaceStage2.PictureFields.DW0.MemoryCompressionEnable = MmcEnabled(mmcMode);
            cmd->ScaledReferenceSurfaceStage2.PictureFields.DW0.CompressionType         = MmcRcEnabled(mmcMode);
            cmd->ScaledReferenceSurfaceStage2.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->pakObjCmdStreamOutBuffer))
        {
            resourceParams.presResource    = params->pakObjCmdStreamOutBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->VdencLcuPakObjCmdBuffer.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(VdencLcuPakObjCmdBuffer.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            cmd->VdencLcuPakObjCmdBuffer.PictureFields.DW0.MemoryCompressionEnable = 0;
            cmd->VdencLcuPakObjCmdBuffer.PictureFields.DW0.CompressionType         = 0;
            cmd->VdencLcuPakObjCmdBuffer.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->segmentMapStreamInBuffer))
        {
            resourceParams.presResource    = params->segmentMapStreamInBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->Vp9SegmentationMapStreaminBuffer.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(Vp9SegmentationMapStreaminBuffer.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->segmentMapStreamOutBuffer))
        {
            resourceParams.presResource    = params->segmentMapStreamOutBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->Vp9SegmentationMapStreamoutBuffer.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(Vp9SegmentationMapStreamoutBuffer.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        cmd->DW61.WeightsHistogramStreamoutOffset = 3 * MHW_CACHELINE_SIZE;

        if (!Mos_ResourceIsNull(params->tileRowStoreBuffer))
        {
            resourceParams.presResource    = params->tileRowStoreBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->VdencTileRowStoreBuffer.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(VdencTileRowStoreBuffer.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            cmd->VdencTileRowStoreBuffer.BufferPictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_VDENC_ROW_STORE_BUFFER_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (this->m_vdencIpdlRowstoreCache.enabled)
        {
            cmd->IntraPredictionRowstoreBaseAddress.BufferPictureFields.DW0.CacheSelect = cmd_t::VDENC_Surface_Control_Bits_CMD::CACHE_SELECT_UNNAMED1;
            cmd->IntraPredictionRowstoreBaseAddress.LowerAddress.DW0.Value              = m_vdencIpdlRowstoreCache.dwAddress << 6;
        }
        else if (!Mos_ResourceIsNull(params->mfdIntraRowStoreScratchBuffer))
        {
            resourceParams.presResource    = params->mfdIntraRowStoreScratchBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->IntraPredictionRowstoreBaseAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(IntraPredictionRowstoreBaseAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            cmd->IntraPredictionRowstoreBaseAddress.BufferPictureFields.DW0.MemoryObjectControlState =
                m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_INTRA_ROWSTORE_SCRATCH_BUFFER_CODEC].Value;
            cmd->IntraPredictionRowstoreBaseAddress.BufferPictureFields.DW0.MemoryCompressionEnable = 0;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->cumulativeCuCountStreamOutBuffer))
        {
            resourceParams.presResource    = params->cumulativeCuCountStreamOutBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->VdencCumulativeCuCountStreamoutSurface.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(VdencCumulativeCuCountStreamoutSurface.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        if (!Mos_ResourceIsNull(params->colocatedMvWriteBuffer))
        {
            resourceParams.presResource    = params->colocatedMvWriteBuffer;
            resourceParams.dwOffset        = 0;
            resourceParams.pdwCmd          = (uint32_t *)&(cmd->ColocatedMvAvcWriteBuffer.LowerAddress);
            resourceParams.dwLocationInCmd = _MHW_CMD_DW_LOCATION(ColocatedMvAvcWriteBuffer.LowerAddress);
            resourceParams.bIsWritable     = true;
            resourceParams.HwCommandType   = MOS_VDENC_PIPE_BUF_ADDR;

            cmd->ColocatedMvAvcWriteBuffer.PictureFields.DW0.MemoryCompressionEnable = 0;
            cmd->ColocatedMvAvcWriteBuffer.PictureFields.DW0.CompressionType         = 0;
            cmd->ColocatedMvAvcWriteBuffer.PictureFields.DW0.MemoryObjectControlState =
                this->m_cacheabilitySettings[MOS_CODEC_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC].Value;

            MHW_CHK_STATUS_RETURN(this->AddResourceToCmd(
                this->m_osItf,
                this->m_currentCmdBuf,
                &resourceParams));
        }

        __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_PIPE_BUF_ADDR_STATE_IMPL_EXT);

        return MOS_STATUS_SUCCESS;
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_WEIGHTSOFFSETS_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_WEIGHTSOFFSETS_STATE);

#define DO_FIELDS()                                                                                                     \
    DO_FIELD(DW1, WeightsForwardReference0, Clip3(-128, 127, params->weightsLuma[0][0] + params->denomLuma));           \
    DO_FIELD(DW1, OffsetForwardReference0, params->offsetsLuma[0][0]);                                                  \
    DO_FIELD(DW1, WeightsForwardReference1, Clip3(-128, 127, params->weightsLuma[0][1] + params->denomLuma));           \
    DO_FIELD(DW1, OffsetForwardReference1, params->offsetsLuma[0][1]);                                                  \
                                                                                                                        \
    DO_FIELD(DW2, WeightsForwardReference2, Clip3(-128, 127, params->weightsLuma[0][2] + params->denomLuma));           \
    DO_FIELD(DW2, OffsetForwardReference2, params->offsetsLuma[0][2]);                                                  \
    DO_FIELD(DW2, WeightsBackwardReference0, Clip3(-128, 127, params->weightsLuma[1][0] + params->denomLuma));          \
    DO_FIELD(DW2, OffsetBackwardReference0, params->offsetsLuma[1][0]);                                                 \
                                                                                                                        \
    DO_FIELD(DW3, CbWeightsForwardReference0, Clip3(-128, 127, params->weightsChroma[0][0][0] + params->denomChroma));  \
    DO_FIELD(DW3, CbOffsetForwardReference0, params->offsetsChroma[0][0][0]);                                           \
    DO_FIELD(DW3, CbWeightsForwardReference1, Clip3(-128, 127, params->weightsChroma[0][1][0] + params->denomChroma));  \
    DO_FIELD(DW3, CbOffsetForwardReference1, params->offsetsChroma[0][1][0]);                                           \
                                                                                                                        \
    DO_FIELD(DW4, CbWeightsForwardReference2, Clip3(-128, 127, params->weightsChroma[0][2][0] + params->denomChroma));  \
    DO_FIELD(DW4, CbOffsetForwardReference2, params->offsetsChroma[0][2][0]);                                           \
    DO_FIELD(DW4, CbWeightsBackwardReference0, Clip3(-128, 127, params->weightsChroma[1][0][0] + params->denomChroma)); \
    DO_FIELD(DW4, CbOffsetBackwardReference0, params->offsetsChroma[1][0][0]);                                          \
                                                                                                                        \
    DO_FIELD(DW5, CrWeightsForwardReference0, Clip3(-128, 127, params->weightsChroma[0][0][1] + params->denomChroma));  \
    DO_FIELD(DW5, CrOffsetForwardReference0, params->offsetsChroma[0][0][1]);                                           \
    DO_FIELD(DW5, CrWeightsForwardReference1, Clip3(-128, 127, params->weightsChroma[0][1][1] + params->denomChroma));  \
    DO_FIELD(DW5, CrOffsetForwardReference1, params->offsetsChroma[0][1][1]);                                           \
                                                                                                                        \
    DO_FIELD(DW6, CrWeightsForwardReference2, Clip3(-128, 127, params->weightsChroma[0][2][1] + params->denomChroma));  \
    DO_FIELD(DW6, CrOffsetForwardReference2, params->offsetsChroma[0][2][1]);                                           \
    DO_FIELD(DW6, CrWeightsBackwardReference0, Clip3(-128, 127, params->weightsChroma[1][0][1] + params->denomChroma)); \
    DO_FIELD(DW6, CrOffsetBackwardReference0, params->offsetsChroma[1][0][1])

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_HEVC_VP9_TILE_SLICE_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_HEVC_VP9_TILE_SLICE_STATE);

#define DO_FIELDS()                                                                                                          \
    DO_FIELD(DW3, NumParEngine, params->numPipe);                                                                            \
    DO_FIELD(DW3, TileNumber, params->tileId);                                                                               \
    DO_FIELD(DW3, TileRowStoreSelect, params->tileRowStoreSelect);                                                           \
    DO_FIELD(DW3, Log2WeightDenomLuma, params->log2WeightDenomLuma);                                                         \
    DO_FIELD(DW3, HevcVp9Log2WeightDenomLuma, params->hevcVp9Log2WeightDenomLuma);                                           \
    DO_FIELD(DW3, Log2WeightDenomChroma, params->log2WeightDenomChroma);                                                     \
                                                                                                                             \
    DO_FIELD(DW4, TileStartCtbX, params->tileStartLCUX * params->ctbSize);                                                   \
    DO_FIELD(DW4, TileStartCtbY, params->tileStartLCUY * params->ctbSize);                                                   \
                                                                                                                             \
    DO_FIELD(DW5, TileWidth, (params->tileWidth >= 256 ? MOS_ALIGN_CEIL(params->tileWidth, 8) : params->tileWidth) - 1);     \
    DO_FIELD(DW5, TileHeight, (params->tileHeight >= 128 ? MOS_ALIGN_CEIL(params->tileHeight, 8) : params->tileHeight) - 1); \
                                                                                                                             \
    DO_FIELD(DW6, StreaminOffsetEnable, params->tileEnable);                                                                 \
    DO_FIELD(DW6, TileStreaminOffset, params->tileStreamInOffset);                                                           \
                                                                                                                             \
    DO_FIELD(DW7, RowStoreOffsetEnable, cmd->DW4.TileStartCtbY == 0 ? params->tileEnable : 0);                               \
    DO_FIELD(DW7, TileRowstoreOffset, cmd->DW4.TileStartCtbY == 0 ? cmd->DW4.TileStartCtbX / 32 : 0);                        \
                                                                                                                             \
    DO_FIELD(DW8, TileStreamoutOffsetEnable, params->tileEnable);                                                            \
    DO_FIELD(DW8, TileStreamoutOffset, params->tileId * 19);                                                                 \
                                                                                                                             \
    DO_FIELD(DW9, LcuStreamOutOffsetEnable, params->tileEnable);                                                             \
    DO_FIELD(DW9, TileLcuStreamOutOffset, params->tileLCUStreamOutOffset);                                                   \
                                                                                                                             \
    DO_FIELD(DW17, CumulativeCuTileOffsetEnable, params->tileEnable);                                                        \
    DO_FIELD(DW17, CumulativeCuTileOffset, params->cumulativeCUTileOffset);                                                  \
    __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_HEVC_VP9_TILE_SLICE_STATE_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_WALKER_STATE)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_WALKER_STATE);

#define DO_FIELDS()                                                                \
    DO_FIELD(DW1, FirstSuperSlice, params->firstSuperSlice);                       \
    DO_FIELD(DW1, MbLcuStartXPosition, params->tileSliceStartLcuMbX);              \
    DO_FIELD(DW1, MbLcuStartYPosition, params->tileSliceStartLcuMbY);              \
                                                                                   \
    DO_FIELD(DW2, NextsliceMbLcuStartXPosition, params->nextTileSliceStartLcuMbX); \
    DO_FIELD(DW2, NextsliceMbStartYPosition, params->nextTileSliceStartLcuMbY)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VD_PIPELINE_FLUSH)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VD_PIPELINE_FLUSH);

#define DO_FIELDS()                                                            \
    DO_FIELD(DW1, HevcPipelineDone, params->waitDoneHEVC);                     \
    DO_FIELD(DW1, VdencPipelineDone, params->waitDoneVDENC);                   \
    DO_FIELD(DW1, MflPipelineDone, params->waitDoneMFL);                       \
    DO_FIELD(DW1, MfxPipelineDone, params->waitDoneMFX);                       \
    DO_FIELD(DW1, VdCommandMessageParserDone, params->waitDoneVDCmdMsgParser); \
    DO_FIELD(DW1, HevcPipelineCommandFlush, params->flushHEVC);                \
    DO_FIELD(DW1, VdencPipelineCommandFlush, params->flushVDENC);              \
    DO_FIELD(DW1, MflPipelineCommandFlush, params->flushMFL);                  \
    DO_FIELD(DW1, MfxPipelineCommandFlush, params->flushMFX);                  \
    __MHW_VDBOX_VDENC_WRAPPER_EXT(VD_PIPELINE_FLUSH_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_CMD1)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_CMD1);

#define DO_FIELDS() __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_CMD1_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_CMD2)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_CMD2);

#define DO_FIELDS() __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_CMD2_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_CMD3)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_CMD3);

#define DO_FIELDS() __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_CMD3_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_CMD4)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_CMD4);

#define DO_FIELDS() __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_CMD4_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }

    _MHW_CMD_SET_DECL_OVERRIDE(VDENC_CMD5)
    {
        _MHW_CMDSET_GETCMDPARAMS_AND_CALLBASE(VDENC_CMD5);

#define DO_FIELDS() __MHW_VDBOX_VDENC_WRAPPER_EXT(VDENC_CMD5_IMPL_EXT)

#include "mhw_hwcmd_process_cmdfields.h"
    }
};
}  // namespace vdenc
}  // namespace vdbox
}  // namespace mhw

#endif  // __MHW_VDBOX_VDENC_IMPL_H__
