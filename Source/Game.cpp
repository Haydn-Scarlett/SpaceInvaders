#include <string>
#include <Windows.h>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Game.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
and even seeding the random number generator.
*/
SpaceInvaders::SpaceInvaders()
{
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
SpaceInvaders::~SpaceInvaders()
{
	this->inputs->unregisterCallback(key_callback_id);
	this->inputs->unregisterCallback(mouse_callback_id);

	gameplay_area.~GameObject();
	heart.~GameObject();

	for (int i = 0; i < MAX_ALIENS; i++)
	{
		aliens[i].~GameObject();
	}
	for (int i = 0; i < MAX_ALIEN_LASERS; i++)
	{
		alien_lasers[i].~GameObject();
	}
	for (int i = 0; i < MAX_LASERS; i++)
	{
		lasers[i].~GameObject();
	}
	for (int i = 0; i < MAX_WALL_BLOCKS; i++)
	{
		wall[i].~GameObject();
	}

}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The keyHandler and clickHandler
callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool SpaceInvaders::init()
{
	setupResolution();
	if (!initAPI())
	{
		return false;
	}
	renderer->setWindowTitle("Space Invaders!");

	// input handling functions
	inputs->use_threads = false;

	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &SpaceInvaders::keyHandler, this);

	mouse_callback_id = inputs->addCallbackFnc(
		ASGE::E_MOUSE_CLICK, &SpaceInvaders::clickHandler, this);

	clearArrays();
	loadFiles();

	if (!gameplay_area.addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\background.png"))
	{
		return false;
	}
	if (!ship.addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\spaceshooter\\PNG\\playerShip1_red.png"))
	{
		return false;
	}
	if (!heart.addSpriteComponent(renderer.get(),
		".\\Resources\\Textures\\heart.png"))
	{
		return false;
	}

	ASGE::Sprite* background_sprite = gameplay_area.spriteComponent()->getSprite();
	background_sprite->height(game_height * GAMEPLAY_HEIGHT);
	background_sprite->width(background_sprite->height() * 1.25f);
	background_sprite->yPos(game_height * .09f);
	background_sprite->xPos((game_width - background_sprite->width()) * 0.5f);


	ASGE::Sprite* ship_sprite = ship.spriteComponent()->getSprite();
	ship_sprite->height(background_sprite->height() * .03f);
	ship_sprite->width(background_sprite->height() * .15f);
	

	ASGE::Sprite* heart_sprite = heart.spriteComponent()->getSprite();
	heart_sprite->height(game_height * 0.04f);
	heart_sprite->width(game_height * 0.04f);
	heart_sprite->yPos(game_height * 0.05f);
	heart_sprite->xPos(background_sprite->xPos());


	for (int i = 0; i < MAX_ALIENS; i++)
	{
		if (i == 0 || i == 10)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack1.png"))
			{
				return false;
			}

		}
		else if (i == 1 || i == 5 || i == 9)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack2.png"))
			{
				return false;
			}

		}
		else if (i == 2 || i == 8)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack3.png"))
			{
				return false;
			}
		}
		else if (i == 3 || i == 7)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack4.png"))
			{
				return false;
			}
		}
		else if (i == 4 || i == 6)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack5.png"))
			{
				return false;
			}
		}
		else if (i == 11 || i == 21)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyGreen1.png"))
			{
				return false;
			}

		}
		else if (i == 12 || i == 16 || i == 20)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyGreen2.png"))
			{
				return false;
			}

		}
		else if (i == 13 || i == 19)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyGreen3.png"))
			{
				return false;
			}
		}
		else if (i == 14 || i == 18)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyGreen4.png"))
			{
				return false;
			}
		}
		else if (i == 15|| i == 17)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyGreen5.png"))
			{
				return false;
			}
		}
		else if (i == 22 || i == 32)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlue1.png"))
			{
				return false;
			}

		}
		else if (i == 23 || i == 27 || i == 31)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlue2.png"))
			{
				return false;
			}

		}
		else if (i == 24 || i == 30)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlue3.png"))
			{
				return false;
			}
		}
		else if (i == 25 || i == 29)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlue4.png"))
			{
				return false;
			}
		}
		else if (i == 26 || i == 28)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlue5.png"))
			{
				return false;
			}
		}
		else if (i == 33 || i == 43)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyRed1.png"))
			{
				return false;
			}

		}
		else if (i == 34 || i == 38 || i == 42)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyRed2.png"))
			{
				return false;
			}

		}
		else if (i == 35 || i == 41)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyRed3.png"))
			{
				return false;
			}
		}
		else if (i == 36 || i == 40)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyRed4.png"))
			{
				return false;
			}
		}
		else if (i == 37 || i == 39)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyRed5.png"))
			{
				return false;
			}
		}
		else if (i == 44 || i == 54)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack1.png"))
			{
				return false;
			}

		}
		else if (i == 45 || i == 49 || i == 53)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack2.png"))
			{
				return false;
			}

		}
		else if (i == 46 || i == 52)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack3.png"))
			{
				return false;
			}
		}
		else if (i == 47 || i == 51)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack4.png"))
			{
				return false;
			}
		}
		else if (i == 48 || i == 50)
		{
			if (!aliens[i].addSpriteComponent(renderer.get(),
				".\\Resources\\Textures\\spaceshooter\\PNG\\Enemies\\enemyBlack5.png"))
			{
				return false;
			}
		}
		ASGE::Sprite* alien = aliens[i].spriteComponent()->getSprite();
		alien->height((game_height * GAMEPLAY_HEIGHT) * .066f);
		alien->width((game_height * GAMEPLAY_HEIGHT) * .066f);
	}

	for (int i = 0; i < MAX_ALIEN_LASERS; i++)
	{
		if (!alien_lasers[i].addSpriteComponent(renderer.get(),
			".\\Resources\\Textures\\spaceshooter\\PNG\\Lasers\\laserGreen04.png"))
		{
			return false;
		}
		alien_lasers[i].setVisible(false);
		ASGE::Sprite* alien_laser = alien_lasers[i].spriteComponent()->getSprite();
		alien_laser->height((game_height * GAMEPLAY_HEIGHT) * .035f);
		alien_laser->width((game_height * GAMEPLAY_HEIGHT) * .005f);
	}


	for (int i = 0; i < MAX_LASERS; i++)
	{
		if (!lasers[i].addSpriteComponent(renderer.get(),
			".\\Resources\\Textures\\spaceshooter\\PNG\\Lasers\\laserRed04.png"))
		{
			return false;
		}
		lasers[i].setVisible(false);
		ASGE::Sprite* laser = lasers[i].spriteComponent()->getSprite();
		laser->height((game_height * GAMEPLAY_HEIGHT) * .035f);
		laser->width((game_height * GAMEPLAY_HEIGHT) * .005f);
	}

	rect background = gameplay_area.spriteComponent()->getBoundingBox();
		float new_yPos = background.y + (background.height * 0.8f);
		float new_xPos = background.x + (background.length * 0.2f);

	for (int i = 0; i < MAX_WALL_BLOCKS; i++)
	{
		if (!wall[i].addSpriteComponent(renderer.get(),
			".\\Resources\\Textures\\spaceshooter\\PNG\\UI\\buttonRed.png"))
		{
			return false;
		}
		wall[i].setVisible(false);
		ASGE::Sprite* wall_block = wall[i].spriteComponent()->getSprite();
		wall_block->height((game_height * GAMEPLAY_HEIGHT) * .01f);
		wall_block->width((game_height * GAMEPLAY_HEIGHT) * .014f);
		
		new_xPos - (wall_block->width() * 1.5f);
		if (i == 32 || i == 60 || i == 88 || i == 112 || i == 128)
		{
			new_xPos = background.x + (background.length * 0.2f);
			wall_block->xPos(new_xPos - (wall_block->width() * 3.5f));
		}
		else if (i == 12 || i == 33 || i == 61 || i == 89 || i == 113 || i == 129)
		{
			new_xPos = background.x + (background.length * 0.2f);
			wall_block->xPos(new_xPos - (wall_block->width() * 2.5f));
		}
		else if (i == 0 || i == 13 || i == 34 || i == 62 || i == 90)
		{
			wall_block->xPos(new_xPos - (wall_block->width() * 1.5f));
		}
		else if (i == 1 || i == 14 || i == 35 || i == 63)
		{
			wall_block->xPos(new_xPos - (wall_block->width() * 0.5f));
		}
		else if (i == 2 || i == 15 || i == 36 || i == 64 || i == 91)
		{
			wall_block->xPos(new_xPos + (wall_block->width() * 0.5f));
		}
		else if (i == 16 || i == 37 || i == 65 || i == 92 || i == 114 || i == 130)
		{
			new_xPos = background.x + (background.length * 0.2f);
			wall_block->xPos(new_xPos + (wall_block->width() * 1.5f));
		}
		else if (i == 38 || i == 66 || i == 93 || i == 115 || i == 131)
		{
			new_xPos = background.x + (background.length * 0.2f);
			wall_block->xPos(new_xPos + (wall_block->width() * 2.5f));
		}
		else if (i == 39 || i == 67 || i == 94 || i == 116 || i == 132)
		{
			new_xPos = background.x + (background.length * 0.4f);
			wall_block->xPos(new_xPos - (wall_block->width() * 3.5f));
		}
		else if (i == 17 || i == 40 || i == 68 || i == 95 || i == 117 || i == 133)
		{
			new_xPos = background.x + (background.length * 0.4f);
			wall_block->xPos(new_xPos - (wall_block->width() * 2.5f));
		}
		else if (i == 3 || i == 18 || i == 41 || i == 69 || i == 96)
		{
			new_xPos = background.x + (background.length * 0.4f);
			wall_block->xPos(new_xPos - (wall_block->width() * 1.5f));
		}
		else if (i == 4 || i == 19 || i == 42 || i == 70)
		{
			wall_block->xPos(new_xPos - (wall_block->width() * 0.5f));
		}
		else if (i == 5 || i == 20 || i == 43 || i == 71 || i == 97)
		{
			wall_block->xPos(new_xPos + (wall_block->width() * 0.5f));
		}
		else if (i == 21 || i == 44 || i == 72 || i == 98 || i == 118 || i == 134)
		{
			new_xPos = background.x + (background.length * 0.4f);
			wall_block->xPos(new_xPos + (wall_block->width() * 1.5f));
		}
		else if (i == 45 || i == 73 || i == 99 || i == 119 || i == 135)
		{
			new_xPos = background.x + (background.length * 0.4f);
			wall_block->xPos(new_xPos + (wall_block->width() * 2.5f));
		}
		else if (i == 46 || i == 74 || i == 100 || i == 120 || i == 136)
		{
			new_xPos = background.x + (background.length * 0.6f);
			wall_block->xPos(new_xPos - (wall_block->width() * 3.5f));
		}
		else if (i == 22 || i == 47 || i == 75 || i == 101 || i == 121 || i == 137)
		{
			new_xPos = background.x + (background.length * 0.6f);
			wall_block->xPos(new_xPos - (wall_block->width() * 2.5f));
		}
		else if (i == 6 || i == 23 || i == 48 || i == 76 || i == 102)
		{
			new_xPos = background.x + (background.length * 0.6f);
			wall_block->xPos(new_xPos - (wall_block->width() * 1.5f));
		}
		else if (i == 7 || i == 24 || i == 49 || i == 77)
		{
			wall_block->xPos(new_xPos - (wall_block->width() * 0.5f));
		}
		else if (i == 8 || i == 25 || i == 50 || i == 78 || i == 103)
		{
			wall_block->xPos(new_xPos + (wall_block->width() * 0.5f));
		}
		else if (i == 26 || i == 51 || i == 79 || i == 104 || i == 122 || i == 138)
		{
			new_xPos = background.x + (background.length * 0.6);
			wall_block->xPos(new_xPos + (wall_block->width() * 1.5f));
		}
		else if (i == 52 || i == 80 || i == 105 || i == 123 || i == 139)
		{
			new_xPos = background.x + (background.length * 0.6);
			wall_block->xPos(new_xPos + (wall_block->width() * 2.5f));
		}
		else if (i == 53 || i == 81 || i == 106 || i == 124 || i == 140)
		{
			new_xPos = background.x + (background.length * 0.8f);
			wall_block->xPos(new_xPos - (wall_block->width() * 3.5f));
		}
		else if (i == 27 || i == 54 || i == 82 || i == 107 || i == 125 || i == 141)
		{
			new_xPos = background.x + (background.length * 0.8f);
			wall_block->xPos(new_xPos - (wall_block->width() * 2.5f));
		}
		else if (i == 9 || i == 28 || i == 55 || i == 83 || i == 108)
		{
			new_xPos = background.x + (background.length * 0.8f);
			wall_block->xPos(new_xPos - (wall_block->width() * 1.5f));
		}
		else if (i == 10 || i == 29 || i == 56 || i == 84)
		{
			wall_block->xPos(new_xPos - (wall_block->width() * 0.5f));
		}
		else if (i == 11 || i == 30 || i == 57 || i == 85 || i == 109)
		{
			wall_block->xPos(new_xPos + (wall_block->width() * 0.5f));
		}
		else if (i == 31 || i == 58 || i == 86 || i == 110 || i == 126 || i == 142)
		{
			new_xPos = background.x + (background.length * 0.8);
			wall_block->xPos(new_xPos + (wall_block->width() * 1.5f));
		}
		else if (i == 59 || i == 87 || i == 111 || i == 127 || i == 143)
		{
			new_xPos = background.x + (background.length * 0.8);
			wall_block->xPos(new_xPos + (wall_block->width() * 2.5f));
		}



		if (i < 12)
		{
			wall_block->yPos(new_yPos);
		}
		else if (i < 32)
		{
			wall_block->yPos(new_yPos + wall_block->height());
		}
		else if (i < 60)
		{
			wall_block->yPos(new_yPos + (wall_block->height() * 2.f));
		}
		else if (i < 88)
		{
			wall_block->yPos(new_yPos + (wall_block->height() * 3.f));
		}
		else if (i < 112)
		{
			wall_block->yPos(new_yPos + (wall_block->height() * 4.f));
		}
		else if (i < 128)
		{
			wall_block->yPos(new_yPos + (wall_block->height() * 5.f));
		}
		else if (i < MAX_WALL_BLOCKS)
		{
			wall_block->yPos(new_yPos + (wall_block->height() * 6.f));
		}
	}

	return true;
}

/**
*   @brief   Sets the game window resolution
*   @details This function is designed to create the window size, any
aspect ratio scaling factors and safe zones to ensure the
game frames when resolutions are changed in size.
*   @return  void
*/
void SpaceInvaders::setupResolution()
{
	// how will you calculate the game's resolution?
	// will it scale correctly in full screen? what AR will you use?
	// how will the game be framed in native 16:9 resolutions?
	// here are some abritrary values for you to adjust as you see fit
	// https://www.gamasutra.com/blogs/KenanBolukbasi/20171002/306822/Scaling_and_MultiResolution_in_2D_Games.php
	game_height = GetSystemMetrics(SM_CYSCREEN);
	game_width = GetSystemMetrics(SM_CXSCREEN);


}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
keyboard input. For this game, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::keyHandler(const ASGE::SharedEventData data)
{
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}

	if (key->key == ASGE::KEYS::KEY_SPACE &&
		key->action == ASGE::KEYS::KEY_PRESSED
		&& game_state == 1 && laser_shots < MAX_LASERS - 1)
	{
		for (int i = 0; i < MAX_LASERS; i++)
		{
			if (lasers[i].getVisible() == false)
			{
				shootLaser(i);
				return;
			}
		}
	}

	if (key->key == ASGE::KEYS::KEY_UP &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (game_state == 0)
		{
			menu_option--;
			if (menu_option < 0 && game_state == 0)
			{
				menu_option = 2;
			}
		}
		else if (game_state == 4)
		{
			new_initial += 1;
			if (new_initial > 'Z')
			{
				new_initial = 'A';
			}
			new_initials[initial] = new_initial;
		}
	}
	if (key->key == ASGE::KEYS::KEY_DOWN &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (game_state == 0)
		{
			menu_option++;
			if (menu_option > 2)
			{
				menu_option = 0;
			}
		}
		else if (game_state == 4)
		{
			new_initial -= 1;
			if (new_initial < 'A')
			{
				new_initial = 'Z';
			}
			new_initials[initial] = new_initial;
		}
	}

	if (key->key == ASGE::KEYS::KEY_ENTER &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{   //Main menu
		if (game_state == 0)
		{
			if (menu_option == 0)
			{

				game_state = 1;
				new_game = true;
			}
			if (menu_option == 1)
			{
				game_state = 5;
			}
			if (menu_option == 2)
			{
				signalExit();
			}
		}
		else if (game_state == 2 || game_state == 3 || game_state == 5)
		{
			if (updateHighScores() == true)
			{
				game_state = 4;
			}
			else
			{
				game_state = 0;
			}
		}
		else if (game_state == 4)
		{
			high_scores[high_score_idx_to_update].initials = new_initials;
			saveHighScores();

			// reset menu variables
			initial = 0;
			new_initial = 'A';
			new_initials = "AAA";
			high_score_idx_to_update = 0;
			game_state = 0;
		}

	}
	if (key->key == ASGE::KEYS::KEY_A &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Main menu
		if (game_state == 1)
		{

			ship.setVelocity(0.0f, 0.0f);
		}
	}

	if (key->key == ASGE::KEYS::KEY_S &&
		key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Main menu
		if (game_state == 1)
		{
			ship.setVelocity(0.0f, 0.0f);
		}
	}

	if (key->key == ASGE::KEYS::KEY_S &&
		(key->action == ASGE::KEYS::KEY_PRESSED ||
			key->action == ASGE::KEYS::KEY_REPEATED))
	{
		if (game_state == 1)
		{
			ship.setVelocity(1.0f, 0.0f);
		}
	}

	if (key->key == ASGE::KEYS::KEY_A &&
		(key->action == ASGE::KEYS::KEY_PRESSED ||
			key->action == ASGE::KEYS::KEY_REPEATED))
	{
		if (game_state == 1)
		{
			ship.setVelocity(-1.0f, 0.0f);
		}
	}
	if (key->key == ASGE::KEYS::KEY_LEFT &&
		key->action == ASGE::KEYS::KEY_PRESSED && game_state == 4)
	{
		initial -= 1;
		if (initial < 0)
		{
			initial = 2;
		}
		new_initial = new_initials[initial];
	}
	if (key->key == ASGE::KEYS::KEY_RIGHT &&
		key->action == ASGE::KEYS::KEY_PRESSED && game_state == 4)
	{
		initial += 1;
		if (initial > 2)
		{
			initial = 0;
		}
		new_initial = new_initials[initial];
	}
}

/**
*   @brief   Processes any click inputs
*   @details This function is added as a callback to handle the game's
mouse button input. For this game, calls to this function
are thread safe, so you may alter the game's state as you
see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void SpaceInvaders::clickHandler(const ASGE::SharedEventData data)
{
	auto click = static_cast<const ASGE::ClickEvent*>(data.get());

	double x_pos, y_pos;
	inputs->getCursorPos(x_pos, y_pos);
}

/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
current frame. Once the current frame is has finished
the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void SpaceInvaders::update(const ASGE::GameTime& us)
{
	if (game_state == 1)
	{
		if (new_game)
		{
			newGame();
		}
		auto dt_sec = us.delta_time.count() / 1000.0;
		vector2 ship_velocity = ship.getVelocity();

		rect background = gameplay_area.spriteComponent()->getBoundingBox();
		ASGE::Sprite* ship_sprite = ship.spriteComponent()->getSprite();
		//make sure you use delta time in any movement calculations!
		if ((ship_sprite->xPos() <= background.x &&
			ship_velocity.getX() == -1.f) || ((ship_sprite->xPos() +
				ship_sprite->width()) >= (background.x +
					background.length) && ship_velocity.getX() == 1.f))
		{
			ship_velocity.setX(0.f);
		}
		alienCollision();
		shipCollision();
		wallCollision();

		ship_sprite->xPos((float)(ship_sprite->xPos() +
			(ship_velocity.getX()  * (game_height * 0.45f)) *
			(us.delta_time.count() / 1000.f)));

		for (int i = 0; i < MAX_ALIEN_LASERS; i++)
		{
			ASGE::Sprite* alien_laser = alien_lasers[i].spriteComponent()->getSprite();
			vector2 alien_laser_velocity = alien_lasers[i].getVelocity();
			alien_laser->yPos((float)(alien_laser->yPos() +
				(alien_laser_velocity.getY()  * (game_height * 0.45f)) *
				(us.delta_time.count() / 1000.f)));
		}

		for (int i = 0; i < MAX_LASERS; i++)
		{
			ASGE::Sprite* laser = lasers[i].spriteComponent()->getSprite();
			vector2 laser_velocity = lasers[i].getVelocity();
			laser->yPos((float)(laser->yPos() +
				(laser_velocity.getY()  * (game_height * 0.35f)) *
				(us.delta_time.count() / 1000.f)));
		}



		aliens_velocity.setY(.2f *(aliens_velocity.getY() * aliens_velocity.getY()) *
			(us.delta_time.count() / 1000.f));

		
		
		for (int i = 0; i < MAX_ALIENS; i++)
		{
			ASGE::Sprite* alien = aliens[i].spriteComponent()->getSprite();

			alien->xPos((float)(alien->xPos() +
				(aliens_velocity.getX()  * (game_width * 0.1f)) *
				(us.delta_time.count() / 1000.f)));
			alien->yPos((float)(alien->yPos() +
				(aliens_velocity.getY()  * (game_height * 0.1f)) *
				(us.delta_time.count() / 1000.f)));
		}
	}
}

/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
Once the current frame is has finished the buffers are
swapped accordingly and the image shown.
*   @return  void
*/
void SpaceInvaders::render(const ASGE::GameTime &)
{
	renderer->setFont(0);

	if (game_state == 0)
	{
		renderMainMenu();
	}
	else if (game_state == 1)
	{
		renderInGame();
	}
	else if (game_state == 2)
	{
		renderGameOverL();
	}

	else if (game_state == 3)
	{
		renderGameOverW();
	}
	else if (game_state == 4)
	{
		renderNewHighScore();
	}
	else if (game_state == 5)
	{
		renderHighScores();
	}

}

/**
*   @brief   Main menu
*   @details This function is used todisplay the main menu
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::renderMainMenu()
{

	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::MIDNIGHTBLUE);
	// renders the main menu text
	renderer->renderText(
		"WELCOME TO SPACE INVADERS \n Press Esc to quit at any time.", game_width * 0.2f,
		game_height * 0.15f, game_height * 0.002f, ASGE::COLOURS::DARKORANGE);

	renderer->renderText(menu_option == 0 ? ">PLAY" : "PLAY", game_width * 0.2f,
		game_height * 0.3f, game_height * 0.002f, ASGE::COLOURS::WHITESMOKE);

	renderer->renderText(menu_option == 1 ? ">HIGH SCORES" : "HIGH SCORES", game_width * 0.2f,
		game_height * 0.4f, game_height * 0.002f, ASGE::COLOURS::WHITESMOKE);

	renderer->renderText(menu_option == 2 ? ">QUIT" : "QUIT", game_width * 0.2f,
		game_height * 0.5f, game_height * 0.002f, ASGE::COLOURS::WHITESMOKE);




}

/**
*   @brief   In Game Screen
*   @details This function is used todisplay the main menu
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::renderInGame()
{
	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::MIDNIGHTBLUE);
	renderer->renderSprite(*gameplay_area.spriteComponent()->getSprite());
	renderer->renderSprite(*ship.spriteComponent()->getSprite());
	renderer->renderSprite(*heart.spriteComponent()->getSprite());

	renderer->renderText("Score: ",
		(game_width * 0.60f), (game_height * 0.088f),
		game_height * 0.002f, ASGE::COLOURS::DARKORANGE);
	std::string score_string = std::to_string(score);
	renderer->renderText(score_string.c_str(),
		(game_width * 0.73f), (game_height * 0.088f),
		game_height * 0.002f, ASGE::COLOURS::DARKORANGE);

	std::string life_string = std::to_string(lives - 1);
	rect heart_sprite = heart.spriteComponent()->getBoundingBox();
	renderer->renderText(life_string.c_str(),
		(heart_sprite.x + (heart_sprite.length * 1.02f)),
		(heart_sprite.y + (heart_sprite.height * 0.95f)),
		game_height * 0.0025f, ASGE::COLOURS::DARKORANGE);

	for (int i = 0; i < MAX_ALIEN_LASERS; i++)
	{
		if (alien_lasers[i].getVisible() == true)
		{
			renderer->renderSprite(*alien_lasers[i].spriteComponent()->getSprite());
		}

	}
	for (int i = 0; i < MAX_LASERS; i++)
	{
		if (lasers[i].getVisible() == true)
		{
			renderer->renderSprite(*lasers[i].spriteComponent()->getSprite());
		}

	}

	for (int i = 0; i < MAX_ALIENS; i++)
	{
		if (aliens[i].getVisible() == true)
		{
			renderer->renderSprite(*aliens[i].spriteComponent()->getSprite());
		}

	}
	for (int i = 0; i < MAX_WALL_BLOCKS; i++)
	{
		if (wall[i].getVisible() == true)
		{
			renderer->renderSprite(*wall[i].spriteComponent()->getSprite());
		}

	}
}

/**
*   @brief   Game Over loss
*   @details This function is used to display the game over screen
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::renderGameOverL()
{
	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	// renders the main menu text
	renderer->renderText(
		"GAME OVER out of lives \n Press Enter to return to main menu.",
		game_width * 0.25f, game_height * 0.2f, game_height * 0.002f, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("Final Score: ", (game_width * 0.3f), (game_height * 0.5f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);
	std::string score_string = std::to_string(score);
	renderer->renderText(score_string.c_str(),
		(game_width * 0.7f), (game_height * 0.50f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);

}

/**
*   @brief   Game Over Win
*   @details This function is used todisplay the the game over screen
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::renderGameOverW()
{
	// Set Background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	// renders the main menu text
	renderer->renderText(
		"CONGRATULATIONS you cleared the game \n Press Enter to return to main menu.", game_width * 0.25f,
		game_height * 0.2f, game_height * 0.002f, ASGE::COLOURS::DARKORANGE);
	renderer->renderText("Final Score: ", (game_width * 0.3f), (game_height * 0.5f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);
	std::string score_string = std::to_string(score);
	renderer->renderText(score_string.c_str(),
		(game_width * 0.7f), (game_height * 0.50f),
		game_height * 0.004f, ASGE::COLOURS::WHITESMOKE);
}

/**
*   @brief   Update high scores
*   @details This function is used to check and update if single player high
score is higher than the current top ten
*   @see     KeyEvent
*   @return  bool
*/
bool SpaceInvaders::updateHighScores()
{
	bool update_score = false;
	high_score_idx_to_update = 0;
	for (int i = 9; i > -1; i--)
	{
		if (score > high_scores[i].score)
		{
			high_score_idx_to_update = i;
			update_score = true;
		}
	}
	if (update_score)
	{
		for (int i = 9; i > high_score_idx_to_update; i--)
		{
			high_scores[i].score = high_scores[i - 1].score;
			high_scores[i].initials = high_scores[i - 1].initials;
		}
		high_scores[high_score_idx_to_update].score = score;

	}
	score = 0;
	return update_score;
}

/**
*   @brief   High scores
*   @details This function is used to display the high scores
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::renderHighScores()
{
	// re renders the main menu
	renderMainMenu();


	renderer->renderText("HIGH SCORES", game_width * 0.68f, game_height * 0.15f, game_height * 0.002f,
		ASGE::COLOURS::DARKORANGE);
	// renders the high scores
	int j = 0;
	for (int i = game_height * 0.25f; i < game_height * 0.75f; i = i + game_height * 0.05f)
	{
		renderer->renderText(high_scores[j].initials.c_str(), game_width * 0.7f, i, game_height * 0.002f,
			ASGE::COLOURS::GHOSTWHITE);
		// creates a string with the score appended
		std::string score_str_1 = std::to_string(high_scores[j].score);
		renderer->renderText(score_str_1.c_str(), game_width * 0.75f, i, game_height * 0.002f,
			ASGE::COLOURS::GHOSTWHITE);
		j++;
	}
	renderer->renderText("Press Enter to return to Main Menu", game_width * 0.5f, game_height * 0.8f,
		game_height * 0.002f, ASGE::COLOURS::GHOSTWHITE);
}

/**
*   @brief   New High score
*   @details This function is used to display the high score and update the
players initials
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::renderNewHighScore()
{

	renderer->renderText("CONGRATULATIONS YOU SCORED A NEW HIGH SCORE",
		game_width * 0.1f, game_height * 0.15f, game_height * 0.003f, ASGE::COLOURS::DARKORANGE);
	int j = 0;
	for (int i = game_height * 0.25f; i < game_height * 0.75f; i = i + game_height * 0.05f)
	{
		renderer->renderText(high_score_idx_to_update == j ?
			new_initials.c_str() : high_scores[j].initials.c_str(),
			game_width * 0.45f, i, game_height * 0.002f, high_score_idx_to_update == j ?
			ASGE::COLOURS::GHOSTWHITE : ASGE::COLOURS::DARKORANGE);
		std::string score_str_1 = std::to_string(high_scores[j].score);
		renderer->renderText(score_str_1.c_str(), game_width * 0.5f, i, game_height * 0.002f,
			high_score_idx_to_update == j ?
			ASGE::COLOURS::GHOSTWHITE : ASGE::COLOURS::DARKORANGE);
		j++;
	}



	renderer->renderText(
		"Use arrow keys to change initials and press Enter when finished", game_width * 0.1f, game_height * 0.8f,
		game_height * 0.002f, ASGE::COLOURS::GHOSTWHITE);
}

/**
*   @brief   New Game
*   @details This function is used to reset a new game
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::newGame()
{
	setupNewGame();
	
	// re-initialise game variables
	score = 0;
	game_speed = 1.f;
	no_alien_lasers_visible = 0;
	no_hit = 0;
	shots_fired = 0;
	lives = 4;
	ship.setVelocity(0.f, 0.f);
	laser_shots = 0;
	new_game = false;
}

/**
*   @brief   setup New Game 
*   @details This function is used to reset the alien's and the ships position and serve the ball
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::setupNewGame()
{
	// set ball position to center of paddle and velocity to straight up
	rect background_sprite = gameplay_area.spriteComponent()->getBoundingBox();
	float new_yPos = game_height * .09f + ((game_height * 0.8f) * .06f);
	float new_xPos = ((game_width - ((game_height * GAMEPLAY_HEIGHT) * 1.25f)) * 0.506f);

	// re-initialise blocks
	for (int i = 0; i < MAX_ALIENS; i++)
	{
		aliens[i].setVisible(true);
		ASGE::Sprite* alien = aliens[i].spriteComponent()->getSprite();
		alien->yPos(new_yPos);
		alien->xPos(new_xPos);
		new_xPos = alien->xPos() + (alien->width() * 1.2f);
		if (i % 11 == 10)
		{
			new_yPos += (alien->height() * 1.2f);
			new_xPos = ((game_width - ((game_height * GAMEPLAY_HEIGHT) * 1.25f)) * 0.506f);
		}
	}
	// re-initialise gems
	for (int i = 0; i <MAX_ALIEN_LASERS; i++)
	{
		resetAlienLaser(i);
	}
	// re-initialise lasers
	for (int i = 0; i <MAX_LASERS; i++)
	{
		resetLaser(i);
	}
	resetShip();
	resetWall();
	rect target = aliens[0].spriteComponent()->getBoundingBox();
	target_dest = target.y + target.height;
	aliens_velocity.setX(1.f);
	//aliens_velocity.setY(0.f);
	//curved graph
	aliens_velocity.setY(1.f);

}

/**
*   @brief   Collision detection Aliens
*   @details This function is used to detect collisions with the aliens
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::alienCollision()
{
	rect background = gameplay_area.spriteComponent()->getBoundingBox();

	

	// edge detection for lasers
	for (int i = 0; i < MAX_LASERS; i++)
	{
		rect laser_rect = lasers[i].spriteComponent()->getBoundingBox();
		if (laser_rect.y <= background.y)
		{
			resetLaser(i);
		}

	}

	// alien collision detection with lasers
	for (int i = 0; i < MAX_ALIENS; i++)
	{
		

	




		rect alien = aliens[i].spriteComponent()->getBoundingBox();



		// alien edge collision
		if (going_right)
		{
			aliens_velocity.setX(1.f);
		}
		else
		{
			aliens_velocity.setX(-1.f);
		}
		aliens_velocity.setY(1.f);
		if (aliens[i].getVisible())
		{
			// original
			/*if ((alien.x <= (background.x + 0.1f) &&
				aliens_velocity.getX() < 0.f) ||
				(alien.x + alien.length >= (background.x + background.length - 0.1f) &&
					aliens_velocity.getX() > 0.f))
			{
				target_dest = alien.y + alien.height;
				aliens_velocity.setX(0.f);
				aliens_velocity.setY(1.f);
				going_right = 1 - going_right;
			}*/
			// curves, gravity
			if ((alien.x <= (background.x + 0.1f) &&
				aliens_velocity.getX() < 0.f) ||
				(alien.x + alien.length >= (background.x + background.length - 0.1f) &&
					aliens_velocity.getX() > 0.f))
			{
				going_right = 1 - going_right;
			}
			if ((alien.y + alien.height) > (background.y + background.height) &&
				aliens_velocity.getY() > 0.f)
			{ 
				lives = 0;
			}
			for (int j = 0; j < MAX_LASERS; j++)
			{

				// laser collision check
				rect laser_rect = lasers[j].spriteComponent()->getBoundingBox();
				if ((laser_rect.y < alien.y + alien.height) && 
					laser_rect.y > alien.y &&(laser_rect.x > alien.x -
					(laser_rect.length * .5f) && laser_rect.x +
					laser_rect.length  < alien.x + alien.length +
					(laser_rect.length * .5f)) && lasers[j].getVisible())
				{
					resetLaser(j);
					releaseAlienLaser(alien);
					aliens[i].setVisible(false);
					no_hit++;
					score += 50;
				}
			}

		}
		// game over check (win)
		if (no_hit == MAX_ALIENS)
		{
			for (int i = 0; i < MAX_WALL_BLOCKS; i++)
			{
				if (wall[i].getVisible() == true)
				{
					score += 5;
				}
			}
			score = ((score + (lives * 500)) - (shots_fired));
			game_state = 3;
		}
	}

	// game over check (loss)
	if (lives == 0)
	{
		game_state = 2;
	}
}

/**
*   @brief   Collision detection ship
*   @details This function is used to detect collisions with the ship
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::shipCollision()
{
	rect ship_sprite = ship.spriteComponent()->getBoundingBox();
	// check for alien laser collision with paddle or bottom of gameplay area
	for (int i = 0; i < MAX_ALIEN_LASERS; i++)
	{
		if (alien_lasers[i].getVisible() == true);
		{
			rect alien_laser = alien_lasers[i].spriteComponent()->getBoundingBox();
			if (alien_laser.y + alien_laser.height > ship_sprite.y)
			{
				if (alien_laser.x > ship_sprite.x && alien_laser.x + alien_laser.length
					< ship_sprite.x + ship_sprite.length)
				{
					lives--;
					resetShip();
					resetAlienLaser(i);

				}
				else if (alien_laser.y > ship_sprite.y)
				{
					resetAlienLaser(i);
				}
			}

		}
	}
	// game over check (loss)
	if (lives == 0)
	{
		game_state = 2;
	}
}

/**
*   @brief   Collision detection wall
*   @details This function is used to detect collisions with the wall
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::wallCollision()
{
	// check for alien laser collision with paddle or bottom of gameplay area
	for (int i = 0; i < MAX_WALL_BLOCKS; i++)
	{
		if (wall[i].getVisible() == true);
		{
			rect wall_block = wall[i].spriteComponent()->getBoundingBox();
			for (int j = 0; j < MAX_LASERS; j++)
			{

				// laser collision check
				rect laser_rect = lasers[j].spriteComponent()->getBoundingBox();
				if (laser_rect.isInside(wall_block)  && lasers[j].getVisible() && wall[i].getVisible())
				{
					resetLaser(j);
					wall[i].setVisible(false);
				}
			}
			for (int j = 0; j < MAX_ALIEN_LASERS; j++)
			{

				// laser collision check
				rect laser_rect = alien_lasers[j].spriteComponent()->getBoundingBox();
				if (laser_rect.isInside(wall_block) && lasers[j].getVisible() && wall[i].getVisible())
				{
					resetAlienLaser(j);
					wall[i].setVisible(false);
				}
			}

			for (int j = 0; j < MAX_ALIENS; j++)
			{

				// alien collision check
				rect alien = aliens[j].spriteComponent()->getBoundingBox();
				if (wall_block.isInside(alien) && aliens[j].getVisible() && wall[i].getVisible())
				{
					wall[i].setVisible(false);
				}
			}
		}
	}
}

/**
*   @brief   Release Alien Laser
*   @details This function is used to release an alien laser from the
provided alien co-ordinates.
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::releaseAlienLaser(rect alien)
{
	// for every fifth block hit release a gem from the corresponding block
	if (no_hit % 5 == 4)
	{
		ASGE::Sprite* alien_laser = alien_lasers[no_alien_lasers_visible].spriteComponent()->getSprite();
		alien_laser->yPos(alien .y);
		alien_laser->xPos(alien.x + ((alien.length * 0.5f) - (alien_laser->width() * 0.5f)));
		alien_lasers[no_alien_lasers_visible].setVelocity(0.f, 0.5f);
		alien_lasers[no_alien_lasers_visible].setVisible(true);
		no_alien_lasers_visible++;
	}
	if (no_hit % 25 == 24)
	{
		game_speed += 0.1f;
	}
}


/**
*   @brief   Reset Alien Laser
*   @details This function is used to reset a gem's
position and velocity
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::resetAlienLaser(int index)
{
	// reset sprite position, velocity and visibility
	ASGE::Sprite* alien_laser = alien_lasers[index].spriteComponent()->getSprite();
	alien_laser->yPos(0.f);
	alien_laser->xPos(0.f);
	alien_lasers[index].setVisible(false);
	alien_lasers[index].setVelocity(0.f, 0.f);
	no_alien_lasers_visible--;
}

/**
*   @brief   Reset Wall
*   @details This function is used to reset the wall's
position and visibility
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::resetWall()
{
	// reset sprite  and visibility
	for (int i = 0; i < MAX_WALL_BLOCKS; i++)
	{
		wall[i].setVisible(true);
	}
}


/**
*   @brief   Reset Ship
*   @details This function is used to reset the ship's
position and velocity
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::resetShip()
{
	rect background = gameplay_area.spriteComponent()->getBoundingBox();
	ASGE::Sprite* ship_sprite = ship.spriteComponent()->getSprite();
	ship_sprite->yPos(background.y + background.height
		- ship_sprite->height());
	ship_sprite->xPos(background.x + (background.length
		* 0.5f) - (ship_sprite->width() * 0.5f));
	ship.setVelocity(0.f, 0.f);

}

/**
*   @brief   Shoot laser
*   @details This function is used to shoot a laser
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::shootLaser(int index)
{
	// set sprite position for corresponding index to the center of the paddle,
	// set to visible and set velocity to straight up
	no_lasers_visible++;
	rect background_rect = gameplay_area.spriteComponent()->getBoundingBox();
	rect paddle_rect = ship.spriteComponent()->getBoundingBox();
	ASGE::Sprite* laser_sprite = lasers[index].spriteComponent()->getSprite();
	laser_sprite->yPos(background_rect.y + background_rect.height
		- paddle_rect.height);
	laser_sprite->xPos((paddle_rect.x + paddle_rect.length * 0.5f) - (laser_sprite->width() * 0.5f));
	lasers[index].setVelocity(0.0f, -1.0f);
	lasers[index].setVisible(true);
	laser_shots++;
	shots_fired++;
}

/**
*   @brief   Reset laser
*   @details This function is used to reset a laser's
position and velocity
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::resetLaser(int index)
{
	// reset sprite position, velocity and visibility
	ASGE::Sprite* laser_sprite = lasers[index].spriteComponent()->getSprite();
	laser_sprite->yPos(0.f);
	laser_sprite->xPos(0.f);
	lasers[index].setVisible(false);
	lasers[index].setVelocity(0.f, 0.f);
	laser_shots--;
}

/**
*   @brief   Load files
*   @details This function is used to load the high scores
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::loadFiles()
{
	// load high scores
	std::ifstream inFile_one;
	inFile_one.open("High_scores.txt");
	if (!inFile_one.fail())
	{
		for (int i = 0; i < NUM_HIGH_SCORES; i++)
		{
			std::string score;
			getline(inFile_one, high_scores[i].initials);
			getline(inFile_one, score);
			high_scores[i].score = atoi(score.c_str());
		}
		inFile_one.close();
	}
}

/**
*   @brief   Save files
*   @details This function is load the high scores and characters files
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::saveHighScores()
{
	// save high scores array to file
	std::ofstream outFile;
	outFile.open("High_scores.txt");
	if (!outFile.fail())
	{
		for (int i = 0; i < NUM_HIGH_SCORES; i++)
		{
			outFile << high_scores[i].initials << std::endl;
			outFile << high_scores[i].score << std::endl;
		}
		outFile.close();
	}

}

/**
*   @brief   clear arrays
*   @details This function is used to initialise arrays.
*   @see     KeyEvent
*   @return  void
*/
void SpaceInvaders::clearArrays()
{
	for (int i = 0; i < NUM_HIGH_SCORES; i++)
	{
		high_scores[i].initials = "AAA";
		high_scores[i].score = 0;
	}
}