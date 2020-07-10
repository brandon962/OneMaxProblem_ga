#pragma once
#include <string>
#include "algoclass.h"
#include "mybitset.h"

class Ga : public AlgoClass {
private :


public :
	Ga() {

	}

	void run(int _r, int _e, int _b, int _c) {
		//declare variables
		int runs = _r;
		int evolution = _e;
		int bits = _b;
		int chromosome = _c;
		int* savedata = (int*)calloc(evolution, sizeof(int));
		string algoname = "ga";
		MyBitSet* solutions = (MyBitSet*)calloc(chromosome, sizeof(MyBitSet));
		for (int i = 0; i < chromosome; i++) {
			solutions[i] = MyBitSet(bits);
		}
		srand(time(NULL));

		//print the message
		mesg(runs, evolution, bits, algoname, chromosome);

		//start
		//initial & evaluation
		for (int i = 0; i < chromosome; i++) {
			solutions[i] = initial(solutions[i], bits);
		}

		for (int i = 0; i < runs; i++) {

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
		
		sol.np = evaluation(sol.bit_map);
		return sol;
	}
	int evaluation(vector<bool> bit_map) {
		int c = 0;
		int bit_size = bit_map.size();
		for (int i = 0; i < bit_size; i++) {
			if (bit_map[i])
				c++;
		}
		return c;
	}
	void transition() {

	}
};