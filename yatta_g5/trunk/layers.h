#ifndef LAYERS_H
#define LAYERS_H

#include <QList>
#include <QString>
#include "coreshared.h"
#include "presets.h"


class TMarkerLayer : public TLayer
{
protected:
    TPresets &presets;
    QList<TSection> sections;
public:
    TMarkerLayer(TPresets &apresets);
    bool remove(int index);
    int count();
    const TSection &getByFrame(int frame);
    const TSection &operator [](int i);
    bool setPreset(int index, int preset);
    bool add(int start, int preset);
    bool isPresetUsed(int id) const;
};

class TSectionLayer : public TMarkerLayer {
public:
    TSectionLayer(TPresets &apresets);
    TLayerType layerType() const;
};

class TDecimationLayer : public TMarkerLayer {
public:
    TDecimationLayer(TPresets &apresets);
    TLayerType layerType() const;
};


class TCustomListLayer : public TLayer
{
private:
    TPresets &presets;
    QList<TCustomRange> ranges;
    int fPreset;
public:
    TCustomListLayer(TPresets &apresets);
    int preset() const;
    bool setPreset(int preset);
    bool add(int start, int end);
    void remove(int index);
    int count();
    const TCustomRange *getByFrame(int frame);
    const TCustomRange &operator [](int i);

    TLayerType layerType() const;
    bool isPresetUsed(int id) const;
};

class TLayers
{
private:
    QList<TLayer *> layers;
public:
    TPresets presets;

    bool isPresetUsed(int id);
    int count();
    void exchange(int i1, int i2);
    const TLayer &operator [](int i);
    int customListLayerCount();
    int sectionLayerCount();
    TDecimationLayer &decimationLayer();
    TSectionLayer &sectionLayer(int index);
    TCustomListLayer &customListLayer(int index);
    bool addLayer(QString &name, TLayerType type, int index = -1);

    TLayers();
    ~TLayers();
};

#endif // LAYERS_H
