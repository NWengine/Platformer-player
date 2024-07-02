#pragma once
#include "NWengineCore.h"

class player : public Scriptable {
public:
	SCRIPT_CONSTR(player);

	void Start()  override;
	void Update() override;

	bool  isGliding          = 0;
	int   tempDir;

private:
	int   hMove              = 0;
	float actualFallingSpeed = 0.0f;
	bool  isGrounded         = 0.0f;
	float animClock          = 0.0f;
	Interpolator anim 		 = Interpolator(1.0f, 0.5f, 1.0f);
	float jumpTimeBuffer     = 0.0f;
	bool isControlled        = 1;
	//Serialized
	float speed		   		 = 200.0f;
	float fallingSpeed 		 = 1000.0f;
	float jmp                =  500.0f;
	float factor             = 1000.0f;
	float glidingFactor      = 6.0f;

	float jumpTime 			 = 0.3f;
};
