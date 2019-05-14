#ifndef _ROS_SERVICE_GetVariable_h
#define _ROS_SERVICE_GetVariable_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"

namespace duckietown_msgs
{

static const char GETVARIABLE[] = "duckietown_msgs/GetVariable";

  class GetVariableRequest : public ros::Msg
  {
    public:
      typedef std_msgs::String _name_json_type;
      _name_json_type name_json;

    GetVariableRequest():
      name_json()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->name_json.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->name_json.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETVARIABLE; };
    const char * getMD5(){ return "e62a392e1985c0f620cc4494f046ad84"; };

  };

  class GetVariableResponse : public ros::Msg
  {
    public:
      typedef std_msgs::String _value_json_type;
      _value_json_type value_json;

    GetVariableResponse():
      value_json()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->value_json.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->value_json.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETVARIABLE; };
    const char * getMD5(){ return "8570e70d8c775be7006dff91bf8174b8"; };

  };

  class GetVariable {
    public:
    typedef GetVariableRequest Request;
    typedef GetVariableResponse Response;
  };

}
#endif
