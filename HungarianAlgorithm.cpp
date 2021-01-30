#include "HungarianAlgorithm.h"

vector<vector<int>> HungarianAlgorithm::make_matrix(int n, int val)
{
	vector<vector<int>> matrix;
	for (int i = 0; i < n; i++)
	{
		vector<int>row;
		for (int j = 0; j < n; j++)
		{
			row.push_back(val);
		}
		matrix.push_back(row);
	}
	return matrix;
}

void HungarianAlgorithm::clear_covers()
{
	for (int i = 0; i < n; i++)
	{
		row_covered[i] = false;
		col_covered[i] = false;
	}
}

vector<int> HungarianAlgorithm::find_a_zero(int i0, int j0)
{
	//find the first uncovered element with value 0
	int row = -1;
	int col = -1;
	int i = i0;
	bool done = false;
	int j;

	while (!done)
	{
		j = j0;
		while (true)
		{
			if (C[i][j] == 0 && (!row_covered[i]) && (!col_covered[j]))
			{
				row = i;
				col = j;
				done = true;
			}
			j = (j + 1) % n;
			if (j == j0)
			{
				break;
			}
		}
		i = (i + 1) % n;
		if (i == i0)
		{
			done = true;
		}
	}
	auto result = { row, col };
	return result;
}

int HungarianAlgorithm::find_star_in_row(int row)
{
	//find the first starred element in the specific row.
	//return the column index, or -1 if no starred element was found

	int col = -1;
	for (int j = 0; j < n; j++)
	{
		if (marked[row][j] == 1)
		{
			col = j;
			break;
		}
	}
	return col;
}

int HungarianAlgorithm::find_star_in_col(int col)
{
	//find the first starred element in the specified row. Returns
	// the row index, or -1 if no starred element was found.

	int row = -1;
	for (int i = 0; i < n; i++)
	{
		if (marked[i][col] == 1)
		{
			row = i;
			break;
		}
	}
	return row;
}
int HungarianAlgorithm::find_prime_in_row(int row)
{
	//find the first prime element in the specified row. Returns the column
	//index, or -1 if no starred elemnt was found.
	int col = -1;
	for (int j = 0; j < n; j++)
	{
		if (marked[row][j] == 2)
		{
			col = j;
			break;
		}
	}
	return col;
}
void HungarianAlgorithm::convert_path(int count)
{
	for (int i = 0; i < count + 1; i++)
	{
		if (marked[path[i][0]][path[i][1]] == 1)
		{
			marked[path[i][0]][path[i][1]] = 0;
		}
		else
		{
			marked[path[i][0]][path[i][1]] = 1;
		}
	}
}
void HungarianAlgorithm::erase_primes()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (marked[i][j] == 2)
			{
				marked[i][j] = 0;
			}
		}
	}
}
int HungarianAlgorithm::find_smallest()
{
	int minval = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((!row_covered[i]) && (!col_covered[j]))
			{
				if (minval > C[i][j])
				{
					minval = C[i][j];
				}
			}
		}
	}
	return minval;
}

//steps
void HungarianAlgorithm::step1()
{
	vector<int> vals;
	for (int i = 0; i < n; i++)
	{
		//find min value for current row
		vals = (C[i]);
		int minval = vals[0];
		for (int j = 1; j < vals.size(); j++)
		{
			if (vals[j] < minval)
			{
				minval = vals[j];
			}
		}
		//subtract that value from each value in current row
		for (int j = 0; j < n; j++)
		{
			C[i][j] -= minval;
		}

	}
	step2();

}

void HungarianAlgorithm::step2()
{
	//fina a zero in the resulting matrix. If there's no starred zero it its row or column,
	//star Z. Repeat for each element in the matrix. 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((C[i][j] == 0) && (!col_covered[j]) && (!row_covered[i]))
			{
				marked[i][j] = 1;
				col_covered[j] = true;
				row_covered[i] = true;
				break;
			}
		}
	}
	clear_covers();
	step3();
}
void HungarianAlgorithm::step3()
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (marked[i][j] == 1 && (!col_covered[j]))
			{
				col_covered[j] = true;
				count++;
			}
		}
	}
	if (count >= n)
	{
		//DONE
	}
	else
	{
		step4();
	}
}

void HungarianAlgorithm::step4()
{
	int step = 0;
	bool done = false;
	int row = 0;
	int col = 0;
	int star_col = -1;

	while (!done)
	{
		auto result = find_a_zero(row, col);
		row = result[0];
		col = result[1];
		if (row < 0)
		{
			done = true;
			step6();
		}
		else
		{
			marked[row][col] = 2;
			star_col = find_star_in_row(row);
			if (star_col >= 0)
			{
				col = star_col;
				row_covered[row] = true;
				col_covered[col] = false;
			}
			else
			{
				done = true;
				Z0_r = row;
				Z0_c = col;

				step5();
			}
		}
	}
}

void HungarianAlgorithm::step5()
{
	int count = 0;
	path[count][0] = Z0_r;
	path[count][1] = Z0_c;
	bool done = false;

	int row;
	int col;
	while (!done)
	{
		row = find_star_in_col(path[count][1]);
		if (row >= 0)
		{
			count++;
			path[count][0] = row;
			path[count][1] = path[count - 1][1];
		}
		else
		{
			done = true;
		}

		if (!done)
		{
			col = find_prime_in_row(path[count][0]);
			count++;
			path[count][0] = path[count - 1][0];
			path[count][1] = col;
		}
	}
	convert_path(count);
	clear_covers();
	erase_primes();

	step3();
}

void HungarianAlgorithm::step6()
{
	int minval = find_smallest();
	int events = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (row_covered[i])
			{
				C[i][j] += minval;
				events++;
			}
			if (!col_covered[j])
			{
				C[i][j] -= minval;
				events++;
			}
			if (row_covered[i] && (!col_covered[j]))
			{
				events -= 2;
			}
		}
	}
	if (events == 0)
	{
		std::cout << "Matrix cannot be solved!\n";
	}
	step4();
}

vector<vector<int>> HungarianAlgorithm::compute(vector<vector<int>>& cost_matrix)
{
	C = cost_matrix;
	n = C.size();
	original_length = cost_matrix.size();
	original_width = cost_matrix[0].size();
	Z0_r = 0;
	Z0_c = 0;
	path = make_matrix(n * 2, 0);
	marked = make_matrix(n, 0);

	for (int i = 0; i < n; i++)
	{
		row_covered.push_back(false);
		col_covered.push_back(false);
	}

	step1();

	vector<vector<int>> results;
	for (int i = 0; i < original_length; i++)
	{
		for (int j = 0; j < original_width; j++)
		{
			if (marked[i][j] == 1)
			{
				results.push_back({ i,j });
			}
		}
	}
	return results;
}