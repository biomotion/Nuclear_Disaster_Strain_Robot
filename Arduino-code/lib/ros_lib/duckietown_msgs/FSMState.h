#ifndef _ROS_duckietown_msgs_FSMState_h
#define _ROS_duckietown_msgs_FSMState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace duckietown_msgs
{

  class FSMState : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _state_type;
      _state_type state;
      enum { LANE_FOLLOWING = "LANE_FOLLOWING" };
      enum { INTERSECTION_COORDINATION = "INTERSECTION_COORDINATION" };
      enum { INTERSECTION_CONTROL = "INTERSECTION_CONTROL" };
      enum { NORMAL_JOYSTICK_CONTROL = "NORMAL_JOYSTICK_CONTROL" };
      enum { SAFE_JOYSTICK_CONTROL = "SAFE_JOYSTICK_CONTROL" };
      enum { PARKING = "PARKING" };
      enum { ARRIVE_AT_STOP_LINE = "ARRIVE_AT_STOP_LINE" };
      enum { LANE_RECOVERY = "LANE_RECOVERY" };
      enum { INTERSECTION_RECOVERY = "INTERSECTION_RECOVERY" };
      enum { CALIBRATING = "CALIBRATING" };
      enum { CALIBRATING_CALC = "CALIBRATING_CALC" };

    FSMState():
      header(),
      state("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
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
      offset += this->header.deserialize(inbuffer + offset);
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

    const char * getType(){ return "duckietown_msgs/FSMState"; };
    const char * getMD5(){ return "3c94938238cecfe40fdf747aae8abbaa"; };

  };

}
#endif