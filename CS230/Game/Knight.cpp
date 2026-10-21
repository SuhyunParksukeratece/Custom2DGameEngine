/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Knight.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/


#pragma once
#include "Knight.h"
#include "Gravity.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "Portal.h"
#include "States.h"
#include "Particles.h"
#include "../Engine/Particle.h"
#include <math.h>

#include "../Engine/Constants.h"
#include "Sword.h"
#include "Score.h"
#include "Mission.h"

Knight::Knight(Math::vec2 position, GameObject* standing_on) :
	GameObject(position),
	standing_on(standing_on)

{
	AddGOComponent(new CS230::Sprite("Assets/Knight.spt", this));
	current_state = &state_idle;
	current_state->Enter(this);
	exploded = false;
	check_state = &state_idle;
	SetScale({ 1.5, 1.5 });

	shot_timer = new CS230::Timer(0.0);
	AddGOComponent(shot_timer);
	shot_timer->Set(shot_time);
}

void Knight::update_x_velocity(double dt) {


	if (GetVelocity().x > x_drag * dt) {
		UpdateVelocity({ -x_drag * dt, 0 });
	}
	else if (GetVelocity().x < -x_drag * dt) {
		UpdateVelocity({ x_drag * dt, 0 });
	}
	else {
		SetVelocity({ 0, GetVelocity().y });
	}
}

void Knight::Update(double dt)
{
	GameObject::Update(dt);

	auto collider = GetGOComponent<CS230::RectCollision>();

	if (collider != nullptr)
	{
		auto bounds = collider->WorldBoundary();

		if (bounds.Left() < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x)
		{
			UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x - bounds.Left(), 0 });
			SetVelocity({ 0, GetVelocity().y });
		}

		if (bounds.Right() > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x)
		{
			UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - bounds.Right(), 0 });
			SetVelocity({ 0, GetVelocity().y });
		}

		// Check if standing on floor
		if (standing_on == nullptr || collider->IsCollidingWith(standing_on->GetPosition()))
		{
			standing_on = nullptr;
			change_state(&state_falling);
		}
	}
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter) && shot_timer->Remaining() == 0) {
		Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(
			new Sword(
				{ GetPosition().x, GetPosition().y + 50 },
				GetScale(),
				Math::vec2{ 0, Sword::DefaultVelocity }));
		shot_timer->Reset();
	}
	CS230::Hp* hp = Engine::GetGameStateManager().GetGSComponent<CS230::Hp>();
	if (hp->Value() <= 0) {
		change_state(&state_dead);
	}
	CS230::Mission* mission = Engine::GetGameStateManager().GetGSComponent<CS230::Mission>();
	if (mission->Value() >= 25) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
	}
	UpdateGOComponents(dt);
}

void Knight::State_Idle::Enter(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::sparkle>>()->Emit(9, knight->GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
}

void Knight::State_Idle::Update(GameObject* object, double dt) { }

void Knight::State_Idle::CheckExit(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);

	if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
		knight->change_state(&knight->state_jumping);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
		knight->check_state = &knight->state_idle;
		knight->change_state(&knight->state_attack);
	}
	if (knight->standing_on != nullptr && !knight->standing_on->GetGOComponent<CS230::Collision>()->IsCollidingWith(knight->GetPosition())) {
		knight->standing_on = nullptr;
		knight->change_state(&knight->state_falling);
	}
}


void Knight::State_Jumping::Enter(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter) == false) {
		knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
	}
	else {
		knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
	}
	knight->SetVelocity({ knight->GetVelocity().x,  Knight::jump_velocity });

	knight->standing_on = nullptr;
}

void Knight::State_Jumping::Update(GameObject* object, double dt) {
	Knight* knight = static_cast<Knight*>(object);
	knight->UpdateVelocity({ 0 , (-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt) });
	knight->update_x_velocity(dt);
}

void Knight::State_Jumping::CheckExit(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::W) == false) {
		knight->change_state(&knight->state_falling);
		knight->SetVelocity({ knight->GetVelocity().x, 0 });
	}
	else if (knight->GetVelocity().y <= 0) {
		knight->change_state(&knight->state_falling);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter)) {
		knight->change_state(&knight->state_attack);
	}
}


void Knight::State_Dead::Enter(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dead));
}

void Knight::State_Dead::Update(GameObject* object, double dt) {
	Knight* knight = static_cast<Knight*>(object);
	Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
}

void Knight::State_Dead::CheckExit(GameObject* object) {

}


void Knight::State_Attack::Enter(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
}


void Knight::State_Attack::Update(GameObject* object, double dt) {
	Knight* knight = static_cast<Knight*>(object);
	knight->update_x_velocity(dt);
}

void Knight::State_Attack::CheckExit(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);

	if (knight->standing_on != nullptr) {
		if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter) == false) {
			knight->change_state(&knight->state_idle);
		}
	}

}

void Knight::State_Falling::Enter(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Enter) == false) {
		knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
	}
	else {
		knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
	}
}

void Knight::State_Falling::Update(GameObject* object, double dt) {
	Knight* knight = static_cast<Knight*>(object);

	knight->UpdateVelocity({ 0, -(Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt) });
	knight->update_x_velocity(dt);
}

void Knight::State_Falling::CheckExit(GameObject* object) {
	Knight* knight = static_cast<Knight*>(object);
	if (knight->standing_on != nullptr)
	{
		if (knight->GetVelocity().x != 0)
		{
			knight->change_state(&knight->state_idle);
		}
		else
		{
			knight->change_state(&knight->state_idle);
		}
		knight->SetVelocity({ knight->GetVelocity().x, 0 });
	}
}


bool Knight::CanCollideWith(GameObjectTypes) {
	return true;
}

void Knight::ResolveCollision(GameObject* other_object)
{
	if (exploded == false) {
		exploded = true;
	}

	Math::rect knight_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();

	Math::rect  other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

	switch (other_object->Type())
	{

	case GameObjectTypes::Floor:
	{
		// ...
		if (current_state == &state_falling) {
			if (knight_rect.Bottom() <= other_rect.Top()) {
				SetPosition({ GetPosition().x, other_rect.Top() });
				// ...
				standing_on = other_object;
				current_state->CheckExit(this);
				return;
			}
		}

		break;
	}
	} //switch
} //function

void Knight::Draw(Math::TransformationMatrix camera_matrix) {
	CS230::GameObject::Draw(camera_matrix);
}