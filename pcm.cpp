#include <bits/stdc++.h>
using namespace std;

// Method to compare which one is the more close.
// We find the closest by taking the difference
// between the target and both values. It assumes
// that val2 is greater than val1 and target lies
// between these two.
double getClosest(double val1, double val2,
                  double target)
{
    if (target - val1 >= val2 - target)
        return val2;
    else
        return val1;
}

// Returns element closest to target in arr[]
double findClosest(double arr[], int n, double target)
{
    // Corner cases
    if (target <= arr[0])
        return arr[0];
    if (target >= arr[n - 1])
        return arr[n - 1];

    // Doing binary search
    int i = 0, j = n, mid = 0;
    while (i < j) {
        mid = (i + j) / 2;

        if (arr[mid] == target)
            return arr[mid];

        /* If target is less than array element,
            then search in left */
        if (target < arr[mid]) {

            // If target is greater than previous
            // to mid, return closest of two
            if (mid > 0 && target > arr[mid - 1])
                return getClosest(arr[mid - 1],
                                  arr[mid], target);

            /* Repeat for left half */
            j = mid;
        }

            // If target is greater than mid
        else {
            if (mid < n - 1 && target < arr[mid + 1])
                return getClosest(arr[mid],
                                  arr[mid + 1], target);
            // update i
            i = mid + 1;
        }
    }

    // Only single element left after search
    return arr[mid];
}


vector<double> createZones(double maxAmp, double minAmp, int n, double delta) {
    vector<double> tempZone;
    tempZone.push_back(minAmp);

    while(minAmp != maxAmp) {
        minAmp += delta;
        tempZone.push_back(minAmp);
    }

    return tempZone;
}

vector<double> getNorPAMVal(vector<double> amps, double delta) {
    vector<double> tempNorPAMVal;
    for(auto amp: amps) {
        double newPAMVal = amp / delta;
        tempNorPAMVal.push_back(newPAMVal);
    }
    return tempNorPAMVal;
}

vector<double> filterZones(double zones[], double nearestZone1, int n) {
    vector<double> newZones;
    for(int i=0; i<n; i++) {
        if(zones[i] != nearestZone1) {
            newZones.push_back(zones[i]);
        }
    }

    return newZones;
}

vector<double> getQuantizationVal(vector<double> amps, double zones[], int n){
    vector<double> quantizationVals;
    for(auto amp: amps) {
        double nearestZone1 = findClosest(zones, n, amp);

        int count = 0;
        double newZones[n];
        vector<double> newZonesVector = filterZones(zones, nearestZone1, n);
        for(auto eachZone: newZonesVector) {
            newZones[count] = eachZone;
            count++;
        }

        double nearestZone2 = findClosest(newZones, n-1, amp);

        double quantizationVal =  (nearestZone1+nearestZone2) / 2;

        quantizationVals.push_back(quantizationVal);
    }

    return quantizationVals;
}

vector<double> getNorQuantizationVal(vector<double> quantizationVals, double delta) {
    vector<double> newQuantizationVals;
    for(auto quantizationVal: quantizationVals) {
        double newVal = quantizationVal / delta;
        newQuantizationVals.push_back(newVal);
    }

    return newQuantizationVals;
}

vector<double> getNormalizedErr(vector<double> norQuantizationVals, vector<double> norPAMVals) {
    vector<double> normalizedErrors;
    for(int i=0; i<norQuantizationVals.size(); i++) {
        double normalizeErr = norQuantizationVals.at(i) - norPAMVals.at(i);
        normalizedErrors.push_back(normalizeErr);
    }

    return normalizedErrors;
}

int main()
{
    int n = 9;
    double zones[100];
    double maxAmp = 20;
    double minAmp = -20;
    double delta = 5;

    // -6.1, 7.5, 16.2, 19.7, 11, -5.5, -11.3, -9.4, -6
    // -12.3, -15.9, -28.6, -39.0, 37.1, 19.7, 11, 25.5, -3.3
    vector<double> actualAmplitude {-6.1, 7.5, 16.2, 19.7, 11, -5.5, -11.3, -9.4, -6};
    vector<double> norPAMVals;
    vector<double> quantizationVal;
    vector<double> norQuantizationVal;
    vector<double> normalizedErr;

    vector<double> getZones = createZones(maxAmp, minAmp, n, delta);

    int count = 0;
    for(auto eachZone: getZones) {
        zones[count] = eachZone;
        count++;
    }

    norPAMVals = getNorPAMVal(actualAmplitude, delta);
    quantizationVal = getQuantizationVal(actualAmplitude, zones, count);
    norQuantizationVal = getNorQuantizationVal(quantizationVal, delta);
    normalizedErr = getNormalizedErr(norQuantizationVal, norPAMVals);

    cout << "normalized PAM values: ";
    for(auto pamVal: norPAMVals) {
        cout << pamVal << "  ";
    }

    cout << " \n";

    cout << "quantization values: ";
    for(auto quanVal: quantizationVal) {
        cout << quanVal << "  ";
    }

    cout << " \n";

    cout << "normalization quantized values: ";
    for(auto norQuanVal: norQuantizationVal) {
        cout << norQuanVal << "  ";
    }

    cout << " \n";

    cout << "normalized errors: ";
    for(auto err: normalizedErr) {
        cout << err << "  ";
    }

    cout << " \n";
}
