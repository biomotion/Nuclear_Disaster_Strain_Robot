#ifndef _ROS_duckietown_msgs_GlobalPose_h
#define _ROS_duckietown_msgs_GlobalPose_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose2D.h"

namespace duckietown_msgs
{

  class GlobalPose : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef int32_t _bot_id_type;
      _bot_id_type bot_id;
      typedef geometry_msgs::Pose2D _pose_type;
      _pose_type pose;
      typedef float _delta_x_type;
      _delta_x_type delta_x;
      typedef float _delta_y_type;
      _delta_y_type delta_y;
      typedef float _delta_theta_type;
      _delta_theta_type delta_theta;
      typedef const char* _tiletype_type;
      _tiletype_type tiletype;
      uint32_t cam_id_length;
      typedef int32_t _cam_id_type;
      _cam_id_type st_cam_id;
      _cam_id_type * cam_id;
      uint32_t reference_tag_id_length;
      typedef int32_t _reference_tag_id_type;
      _reference_tag_id_type st_reference_tag_id;
      _reference_tag_id_type * reference_tag_id;

    GlobalPose():
      header(),
      bot_id(0),
      pose(),
      delta_x(0),
      delta_y(0),
      delta_theta(0),
      tiletype(""),
      cam_id_length(0), cam_id(NULL),
      reference_tag_id_length(0), reference_tag_id(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
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
      offset += this->pose.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_x);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_y);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_theta);
      uint32_t length_tiletype = strlen(this->tiletype);
      varToArr(outbuffer + offset, length_tiletype);
      offset += 4;
      memcpy(outbuffer + offset, this->tiletype, length_tiletype);
      offset += length_tiletype;
      *(outbuffer + offset + 0) = (this->cam_id_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->cam_id_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->cam_id_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->cam_id_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cam_id_length);
      for( uint32_t i = 0; i < cam_id_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_cam_idi;
      u_cam_idi.real = this->cam_id[i];
      *(outbuffer + offset + 0) = (u_cam_idi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cam_idi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cam_idi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cam_idi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cam_id[i]);
      }
      *(outbuffer + offset + 0) = (this->reference_tag_id_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->reference_tag_id_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->reference_tag_id_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->reference_tag_id_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->reference_tag_id_length);
      for( uint32_t i = 0; i < reference_tag_id_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_reference_tag_idi;
      u_reference_tag_idi.real = this->reference_tag_id[i];
      *(outbuffer + offset + 0) = (u_reference_tag_idi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_reference_tag_idi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_reference_tag_idi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_reference_tag_idi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->reference_tag_id[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
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
      offset += this->pose.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_x));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_y));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_theta));
      uint32_t length_tiletype;
      arrToVar(length_tiletype, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_tiletype; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_tiletype-1]=0;
      this->tiletype = (char *)(inbuffer + offset-1);
      offset += length_tiletype;
      uint32_t cam_id_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      cam_id_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      cam_id_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      cam_id_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->cam_id_length);
      if(cam_id_lengthT > cam_id_length)
        this->cam_id = (int32_t*)realloc(this->cam_id, cam_id_lengthT * sizeof(int32_t));
      cam_id_length = cam_id_lengthT;
      for( uint32_t i = 0; i < cam_id_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_cam_id;
      u_st_cam_id.base = 0;
      u_st_cam_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_cam_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_cam_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_cam_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_cam_id = u_st_cam_id.real;
      offset += sizeof(this->st_cam_id);
        memcpy( &(this->cam_id[i]), &(this->st_cam_id), sizeof(int32_t));
      }
      uint32_t reference_tag_id_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      reference_tag_id_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      reference_tag_id_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      reference_tag_id_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->reference_tag_id_length);
      if(reference_tag_id_lengthT > reference_tag_id_length)
        this->reference_tag_id = (int32_t*)realloc(this->reference_tag_id, reference_tag_id_lengthT * sizeof(int32_t));
      reference_tag_id_length = reference_tag_id_lengthT;
      for( uint32_t i = 0; i < reference_tag_id_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_reference_tag_id;
      u_st_reference_tag_id.base = 0;
      u_st_reference_tag_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_reference_tag_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_reference_tag_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_reference_tag_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_reference_tag_id = u_st_reference_tag_id.real;
      offset += sizeof(this->st_reference_tag_id);
        memcpy( &(this->reference_tag_id[i]), &(this->st_reference_tag_id), sizeof(int32_t));
      }
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/GlobalPose"; };
    const char * getMD5(){ return "1f96ea214bbade01cee3f57e21d85ae7"; };

  };

}
#endif