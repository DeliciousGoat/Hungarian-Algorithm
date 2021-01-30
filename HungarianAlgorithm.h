#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;

class HungarianAlgorithm
{
private:
	vector<vector<int>> C;
	vector<bool> row_covered;
	vector<bool> col_covered;
	int original_length = 0;
	int original_width = 0;
	int n = 0;
	int Z0_r = 0;
	int Z0_c = 0;
	vector<vector<int>> marked;
	vector<vector<int>> path;

	//helper functions
	vector<vector<int>> make_matrix(int n, int val);
	void clear_covers();
	vector<int> find_a_zero(int i0, int j0);
	int find_star_in_row(int row);
	int  find_star_in_col(int col);
	int find_prime_in_row(int row);
	void convert_path(int count);
	void erase_primes();
	int find_smallest();

	//steps
	void step1();
	void step2();
	void step3();
	void step4();
	void step5();
	void step6();

public:
	HungarianAlgorithm () = default;
	vector<vector<int>> compute(vector<vector<int>>& cost_matrix);
};