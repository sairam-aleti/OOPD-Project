/* Utility.h
 * Small generic utilities for the simulator.
 * Demonstrates use of templates as required by assignment.
 */
#ifndef UTILITY_H
#define UTILITY_H

template <typename T>
T clampValue(T value, T minVal, T maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

#endif // UTILITY_H
