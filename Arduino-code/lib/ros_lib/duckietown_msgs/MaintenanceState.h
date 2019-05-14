#ifndef _ROS_duckietown_msgs_MaintenanceState_h
#define _ROS_duckietown_msgs_MaintenanceState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace duckietown_msgs
{

  class MaintenanceState : public ros::Msg
  {
    public:
      typedef const char* _state_type;
      _state_type state;
      enum { WAY_TO_MAINTENANCE = "WAY_TO_MAINTENANCE" };
      enum { WAY_TO_CHARGING = "WAY_TO_CHARGING" };
      enum { CHARGING = "CHARGING" };
      enum { WAY_TO_CALIBRATING = "WAY_TO_CALIBRATING" };
      enum { CALIBRATING = "CALIBRATING" };
      enum { WAY_TO_CITY = "WAY_TO_CITY" };
      enum { NONE = "NONE" };

    MaintenanceState():
      state("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_state = strlen(this->state);
      varToArr(outbuffer + offset, length_state);
      offset += 4;
      memcpy(outbuffer + offset, this->state, length_state);
      offset += length_state;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_state;
      arrToVar(length_state, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_state; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_state-1]=0;
      this->state = (char *)(inbuffer + offset-1);
      offset += length_state;
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/MaintenanceState"; };
    const char * getMD5(){ return "076259ec4d51665ce2a0b26c9055f2df"; };

  };

}
#endif