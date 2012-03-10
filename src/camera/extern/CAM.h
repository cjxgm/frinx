
#ifndef __CAM_H__
#define __CAM_H__

extern float CAM_target[3];
extern float CAM_forward[3];
extern float CAM_up[3];
extern float CAM_dist;

void CAM_apply();
void CAM_rotate(float ax, float ay, float az);

#endif

