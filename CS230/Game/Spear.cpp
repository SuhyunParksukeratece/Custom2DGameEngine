/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Spear.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "Spear.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "Cat.h"
#include "States.h"
#include "Score.h"
#include "Hp.h"
#include "Particles.h"
#include "../Engine/Constants.h"
#include "EnemyHp.h"
#include "Mission.h"



Spear::Spear(Math::vec2 position, double left_boundary, double right_boundary) : CS230::GameObject(position), left_boundary(left_boundary), right_boundary(right_boundary)
{
	AddGOComponent(new CS230::Sprite("Assets/spear.spt", this));
	SetPosition(position);
	current_state = &state_walking;
	current_state->Enter(this);
	SetScale({ 2.5, 2.5 });

	enemyhp = new CS230::EnemyHp(1);
	AddGOComponent(enemyhp);

	dead_timer = new CS230::Timer(0.0);
	AddGOComponent(dead_timer);

	hp_timer = new CS230::Timer(0.0);
	AddGOComponent(hp_timer);
	//spear_hp->Set(5);
}


void Spear::ResolveCollision(GameObject* other_object)
{

	switch (other_object->Type())
	{
	case GameObjectTypes::Sword:
		enemyhp->Damage(1);
		break;

	case GameObjectTypes::Thorneenemy:
		enemyhp->Damage(1);
		break;
	}

	if (enemyhp->Value() <= 0) {
		RemoveGOComponent<CS230::Collision>();
		CS230::Score* score = Engine::GetGameStateManager().GetGSComponent<CS230::Score>();
		score->Add(100);
		CS230::Mission* mission = Engine::GetGameStateManager().GetGSComponent<CS230::Mission>();
		mission->Add(1);
		change_state(&state_dead);
	}

}

void Spear::State_Dead::Enter(GameObject* object) {
	Spear* spear = static_cast<Spear*>(object);
	spear->SetVelocity({ 0,0 });
	spear->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
	Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::dead_particle>>()->Emit(1, spear->GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
	spear->dead_timer->Set(dead_time);
}

void Spear::State_Dead::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {}
void Spear::State_Dead::CheckExit([[maybe_unused]] GameObject* object) {
	Spear* spear = static_cast<Spear*>(object);
	if (spear->dead_timer->RemainingInt() == 0) {
		spear->Destroy();
	}
}



void Spear::State_Walking::Enter(GameObject* object) {
	Spear* spear = static_cast<Spear*>(object);
	spear->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
}


void Spear::State_Walking::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Spear* spear = static_cast<Spear*>(object);

	spear->SetVelocity({ -spear->walking_speed, 0 });
	spear->SetScale({ -2.5, 2.5 });
}

void Spear::State_Walking::CheckExit(GameObject* object) {
	Spear* spear = static_cast<Spear*>(object);

	if (spear->GetPosition().x <= spear->left_boundary) {
		spear->change_state(&spear->state_idle);
	}

}

void Spear::State_Idle::Enter(GameObject* object) {
	Spear* spear = static_cast<Spear*>(object);
	spear->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	spear->hp_timer->Set(hp_time);
}

void Spear::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Spear* spear = static_cast<Spear*>(object);
	spear->SetVelocity({ 0, 0 });
	spear->SetPosition({ spear->GetPosition().x, spear->GetPosition().y });

	if (spear->hp_timer->RemainingInt() <= 0) {
		CS230::Hp* hp = Engine::GetGameStateManager().GetGSComponent<CS230::Hp>();
		hp->Damage(1);
		spear->hp_timer->Reset();
	}


}

void Spear::State_Idle::CheckExit(GameObject* object) {
	Spear* spear = static_cast<Spear*>(object);

}

