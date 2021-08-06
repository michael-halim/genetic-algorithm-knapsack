#include<iostream>
#include<math.h>
#include<queue>
#include<time.h>
#define TOTAL_POPULATION 10
#define SELECTED_PARENTS 5
#define MUTATIONS 15
#define GENERATIONS 200
#define TOTAL_ITEMS 12
#define MAX_WEIGHT 20
using namespace std;

class Item {
	string name;
	int weight, value;
public:
	Item(string name = "No Name", int weight = 0, int value = 0) {
		this->name = name;  this->weight = weight;  this->value = value;
	}
	void setAll(string name = "No Name", int weight = 0, int value = 0) { setName(name); setWeight(weight); setValue(value);   }
	void setName(string name) { this->name = name;  }
	void setWeight(int weight) { this->weight = weight;  }
	void setValue(int value) {  this->value = value;  }
	int getWeight() { return weight; }
	int getValue() { return value; }
	string getName() { return name; }
	void display() {
		cout << "Item Name : " << name << "\n Weight : " << weight << "\n Value : " << value << "\n\n";
	}
};
class Population {
	int index;
	int weight,value;
	bool isOld;// if it old means from old gen (value 1) and has value of 0 if it from new Gen
	
public:
	Population() {
		value = 0;
		weight = 0;
	}
	void setIsOld(bool o) { isOld = o; }
	void setAll(int i, int v, int w, bool o) {
		setIndex(i); setValue(v); setWeight(w); setIsOld(o);
	}
	void setWeight(int w) { weight = w; }
	void setValue(int v) { value = v; }
	void setIndex(int i) { index = i; }
	
	int getindex() { return index; }
	int getWeight() { return weight; }
	bool getIsOld() { return isOld; }
	int getValue() { return value; }
};
class CompareValue {
public:
	bool operator()(Population& p1, Population& p2) {
		if (p1.getValue() < p2.getValue()) return true;
		return false;
	}
};

bool isMutated(int num[MUTATIONS], int other_num) {
	for (int i = 0; i < MUTATIONS; i++)
		if (num[i] == other_num) return true;

	return false;
}
void generatePopulation(bool populations[TOTAL_POPULATION][TOTAL_ITEMS], Item* items) {
	int totalWeight = 0;
	for (int i = 0; i < TOTAL_POPULATION; i++) {

		do {
			totalWeight = 0;
			for (int j = 0; j < TOTAL_ITEMS; j++) {
				int num = rand() % 2;
				
				if (num == 1)
					totalWeight += items[j].getWeight();

				populations[i][j] = num;
				
			}
		} while (totalWeight > MAX_WEIGHT);
	}
}
void displayPopulations(bool populations[][TOTAL_ITEMS] , Item*items, int opt = 0) {
	int totalWeight = 0, totalValue = 0;
	int total_num;
	if (opt == 0) total_num = TOTAL_POPULATION;
	else total_num = SELECTED_PARENTS;

	for (int i = 0; i < total_num; i++) {

		cout << "Gen " << i + 1 << endl;

		for (int j = 0; j < TOTAL_ITEMS; j++){
			if (populations[i][j] == 1) {
				totalWeight += items[j].getWeight();
				totalValue += items[j].getValue();
			}		
			cout << populations[i][j] << " ";
		}
		cout << " | Weight : " << totalWeight << " | Value : " << totalValue << endl;
		totalWeight = 0 ,totalValue = 0;
	}
}
void naturalSelection (bool old_gen[TOTAL_POPULATION][TOTAL_ITEMS], bool current_gen[][TOTAL_ITEMS], Item* items) {
	priority_queue<Population, vector<Population>, CompareValue> q;
	Population tmp;
	int totalWeight = 0, totalValue = 0;
	for (int i = 0; i < TOTAL_POPULATION; i++){
		for (int j = 0; j < TOTAL_ITEMS; j++){

			if (old_gen[i][j] == 1) {
				totalWeight += items[j].getWeight();
				totalValue += items[j].getValue();
			}
			
		}

		tmp.setAll(i, totalValue, totalWeight, 1);
		q.push(tmp);

		totalWeight = 0, totalValue = 0;
		for (int j = 0; j < TOTAL_ITEMS; j++)
		{
			if (current_gen[i][j] == 1) {
				totalWeight += items[j].getWeight();
				totalValue += items[j].getValue();
			}
		}
		tmp.setAll(i, totalValue, totalWeight, 0);
		q.push(tmp);
		totalWeight = 0, totalValue = 0;
	}
	cout << "Natural Selection \n\n";
	for (int i = 0; i < TOTAL_POPULATION; i++){
		tmp = q.top();
		if (tmp.getWeight() <= MAX_WEIGHT) {

			if (tmp.getIsOld()) 
				for (int j = 0; j < TOTAL_ITEMS; j++)		
					old_gen[i][j] = old_gen[tmp.getindex()][j];	
			
			else 
				for (int j = 0; j < TOTAL_ITEMS; j++)			
					old_gen[i][j] = current_gen[tmp.getindex()][j] ;
			
		}
		
		q.pop();
	}
	while (!q.empty())
		q.pop();

}
int main() {
	srand(time(NULL));

	//Declare 12 Item in Items
	Item* items = new Item[12];
	items[0].setAll("Bug Repellent", 2, 12); items[1].setAll("Tent", 11, 20);  items[2].setAll("Stove", 4, 5);  items[3].setAll("Clothes", 5, 11); items[4].setAll("Dried Foods", 3, 50);
	items[5].setAll("First Aid Kit", 3, 15); items[6].setAll("Flash Light", 2, 6);  items[7].setAll("Novel", 2, 4); items[8].setAll("Rain Gear", 2, 5); items[9].setAll("Sleeping Bag", 3, 25);
	items[10].setAll("Water Filter", 1, 30); items[11].setAll("Lantern", 7, 10);

	//Initial Population
	bool populations [TOTAL_POPULATION][TOTAL_ITEMS];

	int total_population_value = 0;

	//Make N Total Population
	
	generatePopulation(populations,items);

	//Display All Population
	displayPopulations(populations,items);
	
	for (int m = 0; m < GENERATIONS; m++){

		bool selected_populations[SELECTED_PARENTS][TOTAL_ITEMS];
		for (int i = 0; i < SELECTED_PARENTS; i++){

			int num = rand() % TOTAL_POPULATION;

			for (int j = num; j < num + 1; j++)			
				for (int k = 0; k < TOTAL_ITEMS; k++)				
					selected_populations[i][k] = populations[j][k];
				
		}

		cout << "\nSelected Populations \n" << endl;
		displayPopulations(selected_populations, items, 1);

		//declare Mutations
		//How %pct mutations works : create random number and when another random has the same number in the array, the mutation is active
		int random_num_mutations[MUTATIONS];

		for (int i = 0; i < MUTATIONS; i++)
			random_num_mutations[i] = rand() % 100;

		bool new_populations[TOTAL_POPULATION][TOTAL_ITEMS];

		for (int i = 0; i < TOTAL_POPULATION; i += 2){

			//crosover with selected parents
			int x = rand() % SELECTED_PARENTS;
			int y = rand() % SELECTED_PARENTS;
			int mutations = rand() % 100;

			int crossover_point = rand() % TOTAL_ITEMS;

			for (int j = 0; j < crossover_point; j++)
			{
				new_populations[i][j] = selected_populations[x][j];
				new_populations[i + 1][j] = selected_populations[y][j];
			}
			for (int j = crossover_point; j < TOTAL_ITEMS; j++)
			{
				new_populations[i][j] = selected_populations[y][j];
				new_populations[i + 1][j] = selected_populations[x][j];
			}

			if (isMutated(random_num_mutations, mutations)) {
				int a = rand() % 2;
				int random_index = rand() % TOTAL_ITEMS;
				if (a == 0) {
					if (new_populations[i][random_index] == 0) new_populations[i][random_index] = 1;
					else new_populations[i][random_index] = 0;

				}
				else {
					if (new_populations[i + 1][random_index] == 0) new_populations[i][random_index] = 1;
					else new_populations[i + 1][random_index] = 0;
				}
			}
		}
		cout << "Current Gen" << endl;
		displayPopulations(new_populations, items);
		naturalSelection(populations, new_populations, items);
		cout << "New Gen" << endl;
		displayPopulations(populations, items);
	}
}