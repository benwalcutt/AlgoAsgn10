#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

class Node {
	public:
	Node * next;
	
	int value;
	int remainder;
	
	Node() {
		next = NULL;
		value = remainder = 0;
	}
	/*
	Node(Node& par, int initial) {
		parent = par;
		child = NULL;
		assigned = remainder = initial;
	}
	*/
};

void delete_list(Node * head) {
	Node * current;
	Node * target;
	
	target = head->next;
	while (target != NULL) {
		current = target;
		target = current->next;
		delete current;
	}
}


int* counting_sort(int* input, int num) {
	int RANGE = 1000000;
	int* count;
	int* output;
	
	output = new int[num];
	count = new int[RANGE + 1];
	
	for (int i = 0; i < num; i++) {
		++count[input[i]];
	}
	
	for (int i = 1; i <= RANGE; i++) {
		count[i] += count[i - 1];
	}
	
	for (int i = 0; i < num; i++) {
		output[count[input[i]] - 1] = input[i];
		--count[input[i]];
	}
		
	return output;
}

Node * linked_sort(Node * input) {
	bool changed = true;
	bool done = false;
	Node * node_to_be_checked;
	Node * search_node;
	Node * attaching_node;
	Node * dummy;
	int destination;
	int counter = 0;
	int othercounter = 0;
	
	Node * buckets[10];
	for (int i = 0; i < 10; i++) {
		buckets[i] = new Node;
	}

	
	while (counter < 7) {
		for (int i = 0; i < 10; i++) {
			buckets[i]->next = NULL;
			
		}
		othercounter = 0;
		node_to_be_checked = input->next;
		while (node_to_be_checked != NULL) {
			destination = node_to_be_checked->remainder % 10;
			node_to_be_checked->remainder /= 10;
			attaching_node = buckets[destination];
			search_node = attaching_node->next;
		
			while (!done) {
				if (search_node == NULL) {
					attaching_node->next = node_to_be_checked;
					
					node_to_be_checked = node_to_be_checked->next;
					attaching_node->next->next = NULL;
					done = true;
					
				}
				else {
					attaching_node = search_node;
					search_node = attaching_node->next;
				}
			}
			done = false;
			othercounter++;
		}
		
		// I know the next 100-ish lines can be placed in a loop. Given time, I would make that happen
		// This is not a testament to laziness, but a testament to "get it working, then optimize"
		// Especially at 2:00 am
		if (buckets[0]->next != NULL) {
			input->next = buckets[0]->next;
		}
		else if (buckets[1]->next != NULL) {
			input->next = buckets[1]->next;
		}
		else if (buckets[2]->next != NULL) {
			input->next = buckets[2]->next;
		}
		else if (buckets[3]->next != NULL) {
			input->next = buckets[3]->next;
		}
		else if (buckets[4]->next != NULL) {
			input->next = buckets[4]->next;
		}
		else if (buckets[5]->next != NULL) {
			input->next = buckets[5]->next;
		}
		else if (buckets[6]->next != NULL) {
			input->next = buckets[6]->next;
		}
		else if (buckets[7]->next != NULL) {
			input->next = buckets[7]->next;
		}
		else if (buckets[8]->next != NULL) {
			input->next = buckets[8]->next;
		}
		else if (buckets[9]->next != NULL) {
			input->next = buckets[9]->next;
		}
		
		dummy = buckets[0];
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[1]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[2]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[3]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[4]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[5]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[6]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[7]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[8]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		
		dummy->next = buckets[9]->next;
		
		while (dummy->next != NULL) {
			dummy = dummy->next;
		}
		counter++;
		
	}	
	return input;
}

int main() {
	clock_t start, end;
	float elapsed;
	int num_of_numbers;
	int input_counter;
	int input;
	
	int * numbers;
	
	Node * head = new Node;
	head->next = NULL;
	Node * current;
	
	cin >> num_of_numbers;
	input_counter = num_of_numbers;
	cin.ignore();
	
	numbers = new int[num_of_numbers];
	start = clock();
	while (input_counter-- != 0) {
		cin >> input;
		cin.ignore();
		
		current = new Node;
		current->value = input;
		current->remainder = input;
		current->next = head->next;
		head->next = current;
		
		numbers[input_counter - 1] = input;
	}
	end = clock();
	elapsed = end-start;
	cout << "Setup time: " << elapsed / CLOCKS_PER_SEC << " seconds" << endl;
	start = clock();
	
	head = linked_sort(head);
	current = head->next;
	/*
	cout << "Printing from linked list: " << endl;
	while (current != NULL) {
		cout << current->value << endl;
		current = current->next;
	}
	*/	
	end = clock();
	elapsed = end - start;
	cout << "Linked list time: " << elapsed / CLOCKS_PER_SEC << " seconds" << endl;
	start = clock();
	numbers = counting_sort(numbers, num_of_numbers);
	/*
	cout << "Printing from counting sort: " << endl;
	for (int i = 1; i < num_of_numbers; i++) {
		cout << numbers[i] << endl;
	}
	*/
	end = clock();
	elapsed = end - start;
	cout << "Counting sort time: " << elapsed / CLOCKS_PER_SEC << " seconds" << endl;
	start = clock();
	delete_list(head);
	delete[] numbers;
	end = clock();
	elapsed = end-start;
	cout << "Cleanup time: " << elapsed / CLOCKS_PER_SEC << " seconds" << endl;
	return 0;
}
