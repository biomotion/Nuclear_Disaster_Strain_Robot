#ifndef _ROS_duckietown_msgs_IntersectionPoseImgDebug_h
#define _ROS_duckietown_msgs_IntersectionPoseImgDebug_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/CompressedImage.h"

namespace duckietown_msgs
{

  class IntersectionPoseImgDebug : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _x_type;
      _x_type x;
      typedef float _y_type;
      _y_type y;
      typedef float _theta_type;
      _theta_type theta;
      typedef uint8_t _type_type;
      _type_type type;
      typedef float _likelihood_type;
      _likelihood_type likelihood;
      typedef float _x_init_type;
      _x_init_type x_init;
      typedef float _y_init_type;
      _y_init_type y_init;
      typedef float _theta_init_type;
      _theta_init_type theta_init;
      typedef sensor_msgs::CompressedImage _img_type;
      _img_type img;

    IntersectionPoseImgDebug():
      header(),
      x(0),
      y(0),
      theta(0),
      type(0),
      likelihood(0),
      x_init(0),
      y_init(0),
      theta_init(0),
      img()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y);
      union {
        float real;
        uint32_t base;
      } u_theta;
      u_theta.real = this->theta;
      *(outbuffer + offset + 0) = (u_theta.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_theta.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_theta.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_theta.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta);
      *(outbuffer + offset + 0) = (this->type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->type);
      union {
        float real;
        uint32_t base;
      } u_likelihood;
      u_likelihood.real = this->likelihood;
      *(outbuffer + offset + 0) = (u_likelihood.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_likelihood.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_likelihood.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_likelihood.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->likelihood);
      union {
        float real;
        uint32_t base;
      } u_x_init;
      u_x_init.real = this->x_init;
      *(outbuffer + offset + 0) = (u_x_init.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x_init.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x_init.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x_init.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->x_init);
      union {
        float real;
        uint32_t base;
      } u_y_init;
      u_y_init.real = this->y_init;
      *(outbuffer + offset + 0) = (u_y_init.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y_init.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_y_init.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_y_init.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_init);
      union {
        float real;
        uint32_t base;
      } u_theta_init;
      u_theta_init.real = this->theta_init;
      *(outbuffer + offset + 0) = (u_theta_init.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_theta_init.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_theta_init.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_theta_init.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta_init);
      offset += this->img.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        float real;
        uint32_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y = u_y.real;
      offset += sizeof(this->y);
      union {
        float real;
        uint32_t base;
      } u_theta;
      u_theta.base = 0;
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->theta = u_theta.real;
      offset += sizeof(this->theta);
      this->type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->type);
      union {
        float real;
        uint32_t base;
      } u_likelihood;
      u_likelihood.base = 0;
      u_likelihood.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_likelihood.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_likelihood.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_likelihood.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->likelihood = u_likelihood.real;
      offset += sizeof(this->likelihood);
      union {
        float real;
        uint32_t base;
      } u_x_init;
      u_x_init.base = 0;
      u_x_init.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x_init.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x_init.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x_init.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->x_init = u_x_init.real;
      offset += sizeof(this->x_init);
      union {
        float real;
        uint32_t base;
      } u_y_init;
      u_y_init.base = 0;
      u_y_init.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y_init.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_y_init.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_y_init.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->y_init = u_y_init.real;
      offset += sizeof(this->y_init);
      union {
        float real;
        uint32_t base;
      } u_theta_init;
      u_theta_init.base = 0;
      u_theta_init.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_theta_init.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_theta_init.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_theta_init.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->theta_init = u_theta_init.real;
      offset += sizeof(this->theta_init);
      offset += this->img.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/IntersectionPoseImgDebug"; };
    const char * getMD5(){ return "0027b9b3f880873af8e49663f8172f1a"; };

  };

}
#endif