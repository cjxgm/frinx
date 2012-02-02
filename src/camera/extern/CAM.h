
#ifndef __CAM_H__
#define __CAM_H__

typedef struct CAM_Camera
{
	float target[3];
	float forward[3];
	float up[3];
	float dist;
}
CAM_Camera;

void CAM_apply(CAM_Camera * cam);
//void CAM_turnx(CAM_Camera * cam, float a);
void CAM_turny(CAM_Camera * cam, float a);
//void CAM_turnz(CAM_Camera * cam, float a);

#endif

