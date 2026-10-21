/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 4, 2023
*/


#pragma once
#include "Cat.h"
#include "Mode1.h"
#include "Gravity.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "Portal.h"
#include "States.h"
#include "Particles.h"
#include "../Engine/Particle.h"
//¿¡..? Áú¹®
#include "../Engine/Constants.h"


Cat::Cat(Math::vec2 position, GameObject* standing_on) :
	//start_position(start_position),
	GameObject(position),
	standing_on(standing_on)
	//camera(camera)
{
	AddGOComponent(new CS230::Sprite("Assets/Cat.spt", this));
	current_state = &state_idle;
	current_state->Enter(this);

	hurt_timer = new CS230::Timer(0.0);
	AddGOComponent(hurt_timer);
}

//void Cat::Load()
//{
//	sprite.Load("Assets/Cat.spt");
//	velocity = { 0,0 };
//	position = start_position;
//	current_state = &state_idle;
//	current_state->Enter(this);
//	//state_idle.Enter(this);
//}

void Cat::update_x_velocity(double dt) {
	//Math::vec2 Vel = GetVelocity();
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
		UpdateVelocity({ x_acceleration * dt, 0 });
		//Vel.x += x_acceleration * dt;
		//velocity.x += x_acceleration * dt;
		if (GetVelocity().x > max_velocity) {
			SetVelocity({ max_velocity, GetVelocity().y });
			//Vel.x = max_velocity;
		}
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
		UpdateVelocity({ -x_acceleration * dt, 0 });
		//Vel.x -= x_acceleration * dt;
		if (GetVelocity().x < -max_velocity) {
			SetVelocity({ -max_velocity, GetVelocity().y });
			//Vel.x = -max_velocity;
		}
	}
	else {
		if (GetVelocity().x > x_drag * dt) {
			UpdateVelocity({ -x_drag * dt, 0 });
			//Vel.x -= x_drag * dt;
		}
		else if (GetVelocity().x < -x_drag * dt) {
			UpdateVelocity({ x_drag * dt, 0 });
			//Vel.x += x_drag * dt;
		}
		else {
			SetVelocity({ 0, GetVelocity().y });
			//Vel.x = 0;
		}
	}
}

/*void Cat::change_state(State* new_state) {
	Engine::GetLogger().LogDebug("Cat Leaving State: " + current_state->GetName());
	Engine::GetLogger().LogDebug("Cat Entering State: " + new_state->GetName());
	current_state = new_state;
	current_state->Enter(this);
}*/

//void Cat::Draw(Math::TransformationMatrix camera_matrix) {
//	sprite.Draw(camera_matrix * object_matrix);
//}


/*void Cat::Update(double dt) {
	GameObject::Update(dt);

	CS230::RectCollision* collider = GetGOComponent<CS230::RectCollision>();*/

	// Boundary Check
	/*if (GetPosition().x < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) {
		SetPosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x) {
		SetPosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}*/

	/*
		if (collider != nullptr)
		{
			Math::rect worldBoundary = collider->WorldBoundary();
			Math::vec2 newPosition = GetPosition();

			if (worldBoundary.Left() / 2 < 0)
			{
				UpdatePosition({ ,  0 });
				SetVelocity({ 0, GetVelocity().y });
			}
			else if (worldBoundary.Right() > Engine::GetWindow().GetSize().x)
			{
				newPosition.x = Engine::GetWindow().GetSize().x - worldBoundary.Size().x;
				SetVelocity({ 0, GetVelocity().y });
				//SetVelocity({ -hurt_acceleration, hurt_velocity });
			}

			SetPosition(newPosition);

		}*/

void Cat::Update(double dt)
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
	}

	/*
	if (GetPosition().x < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2)
	{
		SetPosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x)
	{
		SetPosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	*/

}

void Cat::State_Idle::Enter(GameObject* object) {
	Cat* cat = static_cast<Cat*>(object);
	cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
	//cat->sprite.PlayAnimation(0);
}

void Cat::State_Idle::Update(GameObject* object, double dt) { }

void Cat::State_Idle::CheckExit(GameObject* object) {
	Cat* cat = static_cast<Cat*>(object);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
		cat->change_state(&cat->state_running);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
		cat->change_state(&cat->state_running);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up)) {
		cat->change_state(&cat->state_jumping);
	}
}


void Cat::State_Jumping::Enter(GameObject* object) {
	Cat* cat = static_cast<Cat*>(object);
	//cat->SetPosition({ cat->GetPosition().x,  Cat::jump_velocity });
	//cat->velocity.y = Cat::jump_velocity;
	cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
	cat->SetVelocity({ cat->GetVelocity().x,  Cat::jump_velocity });

	cat->standing_on = nullptr;
}

void Cat::State_Jumping::Update(GameObject* object, double dt) {
	Cat* cat = static_cast<Cat*>(object);
	cat->UpdateVelocity({ 0, (-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue()
 * dt) });
	//cat->velocity.y -= Mode1::gravity * dt;
	cat->update_x_velocity(dt);
}

void Cat::State_Jumping::CheckExit(GameObject* object) {
	Cat* cat = static_cast<Cat*>(object);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false) {
		cat->change_state(&cat->state_falling);
		//cat->SetPosition({ cat->GetPosition().x,  0 });
		cat->SetVelocity({ cat->GetVelocity().x, 0 });
		//cat->velocity.y = 0;
	}
	else if (cat->GetVelocity().y <= 0) {
		cat->change_state(&cat->state_falling);
	}
}


void Cat::State_Falling::Enter(GameObject* object) {
	Cat* cat = static_cast<Cat*>(object);
	cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
	cat->check_y = cat->GetPosition().y;
}

void Cat::State_Falling::Update(GameObject* object, double dt) {
	Cat* cat = static_cast<Cat*>(object);
	cat->UpdateVelocity({ 0, -(Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue()
 * dt) });
	//cat->UpdateVelocity({ 0, -(Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt) });
	//cat->velocity.y -= Mode1::gravity * dt;
	cat->update_x_velocity(dt);
}

void Cat::State_Falling::CheckExit(GameObject* object) {
	/*Cat* cat = static_cast<Cat*>(object);
	if (cat->GetPosition().y <= Mode1::floor)
	{
		if (cat->GetVelocity().x == 0)
		{
			cat->change_state(&cat->state_idle);
		}
		else
		{
			if (cat->GetVelocity().x > 0)
			{
				cat->SetScale({ 1, 1 });
				//cat->flipped = false;
			}
			else
			{
				cat->SetScale({ -1, 1 });
				//cat->flipped = true;
			}
			cat->change_state(&cat->state_running);
		}

		cat->SetPosition({ cat->GetPosition().x, Mode1::floor });
		//cat->position.y = Mode1::floor;
		cat->SetVelocity({ cat->GetVelocity().x , 0 });
		//cat->velocity.y = 0;
	}*/

	Cat* cat = static_cast<Cat*>(object);
	if (cat->standing_on != nullptr) {

		double HIGHT = cat->check_y - cat->GetPosition().y;


		if (cat->GetVelocity().x > 0) {

			if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
				cat->change_state(&cat->state_skidding);
			}
			else {
				cat->change_state(&cat->state_running);
			}
		}
		else if (cat->GetVelocity().x < 0)
		{
			if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))
			{
				cat->change_state(&cat->state_skidding);
			}
			else
			{
				cat->change_state(&cat->state_running);
			}
		}
		else
		{
			if (HIGHT > Cat::LargeFallHeight)
			{
				Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, cat->GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
			}

			cat->change_state(&cat->state_idle);
		}

		cat->SetVelocity({ cat->GetVelocity().x, 0 });
	}

	if (cat->GetPosition().y < -500) {
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Menu));
	}

}


void Cat::State_Running::Enter(GameObject* object)
{
	Cat* cat = static_cast<Cat*>(object);
	cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));

	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))
	{
		cat->SetScale({ 1, 1 });
		//cat->flipped = false;
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left))
	{
		cat->SetScale({ -1, 1 });
		//cat->flipped = true;
	}
}

void Cat::State_Running::Update(GameObject* object, double dt) {
	Cat* cat = static_cast<Cat*>(object);
	cat->update_x_velocity(dt);
}

void Cat::State_Running::CheckExit(GameObject* object)
{
	Cat* cat = static_cast<Cat*>(object);
	if (cat->GetVelocity().x == 0) {
		cat->change_state(&cat->state_idle);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up))
	{
		cat->change_state(&cat->state_jumping);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && cat->GetVelocity().x > 0 ||
		Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && cat->GetVelocity().x < 0)
	{
		cat->change_state(&cat->state_skidding);
	}

	if (cat->standing_on != nullptr && cat->standing_on->GetGOComponent<CS230::Collision>()->IsCollidingWith(cat->GetPosition()) == false) {
		cat->standing_on = nullptr;
		cat->change_state(&cat->state_falling);
	}
	//Cat::GetGOComponent<CS230::Collision>()->IsCollidingWith(other_object)

}


void Cat::State_Skidding::Enter(GameObject* object) {
	Cat* cat = static_cast<Cat*>(object);
	Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, cat->GetPosition(), { 0, 0 }, { 2 * cat->GetVelocity().x, 0 }, Math::PI / 6);
	cat->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Skidding));

}
void Cat::State_Skidding::Update(GameObject* object, double dt)
{
	Cat* cat = static_cast<Cat*>(object);
	if (cat->GetVelocity().x > 0) {
		cat->UpdateVelocity({ -(x_drag + x_acceleration * dt) , 0 });
		//cat->velocity.x -= (x_drag + x_acceleration) * dt;
	}
	else if (cat->GetVelocity().x < 0) {
		cat->UpdateVelocity({ (x_drag + x_acceleration * dt) , 0 });
		//cat->velocity.x += (x_drag + x_acceleration) * dt;
	}
}

void Cat::State_Skidding::CheckExit(GameObject* object)
{
	Cat* cat = static_cast<Cat*>(object);
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up))
	{
		cat->change_state(&cat->state_jumping);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && cat->GetVelocity().x < 0)
	{
		cat->change_state(&cat->state_running);
	}
	else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && cat->GetVelocity().x > 0)
	{
		cat->change_state(&cat->state_running);
	}
}

bool Cat::CanCollideWith(GameObjectTypes) {
	return true;
}

void Cat::ResolveCollision(GameObject* other_object)
{


	//Math::rect cat_rect = catCollider->WorldBoundary();
	//Math::rect other_rect = otherCollider->WorldBoundary();
	Math::rect cat_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();

	Math::rect  other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

	switch (other_object->Type())
	{

	case GameObjectTypes::Floor: [[fallthrough]];

	case GameObjectTypes::Crates:
	{
		// other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

		 /*if (cat_rect.Left() < other_rect.Right() && GetVelocity().x < 0)
		 {
			 // Colliding with crate on the left side
			 UpdatePosition({ other_rect.Right() - cat_rect.Left(), 0 });

			 SetVelocity({ 0, GetVelocity().y });
		 }
		 else if (cat_rect.Right() > other_rect.Left() && GetVelocity().x >= 0)
		 {
			 // Colliding with crate on the right side
			 UpdatePosition({ other_rect.Left() - cat_rect.Right(), 0 });

			 SetVelocity({ 0, GetVelocity().y });
		 }*/

		if (current_state == &state_falling) {
			if (cat_rect.Top() > other_rect.Top()) {
				SetPosition({ GetPosition().x, other_rect.Top() });

				if (check_y > Cat::LargeFallHeight)
				{
					Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
				}

				standing_on = other_object;
				current_state->CheckExit(this);
				return;
			}
		}
		if (cat_rect.Left() < other_rect.Left()) {
			UpdatePosition(Math::vec2{ (other_rect.Left() - cat_rect.Right()), 0.0 });
			SetVelocity({ 0, GetVelocity().y });
		}
		else {
			UpdatePosition(Math::vec2{ (other_rect.Right() - cat_rect.Left()), 0.0 });
			SetVelocity({ 0, GetVelocity().y });
		}


		break;
	}

	case GameObjectTypes::Robot:
	{
		/*other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

	   hurt_timer->Set(2.0);

	   if (cat_rect.Left() < other_rect.Right() && GetVelocity().x < 0)
	   {
		   // Colliding with object on the left side
		   UpdatePosition({ other_rect.Right() - cat_rect.Left(), 0 });

		   // Modify the velocity to bounce back
		   SetVelocity({ hurt_acceleration, hurt_velocity });

		   change_state(&state_falling);
	   }
	   else if (cat_rect.Right() > other_rect.Left() && GetVelocity().x >= 0)
	   {
		   // Colliding with object on the right side
		   UpdatePosition({ other_rect.Left() - cat_rect.Right(), 0 });

		   // Modify the velocity to bounce back
		   SetVelocity({ -hurt_acceleration, hurt_velocity });

		   change_state(&state_falling);
	   }*/

		if (current_state == &state_falling && cat_rect.Top() > other_rect.Top() && hurt_timer->Remaining() == 0) {
			Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Smoke>>()->Emit(2, GetPosition(), { 0, 0 }, { 0, 100 }, Math::PI / 2);
			other_object->ResolveCollision(this);

			SetPosition({ GetPosition().x, other_rect.Top() });
			SetVelocity({ GetVelocity().x, pop_velocity });
			//other_object->ResolveCollision(this);
		}
		else {
			if (cat_rect.Left() < other_rect.Left()) {
				SetVelocity({ -hurt_acceleration, hurt_velocity });
			}
			else {
				SetVelocity({ hurt_acceleration, hurt_velocity });
			}
			change_state(&state_falling);
			hurt_timer->Set(hurt_time);
		}

		standing_on = nullptr;
		break;
	}

	case GameObjectTypes::Asteroid:
	{
		//other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();

		/*hurt_timer->Set(2.0);

		if (cat_rect.Left() < other_rect.Right() && GetVelocity().x < 0)
		{
			// Colliding with object on the left side
			UpdatePosition({ other_rect.Right() - cat_rect.Left(), 0 });

			// Modify the velocity to bounce back
			SetVelocity({ hurt_acceleration, hurt_velocity });

			change_state(&state_falling);
		}
		else if (cat_rect.Right() > other_rect.Left() && GetVelocity().x >= 0)
		{
			// Colliding with object on the right side
			UpdatePosition({ other_rect.Left() - cat_rect.Right(), 0 });

			// Modify the velocity to bounce back
			SetVelocity({ -hurt_acceleration, hurt_velocity });

			change_state(&state_falling);
		}*/


		if (current_state == &state_falling && cat_rect.Top() > other_rect.Top() && hurt_timer->Remaining() == 0) {
			SetPosition({ GetPosition().x, other_rect.Top() });
			SetVelocity({ GetVelocity().x,  bounce_velocity });
			other_object->ResolveCollision(this);
		}

		else {
			if (cat_rect.Left() < other_rect.Left()) {
				SetVelocity({ -hurt_acceleration, hurt_velocity });
			}
			else {
				SetVelocity({ hurt_acceleration, hurt_velocity });
			}
			change_state(&state_falling);
			hurt_timer->Set(hurt_time);
		}

		standing_on = nullptr;
		break;
	}

	case GameObjectTypes::Portal:
	{
		static_cast<Portal*>(other_object)->GoToState();
		break;
	}



	} //switch
} //function

void Cat::Draw(Math::TransformationMatrix camera_matrix) {
	if (hurt_timer->Remaining() == 0.0 || hurt_timer->TickTock() == true) {
		CS230::GameObject::Draw(camera_matrix);
	}
}