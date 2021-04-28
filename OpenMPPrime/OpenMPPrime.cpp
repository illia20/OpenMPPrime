# include <cstdlib>
# include <iostream>
# include <iomanip>

# include <omp.h>

using namespace std;

int main(int argc, char* argv[]);
void tests();
int prime_number(int n);

const int nTests = 4;
int N[nTests] = { 1000, 10000, 100000, 1000000 };

int main(int argc, char* argv[]) {

	cout << "Primes OpenMP\n";
	cout << "Number of processors available = " << omp_get_num_procs() << "\n";
	omp_set_num_threads(4);
	cout << "Number of threads = " << omp_get_max_threads() << "\n";

	tests();

	cout << "\nFinish\n";

	system("pause");

	return 0;
}

void tests() {
	int n;
	int primes;
	double wtime;

	cout << "\n";
	cout << "Count the primes from 1 to N.\n";
	cout << "\n";
	cout << "         N        P          Time\n";
	cout << "\n";

	for (int i = 0; i < nTests; i++) {
		n = N[i];
		wtime = omp_get_wtime();

		primes = prime_number(n);

		wtime = omp_get_wtime() - wtime;

		cout << "  " << setw(8) << n
			<< "  " << setw(8) << primes
			<< "  " << setw(14) << wtime << "\n";
	}
}

int prime_number(int n)
{
	int i;
	int j;
	int prime;
	int total = 0;
# pragma omp parallel \
  shared ( n ) \
  private ( i, j, prime )
# pragma omp for reduction ( + : total )
	for (i = 2; i <= n; i++)
	{
		prime = 1;
		for (j = 2; j < (i / 2 + 1); j++)
		{
			if (i % j == 0)
			{
				prime = 0;
				break;
			}
		}
		total = total + prime;
	}

	return total;
}