#include "level.h"
#include <sgg/graphics.h>
#include "player.h"
#include "util.h"
#include "gamestate.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "enemy.h"
#include "Coins.h"
#include "Hearts.h"
#include "gate.h"
#include <chrono>
#include <ctime>
#include "timer.cpp"
#include "timer.h"
//Αρχικοποιουμε καποιες μεταβλητες  Timepoinτ που θα χρησιμευσουν για την effect() και για τις συγκρουσεις παικτη-enemy
using TimePoint = std::chrono::steady_clock::time_point;
TimePoint lastCollisionTime;
TimePoint lastEffectTime;
TimePoint effectStartTime;
const std::chrono::milliseconds effectDuration(80);

//Σχεδιαζουμε τα block της πιστας
void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	/*std::string& name = m_block_names[i];*/

	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;

	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);

	graphics::drawRect(x, y, 1.0f * m_block_size, 1.0f * m_block_size, m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
}

//Ελεγχος collision αναμεσα σε παικτη και καθε block της πιστας: intersectUp intersectDown intersectSideways
void Level::checkColissions()
{
	

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		 
			if (offset = m_state->getPlayer()->intersectUp(block))
			{
				if (m_state->getPlayer()->m_vy != 0.0f) {
					m_state->getPlayer()->m_pos_y += offset;

					

					break;
				}
			}

			

			
		

	}
	

	for (auto& block : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(block))
		{
			
			m_state->getPlayer()->m_pos_y += offset;

			// ηχος των block για μεγαλα αλματα
			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("brick.wav"), 0.4f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
		
	}

	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			
			break;
		}
	}
	
	
	


}





//Αρχικοποιουμε τα blocks της πιστας τα στατικα και δυναμικα αντικέιμενα,την θεση των εχθρων των coins των hearts και της gate και για καθε ενα καλουμε και την αντιστοιχη init της κλασης τους
void Level::init()
{
	
		m_brush_background.outline_opacity = 0.0f;
		m_brush_background.texture = m_state->getFullAssetPath("forestt11.png");





		for (auto p_gob : m_static_objects)
			if (p_gob) p_gob->init();

		for (auto p_gob : m_dynamic_objects)
			if (p_gob) p_gob->init();




		std::ifstream levelFile(m_state->getFullAssetPath("level1.txt"));
		if (!levelFile) {
			std::cerr << "Unable to open level file!" << std::endl;
			return;
		}

		std::string line;
		int y = 0; 
		while (std::getline(levelFile, line)) {
			for (int x = 0; x < line.length(); ++x) {
				if (line[x] == '1') {  //Το 1 αντιπροσωπευει θεση block
					m_blocks.push_back(Box(x * m_block_size, y * m_block_size, m_block_size, m_block_size));
					m_block_names.push_back("ground.png");
				}
			}
			++y;
		}





		m_enemies.push_back(new Enemy(18.0f, 3.0f));
		m_enemies.push_back(new Enemy(41.0f, 3.0f));
		m_enemies.push_back(new Enemy(23.0f, 5.0f));
		m_enemies.push_back(new Enemy(11.0f, 5.0f));
		m_enemies.push_back(new Enemy(15.0f, 7.0f));
		m_enemies.push_back(new Enemy(35.0f, 7.0f));
		m_enemies.push_back(new Enemy(22.0f, 8.0f));
		m_enemies.push_back(new Enemy(29.0f, 9.0f));
		m_enemies.push_back(new Enemy(41.0f, 11.0f));
		m_enemies.push_back(new Enemy(13.0f, 11.0f));
		m_enemies.push_back(new Enemy(20.0f, 13.0f));
		m_enemies.push_back(new Enemy(30.0f, 13.0f));
		m_enemies.push_back(new Enemy(10.0f, 19.0f));
		m_enemies.push_back(new Enemy(36.0f, 15.0f));
		m_enemies.push_back(new Enemy(41.0f, 17.0f));
		m_enemies.push_back(new Enemy(38.0f, 14.0f));
		m_enemies.push_back(new Enemy(7.0f, 15.0f));


		coins.push_back(new Coins(7.0f, 3.0f));
		coins.push_back(new Coins(14.0f, 7.0f));
		coins.push_back(new Coins(22.0f, 15.0f));
		coins.push_back(new Coins(37.0f, 12.0f));
		coins.push_back(new Coins(5.0f, 15.0f));
		coins.push_back(new Coins(5.0f, 16.0f));
		coins.push_back(new Coins(5.0f, 17.0f));
		coins.push_back(new Coins(5.0f, 18.0f));
		coins.push_back(new Coins(5.0f, 19.0f));
		coins.push_back(new Coins(6.0f, 21.0f));
		coins.push_back(new Coins(7.0f, 21.0f));
		coins.push_back(new Coins(8.0f, 21.0f));
		coins.push_back(new Coins(31.0f, 14.0f));
		coins.push_back(new Coins(40.0f, 5.0f));



		hearts.push_back(new Hearts(14.0f, 11.0f));
		hearts.push_back(new Hearts(5.0f, 7.0f));
		hearts.push_back(new Hearts(26.0f, 9.0f));

		//gate.push_back(new Gate(43.0f, 15.0f));
		gate1 = new Gate(43.0f, 15.0f);



		for (auto coin : coins) {
			if (coin) {

				coin->init();

			}
		}

		for (auto enemy : m_enemies) {
			if (enemy) {

				enemy->init();

			}
		}

		for (auto heart : hearts) {
			if (heart) {

				heart->init();

			}
		}

		
			if (gate1) {

				gate1->init();

			}


		ScoreLevel = 0;

		levelFile.close();


		m_block_brush.outline_opacity = 0.0f;
		m_block_brush_debug.fill_opacity = 0.1f;
		SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
		SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
	

	

}

//Αρχικοποιουμε τα blocks του level2 τα στατικα και δυναμικα αντικέιμενα,την θεση των εχθρων των coins των hearts και της gate και για καθε ενα καλουμε και την αντιστοιχη init της κλασης τους
void Level::init2() {
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getFullAssetPath("Background.png");
	





	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();




	std::ifstream levelFile(m_state->getFullAssetPath("level2.txt"));
	if (!levelFile) {
		std::cerr << "Unable to open level file!" << std::endl;
		return;
	}

	std::string line;
	int y = 0; 
	while (std::getline(levelFile, line)) {
		for (int x = 0; x < line.length(); ++x) {
			if (line[x] == '1') { // Το 1 αντιπροσωπευει ενα block
				m_blocks.push_back(Box(x * m_block_size, y * m_block_size, m_block_size, m_block_size));
				m_block_names.push_back("iceCave.png");
			}
		}
		++y;
	}





	
	m_enemies.push_back(new Enemy(34.0f, 3.0f));
	m_enemies.push_back(new Enemy(30.0f, 4.0f));
	m_enemies.push_back(new Enemy(23.0f, 5.0f));
	m_enemies.push_back(new Enemy(29.0f, 7.0f));
	m_enemies.push_back(new Enemy(41.0f, 7.0f));
	m_enemies.push_back(new Enemy(28.0f, 10.0f));
	m_enemies.push_back(new Enemy(39.0f, 13.0f));
	m_enemies.push_back(new Enemy(11.0f, 14.0f));
	m_enemies.push_back(new Enemy(18.0f, 15.0f));
	m_enemies.push_back(new Enemy(2.0f, 15.0f));
	m_enemies.push_back(new Enemy(21.0f, 16.0f));
	m_enemies.push_back(new Enemy(40.0f, 16.0f));
	m_enemies.push_back(new Enemy(9.0f, 15.0f));

	coins.push_back(new Coins(7.0f, 3.0f));
	coins.push_back(new Coins(14.0f, 7.0f));
	coins.push_back(new Coins(22.0f, 10.0f));
	coins.push_back(new Coins(34.0f, 5.0f));
	coins.push_back(new Coins(9.0f, 10.0f));
	coins.push_back(new Coins(23.0f, 2.0f));
	coins.push_back(new Coins(24.0f, 2.0f));
	coins.push_back(new Coins(25.0f, 2.0f));
	coins.push_back(new Coins(26.0f, 2.0f));
	coins.push_back(new Coins(27.0f, 2.0f));
	coins.push_back(new Coins(28.0f, 2.0f)); 
	coins.push_back(new Coins(29.0f, 2.0f));
	coins.push_back(new Coins(30.0f, 2.0f));
	coins.push_back(new Coins(31.0f, 2.0f));



	hearts.push_back(new Hearts(14.0f, 11.0f));
	
	hearts.push_back(new Hearts(21.0f, 9.0f));

	
	gate1 = new Gate(4.0f, 10.0f);



	for (auto coin : coins) {
		if (coin) {

			coin->init();
			
		}
	}

	for (auto enemy : m_enemies) {
		if (enemy) {

			enemy->init();
			
		}
	}

	for (auto heart : hearts) {
		if (heart) {

			
		}
	}

	if (gate1) {

		gate1->init();
		
	}


	ScoreLevel = 0;

	levelFile.close();


	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.outline_color, 0.3f, 1.0f, 0.2f);
}

//Ζωγραφιζουμε το background,τον παικτη,τους εχθρους,τα coins,τα hearts και την gate και καλουμε για καθε ενα την αντιστοιχη draw της κλασης τους
void Level::draw()
{
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();

	float offset_x = m_state->m_global_offset_x / 2.0f + w / 2.0f;
	float offset_y = m_state->m_global_offset_y / 2.0f + h / 2.0f;
 
	//draw background
	graphics::drawRect(offset_x, offset_y, 3.4f * w, 2.0f * w, m_brush_background);

	


	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();




	//Για καθε block καλεσε την drawblock
	for (int i = 0; i < m_blocks.size(); i++)
	{
		drawBlock(i);
		
	}

	//Για καθε coin καλεσε τη coin->draw()
	for (auto coin : coins) {
		if (coin) {
			coin->draw();
		}
	}
	//Για καθε heart καλεσε τη heart->draw()
	for (auto heart : hearts) {
		if (heart) {
			heart->draw();
		}
	}
	//Για καθε enemy καλεσε τη enemy->draw()
	for (auto enemy : m_enemies) {
		if (enemy) {
			enemy->draw();
		}
	}

	//Καλεσε για την gate1 την draw()
	if (gate1) {
		gate1->draw();
	}
	//}


	
	
}

//Για καθε enemy,block,hearts,coins,gate αν ειναι Active καλουμε την αντιστοιχη update τους και κανουμε update και τον παικτη
void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);
	

	//Αφορα τη μεθοδο effect που θελουμε να διαρκεσει 100 milliseconds-στιγμιαια
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - effectStartTime);


	if (elapsedTime >= effectDuration) {
		SETCOLOR(m_brush_background.fill_color, 1.0f, 1.0f, 1.0f);
	}
	


	for (auto &enemy : m_enemies)
	{
		if (enemy->isActive())
		{
			
			enemy->update(dt);
			
			
		}
		
	}


	for (auto& coin : coins)
	{
		if (coin->isActive())
		{
			
			coin->update(dt);

			
		}
		
	}


	for (auto& heart : hearts)
	{
		if (heart->isActive())
		{
			
			heart->update(dt);

			
		}
		
	}

	
	if (gate1->isActive())
	{
			
		gate1->update(dt);

	}
		
	///Καλουμε καθε συναρτηση μεσα στην update που αφορα collisions 
	checkPlayerGate();
	checkPlayerEnemyCollision();
	checkPlayerCoinsCollision();
	checkPlayerHeartscoll();
	GameObject::update(dt);
	checkColissions();
	
}

//Ελεγχουμε τα collisions αναμεσα σε παικτη και enemies ελέγχοντας αν τα box τους κανουν καποιο intersect
//Αν ο παικτης κανει intersectdown με τον enemy τον σκοτωνει αλλιως αν κανει intersectup η intersectsideways χανει ζωη ο παικτης και ενεργοποιειται το effect()
//Μετραμε το χρονο μετα απο καθε intersect με σκοπο να μη μπορει ο παικτης να χανει ζωη καθολη τη διαρκεια ενος intersect αλλα μονο μια φορα σε καθε intersect,γι αυτο χρησιμοποιουμε τα currentTime και elapsedTime
void Level::checkPlayerEnemyCollision()
{
	
	for (auto& enemy : m_enemies)
	{
		
		if (enemy->isActive())
		{
				if (m_state->getPlayer()->m_player_box.intersectDown(enemy->m_enemy_box)) {  
					


					auto currentTime = std::chrono::steady_clock::now();
					auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastCollisionTime);

					if (elapsedTime.count() >= 1.5f) {			
						
						
						graphics::playSound(m_state->getFullAssetPath("bee_hurt.wav"), 0.6f);
						m_state->updateScore(200); //Αυξανουμε το σκορ αν σκοτωσε ο παικτης τον εχθρο
						ScoreLevel += 200;
						enemy->setActive(false);//Απενεργοποιουμε εχθρο
						
						
						std::cerr << "Intersectdown " << std::endl;
						lastCollisionTime = currentTime;
						enemyToDelete = enemy; //Βλεπουμε ποιος enemy παιθανε με σκοπο να τον κανουμε delete 
					}
				}
				if (m_state->getPlayer()->m_player_box.intersectSideways(enemy->m_enemy_box) || m_state->getPlayer()->m_player_box.intersectUp(enemy->m_enemy_box)) {
			

						auto currentTime = std::chrono::steady_clock::now();
						auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastCollisionTime);

						if (elapsedTime.count() >= 1.0) {
							effect();//Εφε επειδη εχασε ζωη ο παικτης
							graphics::playSound(m_state->getFullAssetPath("playerhurt.wav"), 0.8f);
							m_state->getPlayer()->decreaseLife();//Μειωνουμε τη ζωη του παικτη 
							std::cerr << "Intersect with enemy. Offset: " << std::endl;
							lastCollisionTime = currentTime;

						}
						
				}

		}
	}
	//Διαγραφουμε τον εχθρο που παιθανε 
	if (enemyToDelete)
	{
		m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), enemyToDelete), m_enemies.end());
		delete enemyToDelete; // Διαγραφη του εχθρου που παιθανε
		enemyToDelete = nullptr; // Επαναφορα του δεικτη μετα την αφαιρεση
		
	}
}

//Ελεγχος συγκρουσεων αναμεσα σε παικτη και coins
void Level::checkPlayerCoinsCollision() {
	for (auto& coin : coins) {
		if (coin->isActive()) {
			if (m_state->getPlayer()->m_player_box.intersect(coin->m_coins_box)) {
				graphics::playSound(m_state->getFullAssetPath("coin_earn.wav"), 0.8f);
				m_state->updateScore(100);
				ScoreLevel += 100;//Αυξηση σκορ καθε φορα που παιρνει ενα
				coin->setActive(false);
				
				coinToDelete = coin;//Διαγραφουμε αυτο που παιρνει
			}
		}
	}
	if (coinToDelete)
	{
		coins.erase(std::remove(coins.begin(), coins.end(), coinToDelete), coins.end());
		delete coinToDelete; // Διαγραφη του coin που πηραμε
		coinToDelete = nullptr; // Επαναφορα του δεικτη
	}
}

//Ελεγχος συγκρουσεων αναμεσα σε παικτη και hearts
void Level::checkPlayerHeartscoll(){
	for (auto& heart : hearts) {
		if (heart->isActive()) {
			if (m_state->getPlayer()->m_player_box.intersect(heart->m_hearts_box)) {
				m_state->getPlayer()->increaseLife();//Αυξανουμε ζωη
				heart->setActive(false);
				
				heartToDelete = heart;
			}
		}
	}
	if (heartToDelete)
	{
		hearts.erase(std::remove(hearts.begin(), hearts.end(), heartToDelete), hearts.end());
		delete heartToDelete; // Διαγραφη της καρδιας
		heartToDelete = nullptr; // Επαναφορα του δεικτη
	}
}

//Ελεγχος συγκρουσεων αναμεσα σε παικτη και gate, αν αυτη η συγκρουση γινει οταν το m_current_level=m_level2 δηλαδη βρισκομαστε στο δευτερο level τοτε κανε τη μεταβλητη win true για να τελειωσει το παιχνιδι
//Αλλιως αλλαξε level καθως θα βρισκομαστε στο πρωτο και θα πρεπει να παμε στο δευτερο
void Level::checkPlayerGate() {
	
		if (gate1->isActive()) {
			if (m_state->getPlayer()->m_player_box.intersect(gate1->m_gate_box)) {
				if (m_state->m_current_level = m_state->m_level2) {
					m_state->win = true;
				}else{

				m_state->initLevel2();//Καλεσε την initLevel2 της gamestate
				gate1->setActive(false);
				}
			}
		}
	
		
}


//Αλλαζει χρωμα το background ως ενδειξη απωλειας ζωης γιαυτο στο πρωτο level γινεται κοκκινη λαμψη και στο δευτερο μαυρη, θετουδε timer για να διαρκεσει μολις 100 milliseconds
void Level::effect() {

	//originalBackgroundColor = m_brush_background.fill_color;
	SETCOLOR(m_brush_background.fill_color, 1.0f, 0.0f, 0.0f);
	effectStartTime = std::chrono::steady_clock::now();
}
	



Level::Level(const std::string& name) 
{
	
}

//Καταστρεφουμε ολα τα δεδομενα του Level καθως τα ορισαμε με new και επρεπε να ελευθερωσουμε τη μνημη 
Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;

	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;

	for (auto enemy : m_enemies) {
		if (enemy) delete enemy;
	}


	for (auto coin : coins) {
		if (coin) delete coin;
	}

	for (auto heart : hearts) {
		if (heart) delete heart;
	}

	
	if (gate1) delete gate1;
	
	
}

