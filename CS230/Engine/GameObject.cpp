/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    May 26, 2023
*/

#include "GameObject.h"
#include "Matrix.h"
#include "Collision.h"
#include "ShowCollision.h"
#include "Engine.h"

CS230::GameObject::GameObject(Math::vec2 position) :
	GameObject(position, 0.0, { 1, 1 })
{
	//current_state = &state_none;
	destroy = false;
	matrix_outdated = true;
}

CS230::GameObject::GameObject(Math::vec2 position, double rotation, Math::vec2 scale) :
	velocity({ 0,0 }),
	position(position),
	scale(scale),
	rotation(rotation)
{
	current_state = &state_none;
	current_state->Enter(this);
	matrix_outdated = true;
}

//질문 : 오류남
void CS230::GameObject::Destroy()
{
	destroy = true;
}

bool CS230::GameObject::Destroyed()
{
	return destroy;
}

void CS230::GameObject::Update(double dt) {
	current_state->Update(this, dt);
	//sprite.Update(dt);
	if (velocity.x != 0 || velocity.y != 0) {
		UpdatePosition(velocity * dt);
	}
	UpdateGOComponents(dt);
	current_state->CheckExit(this);
	matrix_outdated = true;
}

void CS230::GameObject::change_state(State* new_state) {
	current_state = new_state;
	current_state->Enter(this);
}

void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
	//질문
	Sprite* sprite = GetGOComponent<Sprite>();
	if (sprite != nullptr) {
		sprite->Draw(camera_matrix * GetMatrix());
	}

	ShowCollision* show_collision = Engine::GetGameStateManager().GetGSComponent<ShowCollision>();
	if (show_collision != nullptr && show_collision->Enabled() != false) {
		// get the RectCollision component and draw the collision box
		Collision* collision = GetGOComponent<Collision>();
		if (collision != nullptr) {
			collision->Draw(camera_matrix);
		}
	}
}


const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
	if (matrix_outdated) {
		object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation) * Math::ScaleMatrix(scale);
		matrix_outdated = false;
	}

	return object_matrix;
}

const Math::vec2& CS230::GameObject::GetPosition() const
{
	return position;
}

const Math::vec2& CS230::GameObject::GetVelocity() const
{
	return velocity;
}

const Math::vec2& CS230::GameObject::GetScale() const
{
	return scale;
}

double CS230::GameObject::GetRotation() const
{
	return rotation;
}

void CS230::GameObject::SetPosition(Math::vec2 new_position) {
	position = new_position;
	matrix_outdated = true;
}

void CS230::GameObject::UpdatePosition(Math::vec2 delta) {
	position += delta;
	matrix_outdated = true;
}

void CS230::GameObject::SetVelocity(Math::vec2 new_velocity)
{
	velocity = new_velocity;
}

void CS230::GameObject::UpdateVelocity(Math::vec2 delta)
{
	velocity += delta;
}

void CS230::GameObject::SetScale(Math::vec2 new_scale)
{
	scale = new_scale;
	matrix_outdated = true;
}

void CS230::GameObject::UpdateScale(Math::vec2 delta)
{
	scale.x *= delta.x;
	scale.y *= delta.y;
	matrix_outdated = true;
}

void CS230::GameObject::SetRotation(double new_rotation)
{
	rotation = new_rotation;
	matrix_outdated = true;
}

void CS230::GameObject::UpdateRotation(double delta)
{
	rotation += delta;
	matrix_outdated = true;
}


bool CS230::GameObject::IsCollidingWith(GameObject* other_object) {
	Collision* collider = GetGOComponent<Collision>();
	return collider != nullptr && collider->IsCollidingWith(other_object);
}

bool CS230::GameObject::CanCollideWith(GameObjectTypes) {
	return false;
}

bool CS230::GameObject::IsCollidingWith(Math::vec2 point) {
	Collision* collider = GetGOComponent<Collision>();
	return collider != nullptr && collider->IsCollidingWith(point);
}

