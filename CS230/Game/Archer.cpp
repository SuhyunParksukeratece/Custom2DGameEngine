/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Archer.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "Archer.h"
#include "../Engine/Collision.h"
#include "Score.h"
#include "../Engine/Engine.h"
#include "Cat.h"
#include "States.h"
#include "Score.h"
#include "Hp.h"
#include "Particles.h"
#include "../Engine/Constants.h"
#include "enemyhp.h"
#include "Mission.h"

Archer::Archer(Math::vec2 position, double left_boundary, double right_boundary) : CS230::GameObject(position), left_boundary(left_boundary), right_boundary(right_boundary)
{
	AddGOComponent(new CS230::Sprite("Assets/archer.spt", this));
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


void Archer::ResolveCollision(GameObject* other_object)
{
	//spear_hp = Engine::GetGameStateManager().GetGSComponent<CS230::Hp>();
	//spear_hp->Damage(1);
	/*if (other_object->Type() == GameObjectTypes::Shoot)
	{*/
	/*if (spear_hp->Value() < 0) {
		RemoveGOComponent<CS230::CircleCollision>();
		this->change_state(&this->state_dead);
	}*/
	//}

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
		/*CS230::Score* score = Engine::GetGameStateManager().GetGSComponent<CS230::Score>();
		score->Add(10);*/
		//Destroy();
		RemoveGOComponent<CS230::Collision>();
		CS230::Score* score = Engine::GetGameStateManager().GetGSComponent<CS230::Score>();
		score->Add(100);
		CS230::Mission* mission = Engine::GetGameStateManager().GetGSComponent<CS230::Mission>();
		mission->Add(1);
		//GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
		change_state(&state_dead);
	}

}

void Archer::State_Dead::Enter(GameObject* object) {
	Archer* archer = static_cast<Archer*>(object);
	archer->SetVelocity({ 0,0 });
	archer->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
	Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::dead_particle>>()->Emit(1, archer->GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
	archer->dead_timer->Set(dead_time);
}

void Archer::State_Dead::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {}
void Archer::State_Dead::CheckExit([[maybe_unused]] GameObject* object) {
	Archer* archer = static_cast<Archer*>(object);
	if (archer->dead_timer->RemainingInt() == 0) {
		archer->Destroy();
	}

}



void Archer::State_Walking::Enter(GameObject* object) {
	Archer* archer = static_cast<Archer*>(object);
	archer->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
}


void Archer::State_Walking::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Archer* archer = static_cast<Archer*>(object);

	archer->SetVelocity({ -archer->walking_speed, 0 });
	archer->SetScale({ -2.5, 2.5 });
}

void Archer::State_Walking::CheckExit(GameObject* object) {
	Archer* archer = static_cast<Archer*>(object);

	if (archer->GetPosition().x <= archer->left_boundary) {
		archer->change_state(&archer->state_idle);
	}

}

void Archer::State_Idle::Enter(GameObject* object) {
	Archer* archer = static_cast<Archer*>(object);
	archer->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	archer->hp_timer->Set(hp_time);
}


void Archer::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
	Archer* archer = static_cast<Archer*>(object);
	archer->SetVelocity({ 0, 0 });
	archer->SetPosition({ archer->GetPosition().x, archer->GetPosition().y });

	if (archer->hp_timer->RemainingInt() <= 0) {
		CS230::Hp* hp = Engine::GetGameStateManager().GetGSComponent<CS230::Hp>();
		hp->Damage(1);
		archer->hp_timer->Reset();
	}

}


void Archer::State_Idle::CheckExit(GameObject* object) {
	Archer* archer = static_cast<Archer*>(object);

}

