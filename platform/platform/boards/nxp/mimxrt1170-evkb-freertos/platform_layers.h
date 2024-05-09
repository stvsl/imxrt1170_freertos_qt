/******************************************************************************
**
** Copyright (C) 2023 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Ultralite module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/
#pragma once

#include <fsl_lcdifv2.h>
#include <qul/private/memutil.h>
#include <platform/framebufferformat.h>
#include <platforminterface/layerengine.h>
#include <platforminterface/drawingdevice.h>

#include <memory>
#include <vg_lite.h>

namespace Qul {
namespace Platform {
namespace Private {

constexpr std::size_t MAX_LAYER_COUNT = 8;

template<typename T, std::size_t N>
struct Array
{
    Array()
        : _count(0)
    {}

    bool add(const T &node)
    {
        if (end() == last()) {
            return false;
        }

        _data[_count] = node;
        ++_count;
        return true;
    }

    void remove(const T &node)
    {
        auto it = std::remove(begin(), end(), node);
        _count = std::distance(begin(), it);
    }

    std::size_t count() const { return _count; }

    T *begin() { return _data; }
    T *end() { return &_data[_count]; }

private:
    T *last() { return &_data[N]; }

    T _data[N];
    std::size_t _count;
};

class Lcdifv2Layer;
class Lcdifv2Sprite;

template<typename T>
class Lcdifv2LayerUpdater
{
public:
    Lcdifv2LayerUpdater(const T &properties);
    void update(const T &properties);
    const T &properties() const;

protected:
    virtual void onUpdated(const int8_t &oldZ) = 0;
    T _properties;
};

template<typename T>
Lcdifv2LayerUpdater<T>::Lcdifv2LayerUpdater(const T &properties)
    : _properties(properties)
{}

template<typename T>
void Lcdifv2LayerUpdater<T>::update(const T &properties)
{
    uint8_t oldZ = _properties.z;
    _properties = properties;
    onUpdated(oldZ);
}

template<typename T>
const T &Lcdifv2LayerUpdater<T>::properties() const
{
    return _properties;
}

class Lcdifv2CommonProperties
{
public:
    virtual bool enabled() const = 0;
    virtual float opacity() const = 0;
    virtual PlatformInterface::Point position() const = 0;
};

class Lcdifv2LayerProperties : public Lcdifv2CommonProperties
{
public:
    uint16_t stride() const;

    virtual uint8_t bpp() const = 0;
    virtual uint8_t *data() const = 0;
    virtual uint8_t *frontBuffer() const = 0;
    virtual Qul::PixelFormat format() const = 0;
    virtual PlatformInterface::Size size() const = 0;
    virtual int platformId() const = 0;
    virtual uint8_t z() const = 0;
};

class Lcdifv2Sprite : public Lcdifv2LayerUpdater<Qul::PlatformInterface::LayerEngine::SpriteLayerProperties>,
                      public Lcdifv2CommonProperties,
                      public Qul::PlatformInterface::LayerEngine::SpriteLayer
{
public:
    Lcdifv2Sprite(const Qul::PlatformInterface::LayerEngine::SpriteLayerProperties &properties);
    ~Lcdifv2Sprite();

    void registerObserver(Lcdifv2Layer *observer);
    void unregisterObserver(Lcdifv2Layer *observer);

    bool enabled() const override;
    float opacity() const override;
    PlatformInterface::Point position() const override;

protected:
    void onUpdated(const int8_t &oldZ) override;

private:
    void notify();

    Array<Lcdifv2Layer *, MAX_LAYER_COUNT> _observers;
};

class Lcdifv2Layer : public Lcdifv2LayerProperties
{
public:
    Lcdifv2Layer(const Qul::PlatformInterface::Screen *screen, int8_t index);
    virtual ~Lcdifv2Layer();

    virtual void onSpriteChanged(const Lcdifv2Sprite *sprite) = 0;
    virtual void onSpriteAttached(Lcdifv2Sprite *sprite) = 0;
    void onSpriteDetached(const Lcdifv2Sprite *sprite);

    static void flush();
    static bool full();
    static bool valid(const Qul::PlatformInterface::Screen *screen, const Qul::PlatformInterface::Size &size);
    static Qul::Platform::FramebufferFormat framebufferFormat(
        const Qul::PlatformInterface::LayerEngine::ItemLayer *layer);

    bool dirty() const;
    void commit() const;
    int swapFrame() const;

protected:
    int8_t index() const;
    void setIndex(const int8_t index);

    void setDirty(bool dirty) const;
    void setSwapFrame(int frame);

    void driverCommonUpdate() const;
    void driverBufferUpdate() const;

    Lcdifv2Sprite *parent() const;

    static void updateIndexes(Lcdifv2Layer *targetLayer, bool removeLayer = false);

    Lcdifv2Sprite *_parent;

private:
    void append();

    mutable bool _dirty;
    int8_t _index;
    const Qul::PlatformInterface::Screen *_screen;

    mutable unsigned int _swapFrame;
};

template<typename T>
class Lcdifv2LayerCommon : public Lcdifv2Layer, public Lcdifv2LayerUpdater<T>
{
public:
    Lcdifv2LayerCommon(const T &properties, const Qul::PlatformInterface::Screen *screen, int8_t index);

    bool enabled() const override;
    float opacity() const override;
    PlatformInterface::Point position() const override;
    int platformId() const override;
    uint8_t z() const override;
};

template<typename T>
Lcdifv2LayerCommon<T>::Lcdifv2LayerCommon(const T &prop, const Qul::PlatformInterface::Screen *screen, int8_t index)
    : Lcdifv2Layer(screen, index)
    , Lcdifv2LayerUpdater<T>(prop)
{}

template<typename T>
float Lcdifv2LayerCommon<T>::opacity() const
{
    return Lcdifv2LayerUpdater<T>::properties().opacity;
}

template<typename T>
int Lcdifv2LayerCommon<T>::platformId() const
{
    return Lcdifv2LayerUpdater<T>::properties().id;
}

template<typename T>
bool Lcdifv2LayerCommon<T>::enabled() const
{
    return Lcdifv2LayerUpdater<T>::properties().enabled;
}

template<typename T>
Qul::PlatformInterface::Point Lcdifv2LayerCommon<T>::position() const
{
    return Lcdifv2LayerUpdater<T>::properties().position;
}

template<typename T>
uint8_t Lcdifv2LayerCommon<T>::z() const
{
    return Lcdifv2LayerUpdater<T>::properties().z;
}

class Lcdifv2ImageLayer : public Lcdifv2LayerCommon<Qul::PlatformInterface::LayerEngine::ImageLayerProperties>,
                          public Qul::PlatformInterface::LayerEngine::ImageLayer
{
public:
    Lcdifv2ImageLayer(const Qul::PlatformInterface::Screen *screen,
                      const Qul::PlatformInterface::LayerEngine::ImageLayerProperties &properties,
                      Qul::PlatformInterface::LayerEngine::SpriteLayer *spriteLayer = nullptr);

    void onSpriteChanged(const Lcdifv2Sprite *sprite) override;
    void onSpriteAttached(Lcdifv2Sprite *sprite) override;

    uint8_t bpp() const override;
    uint8_t *data() const override;
    uint8_t *frontBuffer() const override { return data(); }
    Qul::PixelFormat format() const override;
    PlatformInterface::Size size() const override;

protected:
    void onUpdated(const int8_t &oldZ) override;
};

class Lcdifv2ItemLayer : public Lcdifv2LayerCommon<Qul::PlatformInterface::LayerEngine::ItemLayerProperties>,
                         public Qul::PlatformInterface::LayerEngine::ItemLayer
{
public:
    Lcdifv2ItemLayer(const Qul::PlatformInterface::Screen *screen,
                     const Qul::PlatformInterface::LayerEngine::ItemLayerProperties &properties,
                     Qul::PlatformInterface::LayerEngine::SpriteLayer *spriteLayer = nullptr);

    Qul::PlatformInterface::DrawingDevice *beginFrame(int interval) const;
    void endFrame() const;

    void onSpriteChanged(const Lcdifv2Sprite *sprite) override;
    void onSpriteAttached(Lcdifv2Sprite *sprite) override;

    uint8_t bpp() const override;
    uint8_t *data() const override;
    uint8_t *frontBuffer() const override;

    Qul::PixelFormat format() const override;
    PlatformInterface::Size size() const override;

protected:
    void onUpdated(const int8_t &oldZ) override;

private:
    void swap() const;
    bool waitForTargetFrame() const;
    const vg_lite_buffer_t *vgbuffer() const;

    struct ItemLayerBuffer
    {
        ItemLayerBuffer();
        ~ItemLayerBuffer();

        ItemLayerBuffer(const ItemLayerBuffer &) = delete;
        ItemLayerBuffer(const ItemLayerBuffer &&) = delete;

        ItemLayerBuffer &operator=(const ItemLayerBuffer &) = delete;
        ItemLayerBuffer &operator=(const ItemLayerBuffer &&) = delete;

        void allocate(Lcdifv2ItemLayer *layer);
        uint8_t *data() const;

        Qul::Private::AlignedAllocation _data;
        vg_lite_buffer_t _vgbuffer;
    };

    const static uint8_t _buffersCount = 2;
    ItemLayerBuffer _buffers[_buffersCount];

    mutable uint8_t _bufferId;
    mutable unsigned int _targetFrame = 0;
    mutable Qul::PlatformInterface::DrawingDevice _drawingDevice;
};

} // namespace Private
} // namespace Platform
} // namespace Qul
