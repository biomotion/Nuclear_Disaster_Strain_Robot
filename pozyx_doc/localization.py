from time import sleep
from pypozyx import *
from pypozyx.tools.device_list import *
from pypozyx.tools.discovery import *
from pypozyx.tools.version_check import *

def printErrorCode():
    error_code = SingleRegister()
    status = pozyx.getErrorCode(error_code)
    if status == POZYX_SUCCESS:
        print pozyx.getErrorMessage(error_code)


serial_port = get_first_pozyx_serial_port()
if serial_port == None:
    raise Exception("No Pozyx Device Found")

#Connecting
print "Connect Pozyx via port: ", serial_port
pozyx = PozyxSerial(serial_port)
pozyx.printDeviceInfo()

#Set Anchor Coordinates
anchors = [DeviceCoordinates(0x6755, 1, Coordinates(0, 0, 2790)),
           DeviceCoordinates(0x6754, 1, Coordinates(140, 0, 2790)),
           DeviceCoordinates(0x6742, 1, Coordinates(0, 140, 2790)),
           DeviceCoordinates(0x674f, 1, Coordinates(320, 140, 2790))]
status = pozyx.clearDevices()
for anchor in anchors:
    status &= pozyx.addDevice(anchor)
if len(anchors) > 4:
    status &= pozyx.setSelectionOfAnchors(PozyxConstants.ANCHOR_SELECT_AUTO, len(anchors))

if status == POZYX_SUCCESS:
    for anchor in anchors:
        anchor_coords = Coordinates()
        pozyx.getDeviceCoordinates(anchor, anchor_coords)
        print "Anchor:", anchor, "coordinate:", anchor_coords
else:
    printErrorCode()

#Getting Position
while 1:
    position = Coordinates()
    orientation = EulerAngles()
    acceleration = Acceleration()
    status = pozyx.doPositioning(position, dimension=PozyxConstants.DIMENSION_3D,algorithm=PozyxConstants.POSITIONING_ALGORITHM_UWB_ONLY)
    status &= pozyx.getEulerAngles_deg(orientation)
    status &= pozyx.getAcceleration_mg(acceleration)
    if status == POZYX_SUCCESS: # if get pose from pozyx
        print "Coordinates: ", str(position)
        print "Orientation: ", str(orientation)
	print "Acceleration: ", str(acceleration)
	sleep(0.1)
    else:
        printErrorCode()
