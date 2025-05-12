#include <iostream>
#include <string>
#include <utility>  // for std::pair
#include <vector>
#include <cstdlib>  // for atoi, rand, srand
#include <ctime>

std::pair<int, int> parseDiceNotation(const std::string& input) {
  // Find the 'd' character in the notation
  size_t dPos = input.find('d');
  // std::string::npos is a constant that represents not found
  // We are using this to see if input.find() failed
  // If it did, we throw the exception below
  if (dPos == std::string::npos) {
    throw std::invalid_argument("Invalid format: missing 'd'");
  }

  // Set the value of nStr (n as a string) and sStr (s as a string)
  std::string nStr = input.substr(0, dPos);
  std::string sStr = input.substr(dPos + 1);

  // Set n to be 1 if it is empty, otherwise set it to the value of nStr
  int n = nStr.empty() ? 1 : std::stoi(nStr);
  // Set s to be the value of sStr
  int s = std::stoi(sStr);

  return {n, s};
}

int rollDice(int n, int s) {
  // Create a vector to hold all the rolls
  std::vector<int> rolls(n);
  int sum = 0;

  // Roll a dice of s size n times and get the sum of each
  for (int i = 0; i < n; ++i) {
    int roll = (rand() % s) + 1;  // Add 1 to make rolls between 1 and s
    std::cout << "You rolled: " << roll << "\n";
    sum += roll;
  }

  return sum;
}

int main(int argc, char* argv[]) {
  // Check if the correct amount of arguments is passed before continuing.
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0] << " <dice> <skill check requirement> <skill check reason>\n";
    return 1;
  }

  // Save the command arguments as individual variables for readability and type casting.
  std::string dicenotation = argv[1];
  int checkRequirement = std::atoi(argv[2]);
  std::string skillCheck = argv[3];

  // Output the desired skill check information
  std::cout << "Skill check: " << skillCheck << "\n";
  std::cout << "You need a " << checkRequirement << " to pass.\n";

  // Set the seed TODO: later generate a seed individually
  srand(time(0));

  // Attempt to parse the dice notation and throw an exception on fail
  try {
    // Set n and s to the return value of the parsed dice notation
    auto [n, s] = parseDiceNotation(dicenotation);
    // Create a variable to hold the value of the sum
    int total = rollDice(n, s);
    // Inform the user of their sum
    std::cout << "Your total roll was: " << total << "\n";

    // Finally check if the user's dice roll succeeded the skill check!
    if (total >= checkRequirement) {
      std::cout << "You succeeded the skill check!\n";
    } else {
      std::cout << "I regret to inform you, you have failed the skill check...\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error parsing dice notation: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
