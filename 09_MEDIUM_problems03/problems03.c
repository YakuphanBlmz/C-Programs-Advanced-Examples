#include <stdio.h>
#include <math.h>

#define SIZE 10

double calculateMean(int arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

double calculateStdDev(int arr[], int size, double mean) {
    double sumOfSquares = 0.0;
    for (int i = 0; i < size; i++) {
        sumOfSquares += pow(arr[i] - mean, 2);
    }
    return sqrt(sumOfSquares / (size - 1));
}

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int getTopBottomSum(int sortedArr[], int size) {
    int sum = 0;
    sum += sortedArr[0] + sortedArr[1] + sortedArr[2];
    sum += sortedArr[size - 1] + sortedArr[size - 2] + sortedArr[size - 3];
    return sum;
}

int sumDigits(int number) {
    int sum = 0;
    if (number < 0) {
        number = -number;
    }
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int main() {
    int grades[SIZE] = {85, 92, 78, 65, 95, 88, 72, 90, 68, 81};
    int sortedGrades[SIZE];
    
    for(int i = 0; i < SIZE; i++) {
        sortedGrades[i] = grades[i];
    }

    double mean = calculateMean(grades, SIZE);
    printf("Aritmetik Ortalama: %.2f\n", mean);

    double stdDev = calculateStdDev(grades, SIZE, mean);
    printf("Standart Sapma: %.2f\n", stdDev);

    int max = findMax(grades, SIZE);
    printf("Maksimum Eleman: %d\n", max);

    int min = findMin(grades, SIZE);
    printf("Minimum Eleman: %d\n", min);

    sortArray(sortedGrades, SIZE);
    
    int topBottomSum = getTopBottomSum(sortedGrades, SIZE);
    printf("En Yuksek 3 ve En Dusuk 3 Toplami: %d\n", topBottomSum);

    int digitsSum = sumDigits(topBottomSum);
    printf("Bu Toplamin Basamaklari Toplami: %d\n", digitsSum);

    return 0;
}