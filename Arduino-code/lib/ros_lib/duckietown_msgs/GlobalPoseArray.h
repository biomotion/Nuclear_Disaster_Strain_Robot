#ifndef _ROS_duckietown_msgs_GlobalPoseArray_h
#define _ROS_duckietown_msgs_GlobalPoseArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "duckietown_msgs/GlobalPose.h"

namespace duckietown_msgs
{

  class GlobalPoseArray : public ros::Msg
  {
    public:
      uint32_t poses_length;
      typedef duckietown_msgs::GlobalPose _poses_type;
      _poses_type st_poses;
      _poses_type * poses;

    GlobalPoseArray():
      poses_length(0), poses(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->poses_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->poses_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->poses_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->poses_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->poses_length);
      for( uint32_t i = 0; i < poses_length; i++){
      offset += this->poses[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t poses_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      poses_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      poses_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      poses_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->poses_length);
      if(poses_lengthT > poses_length)
        this->poses = (duckietown_msgs::GlobalPose*)realloc(this->poses, poses_lengthT * sizeof(duckietown_msgs::GlobalPose));
      poses_length = poses_lengthT;
      for( uint32_t i = 0; i < poses_length; i++){
      offset += this->st_poses.deserialize(inbuffer + offset);
        memcpy( &(this->poses[i]), &(this->st_poses), sizeof(duckietown_msgs::GlobalPose));
      }
     return offset;
    }

    const char * getType(){ return "duckietown_msgs/GlobalPoseArray"; };
    const char * getMD5(){ return "b91e4312a72aea6330aa896e2cc04388"; };

  };

}
#endif