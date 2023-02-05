unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
    unsigned long left, right;
    left = 0;
    right = nel-1;
    if (compare(0) == 0) {
        right = 0;
    } else {
        while (right - left > 1) {
            if (compare((right + left) / 2) > 0) {
                right = (right + left) / 2;
            } else if (compare((right + left) / 2) < 0) {
                left = (right + left) / 2;
            } else {
                right = (right + left) / 2;
                break;
            }
        }
    }
    if (compare(right) != 0) {
        right = nel;
    }
    return right;
}
