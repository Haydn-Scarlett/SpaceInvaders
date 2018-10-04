#pragma once
#include <string>
#include <Engine/OGLGame.h>
#include <fstream>
#include <iostream>

#include "Constants.h"
#include "GameObject.h"
#include "Rect.h"



struct Score
{
	long score = 0;
	std::string initials;
};

/**
*  An OpenGL Game based on ASGE.
*/
class SpaceInvaders :
	public ASGE::OGLGame
{
public:
	SpaceInvaders();
	~SpaceInvaders();
	virtual bool init() override;

private:
	void keyHandler(const ASGE::SharedEventData data);
	void clickHandler(const ASGE::SharedEventData data);
	void setupResolution();
	void renderMainMenu();
	void renderInGame();
	void renderGameOverL();
	void renderGameOverW();
	void renderHighScores();
	void renderNewHighScore();
	void setupNewGame();
	void newGame();
	void alienCollision();
	void shipCollision();
	void wallCollision();
	void releaseAlienLaser(rect Alien);
	void resetAlienLaser(int index);
	void resetWall();
	void resetShip();
	void shootLaser(int index);
	void resetLaser(int index);
	bool updateHighScores();

	void clearArrays();
	void saveHighScores();
	void loadFiles();


	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */
	int  mouse_callback_id = -1;        /**< Mouse Input Callback ID. */

										//Add your GameObjects
	GameObject aliens[MAX_ALIENS];
	GameObject wall[MAX_WALL_BLOCKS];
	GameObject alien_lasers[MAX_ALIEN_LASERS];
	GameObject gameplay_area;
	GameObject ship;
	GameObject heart;
	GameObject lasers[MAX_LASERS];

	// menu variables
	int menu_option = 0;
	int initial = 0;

	// game screen to display
	int game_state = 0;

	// in game variables
	bool new_game = true;
	int lives = 0;
	int score = 0;
	int no_hit = 0;
	int no_alien_lasers_visible = 0;
	int no_lasers_visible = 0;
	int laser_shots = 0;
	int shots_fired = 0;
	float game_speed = 1.f;
	vector2 aliens_velocity;
	float target_dest = 0.f;
	bool going_right = true;
	bool going_up = false;

	float square_x = 0.f;

	// high score variables
	Score high_scores[NUM_HIGH_SCORES];
	char new_initial = 'A';
	std::string new_initials = "AAA";
	int high_score_idx_to_update = 0;
};