#ifndef INTERPOLATION_H
#define INTERPOLATION_H

template <class T>
T linearInterpolation(T f1, T f2, double k) {
    return T((double(f2) - double(f1)) * k + f1);
}

#endif // INTERPOLATION_H
