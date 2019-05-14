#ifndef _ROS_duckietown_msgs_RemapPose_h
#define _ROS_duckietown_msgs_RemapPose_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace duckietown_msgs
{

  class RemapPose : public ros::Msg
  {
    public:
      typedef const char* _host_type;
      _host_type host;
      typedef int32_t _frame_id_type;
      _frame_id_type frame_id;
      typedef int32_t _bot_id_type;
      _bot_id_type bot_id;
      typedef geometry_msgs::PoseStamped _posestamped_type;
      _posestamped_type posestamped;

    RemapPose():
      host(""),
      frame_id(0),
      bot_id(0),
      posestamped()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_host = strlen(this->host);
      varToArr(outbuffer + offset, length_host);
      offset += 4;
      memcpy(outbuffer + offset, this->host, length_host);
      offset += length_host;
      union {
        int32_t real;
        uint32_t base;
      } u_frame_id;
      u_frame_id.real = this->frame_id;
      *(outbuffer + offset + 0) = (u_frame_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_frame_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_frame_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_frame_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->frame_id);
      union {
        int32_t real;
        uint32_t base;
      } u_bot_id;
      u_bot_id.real = this->bot_id;
      *(outbuffer + offset + 0) = (u_bot_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bot_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bot_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bot_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bot_id);
      offset += this->posestamped.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_host;
      arrToVar(length_host, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_host; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_host-1]=0;
      this->host = (char *)(inbuffer + offset-1);
      offset += length_host;
      union {
        int32_t real;
        uint32_t base;
      } u_frame_id;
      u_frame_id.base = 0;
      u_frame_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_frame_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_frame_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_frame_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->frame_id = u_frame_id.real;
      offset += sizeof(this->frame_id);
      union {
        int32_t real;
        uint32_t base;
      } u_bot_id;
      u_bot_id.base = 0;
      u_bot_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bot_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bot_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bot_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bot_id = u_bot_id.real;
      offset += sizeof(this->bot_id);
      offset += this->posestamped.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/RemapPose"; };
    const char * getMD5(){ return "f6767842e9bbe0ac792f55ce80fe26b4"; };

  };

}
#endif