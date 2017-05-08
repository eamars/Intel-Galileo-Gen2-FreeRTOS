/**
 * @file device_id.h
 * @brief Intel Quark SoC X1000 device id
 * @author Ran Bao
 * @date May, 2017
 */

#ifndef DEVICE_ID_H_
#define DEVICE_ID_H_

// see section 6.3 in quark x1000 datasheet
#define HOST_BRIDGE_BUS                 0
#define HOST_BRIDGE_DEVICE              0
#define HOST_BRIDGE_FUNCTION            0
#define HOST_BRIDGE_DEVICE_ID           0x0958

#define LEGACY_BRIDGE_BUS               0
#define LEGACY_BRIDGE_DEVICE            31
#define LEGACY_BRIDGE_FUNCTION          0
#define LEGACY_BRIDGE_DEVICE_ID         0x095E


#endif /* DEVICE_ID_H_ */