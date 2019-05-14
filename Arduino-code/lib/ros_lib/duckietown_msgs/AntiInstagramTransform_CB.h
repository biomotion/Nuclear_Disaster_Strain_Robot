#ifndef _ROS_duckietown_msgs_AntiInstagramTransform_CB_h
#define _ROS_duckietown_msgs_AntiInstagramTransform_CB_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace duckietown_msgs
{

  class AntiInstagramTransform_CB : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      int16_t th[6];

    AntiInstagramTransform_CB():
      header(),
      th()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 6; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_thi;
      u_thi.real = this->th[i];
      *(outbuffer + offset + 0) = (u_thi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thi.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->th[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 6; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_thi;
      u_thi.base = 0;
      u_thi.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thi.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->th[i] = u_thi.real;
      offset += sizeof(this->th[i]);
      }
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/AntiInstagramTransform_CB"; };
    const char * getMD5(){ return "ad95a08e9897d117b5fa255272552409"; };

  };

}
#endif