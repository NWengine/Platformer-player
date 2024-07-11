#include "player.h"
#include "../include/nwin/window.h"
void player::Start() {

}

bool ResolveCollisions(Transform* transform, Collider* col, GameObject* goc) {
	bool ret = 0;
	for (auto it = Scene::currentScene->sceneObjs.begin(); it != Scene::currentScene->sceneObjs.end(); ++it) {
		if (&*it == goc) continue;
		Collider* otherCollider = it->GetComponent<Collider>();
		fVec2 depth;
		if (otherCollider) {
			otherCollider->Start();
			if (col->isColliding(otherCollider, &depth)) {
				transform->position = transform->position + depth;
				ret = 1;
			}
		}
	}
	return ret;
}

bool isColliding(Transform* transform, Collider* col, GameObject* goc) {
	for (auto it = Scene::currentScene->sceneObjs.begin(); it != Scene::currentScene->sceneObjs.end(); ++it) {
		if (&*it == goc) continue;
		Collider* otherCollider = it->GetComponent<Collider>();
		fVec2 depth;
		if (otherCollider) {
			otherCollider->Start();
			if (col->isColliding(otherCollider, &depth))
				return 1;
		}
	}
	return 0;
}

bool lastPressed = 0;

void player::Update() {
	Transform* transform = this->goc->GetComponent<Transform>();
	if (transform->position.y < -2000.0f) transform->position = fVec2(0.0f, 0.0f);
	//Don't move if is jumping from a wall
	if (this->jumpTimeBuffer > 0.0f) {
		this->jumpTimeBuffer = Max<float>(this->jumpTimeBuffer - NWTime::_deltaTime, 0.0f);
	}
	else {
            int right      = Inputs::right;
            int left       = Inputs::left;
			hMove = right - left;
	}
     
   

	fVec2 direction      = fVec2(hMove, 1.0f);
	//Resolving collsions
	Collider* col        = this->goc->GetComponent<Collider>();
	col->Start();
	fVec2 speed0         = fVec2(speed, actualFallingSpeed);
	transform->position  = transform->position + direction * speed0 * NWTime::GetDeltaTime();
	ResolveCollisions(transform, col, goc);
	//Jump logic
	transform->position.y -= 1;
    isGrounded       = isColliding(transform, col, goc);	
	if (isGrounded && Inputs::space) {
		actualFallingSpeed = jmp;
		transform->position.y += 1;
		isGrounded   = 0;
	}
	transform->position.y += 1;

	//Annulate speed if grounded decrease it to a minimum value otherwise
	if (!isGrounded)
		actualFallingSpeed    = Max<float>(actualFallingSpeed - factor* NWTime::_deltaTime, -fallingSpeed);
	else
		actualFallingSpeed    = 0.0f;
	//Annulate y speed if upper collision occurs
	transform->position.y 	  += 1;
	if (isColliding(transform, col, goc)) {
		actualFallingSpeed     = 0.0f;
		transform->position.y -= 1;
	}
	transform->position.y -= 1;
	//WallGliding
	transform->position.x += 1;
	tempDir = 0;
	int temp    = 0;
	if (!isGrounded && isColliding(transform, col, goc)) {
		actualFallingSpeed = -fallingSpeed / glidingFactor;
		this->isGliding    =  1;
		tempDir 		   = -1;
	}
	else ++temp;

	transform->position.x -= 2;
	if (!isGrounded && isColliding(transform, col, goc)) {
		actualFallingSpeed = -fallingSpeed / glidingFactor;
		this->isGliding    = 1;
		tempDir  		   = 1;
	}
	else ++temp;
	transform->position.x += 1;
	if (temp == 2) this->isGliding = 0;
	//WallJump
	if (this->isGliding && Inputs::space) {
		this->isGliding = 0;
		transform->position.x += tempDir;
		actualFallingSpeed    = jmp;
		this->hMove = tempDir;
		this->jumpTimeBuffer = this->jumpTime;
	}

}

Scriptable* player::GetScript(GameObject* goc) {
	return new player(goc);
};



