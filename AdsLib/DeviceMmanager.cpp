#include "DeviceManager.h"

DeviceManager* DeviceManager::m_Singleton = nullptr;


DeviceManager::DeviceManager()
{

}


DeviceManager *DeviceManager::Instance()
{
  if(m_Singleton == nullptr)
  {
    m_Singleton = new DeviceManager();
  }
  return m_Singleton;
}

uint8_t DeviceManager::addDevice(AdsDevice* route)
{
    bool device_already_declared = false;
    uint32_t candidate_id{0};
    uint8_t allocated_id{0};
    //TODO track candidate id in this for loop as well
    for(auto item : m_device_map)
    {
        if(item.second == route)
        {
            device_already_declared = true;
            allocated_id = item.first;
            break;
        }
    }

    if(!device_already_declared)
    {
        while (m_device_map.find(candidate_id) == m_device_map.end() || candidate_id < 256)
        {
            candidate_id ++;
        }
        if(candidate_id < 256)
        {
            allocated_id = (uint8_t)candidate_id;
            candidate_id = candidate_id << 24; // the 8 heaviest bits will hold the device ID, the 24 lightest bits will hold the variable ID vot the future notification feature
            m_device_map[candidate_id] = route;
        }
        else
        {
            throw std::overflow_error("256 AdsDevices already registered, try to remove some devices before adding a new device");
        }
    }
    return(allocated_id);
}

bool DeviceManager::removeAdsDevice(uint8_t id)
{
    bool result{false};
    uint32_t actual_id = getDeviceId(id);
    auto it = m_device_map.find(actual_id);
    if(it != m_device_map.end())
    {
        m_device_map.erase(it);
        result = true;
    }
    else
    {
        throw std::out_of_range("Route was not declared");
    }
    return (result);
}

AdsDevice* DeviceManager::getDevice(uint8_t id)
{
    AdsDevice* device;

    uint32_t actual_id = getDeviceId(id);
    auto it = m_device_map.find(actual_id);
    if(it != m_device_map.end())
    {
        device = it->second;
    }
    else
    {
        throw std::out_of_range("Route was not declared");
    }
    return(device);
}

uint32_t DeviceManager::getDeviceId(uint32_t id)
{
    uint32_t mask{255};
    return( id | (mask<<24));
}

uint32_t DeviceManager::getDeviceId(uint8_t id)
{
    return(((uint32_t)id) << 24);
}
