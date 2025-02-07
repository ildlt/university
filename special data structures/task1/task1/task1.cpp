#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

void fill_bag() {

}

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
long long search(vector<vector<long long>>& arr, long long l, long long r, long long x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid][0] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid][0] > x)
            return search(arr, l, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return search(arr, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return -1;
}

int main()
{
    long long n;
    long long maxw;
    long long w_i;
    long long v_i;

    ifstream in("C:/Users/Alexis/test.txt");

    in >> n >> maxw;

    vector<vector<long long>> bag(n);
    //vector<vector<long long>> bag(maxw);
    vector<long long> weights(n);
    vector<long long> values(n);
    vector<vector<long long>> subsets;
    vector<vector<long long>> subsets_b;
    vector<vector<long long>> first_array;
    vector<vector<long long>> second_array;
    vector<vector<long long>> first_array_mod;
    vector<vector<long long>> second_array_mod;

    for (long long i = 0; i < n; i++) {
        in >> w_i >> v_i;
        // add items to the corresponding arrays

        weights[i] = w_i;
        values[i] = v_i;
    }

    long long first_half = n / 2;
    long long second_half = n - first_half;

    //----------- Working with array A
    for (long long i = 0; i < (long long)pow(2, first_half); i++) {
        long long t = i;
        vector<long long> v;
        long long total_value = 0;
        long long total_weight = 0;
        vector<long long> temp;
        long long counter = 0;
        for (long long j = 0; j < first_half; j++) {
            if (t & 1) {
                v.push_back(j + 1);
                total_value += values[j];
                total_weight += weights[j];
                counter = i;
            }
            t >>= 1;
        }

        subsets.push_back(v);
        temp.push_back(total_weight);
        temp.push_back(total_value);
        temp.push_back(counter);
        first_array.push_back(temp);
    }

    sort(first_array.begin(), first_array.end());
    //----------- End

    //----------- Working with array B
    for (long long i = 0; i < (long long)pow(2, second_half); i++) {
        long long t = i;
        vector<long long> v;
        long long total_value = 0;
        long long total_weight = 0;
        vector<long long> temp;
        long long counter = 0;
        for (long long j = 0; j < second_half; j++) {
            //for (long long j = second_half; j < n; j++) {
            if (t & 1) {
                v.push_back(j + first_half + 1);
                total_value += values[j + first_half];
                total_weight += weights[j + first_half];
                //v.push_back(j + 1);
                //total_value += values[j];
                //total_weight += weights[j];
                counter = i;
            }
            t >>= 1;
        }

        subsets_b.push_back(v);
        temp.push_back(total_weight);
        temp.push_back(total_value);
        temp.push_back(counter);
        second_array.push_back(temp);
    }

    sort(second_array.begin(), second_array.end());
    //----------- End

    long long current_max_a = maxw;
    long long current_max_b = maxw;

    long long prev = 0;

    for (long long i = 1; i < first_array.size(); i++) {
        /*if (first_array[i][0] <= maxw) {
            if (first_array[i][1] > first_array[prev][1]) {
                first_array_mod.push_back(first_array[prev]);
                prev = i;
            }
        }*/
        if (first_array[i][0] > maxw) {
            if (first_array[prev][0] <= maxw) {
                first_array_mod.push_back(first_array[prev]);
            }
            else {
                break;
            }
            //break;
        }

        if (first_array[i][1] > first_array[prev][1]) {
            first_array_mod.push_back(first_array[prev]);
            prev = i;
        }

        if (i == first_array.size() - 1) {
            first_array_mod.push_back(first_array[prev]);
        }
    }

    for (long long i = 0; i < second_array.size(); i++) {
        if (second_array[i][0] <= maxw) {
            second_array_mod.push_back(second_array[i]);
        }
    }

    //for (long long i = 1; i < second_array.size(); i++) {
    //    /*if (second_array[i][0] <= maxw) {
    //        if (second_array[i][1] > second_array[prev][1]) {
    //            second_array_mod.push_back(second_array[prev]);
    //            prev = i;
    //        }
    //    }*/
    //    if (second_array[i][0] > maxw) {
    //        if (second_array[prev][0] <= maxw) {
    //            second_array_mod.push_back(second_array[prev]);
    //        }
    //        else {
    //            break;
    //        }
    //        //break;
    //    }

    //    if (second_array[i][1] > second_array[prev][1]) {
    //        second_array_mod.push_back(second_array[prev]);
    //        prev = i;
    //    }

    //    if (i == second_array.size() - 1) {
    //        second_array_mod.push_back(second_array[prev]);
    //    }
    //}

    //----------- Combining values
    long long t_a = -1;
    long long t_b = -1;
    long long max_value = 0;

    //for (long long i = 0; i < first_array_mod.size(); i++) {
    //    long long total_value = 0;
    //    long long total_weight = 0;

    //    vector<long long> temp;
    //    // binary_search(second_array[i][0], second_array.size() - 1, maxw);

    //    for (long long j = 0; j < second_array_mod.size(); j++) {
    //        total_weight = first_array_mod[i][0] + second_array_mod[j][0];
    //        total_value = first_array_mod[i][1] + second_array_mod[j][1];
    //        if (total_weight <= maxw && total_value > max_value) {
    //            max_value = total_value;
    //            t_a = first_array_mod[i][2];
    //            t_b = second_array_mod[j][2];
    //        }
    //    }
    //    //cout << max_value << ", " << t_a << ", " << t_b << "\n";
    //}

    if (first_array_mod.size() > 0 && second_array_mod.size() > 0) {
        for (long long i = 0; i < first_array_mod.size(); i++) {
            long long total_value = 0;
            long long total_weight = 0;

            vector<long long> temp;
            // binary_search(second_array[i][0], second_array.size() - 1, maxw);

            for (long long j = 0; j < second_array_mod.size(); j++) {
                total_weight = first_array_mod[i][0] + second_array_mod[j][0];
                total_value = first_array_mod[i][1] + second_array_mod[j][1];
                if (total_weight <= maxw && total_value > max_value) {
                    max_value = total_value;
                    t_a = first_array_mod[i][2];
                    t_b = second_array_mod[j][2];
                }
            }
            //cout << max_value << ", " << t_a << ", " << t_b << "\n";
        }
    }
    else if (first_array_mod.size() > 0 && second_array_mod.size() == 0) {
        long long total_value = 0;
        long long total_weight = 0;

        for (long long i = 0; i < first_array_mod.size(); i++) {
            total_weight = first_array_mod[i][0];
            total_value = first_array_mod[i][1];
            if (total_weight <= maxw && total_value > max_value) {
                max_value = total_value;
                t_a = first_array_mod[i][2];
                t_b = 0;
            }
        }
    }
    else if (first_array_mod.size() == 0 && second_array_mod.size() > 0) {
        long long total_value = 0;
        long long total_weight = 0;

        for (long long j = 0; j < second_array_mod.size(); j++) {
            total_weight = second_array_mod[j][0];
            total_value = second_array_mod[j][1];
            if (total_weight <= maxw && total_value > max_value) {
                max_value = total_value;
                t_a = 0;
                t_b = second_array_mod[j][2];
            }
        }
    }
    else {
        t_a = 0;
        t_b = 0;
    }

    //for (long long i = 0; i < first_array.size(); i++) {
    //    long long total_value = 0;
    //    long long total_weight = 0;
    //    
    //    vector<long long> temp;
    //    // binary_search(second_array[i][0], second_array.size() - 1, maxw);

    //    for (long long j = 0; j < second_array.size(); j++) {
    //        total_value = first_array[i][0] + second_array[j][0];
    //        total_weight = first_array[i][1] + second_array[j][1];
    //        if (total_weight <= maxw && total_value > max_value) {
    //            max_value = total_value;
    //            t_a = first_array[i][2];
    //            t_b = second_array[j][2];
    //        }
    //    }
    //    //cout << max_value << ", " << t_a << ", " << t_b << "\n";
    //}
    //----------- End

    //cout << max_value << "\n";

    long long answer = 0;

    if (t_a > 0) {
        answer += subsets[t_a].size();
    }
    if (t_b > 0) {
        answer += subsets_b[t_b].size();
    }
    //cout << subsets[t_a].size() + subsets_b[t_b].size() << "\n";

    cout << answer << "\n";

    if (answer != 0) {
        for (const long long& value : subsets[t_a]) {
            cout << value << " ";
        }
        for (const long long& value : subsets_b[t_b]) {
            cout << value << " ";
        }
    }
    //for (const long long& value : subsets[t_a]) {
    //    cout << value << " ";
    //}
    ////cout << "\n";
    //for (const long long& value : subsets_b[t_b]) {
    //    cout << value << " ";
    //}

    // print all of the subsets (optional)
    cout << "subsets:\n";
    for (const vector<long long>& subset : subsets) {
        for (const long long& value : subset)
            cout << value << ", ";
        cout << "\n";
    }

    cout << "subsets B:\n";
    for (const vector<long long>& subset : subsets_b) {
        for (const long long& value : subset)
            cout << value << ", ";
        cout << "\n";
    }

    cout << "first_array:\n";
    for (const vector<long long>& value : first_array_mod)
        cout << value[0] << "," << value[1] << "," << value[2] << " " << "\n";
    // note: an empty line will be printed at the top,
    // indicating an empty subset

    cout << "second_array:\n";
    for (const vector<long long>& value : second_array_mod)
        cout << value[0] << "," << value[1] << "," << value[2] << " " << "\n";
}