#include <iostream>
#include <fstream>
#include <string>

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
};

std::fstream new_game(player user) {
	string user_name;
	cout << "Please enter your name: ";
	cin >> user_name;
	user.name = user_name;

	std::fstream user_file (user_name + ".txt");
	user_file << 1 << endl; //sets player starting level
	user_file << 0 << endl; //sets player starting xp
	user_file << 100 << endl; //sets player starting health
	user_file << 0 << endl; //sets that the player hasn't played before

	return user_file;
}

std::fstream load_game(player user) { 
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

void game(std::fstream& user_file, player user) {
	string temp_string;
	int temp_int;
	string player_action;

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

	user_file.close();
		
	cout << endl;
	cout << "Current Level: " << user.level << endl;
	cout << "Current XP: " << user.xp << endl;
	cout << "Current Health: " << user.health << endl;
	cout << endl;

	played_before(user.played_before);
	user.played_before = 1;

	do {
		cout << "What would you like to do: ";
		cin >> player_action;
	} while (player_action != "quit");

	cout << "Would you like to save your progress? (y/n): ";
	cin >> temp_string;

	if (temp_string == "y") {
		std::fstream user_file (user.name + ".txt", std::ios::out | std::ios::trunc);

		user_file << user.level << endl;
		user_file << user.xp << endl;
		user_file << user.health << endl;
		user_file << user.played_before << endl;
		user_file.close();
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
			std::fstream user_file = new_game(user);
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
