#include <iostream>
#include <string>

#include <Field.hpp>
#include <logics.hpp>

int get_int(std::string &input, int &i) {
  std::string digit;
  for (; i < input.size() && input[i] != ','; i++) {
    if (input[i] == ' ')
      continue;
    digit.push_back(input[i]);
  }
  i++;
  return stod(digit);
}

void allocate_memory_for_field(Field &map) {
  map.field = new bool *[map.sizeY];
  for (int i = 0; i < map.sizeY; i++)
    map.field[i] = new bool[map.sizeX];
}

void get_map_from_user(Field &map) {
  map.sizeX = 9;
  map.sizeY = 9;
  allocate_memory_for_field(map);
  std::cout << "Введите живую клетку в формате: X,Y\nЧтобы закончить ввод "
               "введите '-1'\n";
  std::string input;

  while (true) {
    std::pair<int, int> coords;
    getline(std::cin, input);
    int i = 0;
    coords.first = get_int(input, i) - 1;
    if (coords.first == -2)
      break;
    coords.second = get_int(input, i) - 1;
    map.field[coords.second][coords.first] =
        !map.field[coords.second][coords.first];
  }
}


int main() {
  Field field;
  get_map_from_user(field);
	game_process(field);
  return 0;
}