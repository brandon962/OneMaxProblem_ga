#pragma once
#include <string>
#include "algoclass.h"
#include "mybitset.h"

class Ga {
private :
	int runs;
	int evolution;
	int bits;
	int chromosome;
	int* savedata;
	string algoname = "ga";
	MyBitSet* solutions;
	double mutation_rate;
	double mutation_rate_min;
	double mutation_rate_alpha;
	int save_freq;
	int max_np =INT_MIN;
	
public :
	Ga(int _r, int _e, int _b, int _c, int _mr, int _mrm, int _mra) {
		//declare variables
		runs = _r;
		evolution = _e;
		bits = _b;
		chromosome = _c;
		savedata = (int*)calloc(evolution, sizeof(int));
		algoname = "ga";
		solutions = (MyBitSet*)calloc(chromosome, sizeof(MyBitSet));
		mutation_rate = _mr;
		mutation_rate_min = _mrm;
		mutation_rate_alpha = _mra;
		for (int i = 0; i < chromosome; i++) {
			solutions[i] = MyBitSet(bits);
		}
		srand(time(NULL));
	}

	void run() {
		//print the message
		mesg(runs, evolution, bits, algoname, chromosome);

		//start
		//runs
		for (int i = 0; i < runs; i++) {

			//initialize & fitness
			for (int i = 0; i < chromosome; i++) {
				solutions[i] = initial(solutions[i], bits);
			}

			//evolutioin
			for (int i = 0; i < evolution; i++) {
				
				//fitness function
				solutions = FitnessFunction(solutions, chromosome);

				//selection
				solutions = selectionTournament(solutions, chromosome);

				//crossover
				solutions = crossoverOnePiont(solutions, chromosome);

				//mutation
				solutions = mutation(solutions, chromosome, bits, mutation_rate);
				mutation_rate *= mutation_rate_alpha;
				if (mutation_rate <= mutation_rate_min)
					mutation_rate_alpha = 1;

				//show
				for (int i = 0; i < chromosome; i++) {
					cout << solutions[i].to_string() << "\t" << solutions[i].np << endl;
					
				}
				cout << endl;


			}
			solutions = FitnessFunction(solutions, chromosome);

			//show
			for (int i = 0; i < chromosome; i++) {
				cout << solutions[i].to_string() << "\t" << solutions[i].np << endl;

			}
			cout << endl;
			cout << "max = " << max_np << endl;
		}

	}
private :
	void mesg(int _r, int _i, int _b, string _n, int _c) {
		cout << "HI, here is " << _n << " algo." << endl;
		cout << "We have : " << endl;
		cout << "\t" << _b << " bits" << endl;
		cout << "\t" << _i << " iterations" << endl;
		cout << "\t" << _r << " runs" << endl;
		return;
	}

	MyBitSet initial(MyBitSet sol, int bits) {
		sol.reset();

		for (int i = 0; i < bits; i++) {
			if (rand() % 2)
				sol.flip(i);
		}
		
		sol.np = FitnessFunction(sol.bit_map);
		return sol;
	}

	int FitnessFunction(vector<bool> bit_map) {
		int c = 0;
		int bit_size = bit_map.size();
		for (int i = 0; i < bit_size; i++) {
			if (bit_map[i])
				c++;
		}
		return c;
	}

	MyBitSet* FitnessFunction(MyBitSet* sol, int chr) {
		int c = 0;
		int bit_size = sol[0].size();
		for (int j = 0; j < chr; j++) {
			c = 0;
			for (int i = 0; i < bit_size; i++) {
				if (sol[j].bit_map[i])
					c++;
			}
			sol[j].np = c;
			if (sol[j].np > max_np)
				max_np = sol[j].np;
		}
		return sol;
	}

	MyBitSet* selectionTournament(MyBitSet* source, int numbers) {
		MyBitSet* target = source;
		int r1, r2;
		int max_chr = 0;
		int max_1 = 0;

		for (int i = 0; i < numbers; i++) {
			if (source[i].count() > max_1) {
				max_1 = source[i].count();
				max_chr = i;
			}

		}

		for (int i = 0; i < numbers; i+=2) {
			r1 = rand() % numbers;
			r2 = rand() % numbers;
			target[i] = source[r1].np > source[r2].np ? source[r1] : source[r2];
			target[i + 1] = source[max_chr];
		}
		return target;
	}

	MyBitSet* crossoverOnePiont(MyBitSet* parent, int chr) {
		MyBitSet* child = parent;
		int bits = parent[0].bit_map.size();
		for (int i = 0; i < chr-1; i += 2) {
			for (int j = rand() % bits; j < bits; j++) {
				child[i].bit_map[j] = parent[i + 1].bit_map[j];
				child[i + 1].bit_map[j] = parent[i].bit_map[j];
			}
		}

		return child;
	}
	MyBitSet* mutation(MyBitSet* parent, int chr,int bits, double mut_r = 1.0) {
		MyBitSet* child = parent;

		for (int i = 0; i < chr; i++) {/*
			for (int j = 0; j < bits; j++) {
				if (((double)rand())/RAND_MAX <= (1/bits)*10)
					child[i].flip(j);
			}*/
			if((double)rand()/RAND_MAX >= mut_r)
				child[i].flip(rand()%bits);	
		}

		return child;
	}
};