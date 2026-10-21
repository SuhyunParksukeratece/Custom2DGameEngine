/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Item.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Suhyun Park
Created:    March 8, 2023
Updated:    June 13, 2023
*/

#include "Item.h"
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
#include "ItemFall.h"
#include "thornenemy.h"
#include <stdlib.h>
#include <time.h>


Item::Item(Math::vec2 position, int type) : CS230::GameObject(position)
{
	SetPosition(position);
	SetScale({ 1, 1 });
	std::srand(std::time(nullptr));
	itemfall = new CS230::ItemFall({ 0, 0 }); // Change the delta to (0, 100) for falling down
	AddGOComponent(itemfall);
	itemfall->Set({ 0, -2 });
	switch (type) {
	case 0:
		AddGOComponent(new CS230::Sprite("Assets/item1.spt", this));
		check_type = false;
		break;
	case 1:
		AddGOComponent(new CS230::Sprite("Assets/item2.spt", this));
		check_type = true;
		break;
	}
}


void Item::ResolveCollision(GameObject* other_object)
{

	switch (other_object->Type())
	{
	case GameObjectTypes::Sword:
		int objectType3 = std::rand() % 3;
		if (check_type == false) {
			if (objectType3 == 0) {
				Thornenemy* thornenemy = new Thornenemy(stay);
				thornenemy->SetPosition(stay);
				Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(thornenemy);
			}
			else if (objectType3 == 1) {
				Thornenemy* thornenemy = new Thornenemy(stay_1);
				thornenemy->SetPosition(stay_1);
				Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(thornenemy);
			}
			else {
				Thornenemy* thornenemy = new Thornenemy(stay_2);
				thornenemy->SetPosition(stay_2);
				Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(thornenemy);
			}
		}
		else {
			CS230::Hp* hp = Engine::GetGameStateManager().GetGSComponent<CS230::Hp>();
			hp->Get(1);
		}
		Destroy();
		break;
	}
}

void Item::Update(double dt)
{
	GameObject::Update(dt); // Call the base class update function

	// Update the itemfall component
	UpdatePosition(itemfall->Value());
}

