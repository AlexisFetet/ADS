#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <AdsDevice.h>

#include <map>

class DeviceManager
{
public:

    static DeviceManager *Instance();
    uint8_t addDevice(AdsDevice*);
    bool removeAdsDevice(uint8_t);
    AdsDevice* getDevice(uint8_t);

private :

    DeviceManager();
    AdsDevice* getDevice(uint32_t);
    uint32_t getDeviceId(uint32_t);
    uint32_t getDeviceId(uint8_t);

    std::map<uint32_t,AdsDevice*> m_device_map;
    static DeviceManager* m_Singleton;

};

#endif // DEVICEMANAGER_H
