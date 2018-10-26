#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 216;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 0, 131, 65, 90 });
	forward.frames.push_back({ 75, 129, 63, 90 });
	forward.frames.push_back({ 160, 128, 65, 90 });
	forward.frames.push_back({ 255, 127, 65, 90 });
	forward.frames.push_back({ 340, 128, 65, 91 });
	forward.frames.push_back({ 425, 129, 62, 90 });
	forward.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	ryuPos = (SCREEN_WIDTH / 8) - App->renderer->camera.x * 0.5f;
	timer = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	DrawingPlayer();

	return UPDATE_CONTINUE;
}

void ModulePlayer::DrawingPlayer()
{
	//ryu controls
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (ryuPos > LEFT_BOUND)
			ryuPos -= speedPlayer * 0.5f;
		if (ryuPos <= (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f)
			App->renderer->camera.x += speedPlayer;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (ryuPos < -RIGHT_BOUND)
			ryuPos += speedPlayer * 0.5f;
		if (ryuPos >= (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f)
			App->renderer->camera.x -= speedPlayer;
	}
	if (ryuPos < lastX) // moving forward
	{
		App->renderer->Blit(graphics, ryuPos, 120, &(forward.GetCurrentFrame()));
	}
	else if (ryuPos > lastX) // moving backward
	{
		App->renderer->Blit(graphics, ryuPos, 120, &(backward.GetCurrentFrame()));
	}
	else { //idle
		App->renderer->Blit(graphics, ryuPos, 120, &(idle.GetCurrentFrame()));
	}
	lastX = ryuPos;
}