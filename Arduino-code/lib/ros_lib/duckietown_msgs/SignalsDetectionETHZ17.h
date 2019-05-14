#ifndef _ROS_duckietown_msgs_SignalsDetectionETHZ17_h
#define _ROS_duckietown_msgs_SignalsDetectionETHZ17_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace duckietown_msgs
{

  class SignalsDetectionETHZ17 : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _led_detected_type;
      _led_detected_type led_detected;
      typedef const char* _no_led_detected_type;
      _no_led_detected_type no_led_detected;
      enum { SIGNAL_A = 'car_signal_A' };
      enum { SIGNAL_B = 'car_signal_B' };
      enum { SIGNAL_C = 'car_signal_C' };
      enum { NO_CARS = 'no_cars_detected' };
      enum { CARS = 'cars_detected' };
      enum { GO = 'tl_go' };

    SignalsDetectionETHZ17():
      header(),
      led_detected(""),
      no_led_detected("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_led_detected = strlen(this->led_detected);
      varToArr(outbuffer + offset, length_led_detected);
      offset += 4;
      memcpy(outbuffer + offset, this->led_detected, length_led_detected);
      offset += length_led_detected;
      uint32_t length_no_led_detected = strlen(this->no_led_detected);
      varToArr(outbuffer + offset, length_no_led_detected);
      offset += 4;
      memcpy(outbuffer + offset, this->no_led_detected, length_no_led_detected);
      offset += length_no_led_detected;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_led_detected;
      arrToVar(length_led_detected, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_led_detected; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_led_detected-1]=0;
      this->led_detected = (char *)(inbuffer + offset-1);
      offset += length_led_detected;
      uint32_t length_no_led_detected;
      arrToVar(length_no_led_detected, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_no_led_detected; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_no_led_detected-1]=0;
      this->no_led_detected = (char *)(inbuffer + offset-1);
      offset += length_no_led_detected;
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/SignalsDetectionETHZ17"; };
    const char * getMD5(){ return "c1b7d3a54f028811e1c3b2366af85c0a"; };

  };

}
#endif