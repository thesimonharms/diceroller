#include<iostream>
#include<string>
#include<utility> // for std::pair

std::pair<int, int> parseDiceNotation(const std::string& input) {
  size_t dPos = input.find('d');
  if (dPos == std::string::npos) {
    throw std::invalid_argument("Invalid format: missing 'd'");
  }

  std::string nStr = input.substr(0, dPos);
  std::string sStr = input.substr(dPos + 1);

  int n = nStr.empty() ? : std::stoi(nStr);
  int s = std::stoi(sStr);

  return {n, s};
}

int rollDice(int n, int s) {
  int rolls[n];
  for (int i = 0; i < n; i++) {
    int roll = rand() % s;
    rolls[i] = roll;
    std::cout << "You rolled: " << roll << "\n";
  }

  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += rolls[i];
  }

  return sum;
}

int main(int argc, char* argv[]) {
  std::string skillcheck = argv[4];
  int checkrequirement = atoi(argv[3]);
  int seed = atoi(argv[2]);
  std::string dicenotation = argv[1];
  std::cout << "Skill check: " << skillcheck << "\n";
  std::cout << "You need a " << argv[3] << " to pass.\n";

  srand(seed);

  try {
    std::pair<int, int> n_s_pair = parseDiceNotation(dicenotation);
    int total = rollDice(n_s_pair.first, n_s_pair.second);
    std::cout << "Your total roll was: " << total << "\n";
    if (total >= checkrequirement) {
      std::cout << "You succeeded the skill check!\n";
    } else {
      std::cout << "I regret to inform you, you have failed the skill check...\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error parsing dice notation: " << e.what() << std::endl;
  }

  return 0;
}
