#ifndef _ROS_SERVICE_SetVariable_h
#define _ROS_SERVICE_SetVariable_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"

namespace duckietown_msgs
{

static const char SETVARIABLE[] = "duckietown_msgs/SetVariable";

  class SetVariableRequest : public ros::Msg
  {
    public:
      typedef std_msgs::String _name_json_type;
      _name_json_type name_json;
      typedef std_msgs::String _value_json_type;
      _value_json_type value_json;

    SetVariableRequest():
      name_json(),
      value_json()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->name_json.serialize(outbuffer + offset);
      offset += this->value_json.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->name_json.deserialize(inbuffer + offset);
      offset += this->value_json.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SETVARIABLE; };
    const char * getMD5(){ return "2ff1d830472a201c84516b10d8265cb7"; };

  };

  class SetVariableResponse : public ros::Msg
  {
    public:
      typedef std_msgs::String _success_json_type;
      _success_json_type success_json;

    SetVariableResponse():
      success_json()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->success_json.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->success_json.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SETVARIABLE; };
    const char * getMD5(){ return "9b40e451a7c63a6647ba8c4c52db0f4c"; };

  };

  class SetVariable {
    public:
    typedef SetVariableRequest Request;
    typedef SetVariableResponse Response;
  };

}
#endif
