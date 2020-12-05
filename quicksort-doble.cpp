// #include "quicksort.cpp"
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
}; 

int partition (int arr[], int low, int high,int aux[]) 
{ 
	int pivot = arr[high];
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++) 
	{ 
		if (arr[j] < pivot) 
		{ 
			i++;  
			swap(&arr[i], &arr[j]);
			swap(&aux[i], &aux[j]); 

		} 
	} 
	swap(&arr[i + 1], &arr[high]);
	swap(&aux[i+1], &aux[high]); 

	return (i + 1); 
};

void quickSort(int arr[], int low, int high,int aux[]) 
{ 
	if (low < high) 
	{ 
		int pi = partition(arr, low, high,aux); 
		quickSort(arr, low, pi - 1,aux); 
		quickSort(arr, pi + 1, high,aux); 
	} 
};
