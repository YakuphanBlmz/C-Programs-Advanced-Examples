#include <stdio.h>
#include <stdlib.h>
long long calculateWeightedSum(int*** data, int numGroups, int* sensorsPerGroup, int** readingsPerSensorCount) {
    long long totalSum = 0;
    int g, s, r;
    for (g = 0; g < numGroups; g++) {
        for (s = 0; s < sensorsPerGroup[g]; s++) {
            for (r = 0; r < readingsPerSensorCount[g][s]; r++) {
                long long currentWeight = (long long)g + s + r + 1;
                totalSum += (long long)data[g][s][r] * currentWeight;
            }
        }
    }
    return totalSum;
}
int main() {
    int numGroups = 3;
    int* sensorsPerGroup = (int*)malloc(numGroups * sizeof(int));
    if (sensorsPerGroup == NULL) return 1;
    sensorsPerGroup[0] = 2;
    sensorsPerGroup[1] = 3;
    sensorsPerGroup[2] = 1;
    int** readingsPerSensorCount = (int**)malloc(numGroups * sizeof(int*));
    if (readingsPerSensorCount == NULL) {
        free(sensorsPerGroup);
        return 1;
    }
    int g, s, r;
    for (g = 0; g < numGroups; g++) {
        readingsPerSensorCount[g] = (int*)malloc(sensorsPerGroup[g] * sizeof(int));
        if (readingsPerSensorCount[g] == NULL) {
            for (int i = 0; i < g; i++) free(readingsPerSensorCount[i]);
            free(readingsPerSensorCount);
            free(sensorsPerGroup);
            return 1;
        }
    }
    readingsPerSensorCount[0][0] = 4; readingsPerSensorCount[0][1] = 2;
    readingsPerSensorCount[1][0] = 3; readingsPerSensorCount[1][1] = 1; readingsPerSensorCount[1][2] = 2;
    readingsPerSensorCount[2][0] = 5;
    int*** sensorData = (int***)malloc(numGroups * sizeof(int**));
    if (sensorData == NULL) {
        for (g = 0; g < numGroups; g++) free(readingsPerSensorCount[g]);
        free(readingsPerSensorCount);
        free(sensorsPerGroup);
        return 1;
    }
    for (g = 0; g < numGroups; g++) {
        sensorData[g] = (int**)malloc(sensorsPerGroup[g] * sizeof(int*));
        if (sensorData[g] == NULL) {
            for (int i = 0; i < g; i++) {
                for (int j = 0; j < sensorsPerGroup[i]; j++) free(sensorData[i][j]);
                free(sensorData[i]);
            }
            free(sensorData);
            for (int i = 0; i < numGroups; i++) free(readingsPerSensorCount[i]);
            free(readingsPerSensorCount);
            free(sensorsPerGroup);
            return 1;
        }
        for (s = 0; s < sensorsPerGroup[g]; s++) {
            sensorData[g][s] = (int*)malloc(readingsPerSensorCount[g][s] * sizeof(int));
            if (sensorData[g][s] == NULL) {
                for (int i = 0; i <= g; i++) {
                    for (int j = 0; j < (i == g ? s : sensorsPerGroup[i]); j++) free(sensorData[i][j]);
                    if (i < g) free(sensorData[i]);
                }
                free(sensorData[g]);
                free(sensorData);
                for (int i = 0; i < numGroups; i++) free(readingsPerSensorCount[i]);
                free(readingsPerSensorCount);
                free(sensorsPerGroup);
                return 1;
            }
            for (r = 0; r < readingsPerSensorCount[g][s]; r++) {
                sensorData[g][s][r] = (g * 100) + (s * 10) + r;
            }
        }
    }
    long long totalSum = calculateWeightedSum(sensorData, numGroups, sensorsPerGroup, readingsPerSensorCount);
    printf("Toplam Agirlikli Okuma Degeri: %lld\n", totalSum);
    for (g = 0; g < numGroups; g++) {
        for (s = 0; s < sensorsPerGroup[g]; s++) {
            free(sensorData[g][s]);
        }
        free(sensorData[g]);
    }
    free(sensorData);
    for (g = 0; g < numGroups; g++) {
        free(readingsPerSensorCount[g]);
    }
    free(readingsPerSensorCount);
    free(sensorsPerGroup);
    return 0;
}