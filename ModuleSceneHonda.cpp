#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 10;
	ground.y = 375;
	ground.w = 850;
	ground.h = 65;
	
	// Background
	background.x = 120;
	background.y = 130;
	background.w = 670;
	background.h = 200;
	
	// Cieling
	cieling.x = 90;
	cieling.y = 8;
	cieling.w = 765;
	cieling.h = 50;
	
	// Bath
	bath.x = 165;
	bath.y = 65;
	bath.w = 335;
	bath.h = 49;

	// Bucket
	bucket.x = 540;
	bucket.y = 85;
	bucket.w = 35;
	bucket.h = 29;

	// water animation
	water.frames.push_back({ 0, 0, 0, 0 });
	water.frames.push_back({ 0, 0, 0, 0 });
	water.frames.push_back({ 300, 450, 285, 20 });
	water.frames.push_back({ 8, 450, 285, 20 });
	water.frames.push_back({ 300, 450, 285, 20 });
	water.frames.push_back({ 0, 0, 0, 0 });
	water.frames.push_back({ 0, 0, 0, 0 });
	water.speed = 0.08f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage2.png");

	// Enable the player module
	App->player->Enable();

	// trigger background music
	App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------
	
	// render
	App->renderer->Blit(graphics, -85, 155, &ground, 0.7f); // ground
	App->renderer->Blit(graphics, -58, 0, &cieling, 0.7f); // cieling
	App->renderer->Blit(graphics, -8, -20, &background, 0.7); // background
	App->renderer->Blit(graphics, 215, 120, &bath, 0.7f); // bath
	App->renderer->Blit(graphics, 188, 150, &bucket, 0.7f); // bucket
	App->renderer->Blit(graphics, 243, 132, &(water.GetCurrentFrame()), 0.5f); // water

	// Change Scene with spacebar
	if (transition && App->input->GetKey(SDL_SCANCODE_SPACE) == KeyState::KEY_DOWN)
	{
		//App->fade->FadeToBlack(App->scene_ken, this, 3.0f);
		transition = false;
	}
	return UPDATE_CONTINUE;
}