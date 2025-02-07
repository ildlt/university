#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

int main() {
	const int max = 2000;
	int n;
	int sum;
	string s;
	//vector<bitset<max>> graph(max);
	bitset<max> graph[max];
	bitset<max> current;
	bitset<max> visited;
	bitset<max> possible;

	ifstream in("C:/Users/Alexis/test.txt");

	in >> n;

	for (int i = 0; i < n; i++) {
		in >> s;
		//graph.push_back(bitset<3>(s));
		graph[i] = bitset<max>(s);
	}

	for (int i = 0; i < n; i++) {
		int distance = 1;

		cout << graph[i] << "\n\n";
		/*if (graph[i].all()) {
			sum = sum + n - 1;
			continue;
		}
		if (graph[i].none()) {
			sum = sum + pow(n, 2) * (n - 1);
			continue;
		}
		*/
		
		current.reset();
		visited.reset();

		current.set(i);
		visited.set(i);

		while (current.any()) {
			possible.reset();

			for (int j = current._Find_first(); j < n; j = current._Find_next(j)) {
				possible = possible | graph[j];
			}

			current = ((possible ^ visited) & possible);

			/*if (!current.any()) {
				sum = sum + pow(n, 2) * (n - visited.count());
				break;
			}*/

			sum = sum + pow(distance, 2) * (current.count());
			visited = visited | possible;
			
			distance += 1;
		}
	}

	cout << sum << "\n";
	//там вроде предполагается такой лайфхак : 
	//сделать что - то(битсет или маску) для еще непросмотренных вершин.
	//изначально там все 1. 
	//а потом можно делать побитовое "и" со строкой матрицы смежности
	//+ надо еще занулять биты посещенных вершин

	//сделали &, получили список непросмотренных доступных вершин.
	//потом просмотрели, занулили правильные биты в маске и следующая итерация,


}