#pragma once

#ifndef _MECHANISMMODEL_H  
#define _MECHANISMMODEL_H  

#include "common/Common.hpp"


namespace msr {
	namespace airlib {
		class MechanismModel
		{
		public:
			void LinearModel(Vector3r force, real_T mass, Pose current_pose, Vector3r gravity, Vector3r& linear_accel);

		public:
			real_T test;
		};

	}
}






#endif  










