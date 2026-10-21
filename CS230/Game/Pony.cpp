/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Pony.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "Pony.h"
#include "../Engine/Collision.h"
#include "Score.h"
#include "../Engine/Engine.h"
#include "Cat.h"
#include "States.h"
#include "Score.h"
#include "Hp.h"
#include "../Engine/Constants.h"
#include "Particles.h"
#include "enemyhp.h"
#include "Mission.h"


Pony::Pony(Math::vec2 position, double left_boundary, double right_boundary) : CS230::GameObject(position), left_boundary(left_boundary), right_boundary(right_boundary)
{
	AddGOComponent(new CS230::Sprite("Assets/pony.spt", this));
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

}


void Pony::ResolveCollision(GameObject* other_object)
{
	switch (other_object->Type())
	{
	case GameObjectTypes::Sword:
		//health -= 1;
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

void Pony::State_Dead::Enter(GameObject* object) {
	Pony* pony = static_cast<Pony*>(object);
	pony->SetVelocity({ 0,0 });
	pony->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
	Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::dead_particle>>()->Emit(1, pony->GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
	pony->dead_timer->Set(dead_time);
}

void Pony::State_Dead::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {}
void Pony::State_Dead::CheckExit([[maybe_unused]] GameObject* object) {
	Pony* pony = static_cast<Pony*>(object);
	if (pony->dead_timer->RemainingInt() == 0) {
		pony->Destroy();
	}
}



void Pony::State_Walking::Enter(GameObject* object) {
	Pony* pony = static_cast<Pony*>(object);
	pony->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
}


void Pony::State_Walking::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Pony* pony = static_cast<Pony*>(object);

	pony->SetVelocity({ -pony->walking_speed, 0 });
	pony->SetScale({ -2.5, 2.5 });
}

void Pony::State_Walking::CheckExit(GameObject* object) {
	Pony* pony = static_cast<Pony*>(object);

	if (pony->GetPosition().x <= pony->left_boundary) {
		pony->change_state(&pony->state_idle);
	}
}

void Pony::State_Idle::Enter(GameObject* object) {
	Pony* pony = static_cast<Pony*>(object);
	pony->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	pony->hp_timer->Set(hp_time);
}

void Pony::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Pony* pony = static_cast<Pony*>(object);
	pony->SetVelocity({ 0, 0 });
	pony->SetPosition({ pony->GetPosition().x, pony->GetPosition().y });


	if (pony->hp_timer->RemainingInt() <= 0) {
		CS230::Hp* hp = Engine::GetGameStateManager().GetGSComponent<CS230::Hp>();
		hp->Damage(1);
		pony->hp_timer->Reset();
	}
}

void Pony::State_Idle::CheckExit(GameObject* object) {
	Pony* pony = static_cast<Pony*>(object);
}
