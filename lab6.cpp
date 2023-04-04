class BHeap {
private:
	int* a;
	int N;

	void heapify(int n, int i) {
		int parent = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < n && a[left] > a[parent])
			parent = left;
		if (right < n && a[right] > a[parent])
			parent = right;
		if (parent != i) {
			swap(a[i], a[parent]);
			heapify(n, parent);
		}
	}
public:
	BHeap(int arr[], int n) {
		N = n;
		a = new int[n];
		for (int i = 0; i < n; i++) a[i] = arr[i];
	}
	void heapSort() {
		//for (int i = 0; i < N; i++) a[i] *= -1;
		for (int i = N / 2 - 1; i >= 0; i--) heapify(N, i);
		for (int i = N - 1; i >= 0; i--) {
			swap(a[0], a[i]);
			heapify(i, 0);
		}
		//for (int i = 0; i < N; i++) a[i] *= -1;
	}
	void display() { for (int i = 0; i < N; i++) cout << a[i] << ' '; }
};

int main(int argc, char const* argv[])
{
	//int arr[] = { 4, 10, 3, 5, 1 };
	//int arr[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4};
	//int arr[] = { 12, 11, 13, 5, 6, 7 };
	int arr[] = { 29, 24, 13, 22, 17, 11, 8, 19, 10, 5, 3 };
	BHeap h1(arr, sizeof(arr)/sizeof(*arr));
	h1.heapSort();
	h1.display();

	return 0;
}
