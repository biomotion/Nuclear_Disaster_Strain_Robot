#ifndef _ROS_duckietown_msgs_TurnIDandType_h
#define _ROS_duckietown_msgs_TurnIDandType_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace duckietown_msgs
{

  class TurnIDandType : public ros::Msg
  {
    public:
      typedef int16_t _tag_id_type;
      _tag_id_type tag_id;
      typedef int16_t _turn_type_type;
      _turn_type_type turn_type;

    TurnIDandType():
      tag_id(0),
      turn_type(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_tag_id;
      u_tag_id.real = this->tag_id;
      *(outbuffer + offset + 0) = (u_tag_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tag_id.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->tag_id);
      union {
        int16_t real;
        uint16_t base;
      } u_turn_type;
      u_turn_type.real = this->turn_type;
      *(outbuffer + offset + 0) = (u_turn_type.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_turn_type.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->turn_type);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_tag_id;
      u_tag_id.base = 0;
      u_tag_id.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tag_id.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->tag_id = u_tag_id.real;
      offset += sizeof(this->tag_id);
      union {
        int16_t real;
        uint16_t base;
      } u_turn_type;
      u_turn_type.base = 0;
      u_turn_type.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_turn_type.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->turn_type = u_turn_type.real;
      offset += sizeof(this->turn_type);
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/TurnIDandType"; };
    const char * getMD5(){ return "999e690d54f4de1ab02b7e874091d0ff"; };

  };

}
#endif