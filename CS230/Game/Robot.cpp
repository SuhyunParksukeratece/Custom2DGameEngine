/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Robot.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#include "Robot.h"
#include "../Engine/Collision.h"
#include "Score.h"
#include "../Engine/Engine.h"
#include "Cat.h"
#include "States.h"

//Robot::Robot(Math::vec2 position) : CS230::GameObject(position) {
//	AddGOComponent(new CS230::Sprite("Assets/Robot.spt", this));
//	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::None));
//}

Robot::Robot(Math::vec2 position, Cat* cat, double left_boundary, double right_boundary) : CS230::GameObject(position), cat_p(cat), left_boundary(left_boundary), right_boundary(right_boundary)
{
	AddGOComponent(new CS230::Sprite("Assets/Robot.spt", this));
	SetPosition(position);
	current_state = &state_walking;
	current_state->Enter(this);
}

void Robot::ResolveCollision(GameObject* other_object)
{

	if (other_object->Type() == GameObjectTypes::Cat)
	{
		RemoveGOComponent<CS230::RectCollision>();
		this->change_state(&this->state_dead);
	}

	CS230::Score* score = Engine::GetGameStateManager().GetGSComponent<CS230::Score>();
	score->Add(1);
}

void Robot::State_Dead::Enter(GameObject* object) {
	Robot* robot = static_cast<Robot*>(object);
	robot->SetVelocity({ 0,0 });
	robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}

void Robot::State_Dead::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {}
void Robot::State_Dead::CheckExit([[maybe_unused]] GameObject* object) {}



void Robot::State_Walking::Enter(GameObject* object) {
	Robot* robot = static_cast<Robot*>(object);
	robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
}


void Robot::State_Walking::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Robot* robot = static_cast<Robot*>(object);

	if (robot->GetPosition().x <= robot->left_boundary) {
		robot->SetVelocity({ robot->walking_speed, 0 });
		robot->SetScale({ 1, 1 });
	}
	else if (robot->GetPosition().x > robot->right_boundary) {
		robot->SetVelocity({ -robot->walking_speed, 0 });
		robot->SetScale({ -1, 1 });
	}
}

void Robot::State_Walking::CheckExit(GameObject* object) {
	Robot* robot = static_cast<Robot*>(object);
	Math::vec2 catPosition = robot->cat_p->GetPosition();

	Math::vec2 cat_scale = robot->cat_p->GetScale();
	Math::vec2 robot_scale = robot->GetScale();

	if (catPosition.x > robot->left_boundary && catPosition.x < robot->right_boundary && cat_scale != robot_scale) {
		robot->change_state(&robot->state_angry);
	}
}

void Robot::State_Angry::Enter(GameObject* object) {
	Robot* robot = static_cast<Robot*>(object);
	robot->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Angry));
}

void Robot::State_Angry::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Robot* robot = static_cast<Robot*>(object);
	Math::vec2 catPosition = robot->cat_p->GetPosition();

	if ((catPosition.x < robot->GetPosition().x) && (catPosition.x > robot->left_boundary)) {
		robot->SetVelocity({ -robot->angry_speed, 0 });
		robot->SetScale({ -1, 1 });
	}
	else if ((catPosition.x > robot->GetPosition().x) && catPosition.x < robot->right_boundary) {
		robot->SetVelocity({ robot->angry_speed, 0 });
		robot->SetScale({ 1, 1 });
	}

}

void Robot::State_Angry::CheckExit(GameObject* object) {
	Robot* robot = static_cast<Robot*>(object);
	Math::vec2 catPosition = robot->cat_p->GetPosition();
	if (catPosition.x < robot->left_boundary || catPosition.x > robot->right_boundary) {
		robot->change_state(&robot->state_walking);
	}
}

