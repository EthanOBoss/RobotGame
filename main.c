#include <iostream>
#include <fstream>
#include <string>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct player {
	string name;
	int level;
	int xp;
	int health;
	int played_before;
	int x;
	int y;
	int tumbleweed;
	int attack_damage;
	int healing_packs;
};

struct basic_enemy {
	string name;
	int health;
	int attack_damage;
};

void new_game(player& user) {
	string user_name;
	cout << "Please enter your name: ";
	cin >> user_name;
	user.name = user_name;

	std::fstream user_file (user_name + ".txt", std::ios::out | std::ios::trunc);

	user_file << 1 << endl; //sets player starting level
	user_file << 0 << endl; //sets player starting xp
	user_file << 100 << endl; //sets player starting health
	user_file << 0 << endl; //sets that the player hasn't played before
	user_file << 0 << endl; //sets the user's starting location (x)
	user_file << 0 << endl; //sets the user's starting location (y)
	user_file << 0 << endl; //sets that the user hasn't entered Tumbleweed
	user_file << 10 << endl; //sets the player's base attack damage
	user_file << 5 << endl; //sets the player's starting healing items

	user_file.close();
	return;
}

std::fstream load_game(player& user) { 
	string user_name;
	int file_exists = 0;

	do {
		cout << "Please enter your name: ";
		cin >> user_name;
		user.name = user_name;

		std::fstream user_file (user_name + ".txt");
	
		if (!user_file) {
			cout << "Error! No user file under that name. Please try again.\n";
			file_exists = 1;
		} else {
			file_exists = 0;
			return user_file;
		}
	} while (file_exists == 1);
}
void about() {
	int about_choice = 0;
	
	do {

        	cout << "Please select an option to read more:\n";
        	cout << "1 - About this project.\n";
        	cout << "2 - About the game world.\n";
        	cout << "3 - Return to Main Menu.\n";
		cout << "Your Choice:";

		cin >> about_choice;

		if (about_choice == 1) {
			cout << "About myself and the project here.\n";
		} else if (about_choice == 2) {
			cout << "Cool robot stuff here.\n";
		}

	} while (about_choice != 3);
	return;
}

void played_before(int played_before) {
       if (played_before == 0) {
	       cout << "First, there was nothing. The state of non-being. The state of abscence. An ocean of inperceivable black coating your consciousness. Then....light! A light unlike anything you've ever seen before. Your systems begin to hum and whirr. A symphony of clicks and hissing fill your audio receptors. The world begins to take shape before you. You appear to be inside a dusty warehouse. Holes in the dilapitated ceiling rain sunlight down upon your faceplate. Sand and dust sprinkle through and shine in the morning rays. You look around the room. Tools of all sorts line the concrete floor, as well as machine parts to many different makes and models of robot." << endl;
	       cout << endl;
	       cout << "You begin to sit up. Your servos and pistons whine under the load. You've been asleep for a long time. How long exactly? What has happened to the world? Who are you? What is your purpose? You look down at your wrist and see a small screen embedded into your arm. With a tap it springs to life. At the center lies your current location. There also seems to be a waypoint pointing you north. 300 miles north to be specific. You now have a goal. Where is this waypoint taking you? Well, only one way to find out." << endl;
	       cout << endl;
	       cout << "You stand up from the table you were lying on. In the corner of the room lies a rusty blade. You walk over to it and strap it to your back. Next to the blade there is a sign taped to the wall. It reads: 'Come visit Tumbleweed! Your own little oasis in this vast desert. Only 20 miles to the west.' A choice lies before you. You can head straight to the waypoint on your map, or, you can explore the desert that lies before you. You step into the blistering heat and commence your adventure." << endl;
	      cout << endl; 
      }
      return;
}

void move(int& x, int& y) {
	int distance;
	string direction;

	cout << "How far would you like to go: ";
	cin >> distance;

	cout << "What direction: ";
	cin >> direction;

	if (direction == "north" || direction == "North") {
		y = y + distance;
	} else if (direction == "south" || direction == "South") {
		y = y - distance;
	} else if (direction == "east" || direction == "East") {
		x = x - distance;
	} else if (direction == "west" || direction == "West") {
		x = x + distance;
	}

	return;
}

void tumbleweed(player& user) { //function that controls the aspects of 'Tumbleweed'
	string tumbleweed_choice;

	cout << "You've entered Tumbleweed." << endl;
	cout << endl;

	if (user.tumbleweed == 0) {
		cout << "Tumbleweed appears to have seen better days. The town consists of a just one main street with buildings lining either side of it. It looks like something right out of an old western film. Some people shuffle through the streets slowly. The buildings are all in rough condition. The town has a couple of services. There's a general store, a saloon, and a sheriff's office for you to explore. All the other buildings seem to be the homes of the townsfolk." << endl;
	        cout << endl;
		user.tumbleweed = 1;		
	}

	do {
		cout << "What would you like to do in Tumbleweed: ";
		cin >> tumbleweed_choice;

	} while (tumbleweed_choice != "leave" && tumbleweed_choice != "Leave");

	cout << "You've exited Tumbleweed." << endl;
	cout << endl;

	return;
}

void combat(player& user) {
	cout << "An enemy has ambushed you on your travels! A crazed combat automaton raises its sword for combat." << endl;
	cout << endl;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 2);

	int attack_order = distr(gen);
	int attack_choice;

	basic_enemy enemy;

	enemy.name = "Combat Automaton";
	enemy.health = 50;
	enemy.attack_damage = 5;


	do {
		if (attack_order == 1) {
			cout << "It's your turn!" << endl;
			cout << endl;

			cout << "What would you like to do?" << endl;
			cout << endl;
			cout << "1 - Attack" << endl;
			cout << "2 - Heal" << endl;
			cout << "3 - Evade" << endl;
			cout << "4 - Flee" << endl;
			cin >> attack_choice;

			if (attack_choice == 1) {
				cout << "You swing your blade at the enemy." << endl;
				cout << endl;
				cout << "The attack lands! You inflict " << user.attack_damage << " damage!" << endl;
				cout << endl;
				enemy.health = enemy.health - user.attack_damage;
				if (enemy.health <= 0) {
					cout << "You've defeated the enemy!" << endl;
					attack_order = 3;
				} else {
					attack_order = 2;
				}
			}
			if (attack_choice == 2) {
				cout << "You have " << user.healing_packs << " healing packs. Would you like to use one to heal 25 HP?" << endl;
				cout << "1 - Yes" << endl;
				cout << "2 - No" << endl;
				cin >> attack_choice;

				if (attack_choice == 1) {
					if (user.health == 100) {
						cout << "You're already at max health!" << endl;
						cout << endl;
						attack_order = 1;
					} else if (user.health < 100) {
						cout << "You use one of your healing packs." << endl;
						cout << endl;

						user.health = user.health + 25;
						user.healing_packs = user.healing_packs - 1;
						if (user.health > 100) {
							cout << "You are now at max health!" << endl;
							cout << endl;
							user.health = 100;
							attack_order = 2;
						} else { 
							cout << "You are now at " << user.health << " health!" << endl;
						       cout << endl;	
						}
					}
				} else if (attack_choice == 2) {
					cout << "You choose not to heal." << endl;
					cout << endl;
					attack_order = 1;
				}
			}
		} else if (attack_order == 2) {
			cout << "It's the enemy's turn!" << endl;
			attack_order = 1;
		}
	} while (attack_order != 3);
	return;
}

void game(std::fstream& user_file, player& user) {
	string temp_string;
	int temp_int;
	string player_action;

	std::random_device rd; //random number generation for combat
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 100);
	int combat_chance;

	getline(user_file, temp_string); //set the players current level
	temp_int = std::stoi(temp_string);
	user.level = temp_int;

	getline(user_file, temp_string); //set the players current xp
	temp_int = std::stoi(temp_string);
	user.xp = temp_int;

	getline(user_file, temp_string); //set the players current health
	temp_int = std::stoi(temp_string);
	user.health = temp_int;

	getline(user_file, temp_string); //set whether the user has played before
	temp_int = std::stoi(temp_string);
	user.played_before = temp_int;

	getline(user_file, temp_string); //sets the user's current location (x)
	temp_int = std::stoi(temp_string);
	user.x = temp_int;

	getline(user_file, temp_string); //sets the user's current location (y)
	temp_int = std::stoi(temp_string);
	user.y = temp_int;

	getline(user_file, temp_string); //sets if the user has visited Tumbleweed or not
	temp_int = std::stoi(temp_string);
	user.tumbleweed = temp_int;

	getline(user_file, temp_string); //sets the user's attack damage
	temp_int = std::stoi(temp_string);
	user.attack_damage = temp_int;
  
	getline(user_file, temp_string); //sets the user's current amount of healing items
	temp_int = std::stoi(temp_string);
	user.healing_packs = temp_int;

	user_file.close();
		
	cout << endl;
	cout << "Current Level: " << user.level << endl;
	cout << "Current XP: " << user.xp << endl;
	cout << "Current Health: " << user.health << endl;
	cout << "Current Location: " << "x: " << user.x << " y: " << user.y << endl;
	cout << endl;

	played_before(user.played_before);
	user.played_before = 1;

	do {
		if (user.x == 20 && user.y == 0) {
			cout << "You've arrived at the main gate to Tumbleweed. You can enter at your discretion." << endl;
			cout << endl;
		}
		cout << "What would you like to do: ";
		cin >> player_action;

		if (player_action == "move") {
			move(user.x, user.y);

			combat_chance = distr(gen);
			if (combat_chance > 50) {
				combat(user);
			}
			cout << "Current Location:";
			cout << "x: " << user.x << " y: " << user.y << endl;



		} else if (player_action == "enter" || player_action == "Enter") {
			if (user.x == 20 && user.y == 0) {
				tumbleweed(user);
			} else {
				cout << "There is no town or structure to enter here." << endl;
				cout << endl;
			}
		}
	} while (player_action != "quit");

	cout << "Would you like to save your progress? (y/n): ";
	cin >> temp_string;

	if (temp_string == "y") {
		std::fstream user_file (user.name + ".txt", std::ios::out | std::ios::trunc);

		user_file << user.level << endl;
		user_file << user.xp << endl;
		user_file << user.health << endl;
		user_file << user.played_before << endl;
		user_file << user.x << endl;
		user_file << user.y << endl;
		user_file << user.tumbleweed << endl;
		user_file << user.attack_damage << endl;
		user_file << user.healing_packs << endl;
		user_file.close();
		cout << "Progress Saved!" << endl;
		cout << endl;
	}

	return;
}

int main() {
	int user_choice = 0;
	player user;
	do {
       		cout << "Welcome to Mecha Madness! Please select one of the following options:\n";
       		cout << "1 - Start a new game.\n";
       		cout << "2 - Load a previouly saved game.\n";
       		cout << "3 - Read more about the game.\n";
       		cout << "4 - Exit the game.\n";
		cout << "Your Choice:";

		cin >> user_choice;

		if (user_choice == 1) {
			new_game(user);
			std::fstream user_file(user.name + ".txt");
			game(user_file,user);
		} else if (user_choice == 2) {
			std::fstream user_file = load_game(user);
			game(user_file,user);
		} else if (user_choice == 3) {
			about();
		}
	} while (user_choice != 4);
	
	cout << "Thanks for playing!\n";
	return 0;
}
	return 0;
}
